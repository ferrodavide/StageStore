#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>
#include <iostream>

class Node {
public:

    // Default constructor
    Node() : id(""), label("") {}

    //constructor
    Node(const std::string& id, const std::string& label) : id(id), label(label) {}
    
    //setter
    void set_property(const std::string& key, const std::string& value);

    //getters 
    std::string get_id() const;
    std::string get_label() const;
    std::unordered_map<std::string, std::string> get_properties() const;
    
private:
    std::string id;
    std::string label;
    std::unordered_map<std::string, std::string> properties; // node props. 
};

#endif 
