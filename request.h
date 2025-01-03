#ifndef REQUEST_H
#define REQUEST_H
#include <string>
using namespace std;

class Request {
    string IP_in;
    string IP_out;
    int length;
    bool p_process;

    Request(); //default constructor, creates a random request
};

#endif
