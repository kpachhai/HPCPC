#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "md5.h"



void hexhash(char *str, char *hash);
void forceCrack(char* hash, int maxPassLength);
void checkPass(char* hash, char* string1);
//bool digCheck(int passLength, char* tempString);

int main(int argc, char *argv[])
{
//	bool foundPass = false;
	int maxPassLength = 7;
	if (maxPassLength > 10) maxPassLength = 10; // Caps brute force at length 10 passwords
	char hash[33];

	if (argc < 2) {
		printf("Please enter the password hash in argv[1]\n");
		return -1;
	}

	printf("Hash to crack: %s\n", argv[1]);
	sprintf(hash, "%s",argv[1]);

	forceCrack(hash, passLength, maxPassLength); // This does the brute force

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
forceCrack(hash, string1, passLength, maxPassLength) {
	int nests = maxPassLength;
	func2(hash, string1, passLength, maxPassLength, nests);



}

func2(hash, string1, passLength, maxPassLength, nests) {
	if (nests > 0) {
		func2(hash, string1, passLength, maxPassLength, nests-1);
	}

	for (n = 0; n < strlen(alphanum); n++) {
		string1[passLength] = alphanum[n];
		checkPass(hash, string1);
	}
	passLength++;
	printf("Finished passwords of length %d\n", passLength);
	forceCrack(hash, string1, passLength, maxPassLength);
	
}

*/

/*
bool forceCrack(char* hash, char* tempString, char* alphanum, int passLength, int maxPassLength, bool *foundPass)
{
	char testHash[33];
	int i, j, k, l;
	static int digCount = 0;
	while (digCount > 0) {
		digCount--;
		for (j = 0; j < strlen(alphanum); j++) {	// For every alphanumerical value
			tempString[passLength-1] = alphanum[j];	// Increment myself
			forceCrack(hash, tempString, alphanum, passLength+1, maxPassLength, foundPass);
			if (*foundPass)								// Return if found
				return *foundPass;
		}
	}

// CHECK EVERYTHING
	tempString[passLength] = '\0';				// Moves the null back one space
	for (i = 0; i < strlen(alphanum); i++) {	// For every alphanumerical value
		tempString[passLength-1] = alphanum[i];
		printf("Testing: %s\n", tempString);	// Prints the value we are testing
getchar();									// For testing purposes only
		hexhash(tempString, testHash);			// Hashes string
		for (k = 0; k < strlen(testHash); k++) {// Corrects spaces TODO: Fix zero problem
			if (testHash[k] == ' ')
				testHash[k] = '0';
		}

		for (l = 0; l < strlen(testHash); l++) {// Checks if the hashes match
			if (testHash[l] != hash[l]) {
				*foundPass = false;
				break;
			} else {
				*foundPass = true;
			}
		}
		if (*foundPass) {
			printf("password: %s\n", tempString);
			return *foundPass;
		}
	}
// UNTIL HERE
	if (passLength != 1 && passLength != maxPassLength && digCheck(passLength, tempString)) { // if all previous digits are z's
		digCount+=passLength;
	}

	if (passLength == 1) {
		for (j = 0; j < strlen(alphanum); j++) {	// For every alphanumerical value
			tempString[passLength-1] = alphanum[j];	// Increment myself
			forceCrack(hash, tempString, alphanum, passLength+1, maxPassLength, foundPass);
			if (*foundPass)								// Return if found
				return *foundPass;
		}
	}
	else
		return *foundPass;
}

bool digCheck(int passLength, char* tempString) {
	int i;
	for (i = 0; i < passLength; i++) {
printf("%c\n", tempString[i]);
		if (tempString[i] != 'z') //TODO: Change from z
			return false;
	}
	return true;
}
*/
