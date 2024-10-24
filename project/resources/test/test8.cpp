#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <stack>
#include <unordered_set>
#include <chrono>

/*
This query checks whether a node is reachable from another. Use an algorithm such as Depth-First Search (DFS) to traverse the graph.
*/
void is_reachable(Database& database, const std::string& start_node, const std::string& end_node) {
    auto start_time = std::chrono::high_resolution_clock::now();

    rocksdb::DB* db = database.get_db();
    std::stack<std::string> to_visit;
    std::unordered_set<std::string> visited;

    to_visit.push(start_node);

    bool found = false;
    while (!to_visit.empty() && !found) {
        std::string current_node = to_visit.top();
        to_visit.pop();

        if (current_node == end_node) {
            found = true;
            break;
        }

        if (visited.find(current_node) == visited.end()) {
            visited.insert(current_node);

            // Get the adjacency list of the current node
            std::string key = "a:" + current_node;
            std::string adj_value;
            rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &adj_value);

            if (status.ok()) {
                std::istringstream ss(adj_value);
                std::string adj_entry;
                while (std::getline(ss, adj_entry, '[')) {
                    if (adj_entry.empty()) continue;
                    size_t end_pos = adj_entry.find(';');
                    std::string neighbor_id = adj_entry.substr(0, end_pos);
                    if (visited.find(neighbor_id) == visited.end()) {
                        to_visit.push(neighbor_id);
                    }
                }
            }
        }
    }

    if (found) {
        std::cout << "Node " << end_node << " is reachable from node " << start_node << "." << std::endl;
    } else {
        std::cout << "Node " << end_node << " is NOT reachable from node " << start_node << "." << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Time to check reachability: " << elapsed.count() << " seconds." << std::endl;
}

void call_test8(Database& database, const std::string& start_node, const std::string end_node){
    is_reachable(database, start_node, end_node);
}