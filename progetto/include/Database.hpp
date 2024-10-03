#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include "Node.hpp"
#include "Relationship.hpp"
#include "Adjacency_List.hpp"

class Database{
public:
    Database();
    ~Database();

    /*void add_node(const Node& node);
    void add_relation(const Relationship& rel);
    void add_adj_list(const Adjacency& adj);

    Node get_node(const std::string& id);
    Relationship get_relation(const std::string& id_src, std::string& rel_label, std::string& id_dest);
    Adjacency get_adj_list(const std::string& id_src);*/

private:
    rocksdb::DB* db;
    rocksdb::Options options;
};

#endif