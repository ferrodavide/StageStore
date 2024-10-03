#include "Database.hpp"

Database::Database(){
    rocksdb::DB* db;
    rocksdb::Options options;

    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
    if (!status.ok()){
        std::cerr << "Error opening database: " << status.ToString() << std::endl;
        exit(1);
    }
}

Database::~Database(){ delete db; }

