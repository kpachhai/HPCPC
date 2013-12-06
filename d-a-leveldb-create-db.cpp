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

    string path = "/home/kpachhai/Downloads/KEYVALUEFILES/";
    string fileNames[26] = {
	path + "alypaa.txt",
	path + "carders.cc.txt",
	path + "elitehacker.txt",
	path + "english.txt",
	path + "facebook-first.1.txt",
	path + "facebook-firstnames.txt",
	path + "facebook-f.last.txt",
	path + "facebook-lastnames.txt",
	path + "facebook-names-unique.txt",
	path + "facebook-pastebay.txt",
	path + "faithwriters.txt",
	path + "fuzzing-strings.txt",
	path + "german.txt",
	path + "hak5.txt",
	path + "honeynet.txt",
	path + "hotmail.txt",
	path + "myspace.txt",
	path + "phpbb.txt",
	path + "porno.txt",
	path + "porn-unknown.txt",
	path + "rockyou.txt",
	path + "singles.org.txt",
	path + "tuscl.txt",
	path + "us_cities.txt"
    };

    string databaseDir = "./pass_dir"; 

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, databaseDir, &db);
    assert(status.ok());

    leveldb::WriteOptions woptions;  
 
    for(int i = 0; i < 26; i++) {
	    char * filename = new char[fileNames[i].length() + 1];
	    strcpy(filename, fileNames[i].c_str());

	    file.open(filename);
	    
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
	    cout << "Completed loading passwords and hashes from " << filename << endl;
    }

    int keyValuePairLength = 0;
    //Read the database
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
	keyValuePairLength++;
    }
    assert(it->status().ok());  // Check for any errors found during the scan
    delete it;

    delete db;
    
    cout << "Total Key Value Pair in database : " << keyValuePairLength << endl;

    return 0;
}
