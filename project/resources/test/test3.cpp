#include "src/Entity/Database.hpp"
#include "src/Service/GraphServices.cpp"
#include <iostream>
#include <chrono>

/*
Scans and reads the entire contents of the database, i.e. all stored keys and values.
*/

void read_entire_graph(Database& database) {
    auto start = std::chrono::high_resolution_clock::now();
    // Retrieve the RocksDB pointer
    rocksdb::DB* db = database.get_db();
    // Iterator to traverse all keys
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        // Retrieve key and value
        std::string key = it->key().ToString();
        std::string value = it->value().ToString();
    }
    if (!it->status().ok()) {
        std::cerr << "Error during database scan: " << it->status().ToString() << std::endl;
    }
    delete it; // Free the iterator's memory

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time to read the entire graph: " << elapsed.count() << " seconds." << std::endl;
}

void call_test3(Database& data){
    read_entire_graph(data);
}
