#include <stdio.h>
#include <ctype.h>

/*Function isLetter
*------------------
* Determines whether a given char is a letter
*
* c : given character
*
* returns : 1 if character is a letter, else 0*/
int isLetter(char c)
{
    if((c >= 'A' && c <= 'Z')||(c>= 'a' && c <='z')) return 1;
    return 0;
}

/*Function isDigit
*-----------------
* Determines whether a given char is a digit
*
* c : given char
*
* returns : 1 if char is a digit, else 0*/
int isDigit(char c)
{
    if(c >= '0' && c<= '9') return 1;
    return 0;
}

/*Function order
*---------------
* returns number representing type of given char (letter, digit or other)
* such that 1 represents letters, 2 represents digits and 3 represents all others.
* 
* c : given char for value is returned
*
* returns : int (1,2 or 3) representing type of given char (letter, digit or other - resepectively)*/
int order(char c)
{
    if (isLetter(c)) return 1;
    else if (isDigit(c)) return 2;
    return 3;
}

/*Function swap
*--------------
* Swaps places of two chars at given indeces of given char array
*
* arr : char array
* i : index i
* j : index j*/
void swap(char arr[], int i,int j)
{
    char temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/*Function : ReorderArray
*------------------------
* Reorders a given char array using bubble sort
* such that all letters appear together in the lowest indeces (not necessarily in alphabetical order),
* followed by all digits (not necessarily in numeric order), and then all other characters.
* prints error message if given array size is negative.
*
* arr : character array
* size : size of the char array
*/
void ReorderArray(char arr[], int size)
{
    if(size >=0)
    {
        for(int j = 0;j+1<size;j++)
        {
            for(int i = 0;i+1<size;i++)
            {
                if(order(arr[i+1])<order(arr[i]))
                {
                    swap(arr,i,i+1);
                }
            }
        }
    }
    else printf("\nError - negative array size\n");
}

/*Function : main
*--------------
*demonstrates ReorderArray with demonstration array 
*/
int main(void)
{
    char arr[] = {'s','5','=','r','1','!','t','T','y','9','@','<','4'};
    ReorderArray(arr,sizeof(arr));
    for(int i=0;i<sizeof(arr);i++)
    {
        printf("%c ,", arr[i]);
    }
    return 0;
}