#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mpi.h"     /* For MPI functions, etc */ 
#include "md5.h"



void hexhash(char *str, char *hash); // Gets the strings hash value
// void forceCrack(char* hash, int maxPassLength);
int forceCrack2(char* hash, int maxPassLength, int myRank); // Cracks the password
void checkPass(char* hash, char* string1); // Compares two hashes

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int comm_sz;               // Number of processes
    int myRank;               // My process rank 
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); // Get the number of processes 
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // Get my rank among all the processes 


	int maxPassLength = 3;
	if (maxPassLength > 10) maxPassLength = 10; // Caps brute force at length 10 passwords
	char hash[33];

	if (argc < 2) {
		if (myRank == 0)
			printf("Please enter the password hash in argv[1]\n");
		return -1;
	}

	printf("Hash to crack: %s\n", argv[1]);
	sprintf(hash, "%s",argv[1]);
	forceCrack2(hash, maxPassLength, myRank); // This does the brute force

	MPI_Finalize();
	return 0;
}

void hexhash(char *str, char *hash)
{
	struct MD5Context mdc;
	unsigned char dg[16];
	MD5Init(&mdc);
	MD5Update(&mdc, str, strlen(str));
	MD5Final(dg, &mdc);
	
	sprintf(hash, "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x", 
		dg[0], dg[1], dg[2],
 		dg[3], dg[4], dg[5], dg[6], dg[7], dg[8], dg[9], dg[10], dg[11],	
 		dg[12], dg[13], dg[14], dg[15]);
}

int forceCrack2(char* hash, int maxPassLength, int myRank)
{
	char* alphanum =							// Character set to check passwords of
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";
	int alphanumLength = strlen(alphanum); 		// 62
	int spot[maxPassLength]; 					// Gives you the index into alphanum you should have for each character place
	char str[maxPassLength];					// Test string
	int i, j, k;
	for (i = 0; i < maxPassLength; i++) {		// Set initial values for arrays
		spot[i] = -1;
		str[i] = 0;
	}
	spot[0] = 0;


	if (myRank == 0)  {
		printf("alphanumLength: %d\n", alphanumLength);
		printf("maxPassLength: %d\n", maxPassLength);
	}
	while (true) {
		for(j = 0; j < maxPassLength; j++) 				// For each character in the string
		{
			if(spot[j] == alphanumLength)				// If we're at the last character
			{
				spot[j] = 0;						// Reset back to the first
				for(k = 1; k < maxPassLength; k++)		// And "carry" to the right (Multiple times if multiple carries)
				{
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
	return 0;
}

void checkPass(char* hash, char* tempString)
{
	char testHash[33];
	int k, l;
	bool foundPass = false;

//	printf("Testing: %s\n", tempString);	// Prints the value we are testing
	hexhash(tempString, testHash);			// Hashes string
	for (k = 0; k < strlen(testHash); k++) {// Corrects spaces TODO: Fix zero problem
		if (testHash[k] == ' ')
			testHash[k] = '0';
	}

	for (l = 0; l < strlen(testHash); l++) {// Checks if the hashes match
		if (testHash[l] != hash[l]) {
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

/*
void forceCrack(char* hash, int maxPassLength)
{
	int i, j, k, l, m, n, o, p, q, r;
	char string1[maxPassLength + 1];
	int passLength = 0;
	char alphanum[63] = 
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";

	for (i = 0; i <= sizeof(string1); i++) string1[i] = '\0'; // Sets the string to nulls
	if (passLength < maxPassLength) {			// 1 Length
		for (i = 0; i < strlen(alphanum); i++) {	// For every alphanumerical value
			string1[0] = alphanum[i];
			checkPass(hash, string1);				// Checks the string
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 2 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				checkPass(hash, string1);
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 3 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					checkPass(hash, string1);
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 4 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					for (l = 0; l < strlen(alphanum); l++) {
						string1[3] = alphanum[l];
						checkPass(hash, string1);
					}
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 5 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					for (l = 0; l < strlen(alphanum); l++) {
						string1[3] = alphanum[l];
						for (m = 0; m < strlen(alphanum); m++) {
							string1[4] = alphanum[m];
							checkPass(hash, string1);
						}
					}
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 6 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					for (l = 0; l < strlen(alphanum); l++) {
						string1[3] = alphanum[l];
						for (m = 0; m < strlen(alphanum); m++) {
							string1[4] = alphanum[m];
							for (n = 0; n < strlen(alphanum); n++) {
								string1[5] = alphanum[n];
								checkPass(hash, string1);
							}
						}
					}
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 7 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					for (l = 0; l < strlen(alphanum); l++) {
						string1[3] = alphanum[l];
						for (m = 0; m < strlen(alphanum); m++) {
							string1[4] = alphanum[m];
							for (n = 0; n < strlen(alphanum); n++) {
								string1[5] = alphanum[n];
								for (o = 0; o < strlen(alphanum); o++) {
									string1[6] = alphanum[o];
									checkPass(hash, string1);
								}
							}
						}
					}
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 8 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					for (l = 0; l < strlen(alphanum); l++) {
						string1[3] = alphanum[l];
						for (m = 0; m < strlen(alphanum); m++) {
							string1[4] = alphanum[m];
							for (n = 0; n < strlen(alphanum); n++) {
								string1[5] = alphanum[n];
								for (o = 0; o < strlen(alphanum); o++) {
									string1[6] = alphanum[o];
									for (p = 0; p < strlen(alphanum); p++) {
										string1[7] = alphanum[p];
										checkPass(hash, string1);
									}
								}
							}
						}
					}
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 9 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					for (l = 0; l < strlen(alphanum); l++) {
						string1[3] = alphanum[l];
						for (m = 0; m < strlen(alphanum); m++) {
							string1[4] = alphanum[m];
							for (n = 0; n < strlen(alphanum); n++) {
								string1[5] = alphanum[n];
								for (o = 0; o < strlen(alphanum); o++) {
									string1[6] = alphanum[o];
									for (p = 0; p < strlen(alphanum); p++) {
										string1[7] = alphanum[p];
										for (q = 0; q < strlen(alphanum); q++) {
											string1[8] = alphanum[q];
											checkPass(hash, string1);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}

	if (passLength < maxPassLength) { // 10 Length
		for (i = 0; i < strlen(alphanum); i++) {
			string1[0] = alphanum[i];
			for (j = 0; j < strlen(alphanum); j++) {
				string1[1] = alphanum[j];
				for (k = 0; k < strlen(alphanum); k++) {
					string1[2] = alphanum[k];
					for (l = 0; l < strlen(alphanum); l++) {
						string1[3] = alphanum[l];
						for (m = 0; m < strlen(alphanum); m++) {
							string1[4] = alphanum[m];
							for (n = 0; n < strlen(alphanum); n++) {
								string1[5] = alphanum[n];
								for (o = 0; o < strlen(alphanum); o++) {
									string1[6] = alphanum[o];
									for (p = 0; p < strlen(alphanum); p++) {
										string1[7] = alphanum[p];
										for (q = 0; q < strlen(alphanum); q++) {
											string1[8] = alphanum[q];
											for (r = 0; r < strlen(alphanum); r++) {
												string1[9] = alphanum[r];
												checkPass(hash, string1);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		passLength++;
		printf("Finished passwords of length %d\n", passLength);
	}
	
	printf("Did not find password\n");
}
*/
