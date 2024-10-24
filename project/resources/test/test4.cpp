#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <chrono>

/*
Finds all nodes that have a specific property with a certain value in the database.
*/

void filter_nodes_by_property(Database& database, const std::string& property_key, const std::string& property_value) {
    auto start = std::chrono::high_resolution_clock::now();
    
    rocksdb::DB* db = database.get_db();
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    
    // Iterate over all nodes to find those with the specified property
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::string key = it->key().ToString();
        
        // If the key corresponds to a node (assuming it starts with "n:")
        if (key.find("n:") == 0) {
            std::string value = it->value().ToString();
            
            // Check if the value contains the required property
            if (value.find(property_key + " = " + property_value) != std::string::npos) {
                //std::cout << "Node found - Key: " << key << ", Value: " << value << std::endl;
                std::cout << key << std::endl;
            }
        }
    }
    
    if (!it->status().ok()) {
        std::cerr << "Error during database scan: " << it->status().ToString() << std::endl;
    }

    delete it;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time to filter by property: " << elapsed.count() << " seconds." << std::endl;
}

void call_test4(Database& data, const std::string& property_key, const std::string& property_value){
    filter_nodes_by_property(data, property_key, property_value);
}
