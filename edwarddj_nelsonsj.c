/*
 * David Edwardson & Steven Nelson
 * CS 352 Lab 1 - Fall 2018 
 * Code Generation and File Validation
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

typedef unsigned short ushort;
typedef unsigned int uint32;
typedef unsigned long uint64;

uint32 getCode(char*, int);
bool testValidity(char*, uint32);
long getBytes(char*);

int main(){

	char fileA[256];
	char fileB[256];
	char again[256];

	printf("Enter filename: ");
	scanf("%s", fileA);
	long bytesA = getBytes(fileA);
	uint32 someCode;

	if (bytesA != NULL){
		someCode = getCode(fileA, bytesA);
	} 

//Loop forever
	while (1){
		printf("Enter another fileName for validation with %s: \n", fileA);
		scanf("%s", fileB);
		long bytesB = getBytes(fileB);
		if (bytesB != NULL){
			if (testValidity(fileB, someCode)){
				printf("Validation: Success! They have the same contents.\n");
			
			} else {
				printf("Validation: Fail -> files have different contents \n");
			}

			printf("Again? Enter 'Y' for yes: ");
			scanf("%s", again);

			if (strcmp(again, "Y") == 0){
				continue;
			} else {
				break;
			}
		}
	} // end of while
 
 return 0;
}


/* send file in -> 32-bit code returned */
uint32 getCode(char* file, int count){

	/* count = byte count */
	char* buffer; //put 32-bits of file in a buffer
	
	register  uint64 total = 0;
	FILE* f = fopen(file, "rb");

	int i = 0;

	if (f != NULL){
		buffer =(char*)malloc(count + 1);
		fread(buffer, count, 1, f);
		fclose(f);	
	}
	
	int tempInt = 0;
	int byte = 8;
	uint32 theBits = 0;
	
	//int bitCount;
	uint32 tempBits;

	
	while (count--){		
			tempBits = buffer[count];
			tempInt = buffer[count];
			// Shift in iterations of one byte
			theBits = theBits | tempBits << (i * byte);
			
			//Add a byte
			i++;

			// We have reached 32 bits, so reset i
			if (i == 4){
				i = 0;
				//Now add our 32 bit chunk to the total
				total += theBits;

				// Check for overflow, so shift right 32 bits.
				int tempInt = total >> 32;
				// Returns true if we have anything left after the shift
				if (tempInt >= 1){
					// Bitwise AND with all 1's
					total = total & UINT_MAX;
					total += 1;
				}
				
				tempInt = 0;
			}
	}
	//Ones compliment of total
	total = ~total;
	printf("Calculated Code: %x (in hex)\n", total);
	free(buffer);
	return total;
}

bool testValidity(char* newFile, uint32 someCode){
	int count;
	count = getBytes(newFile);
	return (getCode(newFile, count) == someCode);
}

long getBytes(char* file){
	long bytes;
	FILE* f = fopen(file, "rb");
	if (f){
		for (bytes = 0; getc(f) != EOF; bytes++);
	} else {
		printf("No such file or directory.\n", strerror());
		exit(0);
	}
	


	fclose(f);
	return bytes;
}
