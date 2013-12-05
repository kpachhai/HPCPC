#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <ostream>

using namespace std;

struct hashes
{
    char * hash;
    char * pass;
};

void readPassFile(hashes *, char *);
void readHashFile(hashes *, char *);
void writeFile(hashes *, char *, int);

void readPassFile(hashes * record, char * fileName) {
	int i = 0;
	ifstream file;
	string line;
	
    file.open(fileName); 	//passlist/wordsforsimpletest.txt
    while(getline(file, line)) {
        string key,value;
        istringstream liness(line);
        getline(liness, key, ',');
        getline(liness, value, ',');
            
        record[i].pass = new char[key.size() + 1];
        copy(key.begin(), key.end(), record[i].pass);
        record[i].pass[key.size()] = '\0';

        record[i].hash = new char[value.size() + 1];
        copy(value.begin(), value.end(), record[i].hash);
        record[i].hash[value.size()] = '\0';          
        i++;
    }
    file.close();
}

void readHashFile(hashes * hToCheck, char * fileName ) {
    ifstream file; 
    string line;
    int i = 0;
    
    file.open(fileName);	//passlist/hashFileToTest.txt
    while(getline(file, line)) {
        string key = "NOT FOUND";
		string value = line;            
		
        hToCheck[i].pass = new char[key.size() + 1];
        copy(key.begin(), key.end(), hToCheck[i].pass);
        hToCheck[i].pass[key.size()] = '\0';
        

        hToCheck[i].hash = new char[value.size() + 1];
        copy(value.begin(), value.end(), hToCheck[i].hash);
        hToCheck[i].hash[value.size()] = '\0';   
        i++;       
    }
    file.close();    
}

void writeFile(hashes * hToCheck, char * fileName, int nLinesHFile) { 
	int i;
    ofstream  fileToWriteTo;
    fileToWriteTo.open(fileName); //passlist/convertedHash.txt    
    for(i = 0; i < nLinesHFile; i++) {
    	if(strcmp(hToCheck[i].pass, "NOT FOUND") != 0) {
    		fileToWriteTo << hToCheck[i].pass << ", " << hToCheck[i].hash << endl;
    	}
    }
    fileToWriteTo.close();
}

int main(int argc, char ** argv) {
 	char * PFile = argv[1];
 	int nLinesPFile = atoi(argv[2]);
 	char * HFile = argv[3];
 	int nLinesHFile = atoi(argv[4]);
 	char * outputFile = argv[5];

    hashes * record = new hashes[nLinesPFile];
    hashes * hToCheck = new hashes[nLinesHFile];
    int i, j;
    
    readPassFile(record, PFile);
    readHashFile(hToCheck, HFile);
    
    for(i = 0; i < nLinesPFile; i++) {
        if(strcmp(record[i].hash, hToCheck[i].hash) == 0) {
        	string password = record[i].pass;
     		hToCheck[i].pass = new char[password.size() + 1];
        	copy(password.begin(), password.end(), hToCheck[i].pass);
        	hToCheck[i].pass[password.size()] = '\0';
        }
    }

	writeFile(hToCheck, outputFile, nLinesHFile);
    
    return 0;
    
}

