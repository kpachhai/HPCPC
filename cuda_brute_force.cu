#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ostream>

// #include <time.h>
#include "md5.h"

#define HASH_LENGTH 33

int forceCrack(char* hash, int maxPassLength); // Cracks the password
void checkPass(char* hash, char* string1); // Compares two hashes
// void forceCrackIn( int * spot_, char * str_, int maxPassLength_, bool *search_, char hash_);

__global__ void forceCrackIn( int * spot_, char * str_, int maxPassLength_, bool *search_, char * alphanum_, int alphanumLength_)
{
	int j, k;
	
	printf("Hello thread %d\n", threadIdx.x);
	if(threadIdx.x == 0){
		printf("%d\n", maxPassLength_);
		printf("%d\n", alphanumLength_);
		printf("%s\n", alphanum_[0]);
	}

	for(j = 0; j < maxPassLength_; j++) 				// For each character in the string
	{
		printf("a from thread %d\n", threadIdx.x);
		printf("spot_[j] = %d from thread %d\n",spot_[j], threadIdx.x);
		if(spot_[j] == alphanumLength_)				// If we're at the last character
		{
			printf("b from thread %d\n", threadIdx.x);
			spot_[j] = 0;						// Reset back to the first
			for(k = 1; k < maxPassLength_; k++)		// And "carry" to the right (Multiple times if multiple carries)
			{
				printf("c from thread %d\n", threadIdx.x);
				if (j+k == maxPassLength_)
				{
					printf("d from thread %d\n", threadIdx.x);
					search_ = false;
					break;
				}
				if(spot_[j+k] < alphanumLength_)
				{
					printf("e from thread %d\n", threadIdx.x);
					spot_[j+k] += 1;
					break;						// Successful carry. Stop.
				}
			}
		}
		if(spot_[j] >= 0)
		{ 
			printf("f from thread %d\n", threadIdx.x);
			printf("alphanum_[spot_[j]] is %c\n", alphanum_[spot_[j]]);
			str_[j] = alphanum_[spot_[j]];
			printf("str_[j] is %c\n", str_[j]);

		}

	} 							// Increment least significant character
}


MD5 md5; // Yes, these are a global variable

int main(int argc, char **argv)
{

	int maxPassLength = 5; // Will not check passwords longer than this
	char hash[33];


	sprintf(hash, "%s",argv[1]);

	std::cout << "Pre force crack" << std::endl;
    forceCrack(hash, maxPassLength); // This does the brute force
    std::cout << "Done!" << std::endl;

    return 0;
}

int forceCrack(char* hash, int maxPassLength)
{
	std::cout << "In force crack" << std::endl;
	char alphanum[62];  							// Character set to check passwords of
	std::cout << "1" << std::endl;

	sprintf(alphanum, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	std::cout << "2" << std::endl;
    // std::cout << alphanum[0] << std::endl;

	int alphanumLength = strlen(alphanum); 		// 62
	// std::cout << alphanumLength << std::endl;
	std::cout << "3" << std::endl;

	char * temp = alphanum;

	int spot[maxPassLength]; 					// Gives you the index into alphanum you should have for each character place
	char str[maxPassLength];					// Test string
	std::cout << "5" << std::endl;

	bool search = true;

	std::cout << "Init Spot and String" << std::endl;
	for (int i = 0; i < maxPassLength; i++) {		// Set initial values for arrays
		spot[i] = -1;
		str[i] = 0;
	}
	spot[0] = 0;

    //---------------------//
	// Cuda Version
	//---------------------//
	// varibles that will need to be accessed by kernel are copied to gpu
	int * spotPtr;
	char  * strPtr;
	const int spotSize = maxPassLength*sizeof(int);
	const int strSize = maxPassLength*sizeof(char);


	// Allocate and Transfer memory to the device
	std::cout << "Starting Cuda Stuff" << std::endl;
	cudaMalloc( (void**)&spotPtr, spotSize ); 
	cudaMalloc( (void**)&strPtr, strSize );
	
	cudaMemcpy( spotPtr, spot, spotSize, cudaMemcpyHostToDevice ); 
	cudaMemcpy( strPtr, str, strSize, cudaMemcpyHostToDevice );

	// Perform the array addition
	// dimBlock defines number of threads kernel will run on
	dim3 dimBlock( maxPassLength );
	// dimGrid defines number of blocks scheduled on different compute units on gpu  
	dim3 dimGrid ( 1 );
	// while (search)
	// {
	std::cout << "Cracking" << std::endl;
		// forceCrackIn( int * spot_, char * str_, int maxPassLength_, bool *search_, char * alphanum_, int alphanumLength_)
	forceCrackIn<<<dimGrid, dimBlock>>>(spotPtr, strPtr, maxPassLength, &search, temp, alphanumLength);
	std::cout << "Done Cracking" << std::endl;
		// Copy the Contents from the GPU
		checkPass(hash, str);				// Checks the string
		spot[0]++; 	
	// }
		cudaMemcpy( str, strPtr, strSize, cudaMemcpyDeviceToHost );
		cudaFree( str );

    // CUDA VERSION DONE //


		return 0;
	}


	void checkPass(char* hash, char* tempString)
	{
		char testHash[HASH_LENGTH];
		int i;
		bool foundPass = false;
		sprintf(testHash, "%s", md5.digestString(tempString));

		printf("%s\n", tempString);
	for (i = 0; i < HASH_LENGTH; i++) {// Checks if the hashes match
		if (testHash[i] != hash[i]) {
			foundPass = false;
			break;
		} else {
			foundPass = true;
		}
	}
	if (foundPass) {
		printf("The password is %s\n", tempString);
		exit(0);
	}
}
