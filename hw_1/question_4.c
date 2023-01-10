#include <stdio.h>

/*Function : pyth
*----------------
* prints all pythagorean triples of the form: j^2 + k^2 = i^2, where j,k,i are natural
* and 0<i<100; the function does not display duplicate triples eg. (4 3 5) is displayed but (3 4 5) is not 
*/
void pyth()
{
    for(unsigned int i=1; i<100;i++)
    {
        for(unsigned int j=1;j<=i;j++)
        {
            for(unsigned int k=1;k<=j;k++)
            {
                if(((i*i) == (j*j+k*k))) printf("%3u %3u %3u\n",j,k,i);
            }
        }
    }
}

/*Function : main
*----------------
* calls pyth()
*/
int main(void)
{
    pyth();
    return 0;
}