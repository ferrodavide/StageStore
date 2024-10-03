#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>


class Node {
public:
    Node();
    Node(const std::string& id, const std::string& label);
    void set_property(const std::string& key, const std::string& value);
    std::string get_property(const std::string& key) const;
    
    // Aggiungi questi metodi
    std::string get_id() const;
    std::string get_label() const;
    
private:
    std::string id;
    std::string label;
    std::unordered_map<std::string, std::string> properties; // Proprietà del nodo
};

#endif 
