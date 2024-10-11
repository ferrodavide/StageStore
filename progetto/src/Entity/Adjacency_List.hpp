#ifndef ADJLIST_HPP
#define ADJLIST_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class Adjacency_List{
public:
    //costructors
    Adjacency_List (){
        head = nullptr;
        tail = nullptr;
    };
    Adjacency_List (string id_S){
        head = nullptr;
        tail = nullptr;
    }
    ~Adjacency_List(){
        adj_p current = head;
        while (current) {
            adj_p next = current->next; 
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    //setters
    void set_adj_list_node(string id_src);
    void set_adj_list_relationship(std::string id_s, std::string id_dest , std::string label_dest, std::string label_rel, std::string prop_name, std::string prop_val);
    
    //getters
    std::vector<std::string> get_id_dest(const std::string& id_s) const;
    std::unordered_map<string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> get_adj_list(const std::string& id_s) const;

    void append(const std::string& id_s);
    void print() const;
private:
    struct adj{
        std::string id_src;
        std::vector<std::string> id_dest;
        std::unordered_map<string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> adj_list;
        adj* next;
        adj* prev;

        adj(std::string id) : id_src(id), next(nullptr), prev(nullptr) {}
    };
    typedef adj* adj_p;
    adj_p head;
    adj_p tail;
};

#endif