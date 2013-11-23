#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "mpi.h"     /* For MPI functions, etc */ 
#include "md5.h"

#define HASH_LENGTH 33

int forceCrack(char* hash, int maxPassLength, int myRank); // Cracks the password
void checkPass(char* hash, char* string1); // Compares two hashes

MD5 md5; // Yes, these are a global variable

int main(int argc, char **argv)
{
//    MPI_Init(&argc, &argv);

//    int comm_sz;
    int myRank = 0; // Change once using MPI
//    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
//    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);


	int maxPassLength = 5; // Will not check passwords longer than this
	char hash[33];

	if (argc < 2) {
		if (myRank == 0)
			printf("Please enter the password hash in argv[1], not the password we are checking against\n");
//      MPI_Finalize();
		return -1;
	}
    sprintf(hash, "%s",argv[1]);
    forceCrack(hash, maxPassLength, myRank); // This does the brute force

//	MPI_Finalize();
	return 0;
}

int forceCrack(char* hash, int maxPassLength, int myRank)
{
	char* alphanum;  							// Character set to check passwords of
    sprintf(alphanum, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	int alphanumLength = strlen(alphanum); 		// 62
	int spot[maxPassLength]; 					// Gives you the index into alphanum you should have for each character place
	char str[maxPassLength];					// Test string
	int i, j, k;
    bool search = true;
	for (i = 0; i < maxPassLength; i++) {		// Set initial values for arrays
		spot[i] = -1;
		str[i] = 0;
	}
	spot[0] = 0;


	if (myRank == 0)  {
		printf("alphanumLength: %d\n", alphanumLength);
		printf("maxPassLength: %d\n", maxPassLength);
	}
	while (search) {
		for(j = 0; j < maxPassLength; j++) 				// For each character in the string
		{
			if(spot[j] == alphanumLength)				// If we're at the last character
			{
				spot[j] = 0;						// Reset back to the first
				for(k = 1; k < maxPassLength; k++)		// And "carry" to the right (Multiple times if multiple carries)
				{
                    if (j+k == maxPassLength)
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
		checkPass(hash, str);				// Checks the string
		spot[0]++; 							// Increment least significant character
	}
    if (myRank == 0)
    {
        printf("Could not find matching hash for words of length %d or less\n", maxPassLength);
    }
//    MPI_Finalize();
	return 0;
}

void checkPass(char* hash, char* tempString)
{
    char testHash[HASH_LENGTH];
	int i;
	bool foundPass = false;
    sprintf(testHash, "%s", md5.digestString(tempString));
    
//    printf("%s\n", tempString);
	for (i = 0; i < HASH_LENGTH; i++) {// Checks if the hashes match
		if (testHash[i] != hash[i]) {
			foundPass = false;
			break;
		} else {
			foundPass = true;
		}
	}
	if (foundPass) {
		printf("The password is: %s\n", tempString);
		exit(0);
	}
} 
