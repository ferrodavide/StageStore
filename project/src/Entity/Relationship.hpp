#ifndef RELATIONSHIP_HPP
#define RELATIONSHIP_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class Relationship{
public:

    // Default constructor
    Relationship() {
        key_rel[0] = "";
        key_rel[1] = "";
        key_rel[2] = "";
    }
    
    //constructor
    Relationship(const std::string& id_src, const std::string& label, const std::string& id_dest){
        key_rel[0] = id_src;
        key_rel[1] = label;
        key_rel[2] = id_dest;
    }

    //setter
    void set_property(const std::string& key, const std::string& value);
    
    //getters
    std::string get_key_rel() const;
    std::string get_key_src() const;
    std::string get_key_lab() const;
    std::string get_key_dest() const;
    std::unordered_map<std::string, std::string> get_properties() const;
    
private:
    std::string key_rel[3]; //native array for memorize "id_src, label_rel, id_dest"
    std::unordered_map<std::string, std::string> properties; //properties in this form: "name_prop: value_prop" (name:"Matteo", age:"22")
};

#endif