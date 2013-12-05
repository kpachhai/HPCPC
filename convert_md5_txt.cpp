// Compile: g++ convert_md5_txt.cpp -o convert -lcrypto -lssl
// Run: ./convert <dictionary file> ie ./convert passlist/hugepasslist.txt
#include <iostream>
#include <fstream>
#include <openssl/md5.h>

using namespace std;

int main(int argc, char** argv)
{
        if(argc != 2)
        {
                cout << "Incorrect parameters" << endl;
                return -1;
        }

        string fileName = argv[1];
        unsigned char digest[16];
        MD5_CTX ctx;
        
        //Opens and reads the list of passwords
        ifstream myfile;
        ofstream outputFile;
        string password;        

        myfile.open(fileName.c_str());
        outputFile.open("passlist/hashlist.txt");        
        if(myfile.is_open())
        {
                while( getline(myfile,password) )
                {        
                        outputFile << password << ",";
                        
                        //Converts the string into a md5 hash        
                        MD5_Init(&ctx);
                            MD5_Update(&ctx, password.c_str(), password.length());        
                        MD5_Final(digest, &ctx);
                        
                        char mdString[33];
                            for (int i = 0; i < 16; i++)
                        {
                                sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
                        }        
                        outputFile << mdString << endl;        
                }
                outputFile.close();
                myfile.close();
        }
                
        else
        {
                cout << "Unable to open file!" << endl;
        }
        
        return 0;
}