#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <sys/time.h>

using namespace std;

double get_walltime() {
    struct timeval time;
    if(gettimeofday(&time, NULL)) {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}

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
    #pragma acc parallel
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
        string key = "";
        hToCheck[i].pass = key;

	string value = line;            
        hToCheck[i].hash = value;        

        i++;       
    }
    file.close();    
}

void writeFile(hashes * result, char * fileName, int size) { 
	int i;
    ofstream  fileToWriteTo;
    fileToWriteTo.open(fileName); //passlist/convertedHash.txt    
    for(i = 0; i < size; i++) {
    	fileToWriteTo << result[i].pass << ", " << result[i].hash << endl;
    }
    fileToWriteTo.close();
}

int performMainComputation(hashes * record, hashes * hToCheck, hashes * result, int nLinesPFile, int nLinesHFile) {
    int i, j;
    int row = nLinesPFile;
    int col = nLinesHFile;

    if(nLinesPFile < nLinesHFile) {
	row = nLinesHFile;
	col = nLinesPFile;
    }
    #pragma acc data copy(result,record)
    int indexStruct = 0;

    #pragma acc parallel
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            if(record[i].hash.compare(hToCheck[j].hash) == 0) {
		result[indexStruct].pass = record[i].pass;
		result[indexStruct].hash = record[i].hash;
		indexStruct++;
            }
	}
    }

    return indexStruct;
}

void printBenchmark(int nLinesHFile, double readTime, int nPassCracked, double execTime, double writeTime) {
    cout << endl;
    cout << "Read time of the file with " << nLinesHFile << " pass hashes = " << readTime << " seconds" << endl << endl;
    cout << "Total number of passwords cracked = " << nPassCracked << endl;
    cout << "Total execution time for the main computation = " << execTime << " seconds" << endl;
    cout << endl;
    cout << "Write time of the output file = " << writeTime << " seconds" << endl << endl;
}

int main(int argc, char ** argv) {
    char * PFile = argv[1];
    int nLinesPFile = atoi(argv[2]);
    char * HFile = argv[3];
    int nLinesHFile = atoi(argv[4]);
    char * outputFile = argv[5];

    hashes * record = new hashes[nLinesPFile];
    hashes * hToCheck = new hashes[nLinesHFile];
    hashes * result = new hashes[nLinesHFile];
    
    double startReadTime = get_walltime();   
    readPassFile(record, PFile);
    readHashFile(hToCheck, HFile);
    double readTime = get_walltime() - startReadTime;
     
    double startExecTime = get_walltime();
    int nPassCracked = performMainComputation(record, hToCheck, result, nLinesPFile, nLinesHFile);
    double execTime = get_walltime() - startExecTime;

    double startWriteTime = get_walltime();
    writeFile(result, outputFile, nPassCracked);
    double writeTime = get_walltime() - startWriteTime;
 
    printBenchmark(nLinesHFile, readTime, nPassCracked, execTime, writeTime);
   
    return 0;
    
}

