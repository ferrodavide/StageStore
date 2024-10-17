#include "src/Entity/Relationship.hpp"

// set a property
void Relationship::set_property(const std::string& key, const std::string& value) {
    properties[key] = value;
}

// return key_rel as a string
std::string Relationship::get_key_rel() const {
    std::string s =  key_rel[0] + " " + key_rel[1] + " " + key_rel[2];
    return s;
}

std::string Relationship::get_key_src() const { return key_rel[0]; }
std::string Relationship::get_key_lab() const { return key_rel[1]; }
std::string Relationship::get_key_dest() const { return key_rel[2]; }

//return the unordered map
std::unordered_map<std::string, std::string> Relationship::get_properties() const {
    return properties;
}