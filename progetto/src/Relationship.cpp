#include "Relationship.hpp"
#include <iostream>

// Costruttore: inizializza la relazione con ID e nodi sorgente e destinazione
Relationship::Relationship(const std::string& id, const std::string& src_node, const std::string& dest_node)
    : id(id), src_node(src_node), dest_node(dest_node) {}

// Restituisce l'ID della relazione
std::string Relationship::get_id() const {
    return id;
}

// Restituisce il nodo sorgente
std::string Relationship::get_source_node() const {
    return src_node;
}

// Restituisce il nodo destinazione
std::string Relationship::get_dest_node() const {
    return dest_node;
}

// Aggiunge una proprietà alla relazione
void Relationship::add_property(const std::string& key, const std::string& value) {
    properties[key] = value;  // Sovrascrive il valore se la chiave esiste già
}

// Restituisce il valore di una proprietà
std::string Relationship::get_property(const std::string& key) const {
    auto it = properties.find(key);
    if (it != properties.end()) {
        return it->second;
    }
    return "";  // Restituisce una stringa vuota se la proprietà non esiste
}

// Rimuove una proprietà dalla relazione
void Relationship::remove_property(const std::string& key) {
    properties.erase(key);  // Rimuove la proprietà se esiste
}

// Stampa tutte le proprietà della relazione
void Relationship::print_properties() const {
    std::cout << "Relationship ID: " << id << "\nProperties:\n";
    for (const auto& prop : properties) {
        std::cout << prop.first << ": " << prop.second << "\n";
    }
}
