#include "src/Entity/Adjacency_List.hpp"

//getters
std::string Adjacency_List::get_id_src() const{
    return id_src;
}
std::string Adjacency_List::get_id_dest() const{
    return id_dest;
}

//setters
std::unordered_map<string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> Adjacency_List::get_adj_list() const{
    return adj_list;
}
void Adjacency_List::set_adj_list_node(string id_s){
    id_src = id_s;
}
void Adjacency_List::set_adj_list_relationship(string id_d, string label_dest, string label_rel, string prop_name, string prop_val){
    id_dest = id_d;
    //insert the property
    adj_list[label_dest][label_rel][prop_name] = prop_val;
}

//print the adj_list
void Adjacency_List::print() const {
    std::cout << "Source Node ID: " << id_src << std::endl;
 
    std::cout << "Destination Node ID: " << id_dest << std::endl;

    for (const auto& dest_entry : adj_list) {
        const std::string& label_dest = dest_entry.first;  // Label di destinazione
        const auto& rel_map = dest_entry.second;  // Mappa delle relazioni

        std::cout << "  Destination Label: " << label_dest << std::endl;

        for (const auto& rel_entry : rel_map) {
            const std::string& label_rel = rel_entry.first;  // Label della relazione
            const auto& prop_map = rel_entry.second;  // Mappa delle proprietà

            std::cout << "    Relationship Label: " << label_rel << std::endl;

            for (const auto& prop_entry : prop_map) {
                const std::string& prop_name = prop_entry.first;  // Nome della proprietà
                const std::string& prop_value = prop_entry.second;  // Valore della proprietà

                std::cout << "      Property: " << prop_name << " = " << prop_value << std::endl;
            }
        }
    }
}  
