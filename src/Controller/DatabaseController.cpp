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

    // Costruisci una singola stringa per tutte le proprietà
    std::string prop_string;
    for (const auto& prop : rel.get_properties()) {
        prop_string += prop.first + ";" + prop.second + ";";
    }
    
    // Rimuovi l'ultimo punto e virgola
    if (!prop_string.empty()) {
        prop_string.pop_back();
    }
    
    // Chiama add_adj_list una sola volta per relazione
    add_adj_list(rel.get_key_src(), rel.get_key_dest(), lab_dest, rel.get_key_lab(), prop_string);
}

void Database::add_adj_list(std::string src, std::string id_d, std::string label_dest, std::string label_rel, std::string prop_string) {
    std::string key = "a:" + src;
    std::string check;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &check);

    // Costruzione del nuovo blocco relazione
    std::string new_block = "[" + id_d + ";" + label_dest + ";" + label_rel + ";" + prop_string + "]";

    if (check.empty()) {
        // Se non esiste una lista di adiacenza, la creiamo ex novo
        status = db->Put(rocksdb::WriteOptions(), key, new_block);
        if (!status.ok()) {
            std::cerr << "Error saving adjacency list to database: " << status.ToString() << std::endl;
        }
    } else {
        // Cerca se esiste già una relazione con lo stesso `id_d` e `label_rel`
        size_t pos = check.find("[" + id_d + ";" + label_dest + ";" + label_rel);
        if (pos != std::string::npos) {
            // Se esiste, trova il punto in cui aggiungere le nuove proprietà
            size_t end_pos = check.find("]", pos);
            if (end_pos != std::string::npos) {
                // Estrai la parte esistente e aggiungi nuove proprietà alla relazione esistente
                std::string existing_block = check.substr(pos, end_pos - pos);
                std::string updated_block = existing_block.substr(0, existing_block.length() - 1) + ";" + prop_string + "]";

                // Sostituisci il vecchio blocco con quello aggiornato
                check.replace(pos, end_pos - pos + 1, updated_block);
            }
        } else {
            // Cerca se esiste già una relazione con lo stesso `id_d` ma con un'etichetta di relazione diversa
            size_t dest_pos = check.find("[" + id_d + ";" + label_dest);
            if (dest_pos != std::string::npos) {
                // Se esiste, aggiungi la nuova relazione (con una nuova etichetta) nello stesso nodo di destinazione
                size_t end_block_pos = check.find("]", dest_pos);
                if (end_block_pos != std::string::npos) {
                    check.insert(end_block_pos, ";" + label_rel + ";" + prop_string);
                }
            } else {
                // Se non esiste una relazione con lo stesso nodo di destinazione, aggiungi un nuovo blocco relazione
                check += new_block;
            }
        }

        // Salva la lista aggiornata
        status = db->Put(rocksdb::WriteOptions(), key, check);
        if (!status.ok()) {
            std::cerr << "Error saving adjacency list to database: " << status.ToString() << std::endl;
        }
    }
}

void Database::print_list(){
    list.print();
}