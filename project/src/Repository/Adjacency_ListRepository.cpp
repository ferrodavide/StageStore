#include "src/Entity/Adjacency_List.hpp"

//getters
std::vector<std::string> Adjacency_List::get_id_dest(const std::string& id_s) const{
    adj_p current = head;
    while(current){
        if(current->id_src == id_s) return current->id_dest;
        current = current->next;
    }

    return vector<string>();
}

unordered_map<string, unordered_map<string, unordered_map<string, string>>> Adjacency_List::get_adj_list(const string& id_s) const{
    adj_p current = head;
    while(current){
        if(current->id_src == id_s) return current->adj_list;
        current = current->next;
    }

    return unordered_map<string, unordered_map<string, unordered_map<string, string>>>();
}

//setters
void Adjacency_List::set_adj_list_node(const string& id_src){
    adj_p current = head;
    bool check = false;
    while(current && !check){
        if(current->id_src == id_src) check = true;
        current = current->next;
    }

    if(!check){
        append(id_src);
    }
}

void Adjacency_List::set_adj_list_relationship(const string& id_s, const string& id_dest, const string& label_dest, const string& label_rel, const string& prop_name, const string& prop_val){
    adj_p current = head;
    while(current){
        if(current->id_src == id_s){
            current->id_dest.push_back(id_dest);
            current->adj_list[label_dest][label_rel][prop_name] = prop_val;
            return;
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
    while (current) {
        std::cout << "ID SOURCE: " << current->id_src << std::endl;

        // Iterate and print the destination IDs (unordered_set)
        for (const auto& dest_id : current->id_dest) {
            std::cout << "ID DESTINATION: " << dest_id << " RELATED TO THE SOURCE NODE: " << current->id_src << std::endl;
        }

        std::cout << "Adjacency list:" << std::endl;

        // Iterate and print the adjacency list
        for (const auto& dest_entry : current->adj_list) {
            const std::string& label_dest = dest_entry.first;  // destination label
            const auto& rel_map = dest_entry.second;  // relations map

            std::cout << "  Destination Label: " << label_dest << std::endl;

            for (const auto& rel_entry : rel_map) {
                const std::string& label_rel = rel_entry.first;  // relations label
                const auto& prop_map = rel_entry.second;  // properties map

                std::cout << "    Relationship Label: " << label_rel << std::endl;

                for (const auto& prop_entry : prop_map) {
                    const std::string& prop_name = prop_entry.first;  // property name
                    const std::string& prop_value = prop_entry.second;  // property value

                    std::cout << "      Property: " << prop_name << " = " << prop_value << std::endl;
                }
            }
        }
        current = current->next;
    }
}

