# Real-Time Traffic Routing Optimization Using Parallel Bellman-Ford Algorithm
## Parallel-and-Distributed-Systems-Project-

This project focuses on optimizing traffic or logistics routing in real-time using the **Bellman-Ford Algorithm**, parallelized with **OpenMP**. The goal is to model the system as a graph, where nodes represent locations, and edges represent roads or paths. The Bellman-Ford algorithm will compute the shortest paths between the source node and all other nodes, and the system will be updated dynamically to handle real-time changes (e.g., road closures, accidents, or traffic flow updates).

## Features

- **Graph-Based Modeling**: Locations are modeled as nodes, and roads are modeled as edges with weights representing travel time, distance, or cost.
- **Parallelized Bellman-Ford Algorithm**: The traditional Bellman-Ford algorithm is parallelized using OpenMP to improve performance.
- **Real-Time Updates**: The system can handle dynamic changes such as road closures or traffic updates, allowing real-time re-routing.
- **C++ Implementation**: The project is implemented in C++ for performance, utilizing OpenMP for parallel processing.

## Project Structure

- `src/` - Source code of the project, including the implementation of the Bellman-Ford algorithm and the parallelization using OpenMP.
- `docs/` - Documentation and research related to the project.

## Dependencies

- **C++ Compiler** (with OpenMP support, e.g., GCC or Clang)
- **OpenMP** - Used to parallelize the Bellman-Ford algorithm for performance optimization.

## Compilation and Execution

To compile and run the project, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/real-time-traffic-routing-optimization.git
    ```

2. Navigate to the project directory:
    ```bash
    cd real-time-traffic-routing-optimization
    ```

3. Compile the project using `Makefile`:
    ```bash
    make
    ```

4. Run the program:
    ```bash
    ./traffic_routing
    ```

## Usage

1. The program takes input representing the traffic network, which is a set of hardcoded values depending on locations.
2. After running, the algorithm will calculate the shortest paths from a source node to all other nodes in the graph.
3. You can simulate real-time updates, such as road closures or accidents, and the system will adjust the routing accordingly.

## Contributing

Contributions are welcome! If you would like to improve or extend the project, feel free to fork the repository and submit a pull request.

## Acknowledgements

- The Bellman-Ford algorithm was introduced by Richard Bellman and Lester Ford in the 1950s.
- OpenMP (Open Multi-Processing) is a parallel programming model widely used to improve the performance of computationally intensive tasks.

