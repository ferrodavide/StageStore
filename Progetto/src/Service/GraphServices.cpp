#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // per rand e srand
#include <ctime>    // per time
#include <set>      // per std::set
#include <fstream>  // per file output
#include <sstream>

class GraphServices{
public:
        
    // Funzione per caricare le relazioni dal file CSV
    void load_relation_from_csv(const std::string& filename, Database& db) {
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string id1, rel, id2, since, role;
            std::getline(ss, id1, ',');
            std::getline(ss, rel, ',');
            std::getline(ss, id2, ',');
            std::getline(ss, since, ',');
            std::getline(ss, role, ',');
                
            Relationship relationship(id1, rel, id2);
            relationship.set_property("since", since); // Aggiungi proprietà since
            relationship.set_property("as", role);     // Aggiungi proprietà as
            db.add_relation(relationship);
        }
    }

    // Funzione per caricare i nodi dal file CSV
    void load_node_from_csv(const std::string& filename, Database& db) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Errore nell'apertura del file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(infile, line); // Salta l'intestazione

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string id1, prop1, prop2;
            if (std::getline(ss, id1, ',') && std::getline(ss, prop1, ',') && std::getline(ss, prop2, ',')) {
                Node node(id1, ":Person");
                node.set_property("name", prop1); 
                node.set_property("height", prop2); 
                db.add_node(node);
            } else {
                std::cerr << "Errore nel formato della riga: " << line << std::endl;
            }
        }
    }
};