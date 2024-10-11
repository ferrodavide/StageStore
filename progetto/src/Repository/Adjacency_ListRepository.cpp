#include "src/Entity/Adjacency_List.hpp"

//getters
std::vector<std::string> Adjacency_List::get_id_dest(const std::string& id_s) const{
    adj_p current = head;
    while(current){
        if(current->id_src == id_s) return current->id_dest;
        current = current->next;
    }

    if(!current){
        std::vector<std::string> empty;
        return empty;
    } 
}

std::unordered_map<string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> Adjacency_List::get_adj_list(const std::string& id_s) const{
    adj_p current = head;
    while(current){
        if(current->id_src == id_s) return current->adj_list;
        current = current->next;
    }

    if(!current){
        std::unordered_map<string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> empty;
        return empty;
    } 
}
void Adjacency_List::set_adj_list_node(string id_s){
    adj_p current = head;
    bool check = false;
    while(current && !check){
        if(current->id_src == id_s) check = true;
        current = current->next;
    }

    if(!check){
        append(id_s);
    }
}
void Adjacency_List::set_adj_list_relationship(std::string id_s,std::string id_d, std::string label_dest, std::string label_rel, std::string prop_name, std::string prop_val){
    adj_p current = head;
    while(current){
        if(current->id_src == id_s){
            current->id_dest.push_back(id_d);
            current->adj_list[label_dest][label_rel][prop_name] = prop_val;
        }
        current = current->next;
    }
}

void Adjacency_List::append(const std::string& id_s){
    adj_p new_node = new adj(id_s);
    if (head == nullptr) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node; 
        new_node->prev = tail; 
        tail = new_node;
    }
}

//print the adj_list
void Adjacency_List::print() const {
    adj_p current = head;
    while(current){
        std::cout<<"ID SORGENTE: "<<current->id_src<<std::endl;
        for(int i = 0;i<current->id_dest.size();i++){
            std::cout<<"ID DESTINAZIONI:"<<current->id_dest.at(i)<<"RELATIVI AL NODO SORGENTE: "<<current->id_src<<std::endl;
        }
        std::cout<<"LISTA DI ADIACENZA:"<<std::endl;
        for (const auto& dest_entry : current->adj_list) {
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
        current = current->next;
    }
}  
