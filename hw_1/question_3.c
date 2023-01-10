#include <stdio.h>
#include <math.h>

/*Function : numOccurs
*---------------------
* finds and returns the number of instances of a digit in a number
* by iteratively comparing the LSD of the number to the digit, and incrementing
* a counter if the LSD matches the digit, the number is then truncated to remove the LSD
*
* number : long int representing a positive number
* digit : integer representing a single non zero digit
*
* returns: positive integer representing the number of instances of a digit in a number
* on error returns -1 (if number is not positive or digit is not singe and nonzero) and prints an error message*/
int numOccurs(long number, int digit)
{
    if(number >0 && (digit >0 && digit <= 9))
    {
        int last = number%10;
        int freq =0;
        while(number > 0)
        {
            last = number%10;
            if(digit == last) ++freq;
            number /= 10;
        }
        return freq;
    }
    else
    {
        printf("\nError - number must be larger than 0 and digit must be single and nonzero\n");
        return -1;
    }
}

/*Function : maxOccurs
*---------------------
* calculates and returns the most frequent digit in a number, ignoring instances of 0;
* if multiple digits have the same frequency, the largest digit is returned
* 
* number: positive long int representing a number for which the most frequent digit is to be returned
*
* returns: positive integer representing the most frequent digit in the number
* on error returns -1 (if number is not positive) and prints an error message*/
int maxOccurs(long number)
{
    if(number > 0)
    {
        long copy = number;
        int last = copy%10;
        int max;
        while(last == 0) // discards trailing zeros
        {
            copy /= 10;
            last = copy%10;
        }
        max = last;
        while(copy >0)
        {
            if(last != 0)
            {
                if(numOccurs(number,last) > numOccurs(number,max))
                {
                    max = last;
                }
                else if (numOccurs(number,last) == numOccurs(number,max))
                {
                    if(last > max) max = last;
                }
            }
            copy /= 10;
            last = copy%10;
        }
        return max;
    }
    else
    {
        printf("\nError - number must be larger than 0\n");
        return -1;
    }  
}

/*Function: delReverse
*---------------------
* takes a postive long integer, and returns a new number representing the number with all instances
* of a specified digit removed, with the digits in reverse order - trailing zeros are discarded
*
* number : positive long int representing number
* digit : positive int representing digit to be removed from number
*
* returns : positive long int representing a number with all instances of a specified digit removed, with digits in reverse order
* on error returns -1 (if number is not positive or digit is not single and nonzero) and prints an error message*/ 
long delReverse(long number,int digit)
{
    if(number > 0 && (digit > 0 && digit <=9))
    {
        long reverse = 0;
        while(number > 0)
        {
            int last = number %10;
            if(last != digit)
            {
                reverse *= 10;
                reverse += last;
            }
            number /= 10;
        }
        return reverse;
    }
    else
    {
        printf("Error - number must be larger than 0 and digit must be single and nonzero\n");
        return -1;
    }
}

/*Function : printDigits
*-----------------------
* takes a positive long integer and prints it's digits by order of frequency - from most to least, ignoring zeros;
* if multiple digits have the same frequency, those digits will be printed from largest to smallest.
* on error prints an error message (if number is non positive)
*
* number: positive long int representing a number  
*/
void printDigits(long number)
{
    if(number > 0)
    {
        printf("\nThe digits are ");
        while(number > 0)
        {
            int freq = maxOccurs(number);
            printf("%d ",freq);
            number = delReverse(number,freq);
        }
    }
    else printf("Error - number must be larger than 0");
}

/*Function : main
*----------------
* prompts user for a number and a digit and displays output of above described functions with given input
*/
int main(void)
{
    long num;
    int digit;
    printf("Enter a positive integer and a positive digit, separated by space: \n");
    scanf("%ld %d",&num,&digit);
    int numocc = numOccurs(num,digit);
    int maxocc = maxOccurs(num);
    long delrev = delReverse(num,digit);
    if(numocc != -1) printf("numOccurs(%ld,%d): %d\n",num,digit,numocc);
    if(maxocc != -1) printf("maxOccurs(%ld): %d\n",num,maxocc);
    if(delrev != -1) printf("delReverse(%ld,%d): %ld\n",num,digit,delrev);
    printDigits(num);
    return 0;
}