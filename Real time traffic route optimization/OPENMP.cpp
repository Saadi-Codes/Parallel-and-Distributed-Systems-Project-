#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include "traffic_weight.h"
#include <omp.h>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void parallelBellmanFord(int V, int E, int src, int dest, vector<Edge>& edges) {
    vector<int> distance(V, INT_MAX);
    distance[src] = 0;

    // Start measuring execution time
    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for schedule(static, 50) num_threads(4)
    for (int i = 0; i < V; i++) {
        distance[i] = (i == src) ? 0 : INT_MAX;
    }

    // Main relaxation loop
    for (int i = 0; i < V - 1; i++) {
        #pragma omp parallel for schedule(dynamic, 10) num_threads(4)
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                #pragma omp critical
                distance[v] = min(distance[v], distance[u] + weight);
            }
        }

        #pragma omp single
        {
            int progress = (i + 1) * 100 / (V - 1);
            cout << "\rProgress: [" << string(progress / 2, '#') << string(50 - progress / 2, ' ') << "] " << progress << "%";
            cout.flush();
        }
    }

    // Detect negative weight cycles
    bool negative_cycle = false;
    #pragma omp parallel for shared(negative_cycle) schedule(static, 10) num_threads(4)
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;

        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            #pragma omp atomic write
            negative_cycle = true;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << endl;
    if (negative_cycle) {
        cout << "Graph contains a negative weight cycle!" << endl;
    } else {
        if (distance[dest] == INT_MAX)
            cout << "No path exists from " << src << " to " << dest << endl;
        else
            cout << "Shortest path from " << src << " to " << dest << " is " << distance[dest] << endl;
    }

    cout << "Execution Time: " << elapsed.count() << " seconds" << endl;
}

int main() {
    srand(42); // Fixed seed for consistency

    vector<string> cities = {"Karachi", "Lahore", "Islamabad"};
    vector<int> cityNodes = {5000, 2500, 1500};

    cout << "Choose a city:\n1. Karachi\n2. Lahore\n3. Islamabad\n";
    int cityChoice;
    cin >> cityChoice;

    if (cityChoice < 1 || cityChoice > 3) {
        cout << "Invalid choice!" << endl;
        return -1;
    }

    int V = cityNodes[cityChoice - 1];
    vector<Edge> edges;

    // Parallelized traffic weight initialization
    #pragma omp parallel for schedule(static, 10) num_threads(4)
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            #pragma omp critical
            {
                int weight = rand() % 100 + 1;
                edges.push_back({i, j, weight});
                edges.push_back({j, i, weight});
            }
        }
    }

    int E = edges.size();

    int src, dest;

    cout << "Enter pick-up location (0 to " << V - 1 << "): ";
    cin >> src;
    cout << "Enter drop-off location (0 to " << V - 1 << "): ";
    cin >> dest;

    parallelBellmanFord(V, E, src, dest, edges);

    return 0;
}
