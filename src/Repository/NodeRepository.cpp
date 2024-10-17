#include "src/Entity/Node.hpp"

// set a property
void Node::set_property(const std::string& key, const std::string& value) {
    properties[key] = value;
}

// return node ID
std::string Node::get_id() const {
    return id;
}

//return node label
std::string Node::get_label() const {
    return label;
}

//return the unordered map
std::unordered_map<std::string, std::string> Node::get_properties() const {
    return properties;
}