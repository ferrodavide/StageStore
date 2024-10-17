#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // per rand e srand
#include <ctime>    // per time
#include <set>      // per std::set
#include <fstream>  // per file output
#include <sstream>

// Funzione per generare un nome casuale
std::string generateRandomName() {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Luca"};
    return names[rand() % names.size()];
}

// Funzione per generare un'altezza casuale (tra 150 e 200 cm)
int generateRandomHeight() {
    return rand() % 51 + 150; // Valori tra 150 e 200
}

// Funzione per generare un nodo casuale con proprietà name e height
std::string generateRandomNode(int id) {
    std::string name = generateRandomName();
    int height = generateRandomHeight();
    
    // Formato CSV: id,name,height
    return std::to_string(id) + "," + name + "," + std::to_string(height);
}

// Funzione per generare una data casuale (rappresentata come anni di relazione)
int generateRandomSince() {
    return rand() % 30 + 1990; // Anni tra 1990 e 2020
}

// Funzione per generare un ruolo casuale per la relazione
std::string generateRandomRole() {
    std::vector<std::string> roles = {"colleague", "neighbor", "classmate", "teammate", "mentor"};
    return roles[rand() % roles.size()];
}

// Funzione per generare una relazione casuale con id1 diverso da id2, includendo 'since' e 'as'
std::string generateRandomRelation(int maxID) {
    // Genera ID casuale per id1
    int id1 = rand() % maxID + 1; // ID tra 1 e maxID
    
    int id2;
    // Genera ID casuale per id2, diverso da id1
    do {
        id2 = rand() % maxID + 1;
    } while (id2 == id1); // Continua a rigenerare id2 finché non è diverso da id1

    // Lista di relazioni possibili
    std::vector<std::string> relations = {"KNOWS", "IS_FRIEND_OF", "LIKES", "FOLLOWS", "BLOCKS"};
    
    // Scegli una relazione casuale
    std::string relation = relations[rand() % relations.size()];

    // Genera proprietà since e as
    int since = generateRandomSince();
    std::string role = generateRandomRole();

    // Ritorna la stringa formattata
    return std::to_string(id1) + "," + relation + "," + std::to_string(id2) + "," + std::to_string(since) + "," + role;
}

// Funzione per scrivere un certo numero di nodi casuali in un file CSV
void writeRandomNodesToCSV(const std::string& filename, int numNodes) {
    std::ofstream file(filename);

    if (file.is_open()) {
        // Scrivi l'intestazione del file CSV
        file << "id,name,height\n";
        // Genera e scrivi ogni nodo
        for (int i = 1; i <= numNodes; ++i) {
            std::string node = generateRandomNode(i);
            file << node << "\n";
        }
        file.close();
        std::cout << "File nodi CSV generato con successo: " << filename << std::endl;
    } else {
        std::cerr << "Errore nell'apertura del file: " << filename << std::endl;
    }
}

// Funzione per scrivere un certo numero di relazioni casuali uniche in un file CSV
void writeUniqueRandomRelationsToCSV(const std::string& filename, int numRows, int maxID) {
    std::set<std::tuple<int, std::string, int>> uniqueKeys; // Set per evitare duplicati nella forma (id1, relation, id2)
    std::set<std::string> uniqueRelations;  // Set per le relazioni finali uniche nel formato stringa

    // Continua a generare relazioni finché non ci sono abbastanza relazioni uniche
    while (uniqueRelations.size() < static_cast<size_t>(numRows)) {
        // Genera una relazione casuale
        int id1 = rand() % maxID + 1;
        int id2;
        do {
            id2 = rand() % maxID + 1;
        } while (id2 == id1); // Assicura che id2 sia diverso da id1
        
        std::vector<std::string> relations = {"KNOWS", "IS_FRIEND_OF", "LIKES", "FOLLOWS", "BLOCKS"};
        std::string relation = relations[rand() % relations.size()];
        
        // Controlla se la tripla (id1, relation, id2) è già presente nel set
        std::tuple<int, std::string, int> key = std::make_tuple(id1, relation, id2);
        if (uniqueKeys.find(key) == uniqueKeys.end()) {
            // Se non esiste, aggiungi la tripla chiave al set
            uniqueKeys.insert(key);

            // Genera le proprietà "since" e "role"
            int since = generateRandomSince();
            std::string role = generateRandomRole();
            
            // Crea la relazione formattata come stringa
            std::string relationString = std::to_string(id1) + "," + relation + "," + std::to_string(id2) + "," + std::to_string(since) + "," + role;
            uniqueRelations.insert(relationString);  // Aggiungi la relazione formattata al set delle relazioni
        }
    }

    // Apre il file CSV in scrittura
    std::ofstream file(filename);

    // Verifica che il file sia stato aperto correttamente
    if (file.is_open()) {
        // Scrivi tutte le relazioni uniche nel file CSV
        for (const auto& relation : uniqueRelations) {
            file << relation << "\n"; // Ogni relazione su una nuova riga
        }
        file.close();
        std::cout << "File relazioni CSV generato con successo: " << filename << std::endl;
    } else {
        std::cerr << "Errore nell'apertura del file: " << filename << std::endl;
    }
}


void generate(){
    // Parametri
    const int numNodes = 5; // Numero di nodi da generare
    const int numRows = 20; // Numero di relazioni da generare
    const int maxID = numNodes; // ID massimo per i nodi
    const std::string nodesFilename = "nodi.csv"; // Nome del file CSV per i nodi
    const std::string relationsFilename = "relazioni.csv"; // Nome del file CSV per le relazioni

    // Inizializza il generatore di numeri casuali
    srand(static_cast<unsigned int>(time(nullptr)));

    // Scrivi i nodi casuali nel file CSV
    writeRandomNodesToCSV(nodesFilename, numNodes);

    // Scrivi le relazioni casuali uniche nel file CSV
    writeUniqueRandomRelationsToCSV(relationsFilename, numRows, maxID);
}