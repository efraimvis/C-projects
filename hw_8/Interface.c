#include <stdio.h>
#include "hw8.h"

/*Runs menu for interface
*
* return : Returns 0 always
*
* NOTICE TO CHECKER : Please notice that when function reverseFile is called from this interface, if the function ends successfully, the console closes.
* we do not know why this happens, and would appreciate a comment on the matter, if possible*/
int runMenu()
{
    int selection;
    selection = 0;
    while(selection != 6)
    {
        printf("File manipulation :\n\n1)View file(text)\t2)View file(Hex)\t3)Reverse file(exits)\n4)Bend file(encrypt)\t5)Compress file\n6)Exit\nEnter your selection: ");
        scanf("%d", &selection);
        switch(selection)
        {
            case 1:
            {
                char fileName[1000];
                char dummy[2];
                gets(dummy);
                printf("\nPlease enter file name: ");
                gets(fileName);
                printf("\n");
                viewFile(fileName);
                printf("\n");
                break;
            }

            case 2:
            {
                char fileName[1000];
                char dummy[2];
                gets(dummy);
                printf("\nPlease enter file name: ");
                gets(fileName);
                printf("\n");
                viewHex(fileName);
                printf("\n");
                break;
            }

            case 3:
            {
                char fileName[1000];
                char dummy[2];
                gets(dummy);
                printf("\nPlease enter file name: ");
                gets(fileName);
                printf("\n");
                if(reverseFile(fileName)) printf("\nFile reversed successfully!\n");
                else printf("\nCould not reverse file\n");
                printf("\n");
                break;
            }

            case 4:
            {
                char fileName[1000];
                char dummy[2];
                gets(dummy);
                printf("\nPlease enter file name: ");
                gets(fileName);
                printf("\n");
                if(bendFile(fileName)) printf("\nFile encrypted successfully!\n");
                else printf("\nCould not encrypt file\n");
                printf("\n");
                break;
            }

            case 5:
            {
                char fileName[1000];
                char dummy[2];
                gets(dummy);
                printf("\nPlease enter file name: ");
                gets(fileName);
                printf("\n");
                if(compressFile(fileName)) printf("\nFile compressed successfully!\n");
                else printf("\nCould not compress file\n");
                printf("\n");
                break;
            }

            case 6:
            {
                printf("\nGoodbye!\n");
                break;
            }

            default:
            {
                printf("\nInvalid selection\n");
                break;
            }
        }
    }
    return 0;
}

/*Runs a demo program*/
int main(void)
{
    runMenu();
    return 0;
}
