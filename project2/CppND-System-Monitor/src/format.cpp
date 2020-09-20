#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function


/* Get the elapsed time of the system in HH:MM:SS format */
string Format::ElapsedTime(long seconds) { 
    long hour{};
    long mins{};
    std::string elapsed_time{};
    std::ostringstream osstime;

    hour = seconds/3600;

    seconds = seconds%3600;
    mins = seconds/60;

    seconds = seconds%60;

    osstime << std::setw(2) << std::setfill('0') << hour << ":" 
            << std::setw(2) << std::setfill('0') << mins << ":" 
            << std::setw(2) << std::setfill('0') << seconds;

    /* Convert it into string */
    elapsed_time = osstime.str();   
    
    
    return elapsed_time; 
}