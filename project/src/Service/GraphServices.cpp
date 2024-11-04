#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // for rand and srand
#include <ctime>    // for time
#include <set>      // for std::set
#include <fstream>  // for file output
#include <sstream>

class GraphServices{
public:
        
    // Function to load relations from the CSV file
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
            relationship.set_property("since", since); // Add "since" property
            relationship.set_property("as", role);     // Add "as" property
            db.add_relation(relationship);
        }
    }

    // Function to load nodes from the CSV file
    void load_node_from_csv(const std::string& filename, Database& db) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(infile, line); // Skip the header

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string id1, prop1, prop2;
            if (std::getline(ss, id1, ',') && std::getline(ss, prop1, ',') && std::getline(ss, prop2, ',')) {
                Node node(id1, ":Person");
                node.set_property("name", prop1); 
                node.set_property("height", prop2); 
                db.add_node(node);
            } else {
                std::cerr << "Error in row format: " << line << std::endl;
            }
        }
    }
};