#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <unordered_map>
#include <chrono>

/*
This query finds the node with the most outgoing relationships. 
It stresses the system because it requires a complete scan of all relationships and a count.
*/

void find_node_with_most_relationships(Database& database) {
    auto start = std::chrono::high_resolution_clock::now();

    rocksdb::DB* db = database.get_db();
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    std::unordered_map<std::string, int> relationship_count;

    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::string key = it->key().ToString();
        if (key.find("r:") == 0) {
            std::string node_id = key.substr(2, key.find(':', 2) - 2);
            relationship_count[node_id]++;
        }
    }

    if (!it->status().ok()) {
        std::cerr << "Error during database scan: " << it->status().ToString() << std::endl;
    }

    delete it;

    //Find the node with the most relationships
    std::string max_node;
    int max_count = 0;
    for (const auto& pair : relationship_count) {
        if (pair.second > max_count) {
            max_count = pair.second;
            max_node = pair.first;
        }
    }

    std::cout << "Node with the largest number of relationships: " << max_node << " with " << max_count << " relations." << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time to find the node with the most relationships: " << elapsed.count() << " seconds." << std::endl;
}

void call_test7(Database& database){
    find_node_with_most_relationships(database);
}