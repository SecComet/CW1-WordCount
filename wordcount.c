#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *inFile = "stdin";
char *outFile = "stdout";
int ignoreCase = 0;
int numberOfWords = 0;
char data[20000];
struct word{
    char *name;
    int count;
};
struct word word_array[2000];

void readfile(){
    FILE* file = fopen(inFile, "r");
    char line[1024];
    data[0] = '\0';

    while (fgets(line, sizeof(line), file) != NULL) {
        strcat(data, line);
    }

    fclose(file);
}

void tokenise_analyse(){
    char *token;
    token = strtok(data, " ,.\n?\t");
    int newWord = 1;
    while (token != NULL) {
        #ifdef DEBUG
        printf("\ntoken: %s\n", token);
        #endif
        //go through whole array
        for(int count = 0; count < 2000; count++){
            //if any word in array match token, set new word flag to 0
            if (word_array[count].name != NULL) {
                if(strcmp(word_array[count].name, token) == 0){
                    newWord = 0;
                    word_array[count].count ++;
                }
            }
        }

        if(newWord == 1){
            for(int count = 0; count < 2000; count++){
                if(word_array[count].name == NULL){
                    //numberOfWords ++;
                    word_array[count].name = token;
                    word_array[count].count ++;
                    break;
                }
            }
        }
        token = strtok(NULL, " ");

    }

    for(int i = 0; i < 2000; i++){
        if (word_array[i].name != NULL){
            numberOfWords ++;            
        }
    }


}

void printResult(){
    if(strcmp(outFile, "stdout") != 0){
        FILE *file;
        fopen(outFile, "w");
        fprintf(file, "\nData analysed, Results are as follows: \n");
        fprintf(file, "Total word count: %d\n", numberOfWords);
        for(int count = 0; count < numberOfWords; count++){
        fprintf(file, "%s: %d\n", word_array[count].name, word_array[count].count);
    }
    fclose(file);
    }
    else{
        printf("\nData analysed, Results are as follows: \n");
        printf("Total word count: %d\n", numberOfWords);
        for(int count = 0; count < numberOfWords; count++){
        printf("%s: %d\n", word_array[count].name, word_array[count].count);
    }
    }
    
}

int main(int argc, char **argv){
    #ifdef DEBUG
    printf("Debug mode enabled, not for real use.\n");
    #endif

    for(int i = 0; i < argc; ++i){
        if(strcmp(argv[i], "-i") == 0){
            inFile = argv[i + 1];
        }

        if(strcmp(argv[i], "-o") == 0){
            outFile = argv[i + 1];
        }

        if(strcmp(argv[i], "-c") == 0){
            ignoreCase = 1;
        }
    }

    for(int i = 0; i < 1999; i++){
        word_array[i].name = NULL;
        word_array[i].count = 0;
    }

    printf("Input file: %s\n", inFile);
    printf("Output file: %s\n", outFile);
    printf("Ignore case: %d\n", ignoreCase);

    readfile();
    if(ignoreCase == 1){
        for(int i = 0; data[i]; i++){
            data[i] = tolower(data[i]);
        }
    }
    #ifdef DEBUG
    printf("\nSupplied data: %s", data);
    #endif

    tokenise_analyse();
    printResult();

    return 0;
}