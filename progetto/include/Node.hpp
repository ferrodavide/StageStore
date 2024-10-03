#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>

class Node {
public:
    // Costruttore per creare un nodo con un id e opzionalmente delle proprietà
    Node(const std::string& id);

    // Metodo per ottenere l'ID del nodo
    std::string get_id() const;

    // Metodo per aggiungere una proprietà al nodo
    void add_property(const std::string& key, const std::string& value);

    // Metodo per ottenere il valore di una proprietà
    std::string get_property(const std::string& key) const;

    // Metodo per rimuovere una proprietà
    void remove_property(const std::string& key);

    // Metodo per stampare tutte le proprietà del nodo (utile per il debugging)
    void print_properties() const;

private:
    std::string id;  // Identificatore univoco del nodo
    std::unordered_map<std::string, std::string> properties;  // Mappa chiave-valore per memorizzare le proprietà
};

#endif // NODE_H
