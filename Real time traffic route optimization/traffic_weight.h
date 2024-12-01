#ifndef TRAFFIC_WEIGHTS_H
#define TRAFFIC_WEIGHTS_H

// Maximum number of nodes for Karachi (adjust as needed)
#define MAX_NODES 10000

// Declare the traffic weight array
extern int traffic_weights[MAX_NODES][MAX_NODES];

// Function to initialize the traffic weights array
void initializeTrafficWeights(int V);

#endif // TRAFFIC_WEIGHTS_H
