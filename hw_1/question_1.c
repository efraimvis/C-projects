#include <stdio.h>
#include <math.h>
#define M_PI acos(-1.0)

/*Function : factorial
*---------------------
* recursively calculates the factorial of a non negative integer using:
* n! = n(n-1)!
* on error prints error message (if num is negative)
*
* num: non negative integer for which factorial is calculated
*
* returns: unsigned long number representing factorial of num
* returns -1 on error (if num is negative)*/
unsigned long factorial(int num)
{
    if(num >=0)
    {
        if(num == 0) return 1;
        return num*factorial(num-1);
    }
    else
    {
        printf("Error - number must be non negative");
        return -1;
    }
}

/*Function : sint
*----------------
* approximates sin of an angle in radians using the first ten places in the appropriate Taylor series
*
* x : double representing the angle in radians for which sin is calculated
* 
* returns: double representing sin of x*/
double sint(double x)
{
    x = fmod(x,2*M_PI);
    double sum = 0;
    for(int i=0;i<10;i++)
    {
        sum += ((pow(-1,i))*(pow(x,(2*i+1))))/(factorial(2*i+1));
    }
    return sum;
}

/*Faction : main
*---------------
* prompts user to enter an angle in radians, then prints approximation of the sinus of that angle
*/
int main(void)
{
    double angle;
    printf("enter an angle in radians: \n");
    scanf("%lf",&angle);
    double sin = sint(angle);
    printf("sin(%lf) = %.2lf\n",angle,sin);
    return 0;
}