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
    string hash;
    string pass;
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
            
        record[i].pass = key;
        record[i].hash = value;        
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
        hToCheck[i].pass = key;

	string value = line;            
        hToCheck[i].hash = value;        

        i++;       
    }
    file.close();    
}

void writeFile(hashes * hToCheck, char * fileName, int nLinesHFile) { 
	int i;
    ofstream  fileToWriteTo;
    fileToWriteTo.open(fileName); //passlist/convertedHash.txt    
    for(i = 0; i < nLinesHFile; i++) {
 	string notFound = "NOT FOUND";
    	if(hToCheck[i].pass.compare(notFound) != 0) {
		cout << hToCheck[i].pass << "," << hToCheck[i].hash << endl;
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
        if(record[i].hash.compare(hToCheck[i].hash) == 0) {
	    hToCheck[i].pass = record[i].pass;
        }
    }

	writeFile(hToCheck, outputFile, nLinesHFile);
    
    return 0;
    
}

