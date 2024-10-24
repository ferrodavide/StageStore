#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // for rand and srand
#include <ctime>    // for time
#include <set>      // for std::set
#include <fstream>  // for file output
#include <sstream>
#include <tuple>    // for std::tuple

// Function to generate a random name
std::string generateRandomName() {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Luca"};
    return names[rand() % names.size()];
}

// Function to generate a random height (between 150 and 200 cm)
int generateRandomHeight() {
    return rand() % 51 + 150; // Values between 150 and 200
}

// Function to generate a random node with properties name and height
std::string generateRandomNode(int id) {
    std::string name = generateRandomName();
    int height = generateRandomHeight();
    
    // CSV format: id,name,height
    return std::to_string(id) + "," + name + "," + std::to_string(height);
}

// Function to generate a random date (represented as years of relation)
int generateRandomSince() {
    return rand() % 30 + 1990; // Years between 1990 and 2020
}

// Function to generate a random role for the relation
std::string generateRandomRole() {
    std::vector<std::string> roles = {"colleague", "neighbor", "classmate", "teammate", "mentor"};
    return roles[rand() % roles.size()];
}

// Function to generate a random relation with id1 different from id2, including 'since' and 'as'
std::string generateRandomRelation(int maxID) {
    // Generate random ID for id1
    int id1 = rand() % maxID + 1; // ID between 1 and maxID
    
    int id2;
    // Generate random ID for id2, different from id1
    do {
        id2 = rand() % maxID + 1;
    } while (id2 == id1); // Keep regenerating id2 until it is different from id1

    // List of possible relations
    std::vector<std::string> relations = {"KNOWS", "IS_FRIEND_OF", "LIKES", "FOLLOWS", "BLOCKS"};
    
    // Choose a random relation
    std::string relation = relations[rand() % relations.size()];

    // Generate properties since and as
    int since = generateRandomSince();
    std::string role = generateRandomRole();

    // Return the formatted string
    return std::to_string(id1) + "," + relation + "," + std::to_string(id2) + "," + std::to_string(since) + "," + role;
}

// Function to write a certain number of random nodes to a CSV file
void writeRandomNodesToCSV(const std::string& filename, int numNodes) {
    std::ofstream file(filename);

    if (file.is_open()) {
        // Write the header of the CSV file
        file << "id,name,height\n";
        // Generate and write each node
        for (int i = 1; i <= numNodes; ++i) {
            std::string node = generateRandomNode(i);
            file << node << "\n";
        }
        file.close();
        std::cout << "CSV nodes file successfully generated: " << filename << std::endl;
    } else {
        std::cerr << "Error opening the file: " << filename << std::endl;
    }
}

// Function to write a certain number of unique random relations to a CSV file
void writeUniqueRandomRelationsToCSV(const std::string& filename, int numRows, int maxID) {
    std::set<std::tuple<int, std::string, int>> uniqueKeys; // Set to avoid duplicates in the form (id1, relation, id2)
    std::set<std::string> uniqueRelations;  // Set for the final unique relations in string format

    // Continue generating relations until there are enough unique relations
    while (uniqueRelations.size() < static_cast<size_t>(numRows)) {
        std::string relationString = generateRandomRelation(maxID);
        std::stringstream ss(relationString);
        int id1, id2;
        std::string relation, role;
        int since;

        // Parse the relation string
        std::getline(ss, relation, ',');
        id1 = std::stoi(relation);
        std::getline(ss, relation, ',');
        std::string relationType = relation;  // relation type
        std::getline(ss, relation, ',');
        id2 = std::stoi(relation);
        std::getline(ss, relation, ',');
        since = std::stoi(relation);
        std::getline(ss, role); // role

        // Create a unique key for the relation
        auto key = std::make_tuple(id1, relationType, id2);
        if (uniqueKeys.insert(key).second) { // Insert only if it was not present
            uniqueRelations.insert(relationString);  // Add the formatted relation to the set of relations
        }
    }

    // Open the CSV file for writing
    std::ofstream file(filename);

    // Check if the file was opened correctly
    if (file.is_open()) {
        // Write all unique relations to the CSV file
        for (const auto& relation : uniqueRelations) {
            file << relation << "\n"; // Each relation on a new line
        }
        file.close();
        std::cout << "CSV relations file successfully generated: " << filename << std::endl;
    } else {
        std::cerr << "Error opening the file: " << filename << std::endl;
    }
}

void generate() {
    // Parameters
    const int numNodes = 100000; // Number of nodes to generate
    const int numRows = 1000000; // Number of relations to generate
    const int maxID = numNodes; // Maximum ID for nodes
    const std::string nodesFilename = "nodes.csv"; // CSV file name for nodes
    const std::string relationsFilename = "relations.csv"; // CSV file name for relations

    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Write random nodes to the CSV file
    writeRandomNodesToCSV(nodesFilename, numNodes);

    // Write unique random relations to the CSV file
    writeUniqueRandomRelationsToCSV(relationsFilename, numRows, maxID);
}
