#include "src/Entity/Database.hpp"

//print the db
void Database::print(){
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
            std::cout << it->key().ToString() << " ----> " << it->value().ToString() << std::endl;
    }
    assert(it->status().ok());
    delete it;
}

//ADD NODE
void Database::add_node(const Node& node){
    //list.set_adj_list_node(node.get_id());
    // add_adj_list(list);
    std::string key = "n:" + node.get_id();
    std::string value = node.get_label() + " | ";
    //iterate through the properties and concatenate them to value
    for (const auto& prop : node.get_properties()) {
        value += prop.first + " = " + prop.second + "; ";
    }

    //adds the record into the db
    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Error saving node to database: " << status.ToString() << std::endl;
    }
}

//DELETE 
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

//UPDATE value through the key
void Database::update_node(const std::string& key,const std::string& value){
    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
     if (!status.ok()) {
        std::cerr << "Error updating node to database: " << status.ToString() << std::endl;
    }
}

//ADD_RELATION
void Database::add_relation(const Relationship& rel) {
    list.set_adj_list_node(rel.get_key_src());

    std::string lab_dest;
    std::string key_dest_lab = "n:" + rel.get_key_dest();
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key_dest_lab, &lab_dest);
    
    //get the real label as "Dog", "Person" ecc.
    size_t pos = lab_dest.find("|");
    if (pos != std::string::npos) {
        std::string label = lab_dest.substr(0, pos);
        lab_dest = label;
    }

    // store the relationship on the db
    std::string key = "r:" + rel.get_key_rel();
    std::string value;
    for (const auto& prop : rel.get_properties()) {
        value += prop.first + " = " + prop.second + "; ";
    }

    status = db->Put(rocksdb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Error saving relationship to database: " << status.ToString() << std::endl;
    }

    std::string prop_rel_value;
    // get prop_rel_value from db
    status = db->Get(rocksdb::ReadOptions(), key, &prop_rel_value);
    if (!status.ok()) {
        std::cerr << "Error getting relationship properties: " << status.ToString() << std::endl;
        return;
    }

    // Parsing of prop_rel_value for getting name and value properties
    std::vector<string> prop_name, prop_value;
   for (const auto& prop : rel.get_properties()) {
        prop_name.push_back(prop.first);
        prop_value.push_back(prop.second);

    }
    
    for(int i=0;i<prop_name.size();i++){
        list.set_adj_list_relationship(rel.get_key_src(),rel.get_key_dest(), lab_dest, rel.get_key_lab(), prop_name[i], prop_value[i]);
        add_adj_list(rel.get_key_src(), rel.get_key_dest(), lab_dest, rel.get_key_lab(), prop_name[i], prop_value[i]);
    }
    //list.print();
    //add_adj_list(list);
}

//ADD ADJ
void Database::add_adj_list(std::string src, string id_d, string label_dest, string label_rel, string prop_name, string prop_val){
    std::string key = "a:" + src;
    string check;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &check);
    
    if(check.empty()){
        status = db->Put(rocksdb::WriteOptions(),key , "["+id_d+";"+label_dest+";"+label_rel+";"+prop_name+";"+prop_val+"]");
        if(!status.ok()){
            std::cerr<<"Error saving adjacency list to database: "<<status.ToString()<<std::endl;
        }
    }else{
        bool controllo = false;
        for (size_t i = 0; i < check.length(); i++) {
            if (check[i] == '[') {
                // Trova la sottostringa dopo '[' e confronta con id_d
                size_t next_pos = i + 1;
                size_t end_pos = check.find(';', next_pos);
                if (end_pos != std::string::npos) {
                    std::string found_id = check.substr(next_pos, end_pos - next_pos);

                    // Se il valore trovato corrisponde a id_d, imposta controllo a true
                    if (found_id == id_d) {
                        controllo = true;
                        break; // Esci dal ciclo poiché hai trovato il valore
                    } else {
                        controllo = false;
                    }
                }
            }
        }
        if(controllo==true){
            status = db->Put(rocksdb::WriteOptions(),key , check + ";"+prop_name+";"+prop_val+"]" );
            if(!status.ok()){
                std::cerr<<"Error saving adjacency list to database: "<<status.ToString()<<std::endl;
            } 
        }else{
            status = db->Put(rocksdb::WriteOptions(),key , check + "["+id_d+";"+label_dest+";"+label_rel+";"+prop_name+";"+prop_val+"]" );
            if(!status.ok()){
                std::cerr<<"Error saving adjacency list to database: "<<status.ToString()<<std::endl;
            }
        }
    }
}

void Database::print_list(){
    list.print();
}