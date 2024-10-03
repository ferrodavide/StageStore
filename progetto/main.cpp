#include "Database.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    // Crea un'istanza del database
    Database data;

    Node node1("1", "Person");
    node1.set_property("name", "Matteo");
    node1.set_property("age", "22");

    data.add_node(node1);
    
    data.print();
    return 0;
}