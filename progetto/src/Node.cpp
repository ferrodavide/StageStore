#include "Node.hpp"
#include <iostream>
#include <vector>

Node::Node() : id(""), label("") {}

// Costruttore
Node::Node(const std::string& id, const std::string& label)
    : id(id), label(label) {}

// Imposta una proprietà del nodo
void Node::set_property(const std::string& key, const std::string& value) {
    properties[key] = value;
}

// Restituisce una proprietà del nodo
/*std::string Node::get_property(const std::string& key) const {
    auto it = properties.find(key);
    if (it != properties.end()) {
        return it->second;
    }
    return "";
}*/

// Restituisce l'ID del nodo
std::string Node::get_id() const {
    return id;
}

// Restituisce l'etichetta del nodo
std::string Node::get_label() const {
    return label;
}

std::unordered_map<std::string, std::string> Node::get_properties() const {
    return properties;
}


