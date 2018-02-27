/*  Author: Jason Halley
    Date of Last Modification: 20/02/2018
    Purpose: wordcount reads an input and determines how many times each word appears in the input, it also displays the number of unique words in the input*/

//include statements for required standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//global variables
char *inFile = "stdin";
char *outFile = "stdout";
int useStdIn = 1;
int useStdOut = 1;
int ignoreCase = 0;
int numberOfWords = 0;
int uniqueWords = 0;
int maxWords = 2000;
char data[20000];
struct word{
    char *name;
    int count;
};
struct word word_array[2000];

/*  Function: readFile
    Args: none
    Returns: none
    Purpose: Reads the supplied text file into data, or reads input from stdin into data*/
void readFile(){
    //if text file is provided, open it in read mode and add the text to data line by line
    if(useStdIn == 0){
        FILE* file = fopen(inFile, "r");
        char line[1024];
        data[0] = '\0';

        while (fgets(line, sizeof(line), file) != NULL) {
            strcat(data, line);
        }

    fclose(file);
    }
    //reads line by line into data from stdin if no text file was provided
    else{
        char line[1024];
        data[0] = '\0';
        printf("Please type your intput, press ctrl+z followed by enter when you're finished");
        while (fgets(line, sizeof(line), stdin) != NULL) {
            strcat(data, line);
        }
    }
}

/*  Function: tokeniseAnalyse
    Args: none
    Returns: none
    Purpose: Separates the text into individual words, then finds if it's a new word, if it is adds it to the array of words with a frequency of one.
    If it's not a new word, incraments the frequency of the matching word*/
void tokeniseAnalyse(){
    char *token;
    //gets the first token
    token = strtok(data, " ,.\n?\t");
    int newWord = 1;
    while (token != NULL) {
        //prints each token if program is compiled in debug mode
        #ifdef DEBUG
        printf("\ntoken: %s\n", token);
        #endif
        //go through whole array
        for(int count = 0; count < maxWords; count++){
            //if any word in array match token, set new word flag to 0, incraments the count of the matched word
            if (word_array[count].name != NULL) {
                if(strcmp(word_array[count].name, token) == 0){
                    newWord = 0;
                    word_array[count].count ++;
                }
            }
        }

        //if word doesn't exist in array, set it as a new instance in the lowest index of the array that's empty
        if(newWord == 1){
            for(int count = 0; count < maxWords; count++){
                if(word_array[count].name == NULL){
                    word_array[count].name = token;
                    word_array[count].count ++;
                    break;
                }
            }
			uniqueWords++;
        }
        token = strtok(NULL, " ,.\n?\t");
        numberOfWords ++;
        newWord = 1;
    }
}

/*  Function: printResult
    Args: none
    Returns: none
    Purpose: prints the results to the supplied output textfile, or to stdout if no textfile was supplied*/
void printResult(){
    if(useStdOut == 0){
        //opens the supplied file in write mode, prints the results, then closes the file
        FILE *file2 = fopen(outFile, "w");
        fprintf(file2, "\nData analysed, Results are as follows: \n");
        fprintf(file2, "Total word count: %d\n", numberOfWords);
        //prints as many record from the array as there are unique words
        for(int count = 0; count < uniqueWords; count++){
        fprintf(file2, "%s: %d\n", word_array[count].name, word_array[count].count);
    }
    fclose(file2);
    }
    else{
        printf("\nData analysed, Results are as follows: \n");
        printf("Total word count: %d\n", numberOfWords);
        for(int count = 0; count < uniqueWords; count++){
        printf("%s: %d\n", word_array[count].name, word_array[count].count);
    }
    }
    
}

/*  Function: main
    Args: int argc(number of arguements), char argv(content of arguements)
    Returns: int 0(indicates program ran successfully)
    Purpose: determines the command line arguements, then calls the other functions in order*/
int main(int argc, char **argv){
    //prits a debug mode warning if program is compiled in debug mode
    #ifdef DEBUG
    printf("Debug mode enabled, not for real use.\n");
    #endif

    //searches the arguements for an input file, output file, or ignore case flag
    for(int i = 0; i < argc; ++i){
        if(strcmp(argv[i], "-i") == 0){
            useStdIn = 0;
            inFile = argv[i + 1];
        }

        if(strcmp(argv[i], "-o") == 0){
            useStdOut = 0;
            outFile = argv[i + 1];
        }

        if(strcmp(argv[i], "-c") == 0){
            ignoreCase = 1;
        }
    }

    //ensures every record in the array is cleared
    for(int i = 0; i < maxWords; i++){
        word_array[i].name = NULL;
        word_array[i].count = 0;
    }

    //prints the status of the input file, output file, and ignore case flags
    printf("Input file: %s\n", inFile);
    printf("Output file: %s\n", outFile);
    printf("Ignore case: %d\n", ignoreCase);

    readFile();
    //cancels all data to lower case if the -c arguement was used
    if(ignoreCase == 1){
        for(int i = 0; data[i]; i++){
            data[i] = tolower(data[i]);
        }
    }
    //prints the raw data that was read in if compiled in debug mode
    #ifdef DEBUG
    printf("\nSupplied data: %s", data);
    #endif

    tokeniseAnalyse();
    printResult();

    //returns 0 to show the program ran successfully
    return 0;
}