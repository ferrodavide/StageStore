#include "Database.hpp"

Database::Database(){
    //opening the database
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
    if (!status.ok()) {
        std::cerr << "Error opening database: " << status.ToString() << std::endl;
    }
    // Creare un iteratore per scorrere tutte le chiavi
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::string key = it->key().ToString();
        // Cancellare la chiave
        status = db->Delete(rocksdb::WriteOptions(), key);
        if (!status.ok()) {
            std::cerr << "Errore durante la cancellazione di " << key << ": " << status.ToString() << std::endl;
        }
    }
    delete it;
}

Database::~Database(){ delete db; } //closing the database

void Database::print(){
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
            std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
    }
    assert(it->status().ok());
    delete it;
}

void Database::add_node(const Node& node){

    nodes[node.get_id()] = node;
    std::string key = node.get_id();
    std::string value = node.get_label() + " | "; // Inizia con l'etichetta

    for (const auto& prop : node.get_properties()) {
        value += prop.first + " = " + prop.second + "; "; // Formato chiave=valore
    }

    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Error saving node to database: " << status.ToString() << std::endl;
    }
}

    