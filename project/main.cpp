#include "src/Entity/Database.hpp"
#include "resources/CSV_Generator.cpp"
#include "resources/test/test2.cpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    Database data;
    //data.delete_db();
    //generate();
    /*GraphServices g;
    g.load_node_from_csv("nodes.csv", data);
    g.load_relation_from_csv("relations.csv", data);
    data.print();*/
    //call_test1(data);
    call_test2(data);
    //call_test3(data);
    //call_test4(data, "name", "Alice");
    return 0;
}