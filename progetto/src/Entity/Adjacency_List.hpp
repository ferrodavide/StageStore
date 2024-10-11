#ifndef ADJLIST_HPP
#define ADJLIST_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
class Adjacency_List{
public:
    //costructors
    Adjacency_List (): id_src(), id_dest() {};
    Adjacency_List (string id_S): id_src(id_S), id_dest() {}
    
    //setters
    void set_adj_list_node(string id_src);
    void set_adj_list_relationship(string id_dest ,string label_dest, string label_rel, string prop_name, string prop_val);
    
    //getters
    std::string get_id_src() const;
    std::string get_id_dest() const;
    std::unordered_map<string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> get_adj_list() const;
    
    void print() const;
private:
    std::string id_src;
    std::string id_dest;
    std::unordered_map<string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> adj_list;
};

#endif