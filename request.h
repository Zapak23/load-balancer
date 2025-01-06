#ifndef REQUEST_H
#define REQUEST_H
#include <string>
using namespace std;

/**
 * @brief Represents a web request to be processed by the server
 * 
 * Contains information about the request including source and destination IPs,
 * processing time, and request type.
 */
class Request {
    public:
        /**
         * @brief Checks if this is a processing request
         * @return true if processing request, false if streaming
         */
        bool isProcessRequest();  

        string IP_in;     ///< Source IP address
        string IP_out;    ///< Destination IP address
        int length;       ///< Processing time required
        bool p_process;   ///< Request type flag (true for process, false for streaming)

        /**
         * @brief Default constructor that creates a random request
         */
        Request();
};

#endif
