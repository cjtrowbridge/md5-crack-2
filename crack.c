#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "md5.h"

const int PASS_LEN=20;        // Maximum any password can be
const int HASH_LEN=33;        // Length of MD5 hash strings

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    // Hash the guess using MD5
    char *hashedGuess = md5(guess,strlen(guess));
    
    // Compare the two hashesS
    if(strcmp(hash, hashedGuess)==0){
        //returns zero if both strings match
        free(hashedGuess);
        return 0;
    }else{
        free(hashedGuess);
        return 1; 
    }
}

// Read in a file and return the array of strings.
// Use the technique we showed in class to expand the
// array as you go.
char **readfile(char *filename, int *lines)
{
    //get file size
    struct stat st;
    if (stat(filename, &st) == -1)
    {
        fprintf(stderr, "Can't get info about %s\n", filename);
        exit(1);
    }
    int len = st.st_size;
    
    //malloc space for entire file
    char *file = (char *)malloc(len * sizeof(char));
    
    //read entire file into memory
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "Can't open %s for reading\n", filename);
        exit(1);
    }
    fread(file, 1, len, f);
    fclose(f);
    
    //replace \n with \0
    int count = 0;
    for (int i = 0; i <= len; i++)
    {
        if(file[i] == '\n')
        {
            file[i] = '\0';
            count++;
        }
    }
    
    //malloc space for array of pointers
    char ** line = malloc((count+1) * sizeof(char*));
    
    //fill in addresses
    int word = 0;
    line[word] = file; //the first word in the file
    word++;
    for (int i = 1; i < len; i++)
    {
        if(file[i] == '\0' && (i+1) < len)
        {
            line[word] = &file[i + 1]; //the file pointer plus the distance to this newline
            word++;
        }
    }
    
    line[word] = NULL;
    
    //return address of second array
    *lines = word;
    return line;
}


int main(int argc, char *argv[])
{
    
    struct timespec start, stop;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Read the hash file into an array of strings
    int hashCount = 0;
    char **hashes = readfile(argv[1],&hashCount);
    printf("\nCJ's Crackomatic v1\n====================\nHashes To Crack: %d\n",hashCount);
    
    // Read the dictionary file into an array of strings
    int dictCount = 0;
    char **dict = readfile(argv[2], &dictCount);
    printf("Dictionary Size: %d\n====================\n",dictCount);
    
    
    
    
    //BEGIN GLORIOUS IN-MEMORY FUTURE////////////////////////////////////
    /* This doesnt work
    
    //build a hashed dictionary in memory
    char ** dictHashed = malloc((dictCount+1) * sizeof(char*));
    
    //hash the dictionary items and put their addresses into the dictHashed array
    for (int i = 0; i < dictCount; i++)
    {
        char *hash = md5(dict[i],strlen(dict[i]));
        dictHashed[i] = &hash;
    }
    
    */
    //END GLORIOUS IN-MEMORY FUTURE////////////////////////////////////
    
    
    

    // For each hash, try every entry in the dictionary.
    // Print the matching dictionary entry.
    // Need two nested loops.
    for (int i = 0; i < hashCount; i++)
    {
        
        printf("%2d    %s    ",i+1,hashes[i]);
        
        for (int j = 1; j < dictCount; j++)
        {
            if( 
                tryguess(hashes[i],dict[j]) == 0
            ){
                
                printf("%s",dict[j]);
            }
        }
        printf("\n");
    }
    
    //get runtime
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
    double elapsed = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;    // in microseconds
    
    printf("===============\nElapsed Time: %lf sec\n\n",elapsed/1000000);
    
    
}
