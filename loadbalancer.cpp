#include "loadbalancer.h"
using namespace std;

#include <iostream>
#include <fstream>


LoadBalancer::LoadBalancer(int server_count, bool process_type, const std::string& log_filename) 
    : process_type(process_type) {
    log_file.open(log_filename);
    for (int i = 0; i < server_count; ++i) {
        servers.push_back(WebServer(i));
    }
}

LoadBalancer::~LoadBalancer() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void LoadBalancer::addRequest(Request& req) {
    if (req.isProcessRequest() == process_type) {
        request_queue.push(req);
    }
}

void LoadBalancer::run(int cycles) {
    log_file << (process_type ? "Process" : "Streaming") << " Load Balancer:\n";

    //output the size of the request queue
    log_file << "Request queue size: " << request_queue.size() << "\n";
    
    for (int cycle = 0; cycle < cycles; ++cycle) {
        log_file << "Cycle " << cycle << "\n";

        // Random request generation 
        if (cycle < cycles * .7){

            // 5% chance to generate new requests
            if (rand() % 100 < 5) {
                int num_requests = (rand() % 3 + 1) * 100 + 100; // Generates 100, 200, or 300
                for (int i = 0; i < num_requests; i++) {
                    Request req;
                    addRequest(req);
                }
                log_file << "*** Generated " << num_requests << " random new requests ***" << "\n";
            }
        }

        // SCALE UP
        while (request_queue.size() > servers.size() * 20) {
            addServer();
            log_file << "+++ Added new server. Total servers: " << servers.size() << " +++\n";
        }

        // SCALE DOWN
        while (request_queue.size() < servers.size() * 10 && servers.size() > 3) {
            int old_size = servers.size();
            removeServer();
            if (servers.size() == old_size) {
                break;
            }
            log_file << "--- Removed server. Total servers: " << servers.size() << " ---\n";
            
        }

        // Assign requests to available servers
        for (auto& server : servers) {
            if (server.Available() && !request_queue.empty()) {
                server.processRequest(request_queue.front());
                log_file << "Server " << server.server_id << " processing request from " << request_queue.front().IP_in
              << " to " << request_queue.front().IP_out << " (" << (request_queue.front().p_process ? "process" : "streaming") << ")\n";
                request_queue.pop();
            }
        }

        // Update server states
        for (auto& server : servers) {
            bool completed = server.update();
            if (completed) {
                log_file << "Server " << server.server_id << " completed request\n";
            }
        }
    }
    log_file << "Final Request queue size: " << request_queue.size() << "\n";

    log_file << "Total servers: " << servers.size() << "\n";
}

void LoadBalancer::addServer() {
    int new_id = servers.size();
    servers.push_back(WebServer(new_id));
}

void LoadBalancer::removeServer() {
    if (servers.size() > 3) { 
        for (int i = servers.size() - 1; i >= 0; i--) {
            if (servers[i].Available()) {
                servers.erase(servers.begin() + i);
                return;
            }
        }
    }
}