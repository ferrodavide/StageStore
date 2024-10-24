#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <unordered_map>
#include <chrono>

/*
This query counts the total number of nodes for each type (for example, :Person, :Company, etc.). 
It is used to verify the system's ability to scan the entire graph and perform aggregations.
*/

void count_nodes_by_type(Database& database) {
    auto start = std::chrono::high_resolution_clock::now();

    rocksdb::DB* db = database.get_db();
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    std::unordered_map<std::string, int> type_count;

    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::string key = it->key().ToString();
        if (key.find("n:") == 0) {
            std::string value = it->value().ToString();
            size_t type_start = value.find(':');
            size_t type_end = value.find(';', type_start);
            if (type_start != std::string::npos && type_end != std::string::npos) {
                std::string node_type = value.substr(type_start + 1, type_end - type_start - 1);
                type_count[node_type]++;
            }
        }
    }

    if (!it->status().ok()) {
        std::cerr << "Error during database scan: " << it->status().ToString() << std::endl;
    }

    delete it;

    // Print the results
    for (const auto& pair : type_count) {
        std::cout << "Node type: " << pair.first << ", count: " << pair.second << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time to count nodes by type: " << elapsed.count() << " seconds." << std::endl;
}

void call_test6(Database& database){
    count_nodes_by_type(database);
}