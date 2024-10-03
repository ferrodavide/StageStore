#include "Database.hpp"

Database::Database(){
    //opening the database
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
    if (!status.ok()) {
        std::cerr << "Error opening database: " << status.ToString() << std::endl;
    }
}

Database::~Database(){ delete db; } //closing the database

void Database::add_node(const Node& node){
    //check if the node already exists
    if(nodes.find(node.get_id() != nodes.end())){
        std::cerr<<"Node with ID "<<node.get_id()<<" already exists."<<std::endl;
        return;
    }

    nodes[node.get_id()] = node; //add the node to the unordered map

    //save the node into RocksDB
    std::string key = node.get_id();    
    std::string value = node.get_label();

    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
    if(!status.ok()){
        std::cerr<<"Error saving node to database: "<<status.toString()<<std::endl;
    }else{
        std::cout<<"Node with ID"<<key<<" added succesfully."<<std::endl;
    }
}



    