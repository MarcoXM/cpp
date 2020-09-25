#include <iostream>
#include <random>
#include <string>
#include "TrafficLight.h"

using namespace std;

/* Implementation of class "MessageQueue" */

 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
    unique_lock<mutex> lock{_mutex};
    _cond.wait(lock, [this]() {
        return !(_deque.empty());
    });
  
    auto msg = std::move(_deque.back());
    _deque.clear(); // clear all outdated messages
//     cout << "Message is received. Size of queue: " << _deque.size() << endl;
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    lock_guard<mutex> lock{_mutex};
    _deque.push_back(std::move(msg));
//     cout << "Message is sent" << endl;
  	_cond.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while (_trafficLightMsg.receive() != TrafficLightPhase::green) {}
}

TrafficLight::TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(&TrafficLight::cycleThroughPhases, this);
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
    chrono::time_point<chrono::system_clock> lastUpdate = chrono::system_clock::now();
    int timeout = 4+rand()%2;
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(1));
        if (chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - lastUpdate).count() > timeout) {
            _mutex.lock();
            _currentPhase = _currentPhase == TrafficLightPhase::red ? TrafficLightPhase::green : TrafficLightPhase::red;
            lastUpdate = chrono::system_clock::now();
            _trafficLightMsg.send(TrafficLight::TrafficLightPhase{_currentPhase});
            _mutex.unlock();
        }
    }
}