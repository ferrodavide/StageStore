#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <chrono>

void find_adjacency_list(Database& database, const std::string& node_id) {
    // Get the RocksDB database pointer from the Database class
    auto start = std::chrono::high_resolution_clock::now();
    rocksdb::DB* db = database.get_db();

    // Create an iterator to scan the database
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());

    // Exact key of the adjacency list we want to find
    std::string prefix = "a:" + node_id;

    // Position the iterator on the desired key
    it->Seek(prefix);

    // Check if the current key is exactly what we're looking for
    if (it->Valid() && it->key().ToString() == prefix) {
        // Retrieve the key and value
        std::string key = it->key().ToString();
        std::string value = it->value().ToString();

        // Print the found adjacency list
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    } else {
        std::cout << "No adjacency list found for the node with ID " << node_id << "." << std::endl;
    }

    if (!it->status().ok()) {
        std::cerr << "Error during database scan: " << it->status().ToString() << std::endl;
    }

    delete it; // Free the iterator's memory
     auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time to filter by property: " << elapsed.count() << " seconds." << std::endl;
}

void call_test2(Database& data) {
    std::cout << "\n Node's Adjacency List with ID 6700:" << std::endl;
    find_adjacency_list(data, "6700");
}
