#include "src/Entity/Database.hpp"
#include "resources/CSV_Generator.cpp"
#include "resources/test/test2.cpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    Database data;
    //data.delete_db();
    generate();
    GraphServices g;
    g.load_node_from_csv("nodes.csv", data);
    g.load_relation_from_csv("relations.csv", data);
    
    //data.print();
    //call_test1(data);
   // call_test2(data);
    //call_test3(data);
    //call_test4(data, "name", "Alice");
    //call_test5(data,"5000","9999");
    //call_test6(data);
    //call_test7(data);
    //call_test8(data,"5000","109");
   // call_test9(data,5000);
    return 0;
}
