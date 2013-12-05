#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include "leveldb/db.h"

using namespace std;

int main(int argc, char ** argv) {
    string line;
    string hashValue = argv[1];

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./pass_dir", &db);
    assert(status.ok());

    leveldb::ReadOptions roptions;

    string password;
    leveldb::Status s = db->Get(roptions, hashValue, &password);
    if(s.ok()) cout << "The password is " << password << endl;
    else cout << "Couldn't match the password in the dictionary" << endl;
    delete db;   
    
    return 0;
}
