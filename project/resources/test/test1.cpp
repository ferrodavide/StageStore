#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <chrono>

/*
Query to find all outgoing relationships of a specific node (node_id).
*/
void find_relationships_starting_with(Database& database, const std::string& node_id) {
    // Get the pointer to the RocksDB database from the Database class
 auto start = std::chrono::high_resolution_clock::now();

    rocksdb::DB* db = database.get_db();

    // Create an iterator to scan the database
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());

    // Search pattern: keys should start with "r:" followed by the source node ID
    std::string prefix = "r:" + node_id + " ";

    for (it->Seek(prefix); it->Valid() && it->key().starts_with(prefix); it->Next()) {
        // Retrieve the key and value
        std::string key = it->key().ToString();
        std::string value = it->value().ToString();

        // Print the found relationship
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }

    if (!it->status().ok()) {
        std::cerr << "Error during database scan: " << it->status().ToString() << std::endl;
    }

    delete it; // Free the iterator memory
     auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time to filter by property: " << elapsed.count() << " seconds." << std::endl;
}

void call_test1(Database& data) {    
    find_relationships_starting_with(data, "6700");
}
