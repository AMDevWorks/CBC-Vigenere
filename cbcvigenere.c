// Created by Andrew Morse

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functional Prototypes
char *plainText(char *text);
int cipherText(char *text, char *key, char *vec, int shft);

int main (int argc, char **argv) {
    long charCount, xCount, xDiff;
    int i = 0;
   
    // Header output with argument value output
    printf("\nCBC Vigenere by Andrew Morse\n");
    fflush(stdout);
    printf("Plaintext file name: %s\n", argv[1]);
    fflush(stdout);
    printf("Vigenere keyword: %s\n", argv[2]);
    fflush(stdout);
    printf("Initialize vector: %s\n\n", argv[3]);
    fflush(stdout);
    
    //If the input file is greeater than 1 open file
    if (argc > 1) {
        
        FILE *file = fopen(argv[1], "r");
        
        char *text = malloc(sizeof(char) * 5000);
        fread(text, sizeof(char), 5000, file);
        
        text = plainText(text);
        charCount = strlen(text);
        
        printf("Clean Plaintext: \n\n%s\n\n", text);
        fflush(stdout);
        
        // If the address exists encrpt text
        if (file != NULL) {
            
            // Conditional for vector value shift
            if (cipherText(text, argv[2], argv[3], i)) {
                i += 6;
                while (cipherText(text, argv[2], text + (i - 6), i))
                    i += 6;
            }
            // Intialize difference and count for pads and sum characters
            xCount = strlen(text);
            xDiff = (xCount - charCount);
            
            printf("Ciphertext:\n\n%s\n", text);
            fflush(stdout);
            fclose(file);
        }
        printf("\nNumber of characters in clean plaintext file: %li\n", charCount);
        fflush(stdout);
        
        printf("Block size = 6\n");
        fflush(stdout);
        
        printf("Number of pad characters added: %li\n\n", xDiff);
        fflush(stdout);
        // Free malloc
        free(text);
    }
    
    return 0;
   
}
// pLain text collection and ASCII value change
char *plainText(char *text) {
    int i;
    int j = 0;
    char *tp = malloc(sizeof(char) * 5000);
    
    for (i = 0; i < strlen(text); ++i) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = text[i] - 'A' + 'a';
        }
        if (text[i] >= 'a' && text[i] <= 'z') {
            tp [j++] = text[i];
        }
    }
    tp [j] = 0;
    return tp;
}
// Compare key length to text and IV vector to shift
int cipherText(char *text, char *key, char *vec, int shft) {
    int i = 0;
    unsigned long  textLen = strlen(text);
    unsigned long  keyLen = strlen(key);
    
    for (i = shft; i < shft + keyLen; ++i) {
        if (i >= textLen)
            text[i] = 'x';
        else
            text[i] = ((text[i] - 'a' + key[i - shft] - 'a' + vec[i - shft] - 'a') % 26) + 'a';
    }
    if (i >= textLen) {
        return 0;
    }
    else {
        return 1;
    }
}
