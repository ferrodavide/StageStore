#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>
#include <unordered_map>

class Relationship {
public:
    // Costruttore per creare una relazione con un ID e due nodi (sorgente e destinazione)
    Relationship(const std::string& id, const std::string& src_node, const std::string& dest_node);

    // Metodo per ottenere l'ID della relazione
    std::string get_id() const;

    // Metodo per ottenere il nodo sorgente
    std::string get_source_node() const;

    // Metodo per ottenere il nodo destinazione
    std::string get_dest_node() const;

    // Metodo per aggiungere una proprietà alla relazione
    void add_property(const std::string& key, const std::string& value);

    // Metodo per ottenere il valore di una proprietà
    std::string get_property(const std::string& key) const;

    // Metodo per rimuovere una proprietà
    void remove_property(const std::string& key);

    // Metodo per stampare tutte le proprietà della relazione
    void print_properties() const;

private:
    std::string id;  // Identificatore univoco della relazione
    std::string src_node;  // ID del nodo sorgente
    std::string dest_node;  // ID del nodo destinazione
    std::unordered_map<std::string, std::string> properties;  // Proprietà della relazione
};

#endif // RELATIONSHIP_H
