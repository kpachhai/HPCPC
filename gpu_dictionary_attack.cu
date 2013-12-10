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

void readPassFile(char **, char ** ,char *);
void readHashFile( char **, char ** ,char *);
void writeFile(string *, string *,  char *, int);

void readPassFile(char * record_pass[], char * record_hash[], char * fileName) {
    int i = 0;
    ifstream file;
    string line;
	
    file.open(fileName); 	//passlist/wordsforsimpletest.txt
    while(getline(file, line)) {
        string key,value;
        istringstream liness(line);
        getline(liness, key, ',');
        getline(liness, value, ',');
        
        char tKey[key.length() + 1];
        char tValue[value.length() + 1];
        strcpy(tKey, key.c_str());
        strcpy(tValue, value.c_str());
        record_pass[i] = (char*) malloc(key.length() + 1);
        record_hash[i] = (char*) malloc(value.length() + 1);
		strncpy(record_pass[i], tKey, key.length()+1);
		strncpy(record_hash[i], tValue, value.length()+1);
        i++;
    }
    file.close();
}

void readHashFile(char ** hToCheck_pass, char ** hToCheck_hash, char * fileName ) {
    ifstream file; 
    string line;
    int i = 0;
    
    file.open(fileName);	//passlist/hashFileToTest.txt
    while(getline(file, line)) {
        string key = "";       
	    string value = line;       
        
        char tKey[key.length() + 1];
        char tValue[value.length() + 1];
        strcpy(tKey, key.c_str());
        strcpy(tValue, value.c_str());
        hToCheck_pass[i] = (char*) malloc(key.length() + 1);
        hToCheck_hash[i] = (char*) malloc(value.length() + 1);
		strncpy(hToCheck_pass[i], tKey, key.length()+1);
		strncpy(hToCheck_hash[i], tValue, value.length()+1);
       i++;       
    }
    file.close();  
}

void writeFile(char ** result_pass, char ** result_hash, char * fileName, int size) { 
	int i;
    ofstream  fileToWriteTo;
    fileToWriteTo.open(fileName); //passlist/convertedHash.txt    
    for(i = 0; i < size; i++) {
        fileToWriteTo << result_pass[i]<< ", " << result_hash[i] << endl;
    }
    fileToWriteTo.close();
}


__device__ int d_strcmp (char * s1, char * s2)
{
	  int ret = 0;
	  while (!(ret = *(unsigned char *) s1 - *(unsigned char *) s2) && *s2) ++s1, ++s2;
	  if (ret < 0)
		ret = -1;
	  else if (ret > 0)
		ret = 1 ;
	  return ret;
}

__global__ void gpuComputation(char ** d_record_pass, char ** d_record_hash, char ** d_hToCheck_pass, char ** d_hToCheck_hash, char ** d_result_pass, char ** d_result_hash, int row) {
	int blockindex = blockIdx.x;
	int threadindex = threadIdx.x;
/*	for(i = 0; i < row; i++) {
		char tempKey[32];
	    for(j = 0; j < 32; j++) {
	    	if(d_record_hash[i][j] == d_hToCheck_hash[threadIdx.x][j]) {
	    		tempKey[j] = d_record_pass[i][j];
	    		printf("h");
	    	}
	    }
*/

   		int res = d_strcmp(d_record_hash[blockindex], d_hToCheck_hash[threadindex]);
   		printf("%c\n", d_record_hash[blockindex][0]);
   		printf("here\n");
	  //  printf("%d %d %d\n", blockindex, threadindex, row);
	    
		if(d_strcmp(d_record_hash[blockindex], d_hToCheck_hash[threadindex]) == 0) {
		    for(int j = 0; j < 32; j++) {
		    	//d_result_pass[threadIdx.x][j] = d_record_pass[blockindex][j];
		    	//d_result_hash[threadIdx.x][j] = d_record_hash[blockindex][j];
		    	printf("%c", d_record_hash[threadIdx.x][j]);
		    }
		    printf("\n");
		}
//	}
}

int performMainComputation(char ** record_pass, char ** record_hash, char ** hToCheck_pass, char ** hToCheck_hash, char ** result_pass, char ** result_hash, int nLinesPFile, int nLinesHFile) {
    int row = nLinesPFile;
    int col = nLinesHFile;

 //   int indexStruct = 0;
 
    int rowSize = row * sizeof(int);
    int colSize = col * sizeof(int);

    char * d_record_pass[nLinesPFile], *d_record_hash[nLinesPFile];
    char * d_hToCheck_pass[nLinesHFile], *d_hToCheck_hash[nLinesHFile];
    char * d_result_pass[nLinesHFile], *d_result_hash[nLinesHFile];
   
   cudaMemcpy(d_record_pass, record_pass, rowSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_record_hash, record_hash, rowSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_hToCheck_pass, hToCheck_pass, rowSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_hToCheck_hash, hToCheck_hash, rowSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_result_pass, result_pass, rowSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_result_hash, result_hash, rowSize, cudaMemcpyHostToDevice);
        
    dim3 blocks(row, 1);
    dim3 grids(col, 1);
    
    for(int i = 0; i < 16; i++)
    	cout << record_pass[i] << " " << d_record_pass[i] << endl;
    
    gpuComputation<<<grids, blocks, 1>>>(d_record_pass, d_record_hash, d_hToCheck_pass, d_hToCheck_hash, d_result_pass, d_result_hash, row);
    cudaDeviceSynchronize();
    
    cudaMemcpy(result_pass, d_result_pass, colSize, cudaMemcpyDeviceToHost);
    cudaMemcpy(result_hash, d_result_hash, colSize, cudaMemcpyDeviceToHost); 

   cudaFree(d_record_pass);	cudaFree(d_hToCheck_pass);	cudaFree(d_result_pass);
   cudaFree(d_record_hash);	 cudaFree(d_hToCheck_hash);	cudaFree(d_result_hash);   
  
/*
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            if(record[i].hash.compare(hToCheck[j].hash) == 0) {
				result[indexStruct].pass = record[i].pass;
				result[indexStruct].hash = record[i].hash;
				indexStruct++;
            }
		}
    }
*/
  return 16;
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

    char * record_pass[nLinesPFile];
    char * record_hash[nLinesPFile];
    char * hToCheck_pass[nLinesHFile];
    char * hToCheck_hash[nLinesHFile];
    char * result_pass[nLinesHFile];
    char * result_hash[nLinesHFile];
        
    double startReadTime = get_walltime();   
    readPassFile(record_pass, record_hash, PFile);
    readHashFile(hToCheck_pass, hToCheck_hash, HFile);
    double readTime = get_walltime() - startReadTime;
 
        
    double startExecTime = get_walltime();
    int nPassCracked = performMainComputation(record_pass, record_hash, hToCheck_pass, hToCheck_hash, result_pass, result_hash, nLinesPFile, nLinesHFile);
    double execTime = get_walltime() - startExecTime;


    double startWriteTime = get_walltime();
//    writeFile(result_pass, result_hash, outputFile, nPassCracked);
    double writeTime = get_walltime() - startWriteTime;

    //printBenchmark(nLinesHFile, readTime, nPassCracked, execTime, writeTime);
  
    return 0;
    
}

