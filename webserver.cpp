#include "webserver.h"
#include <iostream>

using namespace std;

WebServer::WebServer(int id) 
    : server_id(id), time_left(0) {
}

bool WebServer::Available() {
    return time_left == 0;
}

void WebServer::processRequest(Request req) {
    time_left = req.length;
}

bool WebServer::update() {
    if (time_left > 0) {
        time_left--;
        if (time_left == 0) {
            return true;
        }
    }
    return false;
}