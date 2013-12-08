#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "mpi.h"     /* For MPI functions, etc */ 
#include "md5.h"
#include <openssl/sha.h>

#define MD5_HASH_LENGTH 32
#define SHA1_HASH_LENGTH 40
#define SHA256_HASH_LENGTH 64

void forceCrack(char* hash, int maxPassLength, int myRank, int numOfProcs, char* hashType); // Iterates through possibilities
void checkPass(char* hash, char* string1, int myRank, char* type); // Compares two hashes

MD5 md5; // Global variable 

int main(int argc, char **argv)
{
    int numOfProcs;
    int myRank;
	int maxPassLength; // Will not check passwords longer than this
	char hashFile[100];
    char hashType[10];
	
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (argc < 2)
    {
        if (myRank == 0)
		    printf("Please enter the file with the hashes to be cracked in argv[1].\n");
        MPI_Finalize();
	    return -1;
	}
    if (argc < 3 || atoi(argv[2]) == 1)
    {
        if (myRank == 0)
            printf("Please enter the max word length to check in argv[2]. Make sure it is higher than 1.\n");
        MPI_Finalize();
	    return -2;
    }
    if (argc < 4)
    {
        if (myRank == 0)
            printf("Please enter the type of hash in argv[3]. Possibilities are: SHA1, SHA256, MD5, BF\n");
        MPI_Finalize();
        return -4;
    }

    sprintf(hashFile, "%s",argv[1]);
    maxPassLength = atoi(argv[2]);
    sprintf(hashType, "%s", argv[3]);
    forceCrack(hashFile, maxPassLength, myRank, numOfProcs, hashType); // This does the brute force

	MPI_Finalize();
	return 0;
}

void forceCrack(char* hashFile, int maxPassLength, int myRank, int numOfProcs, char* hashType)
{
	char alphanum[62+1];  							// Character set to check passwords of
    sprintf(alphanum, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	int alphanumLength = strlen(alphanum); 		// 62
	int spot[maxPassLength]; 					// Gives you the index into alphanum you should have for each character place
	char str[maxPassLength];					// Test string
	int i, j, k;
    bool search = true;
    int startLetter = (int)((double)alphanumLength*((double)(myRank)/(double)numOfProcs));
    int endLetter = (int)((double)alphanumLength*((double)(myRank+1)/(double)numOfProcs) - 1);

	if (myRank == 0)  { // Debugging info
		printf("Size of character set: %d\n", alphanumLength);
		printf("Max length to check: %d\n", maxPassLength);
        printf("File we are checking against: %s\n", hashFile);
	}
    printf("Processor: %d, Start letter: %d, End letter: %d\n", myRank, startLetter, endLetter); // Debugging info

    if (myRank == 0) // Processor 0 will check all possibilities of length less than maxPassLength in addition to 
                     // its share of maxPassLength size passwords. This is around a ~50% increase in time for proc 0
    {
        for (i = 0; i < maxPassLength; i++)		// Set initial values for arrays
        {
            spot[i] = -1;
            str[i] = 0;
        }
    	spot[0] = 0;
    }
    else
    {
    	for (i = 0; i < maxPassLength; i++) {
    		spot[i] = 0;
    		str[i] = 0;
    	}
        spot[maxPassLength-1] = startLetter;
    }

	while (search) {
		for(j = 0; j < maxPassLength; j++) 				// For each character in the string
		{
			if(spot[j] == alphanumLength)				// If we're at the last character
			{
				spot[j] = 0;						// Reset back to the first
				for(k = 1; k < maxPassLength; k++)		// And "carry" to the right (Multiple times if multiple carries)
				{
                    if (j+k == maxPassLength || (j+k == maxPassLength-1 && spot[j+k] == endLetter))
                    {
                        search = false;
                        break;
                    }
					if(spot[j+k] < alphanumLength)
					{
						spot[j+k] += 1;
						break;						// Successful carry. Stop.
					}
				}
			}
			if(spot[j] >= 0)
			{ 
				 str[j] = alphanum[spot[j]];
			}
		}
		checkPass(hashFile, str, myRank, hashType);		// Checks the string
		spot[0]++; 							// Increment least significant character
	}
    printf("Processor %d found all matching hashes for words of length %d or less\n", myRank, maxPassLength);
}

void checkPass(char* hashFile, char* tempString, int myRank, char* type)
{
	int i;
	bool foundPass = false;
    char str[SHA256_HASH_LENGTH+1];
    char testHash[SHA256_HASH_LENGTH+1];

    if (strcmp(type, "MD5") == 0)
    {
        sprintf(testHash, "%s", md5.digestString(tempString));
    }
    else if (strcmp(type, "SHA1") == 0)
    {
        unsigned char binaryHash[SHA_DIGEST_LENGTH];
        unsigned char* sha1String = (unsigned char*)tempString;

        SHA1(sha1String, strlen(tempString), binaryHash);
        for (i = 0; i < SHA_DIGEST_LENGTH; i++)
            sprintf(testHash+2*i, "%02x", binaryHash[i]);
    }
    else if (strcmp(type, "SHA256") == 0)
    {
        unsigned char binaryHash[SHA256_DIGEST_LENGTH];
        unsigned char* sha256String = (unsigned char*)tempString;

        SHA256(sha256String, strlen(tempString), binaryHash);
        for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
            sprintf(testHash+2*i, "%02x", binaryHash[i]);
    }
//    printf("Proc %d: %s\n", myRank, tempString); // Debugging info

    FILE* pFile;
    
    pFile = fopen (hashFile,"r");
    if (pFile == NULL) {
        perror ("Error opening file, aborting\n");
        MPI_Finalize();
        exit(-3);
    }

    while (fscanf (pFile, "%s", str) != EOF)
    {
        foundPass = (strcmp(testHash, str) == 0);
       	if (foundPass) {
    		printf("%s, %s\n", tempString, testHash);
    	}
    }
    fclose (pFile);
} 
