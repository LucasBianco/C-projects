// Lucas Araujo Bianco
// U74104714
// This program is based on the logic of machine learning algorithms where they tokenize the words
// In this program, it will receive an input of a file with many words, and the program will output
// how many unique words are, and sort them in an ascending order, according to the token assigned to them.


#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000 // defining constant variable of the maximuum length for the string arrays and variables
int max_word_length = 0; // defining global variable that will be used to store the maximum length of letters of the words collected


// declaring the functions for the 
int store_unique_str_variables(char str_array[][MAX_LEN], char *text, int n);
int remove_sp_characters(char *text);
int check_NULL_file(FILE *file);
void sorting_string_arrays(char a[][MAX_LEN], int n);
int convert_word_into_token(char *text, char token_array[][MAX_LEN], int n);

// Main Function
int main(int argv, char *argc[]){

    // declaring the two file variables, the one we are going to read and the output file
    FILE *file, *output_file;
    // declaring the string variables: the file_text, that will store the words being read in the file
    // the file name that is gping to be read, and the file that is going to contain the output of the program
    char file_text[MAX_LEN], file_name[MAX_LEN], output_file_name[MAX_LEN];
    // copying the text that was inputted in the command line
    // the first word after ./a.out is the file name that is going to be read
    strcpy(file_name, argc[1]); 
    // the second word after ./a.out is the file name of the output
    strcpy(output_file_name, argc[2]);

    // opening the file to be read and storing it at file
    file = fopen(file_name, "r");
    if(check_NULL_file(file)) return 1; // calling function that check if the file opened is null, 
    // if so it will print that it couldn't read and return 1
    
    // finding how many words there are in the file, so we can initialize the array
    int words = 0; // declaring the variable that will store the quantity of words
    while(!ferror(file) && !feof(file)){ // it will read while there is no reading error
        if (fscanf(file, "%s", file_text) == 1){ // if a word has been read 
            words++; // this word is counted in the variable
        }
    }
   
    
    // restarting the file, to restart the reading of the words
    rewind(file); 
    char all_words[words][MAX_LEN]; // declaring the string array with the quantity of words found and the constant variable
    int len = 0; // declaring the variable that will count how many unique elements were added in the string array all_words
    while(!ferror(file) && !feof(file)){// it will read while there is no reading error
        if (fscanf(file, "%s", file_text) == 1){
            // adding the unique words in the array, by calling the function
            if(store_unique_str_variables(all_words, file_text, len)) len++;
            // if it was added (the function returned 1), the word will be counted in the length variable
        }
    }
   

    // sorting the string array of all the words
  
    sorting_string_arrays(all_words, len);

    


    // writing the elements in the output_file
    output_file = fopen(output_file_name, "w");// opening the file to write elements and storing it at the output file
    if(check_NULL_file(output_file)) return 1;// calling function that check if the file opened is null, 
    // if so it will print that it couldn't read and return 1
    
    int k; // declaring the local variable for the for loop
    fprintf(output_file,"%d\n", len); // printing the qunatity of unique elements in the output file
    for(k = 0; k < len; k++){ // starting the for loop that will print all the unique elements in the output file
        fprintf(output_file,"%s\n", all_words[k]);
    }

    
    rewind(file); // restarting the file, to be read again
    // tokenizing the words in the file based on the sorting string array:
    while(!ferror(file) && !feof(file)){ // it will read while there is no reading error
        if (fscanf(file, "%s", file_text) == 1){
            // if a word was read, it will check if there is any special characters ('.'), remove it and 
            if (remove_sp_characters(file_text)){ // print the word followed with an enter character in the output file
                fprintf(output_file,"%d \n", convert_word_into_token(file_text, all_words, len));
            } else{ // if there is no special character, it will simply print the word in the output file
                fprintf(output_file,"%d ", convert_word_into_token(file_text, all_words, len));
            }
        }
    }
    fclose(file); // close files
    fclose(output_file);
    return 0;
}



// Functions

// this function store unique string variables in the string array
int store_unique_str_variables(char str_array[][MAX_LEN], char *text, int n){
    remove_sp_characters(text); // calling the function that remove any special character
    int i, added = 1; // declaring the variables: local variable 'i' for the for loop
    // the added variable (1 - the word will be added, 0 - the word will not)
    // it will be added unless there is a repeated word that was already stored
    
    if(n != 0){ // if the length of the array is different than zero, 
    // it will check all the elements inside the array
        for(i = 0; i < n; i++){
            if (strcmp(str_array[i],text) == 0){ // if they are equal
                added = 0; // this word will not be added 
                break; // it will break the for loop
            }
        }
    }
    if(added){ // if the added variable was not changed to zero, it will add the word after the last element of the array
        if (max_word_length < strlen(text)){ // if the legth of this word is greater than the global maximum word length variable
            max_word_length = strlen(text) + 1; // the new variable will be the length of this word plus 1 (escape sequence)
        }
        strcpy(str_array[n],text);
    }
    return added; // return if the word was added
}
int check_NULL_file(FILE *file){// function that will check if the file was NULL

    if (file == NULL) { // if the file is NULL
        printf("Error, not able to open the file!\n"); // print that there was an error
        return 1; // return 1, meaning that the file was NULL
    }
    return 0; // return 0, meaning that the file opened
}
// function that remove special characters
int remove_sp_characters(char *text){
    char *ch; // declaring string pointer
    int flag = 0; // declaring flag, that shows if there was a special character
    for (ch = text; *ch != '\0'; ch++){ // this for loop will go through all the characters in a string variable
        if(*ch != '.' && *ch != '\n'){ // if it is not a point nor enter
            *text++ = *ch; // the character will be added to the string variable
        } else {
            flag = 1; // otherwise, it will sinalize that there is a special character (flag = 1)
        }   // and nothing else will happen, the for loop will just be restarted
    }
    *text = '\0'; // the last character where the pointer is pointing will be an escape sequence
    return flag; // return 0 if no character was removed, return 1 if a character was removed. 
}


// this function will sort a string array in alphabetical order
void sorting_string_arrays(char a[][MAX_LEN], int n){
    int i, position = n - 1; // declaring variable for the for loop (i) and the where the string variable in lower alphabetical order
    char lower_alphabetical_word[max_word_length]; // declaring a string variable to store the word in the lowest alphabetical order 
    strcpy(lower_alphabetical_word, a[position]); // store the string variable that is the last position of the array
    if(n == 0) return; // if the size of the array inputted is zero, it ends the recursive void function (meaning that all the array was sorted)
    for(i = n - 2; i >= 0; i--){ // going to all indexes in a descending order, starting with the penultima index
        if(strcmp(lower_alphabetical_word, a[i]) < 0){ // if the word analyzed is lower in alphabetical order
            strcpy(lower_alphabetical_word,a[i]); // the variable will store the word that has the lower alphabetical order
            position = i; // and the position for it will be stored
        }
    }
    // after the for loop analyzed all the words, and found the lowest in alphabetical order for that range:
    // the swaping of the word will occur
    char swap_variable[max_word_length]; // declaring a string variable that will be used as a swap variable
    strcpy(swap_variable, a[n - 1]); // the swap variable will have store the word of the last position
    strcpy(a[n - 1], a[position]); // the last position word will become the lower in alphabetical order 
    strcpy(a[position], swap_variable); // and the position that had the lower word in alphabetical will now store the previous last element of the array

    sorting_string_arrays(a, n - 1); // it will recall the same function for the recursive strategy, until the length passed is zero


}
// function that convert a word into a token, based on the token array given
int convert_word_into_token(char *text, char token_array[][MAX_LEN], int n){ 
    int i, token; // declaring variable for the for loop, and for the token that represents the word analyzed
    for(i = 0; i < n; i++){ // for loop that goes through all the elements in the token_array
        if(strcmp(text, token_array[i]) == 0){ // if the word that is equal to the word we want to convert to token is found
            token = i + 1; // we store the value of the token, which is the position plus 1
            break; // and break the for loop
        }

    }
    return token;// after converting the word into the token, we return its value

}
