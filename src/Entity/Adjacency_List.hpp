#ifndef ADJLIST_HPP
#define ADJLIST_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Adjacency_List{
public:
    //costructors
    Adjacency_List (): head(nullptr), tail(nullptr) {}
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
    void set_adj_list_node(const string& id_src);
    void set_adj_list_relationship(const string& id_s, const string& id_dest, const string& label_dest, const string& label_rel, const string& prop_name, const string& prop_val);
    
    //getters
    std::vector<std::string> get_id_dest(const std::string& id_s) const;
    unordered_map<string, unordered_map<string, unordered_map<string, string>>> get_adj_list(const string& id_s) const;

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