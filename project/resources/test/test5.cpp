#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <algorithm>

/*
This query implements an algorithm for finding the shortest path between two nodes, such as Breadth-First Search (BFS).
It is useful for evaluating the efficiency of the database in retrieving information across multiple levels of the graph.
*/

void find_shortest_path(Database& database, const std::string& start_node, const std::string& end_node) {
    auto start_time = std::chrono::high_resolution_clock::now();

    rocksdb::DB* db = database.get_db();
    std::queue<std::string> to_visit;
    std::unordered_map<std::string, std::string> parent_map;  // Trace the path
    std::unordered_set<std::string> visited;

    to_visit.push(start_node);
    visited.insert(start_node);
    parent_map[start_node] = "";

    bool found = false;
    while (!to_visit.empty() && !found) {
        std::string current_node = to_visit.front();
        to_visit.pop();

        // Get the adjacency list of the current node
        std::string key = "a:" + current_node;
        std::string adj_value;
        rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &adj_value);

        if (status.ok()) {
            // Parse the target IDs from the adjacency list
            std::istringstream ss(adj_value);
            std::string adj_entry;
            while (std::getline(ss, adj_entry, '[')) {
                if (adj_entry.empty()) continue;

                size_t end_pos = adj_entry.find(';');
                std::string neighbor_id = adj_entry.substr(0, end_pos);

                if (visited.find(neighbor_id) == visited.end()) {
                    to_visit.push(neighbor_id);
                    visited.insert(neighbor_id);
                    parent_map[neighbor_id] = current_node;

                    if (neighbor_id == end_node) {
                        found = true;
                        break;
                    }
                }
            }
        }
    }

    if (found) {
        std::cout << "Shortest path between " << start_node << " and " << end_node << ": ";
        std::string node = end_node;
        std::vector<std::string> path;
        while (!node.empty()) {
            path.push_back(node);
            node = parent_map[node];
        }
        std::reverse(path.begin(), path.end());
        for (const auto& step : path) {
            std::cout << step << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found between " << start_node << " and " << end_node << "." << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Time to find the shortest path: " << elapsed.count() << " seconds." << std::endl;
}

void call_test5(Database& database, const std::string& start_node, const std::string& end_node){
    find_shortest_path(database, start_node, end_node);
}