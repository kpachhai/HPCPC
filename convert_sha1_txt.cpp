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

        unsigned char digest[SHA_DIGEST_LENGTH];		

    	SHA_CTX ctx;
        
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

    			SHA1_Init(&ctx);
    			SHA1_Update(&ctx, password.c_str(), password.length());
    			SHA1_Final(digest, &ctx);
 
    			char mdString[SHA_DIGEST_LENGTH*2+1];
    			for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        			sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 
    			outputFile << mdString << endl;
 
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


