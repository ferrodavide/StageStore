#include "Database.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{

    return 0;
}




#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <iostream>

rocksdb::DB* db;
rocksdb::Options options;

void init_DB(){
    options.create_if_missing = true;

    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
    if(!status.ok()) std::cerr<<"Error opening database: "<<status.ToString()<<std::endl;
}

void close_DB(){ delete db; }