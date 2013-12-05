#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "leveldb/db.h"

using namespace std;

int main(int argc, char ** argv) {
    ifstream file; 
    string line;
    char * fileName = argv[1];
    
    file.open(fileName);

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./pass_dir", &db);
    assert(status.ok());

    leveldb::WriteOptions woptions;
    
    while(getline(file, line)) {
        string pass,hash;
        istringstream liness(line);
        getline(liness, pass, ',');
        getline(liness, hash, ',');
          
        leveldb::Slice s = hash;
        leveldb::Slice t = pass;    
        db->Put(woptions,s,t);   
    }
    file.close();

    delete db;
    
    return 0;
}
