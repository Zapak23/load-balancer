#include "loadbalancer.h"
#include "request.h"
using namespace std;

#include <iostream>

#define GREEN_TEXT "\033[32m"
#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

int main() {
    int server_count, cycles;
    cout << "Enter the number of servers (per load balancer): ";
    cin >> server_count;
    if (server_count < 3) {
        server_count = 3;
        cout << "Minimum of 3 servers required. Setting to 3." << endl;
    }
    cout << "Enter the number of cycles to run: ";
    cin >> cycles;

    // Create two load balancers - one for processing, one for streaming
    LoadBalancer process_lb(server_count, true, "process_loadbalancer.log");
    LoadBalancer stream_lb(server_count, false, "stream_loadbalancer.log");

    int request_count;
    cout << "Enter the number of requests to generate: ";
    cin >> request_count;

    for (int i = 0; i < request_count; ++i) {
        Request req;
        process_lb.addRequest(req);
        stream_lb.addRequest(req);
    }

    // Run both load balancers
    process_lb.run(cycles);
    stream_lb.run(cycles);

    // Add status check
    if (process_lb.request_queue.empty() && stream_lb.request_queue.empty()) {
        cout << GREEN_TEXT << "All requests processed!" << RESET_TEXT << endl;
    } else {
        cout << RED_TEXT << "Some requests are not complete" << RESET_TEXT << endl;
    }

    return 0;
}