#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <chrono>

/*
Searches and returns all the nodes with id greater than n, looking for it in the 
adjacency list and which have the 'since' property equal to 2016
*/

void find_nodes_with_condition(Database& database, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    rocksdb::DB* db = database.get_db();

    // Create an iterator to scan the database
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());

    // We want to find nodes with IDs greater than 'n', so we'll seek "a:n"
    std::string prefix = "a:" + std::to_string(n);

    for (it->Seek(prefix); it->Valid(); it->Next()) {
        std::string key = it->key().ToString();

        // Check if the key belongs to the adjacency list (starts with "a:")
        if (key.rfind("a:", 0) == 0) {
            std::string node_id_str = key.substr(2); // Extract the node ID from "a:<id>"
            int node_id = std::stoi(node_id_str);

            // If the node ID is greater than 'n'
            if (node_id > n) {
                std::string value = it->value().ToString();

                // Check if the "since" property equals "2016" in the adjacency list
                if (value.find("since;2016") != std::string::npos) {
                    // Print the matching adjacency list
                    std::cout << "Node ID: " << node_id << ", Adjacency List: " << value << std::endl;
                }
            }
        }
    }

    if (!it->status().ok()) {
        std::cerr << "Error during database scan: " << it->status().ToString() << std::endl;
    }

    delete it; // Free the iterator's memory

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time to filter by property: " << elapsed.count() << " seconds." << std::endl;
}

void call_test9(Database& data, int n) {
    std::cout << "\nNodes with ID greater than " << n << " and property 'since' = 2016:" << std::endl;
    find_nodes_with_condition(data, n);
}
