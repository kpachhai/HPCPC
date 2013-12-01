#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "mpi.h"     /* For MPI functions, etc */ 
#include "md5.h"

#define HASH_LENGTH 32

void forceCrack(char* hash, int maxPassLength, int myRank, int numOfProcs); // Iterates through possibilities
void checkPass(char* hash, char* string1, int myRank); // Compares two hashes

MD5 md5; // Global variable 

int main(int argc, char **argv)
{
    int numOfProcs;
    int myRank;
	int maxPassLength; // Will not check passwords longer than this
	char hash[32+1];
	
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (argc < 2 || strlen(argv[1]) != 32)
    {
        if (myRank == 0)
		    printf("Please enter the 32 digit password hash in argv[1], not the password we are checking against.\n");
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

    sprintf(hash, "%s",argv[1]);
    maxPassLength = atoi(argv[2]);
    forceCrack(hash, maxPassLength, myRank, numOfProcs); // This does the brute force

	MPI_Finalize();
	return 0;
}

void forceCrack(char* hash, int maxPassLength, int myRank, int numOfProcs)
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
	}
    printf("Processor: %d, Start letter: %d, End letter: %d\n", myRank, startLetter, endLetter); // Debugging info

    if (myRank == 0) // Processor 0 will check all possibilities of length less than maxPassLength in addition to 
                     // its share of maxPassLength size passwords. This is up to a ~50% increase in time for proc 0 in the case
                     // that the password is maxPassLength long and ends a letter that falls between startLetter and endLetter for proc 0
                     // or the password does not exist within maxPassLength.
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
		checkPass(hash, str, myRank);		// Checks the string
		spot[0]++; 							// Increment least significant character
	}
    printf("Processor %d could not find matching hash for words of length %d or less\n", myRank, maxPassLength);
}

void checkPass(char* hash, char* tempString, int myRank)
{
    char testHash[HASH_LENGTH];
	int i;
	bool foundPass = false;
    sprintf(testHash, "%s", md5.digestString(tempString));
    
//    printf("Proc %d: %s\n", myRank, tempString); // Debugging info
	for (i = 0; i < HASH_LENGTH; i++) {// Checks if the hashes match
		if (testHash[i] != hash[i]) {
			foundPass = false;
			break;
		} else {
			foundPass = true;
		}
	}
	if (foundPass) {
		printf("Processor %d found the password: %s\n", myRank, tempString);
        MPI_Finalize();
		exit(0);
	}
} 
