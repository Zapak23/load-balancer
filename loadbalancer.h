#ifndef LOADBALANCER_H
#define LOADBALANCER_H
using namespace std;

#include "webserver.h"
#include <vector>
#include <queue>
#include <fstream>

class LoadBalancer {
public:
    vector<WebServer> servers;
    queue<Request> request_queue;

    LoadBalancer(int server_count, bool process_type, const std::string& log_filename);
    ~LoadBalancer();
    void addRequest(Request& req);
    void run(int cycles);
    void addServer();
    void removeServer();
  
private:
    bool process_type;
    std::ofstream log_file;
};

#endif