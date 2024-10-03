#include "Node.hpp"
#include <iostream>

// Costruttore: inizializza il nodo con l'id passato come parametro
Node::Node(const std::string& id) : id(id) {}

// Restituisce l'ID del nodo
std::string Node::get_id() const {
    return id;
}

// Aggiunge una proprietà al nodo
void Node::add_property(const std::string& key, const std::string& value) {
    properties[key] = value;  // Sovrascrive il valore se la chiave esiste già
}

// Restituisce il valore di una proprietà
std::string Node::get_property(const std::string& key) const {
    auto it = properties.find(key);
    if (it != properties.end()) {
        return it->second;
    }
    return "";  // Restituisce una stringa vuota se la proprietà non esiste
}

// Rimuove una proprietà dal nodo
void Node::remove_property(const std::string& key) {
    properties.erase(key);  // Rimuove la proprietà se esiste
}

// Stampa tutte le proprietà del nodo
void Node::print_properties() const {
    std::cout << "Node ID: " << id << "\nProperties:\n";
    for (const auto& prop : properties) {
        std::cout << prop.first << ": " << prop.second << "\n";
    }
}
