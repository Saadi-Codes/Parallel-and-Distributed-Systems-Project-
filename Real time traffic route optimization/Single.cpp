#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include "traffic_weight.h"

using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, int src, int dest, vector<Edge>& edges) {
    vector<int> distance(V, INT_MAX);
    distance[src] = 0;

    // Start measuring execution time
    auto start = chrono::high_resolution_clock::now();

    // Relaxation loop (V-1) times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }

        // Progress bar (percentage) display
        int progress = (i + 1) * 100 / (V - 1); // Calculate the percentage progress
        cout << "\rProgress: [" << string(progress / 2, '#') << string(50 - progress / 2, ' ') << "] " << progress << "%";
        cout.flush();
    }

    // Detect negative weight cycles
    bool negative_cycle = false;
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;

        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            negative_cycle = true;
        }
    }

    // End measuring execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Display results
    cout << endl; // Move to the next line after progress bar
    if (negative_cycle) {
        cout << "Graph contains a negative weight cycle!" << endl;
    } else {
        if (distance[dest] == INT_MAX)
            cout << "No path exists from " << src << " to " << dest << endl;
        else
            cout << "Shortest path from " << src << " to " << dest << " is " << distance[dest] << endl;
    }

    // Output the execution time
    cout << "Execution Time: " << elapsed.count() << " seconds" << endl;
}

int main() {
    srand(time(0));

    // Cities: Karachi, Lahore, Islamabad
    vector<string> cities = {"Karachi", "Lahore", "Islamabad"};
    vector<int> cityNodes = {5000, 2500, 1500};

    // Choose city
    cout << "Choose a city:\n1. Karachi\n2. Lahore\n3. Islamabad\n";
    int cityChoice;
    cin >> cityChoice;

    if (cityChoice < 1 || cityChoice > 3) {
        cout << "Invalid choice!" << endl;
        return -1;
    }

    int V = cityNodes[cityChoice - 1];
    vector<Edge> edges;

    // Initialize traffic weights array
    initializeTrafficWeights(V);

    // Generate edges using the traffic weights
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            int weight = traffic_weights[i][j];
            edges.push_back({i, j, weight});
            edges.push_back({j, i, weight});
        }
    }

    int E = edges.size();

    // Pick up and drop off locations with validation
    int src, dest;

    cout << "Enter pick-up location (0 to " << V - 1 << "): ";
    while (true) {
        cin >> src;
        if (src >= 0 && src < V) break;
        cout << "Invalid pick-up location! Enter a value between 0 and " << V - 1 << ": ";
    }

    cout << "Enter drop-off location (0 to " << V - 1 << "): ";
    while (true) {
        cin >> dest;
        if (dest >= 0 && dest < V) break;
        cout << "Invalid drop-off location! Enter a value between 0 and " << V - 1 << ": ";
    }

    // Run Bellman-Ford Algorithm
    bellmanFord(V, E, src, dest, edges);

    return 0;
}
