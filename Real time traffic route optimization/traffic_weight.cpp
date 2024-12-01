#include "traffic_weight.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int traffic_weights[MAX_NODES][MAX_NODES]; // Traffic weights array

// Function to initialize the traffic weights array
void initializeTrafficWeights(int V) {
    srand(time(0));  // Seed the random number generator

    // Fill the traffic weights array with random values between 1 and 100
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            int weight = rand() % 100 + 1; // Random weight between 1 and 100
            traffic_weights[i][j] = weight;
            traffic_weights[j][i] = weight; // Symmetric traffic weights
        }
    }
}
