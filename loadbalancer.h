#ifndef LOADBALANCER_H
#define LOADBALANCER_H
using namespace std;

#include "webserver.h"
#include <vector>
#include <queue>
#include <fstream>

/**
 * @brief Load balancer class that manages web servers and distributes requests
 * 
 * This class handles the distribution of requests to multiple web servers,
 * dynamically scaling the server pool up or down based on demand.
 */
class LoadBalancer {
public:
    vector<WebServer> servers;     ///< Collection of managed web servers
    queue<Request> request_queue;  ///< Queue of pending requests

    /**
     * @brief Constructs a new Load Balancer
     * @param server_count Initial number of servers to create
     * @param process_type Type of requests to handle (true for process, false for streaming)
     * @param log_filename Path to the log file for recording operations
     */
    LoadBalancer(int server_count, bool process_type, const std::string& log_filename);
    
    /**
     * @brief Destructor that ensures proper cleanup of resources
     */
    ~LoadBalancer();

    /**
     * @brief Adds a new request to the queue
     * @param req The request to be processed
     */
    void addRequest(Request& req);

    /**
     * @brief Executes the load balancer for a specified number of cycles
     * @param cycles Number of simulation cycles to run
     */
    void run(int cycles);

    /**
     * @brief Adds a new server to the pool
     */
    void addServer();

    /**
     * @brief Removes an idle server from the pool if conditions allow
     */
    void removeServer();
  
private:
    bool process_type;         ///< Type of requests this balancer handles
    std::ofstream log_file;    ///< File stream for logging operations
};

#endif