#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <queue>

/**
 * @brief Represents a web server that can process requests
 * 
 * Manages individual server state and request processing capabilities.
 */
class WebServer {
    public:
        int server_id;    ///< Unique identifier for this server
        int time_left;    ///< Remaining time for current request processing

    public:
        /**
         * @brief Constructs a new web server
         * @param id Unique identifier for the server
         */
        WebServer(int id);

        /**
         * @brief Checks if the server can accept new requests
         * @return true if server is available, false if busy
         */
        bool Available();

        /**
         * @brief Assigns a new request to the server
         * @param req The request to be processed
         */
        void processRequest(Request req);

        /**
         * @brief Updates the server's state for one time step
         * @return true if server completed a request, false otherwise
         */
        bool update();
};

#endif