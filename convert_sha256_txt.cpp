// Compile: g++ convert_sha256_txt.cpp -o convert -lcrypto -lssl
// Run: ./convert <dictionary file> ie ./convert passlist/hugepasslist.txt
#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>

using namespace std;

double get_walltime() {
    struct timeval time;
    if(gettimeofday(&time, NULL)) {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}

string sha256(const string str);

int main(int argc, char** argv)
{	
        string fileName = argv[1];
	char * outputFileName = argv[2];

        unsigned char digest[16];
        
        //Opens and reads the list of passwords
        ifstream myfile;
        ofstream outputFile;
        string password;  
	double readTime;      

        myfile.open(fileName.c_str());
        outputFile.open(outputFileName);        
        if(myfile.is_open())
        {
		double startReadTime = get_walltime();
                while( getline(myfile,password) )
                {        
                        outputFile << password << ",";
			
			string shaString;
			shaString = sha256(password);			
 			
			outputFile << shaString << endl;        
                }
		readTime = get_walltime() - startReadTime;
                outputFile.close();
                myfile.close();
        }
                
        else
        {
                cout << "Unable to open file!" << endl;
        }

	cout << "Sha1 dictionary created in: " << readTime << " seconds" << endl;
        
        return 0;
}

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
