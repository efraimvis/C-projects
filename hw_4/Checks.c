#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Checks if a given string represents a valid positive numerical string
* 
* string : string representing number
*
* returns : returns 1 if string is a valid positive number, 0 otherwise*/
int isValidNumString(char* string)
{
    if(string!= NULL)
    {
        int i;
        for(i=0;i<strlen(string);i++)
        {
            if(isdigit(string[i]) == 0) return 0;
        }
        return 1;
    }
    return 0;
}

/*Checks if a given string represents a valid personal 9 digit id number 
* 
* string : string representing id number
*
* returns : returns 1 if string is a valid id, 0 otherwise*/
int isValidIdString(char* string)
{
    if(isValidNumString(string))
    {
        if(strlen(string) == 9) return 1;
    }
    return 0;
}

/*Checks if a given string represents a valid year
*
* string : string representing year
*
* returns: returns 1 if string is a valid year, 0 otherwise*/
int isValidYear(char* string)
{
    if(isValidNumString(string))
    {
        if(strlen(string) == 4)
        {
            if(strcmp(string,"1886") >= 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

/*Checks if given number has a specified number of digits
*
* num : long int representing given number
* k : char representing number of digits
*
* return : returns 1 if given number has k digits, 0 otherwise*/
int hasNumDigits(long num,int k)
{
    if(k >= 0)
    {
        char counter;
        counter = 0;
        while(num != 0)
        {
            num = num/10;
            counter++;
        }
        if(k == counter) return 1;
        else return 0;
    }
    return 0;
}

/*count digits of given number
*
* num : long int representing given number
*
* return : returns number of digits*/
int getNumDigits(long num)
{
    char counter;
    counter = 0;
    while(num != 0)
    {
        num = num/10;
        counter++;
    }
    return counter;
}

/*Checks if given number string has specified number of digits
*
* string : given number string
* k : number of digits
*
* return : returns 1 if number string has a speacified number of digits, 0 otherwise*/
int hasNumDigitsString(char* string,int k)
{
    if(k >=0)
    {
        if(isValidNumString(string))
        {
            if(strlen(string) == k) return 1;
        }
    }
    return 0;
}

/*Checks if given numerical string is a valid phone number
*
* string : given numerical string 
*
* return : returns 1 if given string represents a valid phone number*/
int isValidPhoneNumber(char* string)
{
    if(hasNumDigitsString(string,9) || hasNumDigitsString(string,10))
    {
        if(string[0] == '0')
        {
            if(strlen(string) == 9)
            {
                char second;
                second = string[1];
                if((second == '2') || (second == '3') || (second == '4') || (second == '8') || (second == '9')) return 1;
            }
            else
            {
                if(string[1] == '5') return 1;
            }
        }
    }
    return 0;
}

/*Checks if given number is a valid quantity (non negative integer)
*
* num : given number
*
* return : returns 1 if given number is a quantity, 0 otherwise*/
int isValidQuantity(long num)
{
    if(num >=0) return 1;
    else return 0;
}