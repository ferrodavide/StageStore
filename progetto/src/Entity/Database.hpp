#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <unordered_map>
#include "Adjacency_List.hpp" 
#include "Node.hpp"
#include "Relationship.hpp" 

class Database{
public:
    //constructor
    Database(){
    //opening the database
        options.create_if_missing = true;
        rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
        if (!status.ok()) {
            std::cerr << "Error opening database: " << status.ToString() << std::endl;
        }
        //create an iterator to iterate through all the keys
        rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            std::string key = it->key().ToString();
            //delete the key
            status = db->Delete(rocksdb::WriteOptions(), key);
            if (!status.ok()) {
                std::cerr << "Errore durante la cancellazione di " << key << ": " << status.ToString() << std::endl;
            }
        }
        delete it;
    }
    //destructor
    ~Database(){ delete db; } //closing the database

    void delete_node(const std::string n_key);
    void delete_relationship(const std::string r_key);
    void delete_adjacency_list(const std::string al_key);

    void add_node(const Node& node);
    void add_relation(const Relationship& rel);
    //void add_adj_list(const Adjacency_List& adj);
    void add_adj_list(std::string src,string id_dest ,string label_dest, string label_rel, string prop_name, string prop_val);   //prova

    void update_node(const std::string& key,const std::string& value);

    //not implemented yet
    /*Node get_node(const std::string& id);
    Relationship get_relation(const std::string& id_src, std::string& rel_label, std::string& id_dest);*/
    //Adjacency get_adj_list(const std::string& id_src);

    void print();
    void print_list();
private:
    rocksdb::DB* db;
    rocksdb::Options options;
    Adjacency_List list;
};

#endif