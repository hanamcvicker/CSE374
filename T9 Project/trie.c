/* Copyright [2022] <Hana McVicker>
 * CSE374, HW5, 22wi
 * 11/28/2022
 *
 * trie.c creates a tree made of trieNodes that contains
 * words from a given dictionary file that can be accessed
 * with a numeric sequence. This program also frees dynamically
 * allocated data before the program terminates
 */

// Header files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// Helper functions
char changeCharacter(char c);
int* createNumbers(char *c);
trieNode* make_trienode();
trieNode* insert_trie(trieNode* root, char* word);

// This function takes in a character c as a parameter and
// returns the T9 number (minus 1) associated with the
// character.
char changeCharacter(char c) {
  if ((c == 97) || (c == 98) || (c == 99)) {
    return 1;
  } else if ((c == 100) || (c == 101) || (c == 102)) {
    return 2;
  } else if ((c == 103) || (c == 104) || (c == 105)) {
    return 3;
  } else if ((c == 106) || (c == 107) || (c == 108)) {
    return 4;
  } else if ((c == 109) || (c == 110) || (c == 111)) {
    return 5;
  } else if ((c == 112) || (c == 113) || (c == 114)
    || (c == 115)) {
    return 6;
  } else if ((c == 116) || (c == 117) || (c == 118)) {
    return 7;
  } else if ((c == 119) || (c == 120) || (c == 121)
    || (c == 122)) {
    return 8;
  } else {
    return 0;
  }
}

// This function takes in a pointer to the word character
// as a parameter and returns the word as an array of
// integers, which contains the T9 number pattern
// associated with the given dictionary word.
int* createNumbers(char *word) {
    int *wordNumber = malloc(sizeof(int)*(strlen(word)));
    for (int i = 0; i < strlen(word); i++) {
        wordNumber[i] = changeCharacter(word[i]);
    }
    return wordNumber;
}

// This function has no parameters
// Makes a trieNode with 9 branches and returns the
// empty node
trieNode* make_trienode() {
  trieNode* node = (trieNode*)malloc(sizeof(trieNode));
  for (int i = 0; i < BRANCHES; i++) {
    node->branches[i] = NULL;
  }
  node->word = NULL;
  return node;
}

// This function takes in a pointer to the current node (root)
// and a pointer to the word. It then creates the number
// branches associated with the word based on the T9 value of
// each character. Once the trie creates the number branch for
// the word, it stores the word at the end of the branch. The
// trieNode created then gets returned
trieNode* insert_trie(trieNode* root, char* word) {
  trieNode* temp = root;
  int *wordNums;
  wordNums = createNumbers(word);
  for (int i=0; word[i] != '\0'; i++) {
    int index = wordNums[i];
    if (temp->branches[index] == NULL) {
      temp->branches[index] = make_trienode();
    }
    temp = temp->branches[index];
    }
  while (temp->word != NULL) {
    if (temp->branches[0] == NULL) {
      temp->branches[0] = make_trienode();
    }
    temp = temp->branches[0];
  }
  temp->word  = (char*)malloc((strlen(word)+1));
  strncpy(temp->word, word, strlen(word)+1);
  free(wordNums);
  return root;
}

// This function takes in a pointer to the trieNode
// root and the pointer to the number pattern
// It then traverses through the number pattern to
// get the corresponding branch and returns the word
// at the end of the branch. If the number pattern
// given is not stored in the tree or does not have
// a word associated with the given number pattern,
// it returns a not found statement to the user.
// If the number pattern ends in '#', it will return
// the word stored at that node if there is one. If the
// pattern contains a character that is not 2-9 or '#',
// it also returns a not found statement to the user
char* get_word(trieNode *root, char *pattern) {
  trieNode* temp = root;
  for (int i=0; pattern[i] != '\0'; i++) {
    if (pattern[i] == '#') {
      if (temp->branches[0] != NULL) {
        temp = temp->branches[0];
      } else {
        return "There are no more T9onyms";
      }
      if (i == strlen(pattern)-1) {
        if (temp->word != NULL) {
          return temp->word;
        } else {
          return "Not found in current dictionary";
        }
      }
    } else if (!(pattern[i] > 49  &&  pattern[i] <= 57)) {
      return "Not found in current dictionary";
    } else {
      int  N = (pattern[i] - '0');
      N = N - 1;
      if (temp->branches[N] != NULL) {
        temp = temp->branches[N];
        if ((i == strlen(pattern) - 1)) {
          if (temp->word != NULL) {
          return temp->word;
          } else {
            return "Not found in current dictionary";
          }
        }
      }
    }
  }
  return "Not found in current dictionary.\n";
}

// This function takes in a pointer to the dictionary file
// as a parameter and builds the tree using the words from
// the dict file. It then returns the built trie
trieNode* build_tree(FILE *dict) {
  char dword[MAXLEN];
  trieNode* root = make_trienode();
  while (fgets(dword, MAXLEN, dict) != NULL) {
    if ((dword[strlen(dword) - 1]) == '\n') {
      dword[strlen(dword) - 1] = '\0';
    }
    root = insert_trie(root, dword);
  }
  return root;
}

// This function takes in a pointer to the
// trieNode root and frees the dynamically
// allocated data in the nodes and the words in
// the nodes of the tree (deletes the tree spanning
// from the root)
void free_tree(trieNode* root) {
  if (root == NULL) {
    return;
  }
  for (int i = 0; i < BRANCHES; i++) {
    free_tree(root->branches[i]);
  }
  if (root->word != NULL) {
    free(root->word);
  }
  free(root);
  root = NULL;
}

