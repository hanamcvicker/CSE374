/* Copyright [2022] <Hana McVicker>
 * CSE374
 * 11/7/2022
 * This file creates a version of the unix command wc
 * Reads in a file and reports the number of lines,
 * number of words, and number of characters depending 
 * on whether the user inputs -l, -c, or -w
 * If the user does not input one of these commands, 
 * it will display all three and the total number of lines
 * If less than one file is given, the program will throw an error
 * The program will also throw an error if the file is not readable
*/ 

// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Forward Declarations
int countLines(char *file_to_open);
int countChars(char *file_to_open);
int countWords(char *file_to_open);

int main(int argc, char** argv) {
// Throws error is there in not an input file
  if (argc < 2) {
    fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
    return EXIT_FAILURE;
  }

// initializing variables to store line sum and starting
// index of the input command and first file
  char *input_command = argv[1];
  int start_fileinput = 0;
  int lineSum = 0;
  int *plineSum = &lineSum;

// If the second argument in command line is not a wordcount
// command, start the index at second argument
  if (strncmp(input_command, "-l", 500) == 0 || strncmp
  (input_command, "-w", 500)  == 0 || strncmp(input_command, "-c", 500) == 0) {
    start_fileinput = 2;
  } else {
      start_fileinput = 1;
  }

// If there is a wc command but not a file, throws error
  if ((start_fileinput == 2) && (argc < 3)) {
    fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
    return EXIT_FAILURE;
  }
// outputs the lines, characters, and/or words depending on
// which wordcount command function is written
// If not function is written, the output will print
// all three functions and the name of the file,
// plus thee total sum of lines if multiple files are
// included
  for (int i = start_fileinput; i < argc; i++) {
    char *file_to_open = argv[i];
    FILE *file = fopen(file_to_open, "r");
    if (file) {
      fclose(file);
      int lines = countLines(file_to_open);
      int words = countWords(file_to_open);
      int count = countChars(file_to_open);
      if (strncmp(input_command, "-l", 500) == 0) {
        printf("%d\n", lines);
        } else if (strncmp(input_command, "-w", 500) == 0) {
        printf("%d\n", words);
      } else  if (strncmp(input_command, "-c", 500) == 0) {
        printf("%d\n", count);
      } else {
        printf("%d, %d, %d, %s\n", lines, words, count, file_to_open);
        *plineSum = *plineSum +lines;
      }
    }  else {
         fprintf(stderr, "%s will not open.  Skipping.\n", file_to_open);
    }
    if (*plineSum >  0) {
      printf("Total Lines = %d\n", *plineSum);
    }
  }
  return EXIT_SUCCESS;
}

// Takes in pointer to the file from the main method
// Counts total number of lines in the file
int countLines(char *file_to_open) {
  FILE *file = fopen(file_to_open, "r");
  char c = 0;
  int lines = 0;
  while ((c = getc(file)) != EOF) {
    if (c == '\n') {
      lines++;
    }
  }
  return lines;
  fclose(file);
}

// Takes in pointer to the file from the main method
// Counts total number of characters in the file
int countChars(char *file_to_open) {
  FILE *file = fopen(file_to_open, "r");
  int count = 0;
  while (getc(file) != EOF) {
    count++;
  }
  return count;
  fclose(file);
}

// Takes in pointer to the file from the main method
// Counts total number of words in the file
int countWords(char *file_to_open) {
  FILE *file = fopen(file_to_open, "r");
  char c = 0;
  int words  = 0;
  int prev = 0;
  while ((c = fgetc(file)) != EOF) {
    if (!(isspace(c))) {
      prev = 1;
    } else if (isspace(c)) {
      if (prev == 1) {
        words++;
        prev = 0;
      }
    }
  }
  return words;
  fclose(file);
}
