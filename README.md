# Wordcount

## Purpose of the program

Wordcount reads in text, either from a text file or from standard input, counts how many times each word appears in this, and then prints the results either to standard output or to a text file.  It will also output the number of words in the file.

## Compiler Information

- Microsoft (R) Program Maintenance Utility Version 14.12.25835.0
- Microsoft (R) C/C++ Optimizing Compiler Version 19.12.25835 for x86
- Microsoft (R) Incremental Linker Version 14.12.25835.0

## How to use the application

- Open command prompt, and change the directory to the location of the .c and makefile
- Use `nmake wordcount` to build the application
- To execute, use `wordcount -i <input file> -o <output file>`
- Both the input and output files must be .txt documents, located in the same folder as the .c file and makefile.
- If `-i` or `-o` are missing, the program will expect the text to come from the console, or will print to the console respectively
- If you're inputting text using the console, you will need to use <kbd>ctrl</kbd>+<kbd>z</kbd> on a new line and then press <kbd>Enter</kbd> after your text input to indicate that your input has ended
- Using `-c` will cause the program to ignore capitalised letters, so 'language' and 'Language' will both be treated as the same word.