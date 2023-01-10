#include <stdio.h>
#include <string.h>

/*Function : encrypt
*-------------------
* takes an uppercase latin character and returns the lowercase version of the letter
* some positive integer distance k away, such that the distance wraps around, eg. Z with distance
* 2 becomes b.
*
* letter : char representing an uppercase latin letter
* k : positive integer representing some distance
*
* returns: lowercase version of the character k places away from the input letter, wrapping around the alphabet;
* on error returns 0 (if letter is not uppercase or k is not positive), and prints an error message
*/
char encrypt(char letter,int k)
{
    if((letter >= 65 && letter <= 90) && (k > 0))
    {
        return(97+((letter-65+k)%26));
    }
    else
    {
        printf("\nError - letter must be uppercase and key must be positive\n");
        return 0;
    }
}

/*Function : decrypt
*-------------------
* takes a lowercase latin character and returns the uppercase version of the letter
* some positive integer distance k away, such that the distance wraps around, eg. z with distance
* 2 becomes B.
*
* letter : char representing a lowercase latin letter
* k : positive integer representing some distance
*
* returns: uppercase version of the character k places away from the input letter, wrapping around the alphabet;
* on error returns 0 (if letter is not lowercase or k is not positive), and prints an error message
*/
char decrypt(char letter, int k)
{
    if((letter >= 97 && letter <= 122) && (k>0))
    {
        return(65+((letter-97+(26-k))%26));
    }
    else
    {
        printf("\nError - letter must be lowercase and key must be positive\n");
        return 0;
    }
}

/*Function : encrypt_text
*------------------------
* promts user for a positive encryption key, then for a plaintext string of uppercase letters, performs a Caesar shift of the string with the key,
* and prints the result in lowercase letters; if non positive key is given, an error message is printed and the user is prompted to enter a valid key;
* if some chars in the plaintext string are not uppercase, an error message is printed; the plaintext string is assumed to be 256 chars or less
*/
void encrypt_text()
{
    int k;
    printf("Please enter encryption key :\n");
    scanf("%d",&k);
    while(k < 1) // prompts user to enter a valid key if the key entered is not positive 
    {
        printf("Error - encryption key must be positive, try again: \n");
        scanf("%d",&k);
    }
    char plaintext[256];
    printf("Please enter plaintext in uppercase letters only (max length 256 chars): \n");
    scanf("%s",plaintext);
    char cypher[256];
    strcpy(cypher,plaintext);
    int flag = 0;
    for(int i=0;i<strlen(plaintext);i++) //iterates over plaintext
    {
        if(plaintext[i] >= 65 && plaintext[i] <= 90) cypher[i] = encrypt(cypher[i],k); // if letter is uppercase, encrypt the letter by k
        else // rejects non uppercase letters
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0) printf("%s\n",cypher); // prints encrypted string
    else printf("Error - some letters were not uppercase\n"); // prints error message
}

/*Function : main
*----------------
* calls encrypt_text
*/
int main(void)
{
    encrypt_text();
    return 0;
}