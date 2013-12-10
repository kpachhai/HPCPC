#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <sstream>
#include <sys/time.h>

#include "leveldb/db.h"

using namespace std;

double get_walltime() {
    struct timeval time;
    if(gettimeofday(&time, NULL)) {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}

string execLinuxCommand(char * cmd) {
    FILE * pipe = popen(cmd, "r");
    if(!pipe) return "ERROR";
    char buffer[128];
    string result = "";
    while(!feof(pipe)) {
	if(fgets(buffer, 128, pipe) != NULL)
	    result += buffer;
    }
    pclose(pipe);
    return result;
}

struct hashes
{
    string hash;
    string pass;
};

void readHashFile(hashes * hToCheck, char * fileName ) {
    ifstream file; 
    string line;
    int i = 0;
    
    file.open(fileName);	
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
    fileToWriteTo.open(fileName);   
    for(i = 0; i < nLinesHFile; i++) {
    	fileToWriteTo << hToCheck[i].pass << ", " << hToCheck[i].hash << endl;
    }
    fileToWriteTo.close();
}

void printBenchmark(int nLinesHFile, double readTime, int nPassCracked, double execTime, double writeTime) {
    cout << endl;
    cout << "Read time of the file with " << nLinesHFile << " pass hashes = " << readTime << " seconds" << endl << endl;
    cout << "Total number of passwords cracked = " << nPassCracked << endl;
    cout << "Total execution time for the main computation = " << execTime << " seconds" << endl;
    cout << endl;
    cout << "Write time of the output file = " << writeTime << " seconds" << endl << endl;

    cout << "Total sequential time = " << readTime + execTime + writeTime << " seconds" << endl << endl;
}

int main(int argc, char ** argv) {
    char * HFile = argv[1];
    int nLinesHFile = atoi(argv[2]);
    char * outputFile = argv[3];
    int i;

    hashes * hToCheck = new hashes[nLinesHFile];
    hashes * result = new hashes[nLinesHFile];
    string databaseDir = "./pass_dir";

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, databaseDir, &db);
    assert(status.ok());

    leveldb::ReadOptions roptions;
    leveldb::Status s;

    double startReadTime = get_walltime();
    readHashFile(hToCheck, HFile);
    double readTime = get_walltime() - startReadTime;

    string password;
    int nPassCracked = 0;
    double startExecTime = get_walltime();
    for(i = 0; i < nLinesHFile; i++) {
	s = db->Get(roptions, hToCheck[i].hash, &password);
	if(s.ok()) {
     	    result[nPassCracked].pass = password;
	    result[nPassCracked].hash = hToCheck[i].hash;
	    nPassCracked++;
	}
    }
    double execTime = get_walltime() - startExecTime;

    double startWriteTime = get_walltime();
    writeFile(result, outputFile, nPassCracked);
    double writeTime = get_walltime() - startWriteTime;

    delete db;   

    printBenchmark(nLinesHFile, readTime, nPassCracked, execTime, writeTime);

    return 0;
}
