#include "src/Entity/Database.hpp"
#include <sstream>

// Print methods
void Database::print(){
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << " ----> " << it->value().ToString() << std::endl;
    }
    assert(it->status().ok());
    delete it;
}

void Database::print_list(){
    list.print();
}

// ADD NODE
void Database::add_node(const Node& node){
    // list.set_adj_list_node(node.get_id());
    // add_adj_list(list);
    std::string key = "n:" + node.get_id();
    std::string value = node.get_label() + " | ";
    // Iterate through the properties and concatenate them to value
    for (const auto& prop : node.get_properties()) {
        value += prop.first + " = " + prop.second + "; ";
    }

    // Adds the record into the database
    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Error saving node to database: " << status.ToString() << std::endl;
    }
}

// ADD_RELATION
void Database::add_relation(const Relationship& rel) {
    list.set_adj_list_node(rel.get_key_src());

    std::string lab_dest;
    std::string key_dest_lab = "n:" + rel.get_key_dest();
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key_dest_lab, &lab_dest);
    
    size_t pos = lab_dest.find("|");
    if (pos != std::string::npos) {
        std::string label = lab_dest.substr(0, pos);
        lab_dest = label;
    }

    // Store the relationship in the database
    std::string key = "r:" + rel.get_key_rel();
    std::string value;
    for (const auto& prop : rel.get_properties()) {
        value += prop.first + " = " + prop.second + "; ";
    }

    status = db->Put(rocksdb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Error saving relationship to database: " << status.ToString() << std::endl;
    }

    // Build a single string for all properties
    std::string prop_string;
    for (const auto& prop : rel.get_properties()) {
        prop_string += prop.first + ";" + prop.second + ";";
    }
    
    // Remove the last semicolon
    if (!prop_string.empty()) {
        prop_string.pop_back();
    }
    
    // Call add_adj_list only once per relationship
    add_adj_list(rel.get_key_src(), rel.get_key_dest(), lab_dest, rel.get_key_lab(), prop_string);
}

//ADD ADJLIST
void Database::add_adj_list(std::string src, std::string id_d, std::string label_dest, std::string label_rel, std::string prop_string) {
    std::string key = "a:" + src;
    std::string check;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &check);

    // Build the new relation block
    std::string new_block = "[" + id_d + ";" + label_dest + ";" + label_rel + ";" + prop_string + "]";

    if (check.empty()) {
        // If no adjacency list exists, create a new one
        status = db->Put(rocksdb::WriteOptions(), key, new_block);
        if (!status.ok()) {
            std::cerr << "Error saving adjacency list to database: " << status.ToString() << std::endl;
        }
    } else {
        // Check if a relationship with the same `id_d` and `label_rel` already exists
        size_t pos = check.find("[" + id_d + ";" + label_dest + ";" + label_rel);
        if (pos != std::string::npos) {
            // If it exists, find the point to add the new properties
            size_t end_pos = check.find("]", pos);
            if (end_pos != std::string::npos) {
                // Extract the existing part and add new properties to the existing relationship
                std::string existing_block = check.substr(pos, end_pos - pos);
                std::string updated_block = existing_block.substr(0, existing_block.length() - 1) + ";" + prop_string + "]";

                // Replace the old block with the updated one
                check.replace(pos, end_pos - pos + 1, updated_block);
            }
        } else {
            // Check if a relationship with the same `id_d` but a different relationship label exists
            size_t dest_pos = check.find("[" + id_d + ";" + label_dest);
            if (dest_pos != std::string::npos) {
                // If it exists, add the new relation (with a new label) to the same destination node
                size_t end_block_pos = check.find("]", dest_pos);
                if (end_block_pos != std::string::npos) {
                    check.insert(end_block_pos, ";" + label_rel + ";" + prop_string);
                }
            } else {
                // If no relationship with the same destination node exists, add a new relation block
                check += new_block;
            }
        }

        // Save the updated list
        status = db->Put(rocksdb::WriteOptions(), key, check);
        if (!status.ok()) {
            std::cerr << "Error saving adjacency list to database: " << status.ToString() << std::endl;
        }
    }
}

//GETTERS
Node Database::get_node(const std::string& id) {
    std::string key = "n:" + id;  // Format the key for nodes
    std::string value;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &value);
    
    if (!status.ok()) {
        std::cerr << "Error retrieving node: " << status.ToString() << std::endl;
        return Node();  // Return an empty node in case of an error
    }

    // Split the value to get label and properties
    size_t pos = value.find("|");
    std::string label = value.substr(0, pos - 1);  // Extract the node's label
    std::string properties = value.substr(pos + 2);  // The rest are the properties
    
    Node node(id, label);
    
    // Split the properties by ';' and assign them to the node
    std::istringstream prop_stream(properties);
    std::string prop;
    while (std::getline(prop_stream, prop, ';')) {
        size_t equal_pos = prop.find('=');
        if (equal_pos != std::string::npos) {
            std::string key = prop.substr(0, equal_pos - 1);
            std::string value = prop.substr(equal_pos + 2);
            node.set_property(key, value);
        }
    }
    
    return node;
}

Relationship Database::get_relation(const std::string& id) {
    std::string key = "r:" + id;  // Format the key for relationships
    std::string value;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &value);
    
    if (!status.ok()) {
        std::cerr << "Error retrieving relationship: " << status.ToString() << std::endl;
        return Relationship();  // Return an empty relationship in case of an error
    }

    // Extract the three components of the key: source, relation type, destination
    std::istringstream id_stream(id);
    std::string id_src, rel_type, id_dest;
    std::getline(id_stream, id_src, ' ');
    std::getline(id_stream, rel_type, ' ');
    std::getline(id_stream, id_dest, ' ');
    
    Relationship relationship(id_src, rel_type, id_dest);

    // Split the properties by ';' and assign them to the relationship
    std::istringstream prop_stream(value);
    std::string prop;
    while (std::getline(prop_stream, prop, ';')) {
        size_t equal_pos = prop.find('=');
        if (equal_pos != std::string::npos) {
            std::string key = prop.substr(0, equal_pos - 1);
            std::string value = prop.substr(equal_pos + 2);
            relationship.set_property(key, value);
        }
    }

    return relationship;
}

rocksdb::DB* Database::get_db() { return db; }

//NOT IMPLEMENTED YET
// get_adj_list()

// DELETE
void Database::delete_node(const string n_key){
    rocksdb::Status status = db->Delete(rocksdb::WriteOptions(), n_key);  
    if (!status.ok()) {
        std::cerr << "Error deleting node to database: " << status.ToString() << std::endl;
    }
}

void Database::delete_relationship(const string r_key){
    rocksdb::Status status = db->Delete(rocksdb::WriteOptions(), r_key); 
    if (!status.ok()) {
        std::cerr << "Error deleting relationship to database: " << status.ToString() << std::endl;
    }
}

void Database::delete_adjacency_list(const string al_key){
    rocksdb::Status status = db->Delete(rocksdb::WriteOptions(), al_key); 
    if (!status.ok()) {
        std::cerr << "Error deleting adjacency list to database: " << status.ToString() << std::endl;
    }
}

// UPDATE value through the key
void Database::update_node(const std::string& key,const std::string& value){
    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Error updating node to database: " << status.ToString() << std::endl;
    }
}