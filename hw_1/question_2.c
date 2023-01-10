#include <stdio.h>

/*Function : maxDigit
*--------------------
* takes a non negative integer n and finds the highest digit in n
* by iteratively comparing the LSD of n to the largest LSD of n found, each time discarding the LSD of n. 
*
* n : non negative integer of which the highest digit is returned
*
* returns : integer representing the highest digit in n
* on error returns -1 and prints an error message*/
int maxDigit(int n)
{
    if(n >= 0)
    {
        int largest = n%10;
        int temp = n;
        while(temp >0)
        {
            if(temp%10 > largest)
            { 
                largest = temp%10;
            }
            temp /= 10;
        }
        return largest;
    }
    else
    {
        printf("Error - number must be positive");
    }
    return -1;
}

/*Function : removeDigit
*-----------------------
* removes all instances of the highest digit from a non negative integer
* by finding the highest digit using maxDigit, then generating a new number
* by iteratively summing the LSD of n multiplied by the appropriate multiple of 10, if the LSD of n is not the highest digit
*
* n: non negative integer representing a number
*
* returns : non negative integer representing a new number, in which all instances of the highest digit in n have been removed
* on error returns -1 (if n is negative)*/
int removeDigit(int n)
{
    if(n >=0)
    {
        int max = maxDigit(n);
        int multiplier = 1;
        int sum = 0;
        while(n >0)
        {
            if(n%10 != max)
            {
                sum += multiplier * (n%10);
                multiplier *= 10;
            }
            n /= 10;
        }
        return sum;
    }
    else 
    {
        printf("Error - number must be positive\n");
        return -1;
    }
}

/*Function : main
*----------------
* prompts user to enter a postive number, then prints a new number representing
* the same number, with all instances of the highest digit of the number removed*/
int main(void)
{
    int remove;
    printf("Enter a positive number: \n");
    scanf("%d",&remove);
    remove = removeDigit(remove);
    if(remove != -1) printf("%d\n",remove);
    return 0;
}