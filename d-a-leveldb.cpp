#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <sstream>
#include "leveldb/db.h"

using namespace std;

struct hashes
{
    string hash;
    string pass;
};

void readHashFile(hashes * hToCheck, char * fileName ) {
    ifstream file; 
    string line;
    int i = 0;
    
    file.open(fileName);	//passlist/hashFileToTest.txt
    while(getline(file, line)) {
        string key = "NOT FOUND";
	string value = line;            
		
        hToCheck[i].pass = key;      
        hToCheck[i].hash = value;  
        i++;       
    }
    file.close();    
}

void writeFile(hashes * hToCheck, char * fileName, int nLinesHFile) { 
    int i;
    ofstream  fileToWriteTo;
    fileToWriteTo.open(fileName); //passlist/convertedHash.txt    
    string compareString = "NOT FOUND";
    for(i = 0; i < nLinesHFile; i++) {
    	if(hToCheck[i].pass.compare(compareString)) {
    		fileToWriteTo << hToCheck[i].pass << ", " << hToCheck[i].hash << endl;
    	}
    }
    fileToWriteTo.close();
}

int main(int argc, char ** argv) {
    string line;
    char * HFile = argv[1];
    int nLinesHFile = atoi(argv[2]);
    char * outputFile = argv[3];
    int i;

    hashes hToCheck[nLinesHFile];
    string databaseDir = "./pass_dir";

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, databaseDir, &db);
    assert(status.ok());

    leveldb::ReadOptions roptions;
    leveldb::Status s;

    readHashFile(hToCheck, HFile);
    string password;
    for(i = 0; i < nLinesHFile; i++) {
	s = db->Get(roptions, hToCheck[i].hash, &password);
	if(s.ok()) {
     	    hToCheck[i].pass = password;
	}
    }

    writeFile(hToCheck, outputFile, nLinesHFile);

    delete db;   
    
    return 0;
}
