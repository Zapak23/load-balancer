#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <queue>

class WebServer {
    public:
    int server_id;
    int time_left;

    public:
        WebServer(int id);
        bool Available();
        void processRequest(Request req);
        bool update();

};


#endif