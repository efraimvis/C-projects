#ifndef HW_8_H
#define HW_8_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Creates a new file with reversed order of words in sentences for file with given name, preserving sentence order and starting each new sentence in a new row
*
* fileName - given file name
*
* return : Returns 1 if successful, 0 on error
**/
int reverseFile(const char* fileName);

/*Encrypts a file with given name (bends) as described in assignment into a new file with suffix .bend
*
* fileName - given file name
*
* return : Returns 1 if successful, 0 otherwise*/
int bendFile(const char* fileName);

/*Compresses a file with given name using compressiong algorithm described in assignment
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error*/
int compressFile(const char* fileName);

/*Decompresses a file with given name, and displays the decompressed contents on screen
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error*/
int decompress(const char* fileName);

/*Displays the contents of a file in hexadecimal format (hex dump)
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error*/
int viewHex(const char* fileName);

/*Displays the contents of a file as ascii text
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error*/
int viewFile(const char* fileName);

#endif