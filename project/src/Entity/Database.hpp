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
    }
    //destructor
    ~Database(){ delete db; } //closing the database

    void delete_db(){
        //create an iterator to iterate through all the keys
        rocksdb::Status status;
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
    void delete_node(const std::string n_key);
    void delete_relationship(const std::string r_key);
    void delete_adjacency_list(const std::string al_key);

    void add_node(const Node& node);
    void add_relation(const Relationship& rel);
    //void add_adj_list(const Adjacency_List& adj);
    void add_adj_list(std::string src,string id_d ,string label_dest, string label_rel, string prop_strings);   //prova

    void update_node(const std::string& key,const std::string& value);


    Node get_node(const std::string& id);
    Relationship get_relation(const std::string& id);
    Adjacency_List get_adj_list(const std::string& id_src);
    rocksdb::DB* get_db() {
        return db;  // Assicurati che db sia un membro della classe Database
    }

    //not implemented yet
    /*
    Relationship get_relation(const std::string& id_src, std::string& rel_label, std::string& id_dest);*/
    //Adjacency get_adj_list(const std::string& id_src);

    void print();
    void print_list();

    std::string query_get(const std::string& chiave){
        std::string valore_nodo;
        rocksdb::Status status = db->Get(rocksdb::ReadOptions(), chiave, &valore_nodo);

        return valore_nodo;
    }

private:
    rocksdb::DB* db;
    rocksdb::Options options;
    Adjacency_List list;
};

#endif