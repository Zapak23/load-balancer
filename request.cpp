#include "request.h"
#include <cstdlib>
using namespace std;

Request::Request() {
    p_process = (rand() % 2) == 0;
    length = rand() % 10 + 1; // length is between 1 and 10

    // Generate random IP addresses
    IP_in = std::to_string(rand() % 256) + "." + 
            std::to_string(rand() % 256) + "." + 
            std::to_string(rand() % 256) + "." + 
            std::to_string(rand() % 256);
            
    IP_out = std::to_string(rand() % 256) + "." + 
             std::to_string(rand() % 256) + "." + 
             std::to_string(rand() % 256) + "." + 
             std::to_string(rand() % 256);
}

bool Request::isProcessRequest() {
    return p_process;
}
