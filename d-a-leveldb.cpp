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
    bool found = false;

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./pass_dir", &db);
    assert(status.ok());

    leveldb::ReadOptions roptions;

    leveldb::Iterator* it = db->NewIterator(roptions);
    for(it->SeekToFirst(); it->Valid(); it->Next()) {
        leveldb::Slice sD = it->key();
        leveldb::Slice tD = it->value();
        string key_str = sD.ToString();
        string val_str = tD.ToString();
        if(hashValue.compare(key_str) == 0) {
            found = true;
            cout << "The password is " << val_str << endl;
            break;
        }
    }
    delete it;
    delete db;
    
    if(!found)
        cout << "Couldn't match the password in the dictionary" << endl;
    
    return 0;
}
