#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Function swap
*--------------
* swaps places of two values at given indeces in given char array
*
* arr : given char array
* i : index i
* j : index j*/
void swap(char arr[],int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/*Function reverseArrayHelper
*----------------------------
* Recursively reverses the order of elements in given string
*
* str : given string
* len : length of given string*/
void reverseArrayHelper(char str[], int len)
{
    if(strlen(str) == 1) return;
    if(len > strlen(str)/2)
    {
        swap(str,len-1,strlen(str)-len);
        reverseArrayHelper(str,len-1);
    }
    else return;
}

/*Function reverseArray
*----------------------
* Wrapper function for reverseArrayHelper
* checks that given string length is correct
* on error (given length is incorrect) prints error message
*
* str : given string
* len : length of given string*/
void reverseArray(char str[], int len)
{
    if(len != strlen(str))
    {
        printf("\nError - bad string length\n");
        return;
    }
    else reverseArrayHelper(str,len);
}

/*Functin insertLength
*---------------------
* Recursively replaces all instances of whitespace (starting from index) in given string with the ASCII symbol corresponding to
* the length of the string; e.g if the string is 47 chars long, all spaces will be replaces with '/'.
* on error (string is more than 255 chars long or index is out of range) prints error message.
*
* str : given string
* i : index
*/
void insertLength(char str[],int i)
{
    if((strlen(str) > 255)||(i<0||i>=strlen(str)))
    {
        printf("\nError - String exceeds 255 characters or bad index\n");
        return;
    }
    if(i == (strlen(str)-1)) return;
    else
    {
        if(isspace(str[i])) str[i] = (char)strlen(str);
        insertLength(str,i+1);
    }
}

/*Function main
*--------------
* Demonstrate reverseArray and insertLength with demonstration strings*/
int main(void)
{
    char arr[] = "der si elbat eht dna , elbat eht no si koob ehT";
    printf("\n");
    reverseArray(arr,strlen(arr));
    for(int i =0;i<strlen(arr);i++)
    {
        printf("%c",arr[i]);
    }
    printf("\n");
    insertLength(arr,0);
    for(int i =0;i<strlen(arr);i++)
    {
        printf("%c",arr[i]);
    }
    return 0;
}