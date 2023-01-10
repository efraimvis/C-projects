#ifndef CHECKS_H
#define CHECKS_H

/*Checks if a given string represents a valid personal 9 digit id number 
* 
* string : string representing id number
*
* returns : returns 1 if string is a valid id, 0 otherwise*/
int isValidIdString(char* string);

/*Checks if a given string represents a valid positive numerical string
* 
* string : string representing number
*
* returns : returns 1 if string is a valid positive number, 0 otherwise*/
int isValidNumString(char* string);

/*Checks if a given string represents a valid year
*
* string : string representing year
*
* returns: returns 1 if string is a valid year, 0 otherwise*/
int isValidYear(char* string);

/*Checks if given number has a specified number of digits
*
* num : long int representing given number
* k : char representing number of digits
*
* return : returns 1 if given number has k digits, 0 otherwise*/
int hasNumDigits(long num,int k);

/*count digits of given number
*
* num : long int representing given number
*
* return : returns number of digits*/
int getNumDigits(long num);

/*Checks if given number string has specified number of digits
*
* string : given number string
* k : number of digits
*
* return : returns 1 if number string has speacified number of digits, 0 otherwise*/
int hasNumDigitsString(char* string,int k);

/*Checks if given numerical string is a valid phone number
*
* string : given numerical string 
*
* return : returns 1 if given string represents a valid phone number*/
int isValidPhoneNumber(char* string);

/*Checks if given number is a valid quantity (non negative integer)
*
* num : given number
*
* return : returns 1 if given number is a quantity, 0 otherwise*/
int isValidQuantity(long num);

#endif