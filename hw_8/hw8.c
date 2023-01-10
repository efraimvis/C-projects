#include "hw8.h"

/*Generates a new file name string with a given suffix
*
* fileName - given file name
* suffix - given suffix
*
* return : Returns a new string representing new file name, with desired suffix - on error returns NULL*/
char* appendSuffix(const char* fileName,const char* suffix)
{
    if(fileName)
    {
        int len;
        char* newFile_name;
        len = strlen(fileName);
        newFile_name = (char*)malloc(len+strlen(suffix)+1);
        if(!newFile_name)
        {
            printf("\nMemory allocation error\n");
            return NULL;
        }
        strcpy(newFile_name,fileName);
        strcat(newFile_name,".");
        strcat(newFile_name, suffix);
        return newFile_name;
    }
    return NULL;
}

/*Reverses the word order in a given sentence
*
* sentence - given sentence
*
* return : Returns string representing reversed sentence*/
char* reverseSentence(const char* sentence)
{
    if(sentence)
    {
        char* reverse;
        int wordStart;
        int wordEnd;
        int len;
        int i,j;
        len = strlen(sentence);
        reverse = (char*)malloc(strlen(sentence)+2);
        if(!reverse)
        {
            printf("\nError - could not allocate memory\n");
            return NULL;
        }
        wordStart = len-1;
        wordEnd = len-1;
        i = 0;
        while(wordStart > 0)
        {
            if(isspace(sentence[wordStart]))
            {
                int j;
                j = wordStart+1;
                while(j <= wordEnd)
                {
                    reverse[i] = sentence[j];
                    j++;
                    i++;
                }
                reverse[i++] = ' ';
                wordEnd = wordStart-1;
            }
            wordStart--;
        }
        for(j=0;j<= wordEnd;j++)
        {
            reverse[i] = sentence[j];
            i++;
        }
        while(reverse[i-1] == 0 || isspace(reverse[i-1])) i--;
        reverse[i] = '.';
        reverse[i+1] = '\0';
        return reverse;
    }
    else printf("\nError - sentence string is null\n");
    return NULL;
}

/*Creates a new file with reversed order of words in sentences for file with given name, preserving sentence order and starting each new sentence in a new row
*
* fileName - given file name
*
* return : Returns 1 if successful, 0 on error
**/
int reverseFile(const char* fileName)
{
    if(fileName != NULL)
    {
        FILE *file, *newFile;
        char* newFile_name;
        file = fopen(fileName,"r");
        if(!file)
        {
            printf("\nError - could not open file\n");
            return 0;
        }
        newFile_name = appendSuffix(fileName,"rpl");
        newFile = fopen(newFile_name,"w");
        if(!newFile)
        {
            printf("\nError - could not open file\n");
            return 0;
        }

        while(!feof(file))
        {
            char buff[1000];
            char* reverse;
            int i,c;
            i=0;
            while((c = getc(file)) != '.')
            {
                buff[i] = c;
                i++;
            }
            buff[i] = '\0';
            reverse = reverseSentence(buff);
            /**
            fprintf(newFile,"%s\n",reverseSentence(buff));
            **/
            fprintf(newFile, "%s\n",reverse);
            free(reverse);
            reverse = NULL;
            fflush(newFile);
        }
        free(newFile_name);
        newFile_name = NULL;
        fclose(file);
        fclose(newFile);
        return 1;
    }
    else
    {
        printf("\nError - no file name\n");
    }
    return 0;
}

/*Encrypts a file with given name (bends) as described in assignment into a new file with suffix .bend
*
* fileName - given file name
*
* return : Returns 1 if successful, 0 otherwise*/
int bendFile(const char* fileName)
{
    if(fileName)
    {
        int fileLength;
        int i;
        char curr;
        FILE *file, *newFile;
        char* newFile_name;
        newFile_name = appendSuffix(fileName, "bend");
        file = fopen(fileName,"r");
        if(!file)
        {
            printf("\nError - could not open file %s\n", fileName);
            return 0;
        }
        newFile = fopen(newFile_name,"w");
        if(!newFile)
        {
            printf("\nError - could not open file %s\n",newFile_name);
            return 0;
        }
        fseek(file,0,SEEK_END);
        fileLength = ftell(file);
        fseek(file,0,SEEK_SET);

        if(fileLength % 2 == 0)
        {
            i=0;
            while(i < fileLength/2)
            {
                fseek(file,i,SEEK_SET);
                curr = fgetc(file);
                fputc(curr,newFile);
                fseek(file,-(i+1),SEEK_END);
                curr = fgetc(file);
                fputc(curr,newFile);
                i++;
            }
            fflush(newFile);
        }
        else
        {
            i=0;
            while(i<(fileLength-1)/2)
            {
                fseek(file,i,SEEK_SET);
                curr = fgetc(file);
                fputc(curr,newFile);
                fseek(file,-(i+1),SEEK_END);
                curr = fgetc(file);
                fputc(curr,newFile);
                i++;
            }
            fseek(file,(fileLength-1)/2,SEEK_SET);
            curr = fgetc(file);
            fputc(curr,newFile);
        }
        free(newFile_name);
        newFile_name = NULL;
        fclose(file);
        fclose(newFile);
        return 1;
    }
    else printf("\nError - null filename string\n");
    return 0;
}

/*Finds the value of a character in given array (its index)
*
* values - array of characters
* letter - given character
*
* return : Returns value (index) of given character in array, if not found returns 0*/
char getValue(unsigned char values[16],unsigned char letter)
{
    int i;
    for(i=0;i<16;i++)
    {
        if(values[i] == letter) return i;
    }
    return 0;
}

/*Creates an array of characters representing compression scheme for a given sentence (as described in assignment)
*
* sentence - given sentence
*
* return : Returns an array of characters representing compression scheme for sentence*/
unsigned char* generateValues(const char* sentence)
{
    if(sentence)
    {
        int i,j;
        unsigned char* values;
        values = (unsigned char*)calloc(17,sizeof(unsigned char));
        for(i=0;i<16;i++)
        {
            values[i] = 0;
        }
        for(i=0;i<strlen(sentence);i++)
        {
            j=0;
            while(values[j] != 0)
            {
                if(sentence[i] == values[j]) break;
                j++;
            }
            if(j >= 16)
            {
                printf("\nError - too many distinct characters in sentence, cannot compress\n");
                exit(1);
            }
            values[j] = sentence[i];
            values[16] = j+1;
        }
        return values;
    }
    else printf("\nError - null sentence string\n");
    return NULL;
}

/*Generates an array of characters representing a compressed sentence
*
* sentence - given sentence
*
* return : Returns an array of characters representing a compressed sentence if successful, NULL on error*/
unsigned char* compressSentence(const char* sentence)
{
    if(sentence)
    {
        int i,j;
        unsigned char* values;
        unsigned char* compressed;
        values = generateValues(sentence);
        compressed = (unsigned char*)malloc(strlen(sentence)/2);
        if(!compressed)
        {
            printf("\nError - could not allocate memory\n");
            return NULL;
        }

        j=0;
        if(strlen(sentence) % 2 == 0)
        {
            for(i=0;i<strlen(sentence);i += 2)
            {
                compressed[j] = (getValue(values,sentence[i])<<4)|(getValue(values,sentence[i+1]));
                j++; 
            }
        }
        else
        {
            for(i=0;i<strlen(sentence)-1;i += 2)
            {
                compressed[j] = (getValue(values,sentence[i])<<4)|(getValue(values,sentence[i+1]));
                j++; 
            }
            compressed[j] = getValue(values,sentence[i])<<4;
        }
        return compressed;
    }
    else printf("\nError - sentence string is null\n");
    return NULL;
}

/*Compresses a file with given name using compressiong algorithm described in assignment
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error
* NOTICE : This version of the function compresses a file such that it can be decoded afterwards, you are welcome to test this,
* though it was not requested in the assignment
int compressFile(const char* fileName)
{
    if(fileName)
    {
        FILE *file, *newFile;
        char* newFile_name;
        file = fopen(fileName,"r");
        if(!file)
        {
            printf("\nError - could not open file %s\n", fileName);
        }
        newFile_name = appendSuffix(fileName,"rds");
        newFile = fopen(newFile_name, "wb");
        if(!newFile)
        {
            printf("\nError - could not open file %s\n", newFile_name);
        }
        while(!feof(file))
        {
            char line[1000];
            unsigned char* separator;
            unsigned char* sentence;
            unsigned char* values;
            fgets(line,1000,file);
            if(line[strlen(line)] == '\n') line[strlen(line)] = '\0';
            if(strlen(line) %2 != 0)
            {
                int i;
                for(i=0;i<strlen(line);i++) printf("%x ",line[i]);
                printf("\nError - odd number of characters in line, cannot compress\n");
                exit(1);
            }
            values = generateValues(line);
            sentence = compressSentence(line);
            separator = (unsigned char*)calloc(values[16],sizeof(char));
            fwrite(values+16,sizeof(unsigned char),1,newFile);
            fwrite(values,sizeof(unsigned char),values[16],newFile);
            fwrite(sentence,sizeof(unsigned char),strlen(line)/2,newFile);
            fwrite(separator,sizeof(unsigned char),values[16],newFile);
            free(separator);
            separator = NULL;
            fflush(newFile);
        }
        free(newFile_name);
        newFile_name = NULL;
        fflush(newFile);
        fclose(file);
        fclose(newFile);
        return 1;
    }
    else printf("\nError - bad file name\n");
    return 0;
}*/

/*Compresses a file with given name using compressiong algorithm described in assignment, into an undecipherable .rds file
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error*/
int compressFile(const char* fileName)
{
    if(fileName)
    {
        FILE *file, *newFile;
        char* newFile_name;
        file = fopen(fileName,"r");
        if(!file)
        {
            printf("\nError - could not open file %s\n", fileName);
        }
        newFile_name = appendSuffix(fileName,"rds");
        newFile = fopen(newFile_name, "wb");
        if(!newFile)
        {
            printf("\nError - could not open file %s\n", newFile_name);
        }
        while(!feof(file))
        {
            char line[1000];
            unsigned char* sentence;
            unsigned char* values;
            fgets(line,1000,file);
            if(line[strlen(line)] == '\n') line[strlen(line)] = '\0';
            if(strlen(line) %2 != 0)
            {
                int i;
                for(i=0;i<strlen(line);i++) printf("%x ",line[i]);
                printf("\nError - odd number of characters in line, cannot compress\n");
                exit(1);
            }
            values = generateValues(line);
            sentence = compressSentence(line);
            fwrite(values+16,sizeof(unsigned char),1,newFile);
            fwrite(values,sizeof(unsigned char),values[16],newFile);
            fwrite(sentence,sizeof(unsigned char),strlen(line)/2,newFile);
            fflush(newFile);
        }
        free(newFile_name);
        newFile_name = NULL;
        fflush(newFile);
        fclose(file);
        fclose(newFile);
        return 1;
    }
    else printf("\nError - bad file name\n");
    return 0;
}

/*Finds character with given value (index) in given array
*
* values - character array
* value - given value (index) of character*/
char getLetter(unsigned char* values, unsigned char value)
{
    if(values)
    {
        return values[value];
    }
    else printf("\nError - null values array\n");
    return -1;
}

/*Decodes (more accurately decompresses) a single compressed sentence
*
* values - given array of characters representing compression scheme
* compressed - character array representing compressed sentence, with trailing zeros included
* compressedLength - length of actual compressed sentence, excluding trailing zeros
*
* return : Returns decoded sentence if successful, NULL on error*/
char* decodeSentence(unsigned char* values, unsigned char* compressed,int compressedLength)
{
    if(values && compressed)
    {
        char* sentence;
        int i,j;
        j=0;
        sentence = (char*)malloc((compressedLength*2)+1);
        for(i=0;i<compressedLength;i++)
        {
            sentence[j] = getLetter(values,((compressed[i]>>4)&0x0f));
            sentence[j+1] = getLetter(values,(compressed[i]&0x0f));
            j += 2;
        }
        sentence[j] = '\0';
        return sentence;
    }
    else printf("\nError - bad parameters\n");
    return NULL;
}

/*Decompresses a file with given name, and displays the decompressed contents on screen
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error
* NOTICE : This function will only work with files compressed by the commented out version of compressFile*/
int decompress(const char* fileName)
{
    if(strlen(fileName)>= 5)
    {
        if(fileName[strlen(fileName)-1] == 's' && fileName[strlen(fileName)-2] == 'd' && fileName[strlen(fileName)-3] == 'r' && fileName[strlen(fileName)-4] == '.')
        {   
            FILE *file;
            int fileLength;
            file = fopen(fileName,"rb");
            if(!file) 
            {
                printf("\nError - could not open file %s\n", fileName);
                return 0;
            }
            fseek(file,0,SEEK_END);
            fileLength = ftell(file);
            fseek(file,0,SEEK_SET);
            while(fileLength >= 0)
            {
                unsigned char separator[1];
                unsigned char values[17];
                unsigned char compressed[1000];
                int compressedLength;
                unsigned char i;
                int j;
                i=0;
                j=0;
                fread(separator, sizeof(unsigned char), 1, file);
                fread(values,sizeof(unsigned char),separator[0],file);
                fileLength -= (separator[0]+1);
                while(i < separator[0])
                {
                    fread(compressed+j,sizeof(unsigned char),1,file);
                    fileLength--;
                    if(compressed[j] == 0) i++;
                    else i = 0;
                    j++;
                }
                compressedLength = j-separator[0];
                printf("%s\n", decodeSentence(values,compressed,compressedLength));
                fileLength--;
            }

            fclose(file);
            return 1;
        }
        else printf("\nError - file must be of format .rds\n");
    }
    else printf("\nError - bad file name\n");
    return 0;
}

/*Displays the contents of a file in hexadecimal format (hex dump)
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error*/
int viewHex(const char* fileName)
{
    if(fileName)
    {
        FILE *file;
        long int len;
        file = fopen(fileName,"rb");
        if(!file) 
        {
            printf("\nError - could not open file %s\n",fileName);
            return 0;
        }
        fseek(file,0,SEEK_END);
        len = ftell(file);
        fseek(file,0,SEEK_SET);
        while(len > 0)
        {
            unsigned char letter[1];
            fread(letter,sizeof(unsigned char),1,file);
            printf("%x ", letter[0]);
            len--;
        }

        fclose(file);
        return 1;
    }
    else printf("\nError - bad file name\n");
    return 0;
}

/*Displays the contents of a file as ascii text
*
* fileName - name of given file
*
* return : Returns 1 if successful, 0 on error*/
int viewFile(const char* fileName)
{
    if(fileName)
    {
        FILE *file;
        long int len;
        file = fopen(fileName, "r");
        if(!file)
        {
            printf("\nError - could not open file %s\n", fileName);
            return 0;
        }
        fseek(file,0,SEEK_END);
        len = ftell(file);
        fseek(file,0,SEEK_SET);
        while(len > 0)
        {
            printf("%c",fgetc(file));
            len--;
        }
        fclose(file);
        return 1;
    }
    else printf("\nError - bad file name\n");
    return 0;
}
