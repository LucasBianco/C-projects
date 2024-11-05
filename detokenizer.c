#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10000
int length = 0, greatest_word_size = 0;

int check_NULL_file(FILE *file);
void fprint_words_output(FILE *output_file, FILE *file, char tokenized_words[length][MAX_LEN]);

int main(int argv, char *argc[]){
    // initializing variable that will store the length of all words that were tokenized, and local variable for conditions
    int i = 0;
    // declaring the two file variables, the one we are going to read and the output file
    FILE *file, *output_file;
    // declaring the string variables: the file_text, that will store the words being read in the file
    // the file name that is gping to be read, and the file that is going to contain the output of the program
    char  file_text[MAX_LEN], file_name[MAX_LEN], output_file_name[MAX_LEN];
    // copying the text that was inputted in the command line ,
    // the first word after ./a.out is the file name that is going to be read
    strcpy(file_name, argc[1]); 
    // the second word after ./a.out is the file name of the output
    strcpy(output_file_name, argc[2]);

    file = fopen(file_name, "r");
    if(check_NULL_file(file)) return 1;

    fscanf(file, "%d", &length);
   
    char tokenized_words[length][MAX_LEN];

    while(!ferror(file) && !feof(file) && i < length){
        if(fscanf(file, "%s\n", file_text) == 1){
            strcpy(tokenized_words[i], file_text);
            i++;
            if(strlen(file_text) > greatest_word_size)    greatest_word_size = strlen(file_text);
            
        }
    }

    output_file = fopen(output_file_name, "w");
    if(check_NULL_file(output_file)) return 1;
    
    fprint_words_output(output_file, file, tokenized_words);
    
    fclose(file);
    fclose(output_file);

    return 0;
}

int check_NULL_file(FILE *file){// function that will check if the file was NULL

    if (file == NULL) { // if the file is NULL
        printf("Error, not able to open the file!\n"); // print that there was an error
        return 1; // return 1, meaning that the file was NULL
    }
    return 0; // return 0, meaning that the file opened
}

void fprint_words_output(FILE *output_file, FILE *file, char tokenized_words[length][MAX_LEN]){
    //char token[greatest_word_size];
    //char line_array[256][MAX_LEN];
    char line[256];
    int tokens_array[length];
    char *ch, word_test[length];
    
    int i = 0, k = 0, len_tokens_array = 0;
    char first_element[greatest_word_size];
    strcpy(first_element, tokenized_words[0]);

    while (fgets(line, sizeof(line), file)) {
        // Increment line number for each line read
        
        for(ch = line; *ch != '\0'; ch++){
            
            if(*ch == ' '){
                word_test[k] = '\0';
                tokens_array[i] = atoi(word_test);
                len_tokens_array++;
                i++;
                k = 0;
                strcpy(word_test,"");
                continue;
            }
            word_test[k] = *ch;
            k++;
            
        }
        tokens_array[i] = 0;
        i++;
        len_tokens_array++;
    }
    
    
    for(i=0; i < len_tokens_array; i++){
        
        if(tokens_array[i] == 0){
            fprintf(output_file,".\n");
        }
        else if(i == 0 || tokens_array[i - 1] == 0){
            fprintf(output_file,"%s", tokenized_words[tokens_array[0] - 1]);
        } 
        else if(tokens_array[i] == 1){
            fprintf(output_file, " %s", first_element);
        }
        else{
            fprintf(output_file," %s", tokenized_words[tokens_array[i] - 1]);
        }
    }

}

