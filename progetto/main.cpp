#include "src/Entity/Database.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    Database data;
    //Adjacency_List lista;

    Node node1("1", "Person");
    node1.set_property("name", "Matteo");
    node1.set_property("age", "22");
    node1.set_property("weigth", "76");
    Node node2("2", "Dog");
    node2.set_property("name", "Pippo");
    node2.set_property("age", "21");
    Node node3("3", "Dog");
    node3.set_property("name", "Pluto");
    node3.set_property("age", "29");
    Node node4("4", "Mouse");
    node4.set_property("name", "Topolino");
    node4.set_property("age", "25");
    Node node5("5", "Person");
    node5.set_property("name", "Davide");
    node5.set_property("age", "21");
    node5.set_property("weigth", "70");

    data.add_node(node1);
    data.add_node(node2);
    data.add_node(node3);
    data.add_node(node4);
    data.add_node(node5);
    
    Relationship r1("1","IS_FRIEND_WITH","5");
    r1.set_property("since","2009");
    r1.set_property("play","basketball");
    Relationship r5("1","WORKS_WITH", "2");
    r5.set_property("as","driver");
   /* Relationship r2("4","EATS_WITH","3");
    r2.set_property("for","2 hours");
    r2.set_property("eating","pizza");
    Relationship r3("5","IS_FRIEND_WITH","3");
    r3.set_property("since","1997");
    r3.set_property("from","school");
    Relationship r4("3","WORKS_WITH","4");
    r4.set_property("as","Developer");
    */

    data.add_relation(r1);
  /*  data.add_relation(r2);
    data.add_relation(r3);
    data.add_relation(r4);
    */
    data.add_relation(r5);
    
    //data.print();
    data.print_list();
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    
    return 0;
}

/*#include "src/Entity/Database.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char const *argv[])
{
    // Crea un'istanza del database
    Database data;
    
    // Creazione nodi
    Node node1("1", "Person");
    node1.set_property("name", "Matteo");
    node1.set_property("age", "22");
    node1.set_property("weigth", "76");
    Node node2("2", "Dog");
    node2.set_property("name", "Pippo");
    node2.set_property("age", "21");
    Node node3("3", "Dog");
    node3.set_property("name", "Pluto");
    node3.set_property("age", "29");
    Node node4("4", "Mouse");
    node4.set_property("name", "Topolino");
    node4.set_property("age", "25");
    Node node5("5", "Person");
    node5.set_property("name", "Davide");
    node5.set_property("age", "21");
    node5.set_property("weigth", "70");

    data.add_node(node1);
    data.add_node(node2);
    data.add_node(node3);
    data.add_node(node4);
    data.add_node(node5);
    
    // Lettura delle relazioni dal file CSV
    std::ifstream file("relazioni.csv");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id1, relationship, id2;

            std::getline(ss, id1, ',');
            std::getline(ss, relationship, ',');
            std::getline(ss, id2, ',');

            Relationship rel(id1, relationship, id2);
            data.add_relation(rel);
        }
        file.close();
    } else {
        std::cerr << "Impossibile aprire il file relazioni.csv" << std::endl;
    }

    // Stampa del database
    data.print();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}

*/