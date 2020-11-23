// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next; //pointer to the address of the next word in the linked list
}
node;

// Number of buckets in hash table
const unsigned int N = 4027; //I'm setting to 4026 + 1. The starting hash value in my hash function.

// Hash table
node *table[N + 1];
int count = -1;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //check each word to see if it's in dictionary, or not (is it correctly spelled?)
    // use strcasecmp() to compare two strings with different cases. e.g.: FoO == foo
    int hash_index = hash(word); //returns index value where the word is stored.

    //provide your check function a temporary node for flipping through the chains in your actual hash table
    node *tmp_table = table[hash_index];
    //Make a copy of the Head of the hash table at hash index
    //tmp_table can be treated as the HEAD

    bool match;

    while (tmp_table != NULL)
    {
        match = strcasecmp(tmp_table->word, word);
        if (match == 0)//you found a match!
        {
            return true; //return True, your word is in the index and you should return out of the function
        }
        tmp_table = tmp_table->next;//this advances your 'cursor' or tmp_table to the next node the tmp_table is looking at.
        //eventually ->next will be NULL and the program will escape this loop
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //SOURCE: Adapted from 'djb2' from http://www.cse.yorku.ca/~oz/hash.html
    int hash_val = 0;
    char c = *word;

    //advances character index in the word and then does something

    while (c == *word++)
    {
        hash_val = tolower(c) * 33; //highest value will be z (122) * 33 = 4026
    }

    return hash_val;
}
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary for reading
    FILE *dict_list = fopen(dictionary, "r");

    if (dict_list == NULL)
    {
        printf("dict list is NULL\n");
        return false;
    }

    //Create a word buffer that is of size Lenght + 1;
    char word_buffer[LENGTH + 1];

    //read strings from file one at a time, and pass them into a buffer
    //allocate memory to your temp node
    while (fscanf(dict_list, "%s", word_buffer) != EOF)
    {

        node *word_node = malloc(sizeof(node));
        if (word_node == NULL)
        {
            //checks to see if malloc returns NULL (meaning no memory left!)
            //return out of the program
            return false;
        }

        strcpy(word_node->word, word_buffer);
        word_node->next = NULL;

        //Hash function, determine which index the word should be added to, then link the word node to that index's linked list
        int hash_index = hash(word_buffer); //returns index value where the word is stored.

        //OK, you have a Hash value, the full node could be NULL, so let's add this word to the hash table's index
        //this will establish our HEAD of the linked list. We won't move this down the chain.
        if (table[hash_index] == NULL)
        {
            //insert word into the hash table's hash_index
            table[hash_index] = word_node; //structs are passed by value, so you will pass in word_nodes value into table at hash index

            //TODO: count each word as it's added to that hash table

        }
        //OK, but the hash table at hash index may not be NULL, meaning there's an address of another node we want to copy to the word node,
        //and therefore we need to take that address, insert it into the word node next attribute, and then repoint table to the full word node
        else
        {
            word_node->next = table[hash_index]; //set the word node's next pointer to the address of the table at hash_index. This is the HEAD
            table[hash_index] = word_node; //now repoint the HEAD's next pointer to the location in memory of the current word_node
        }
        size(); //increment your size

    }

    fclose(dict_list);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    count ++; //count is a pointer of type int, since it's an address of a place in memory, this is updated by Reference, not just a copy of count's value.

    //counts how many words are in the dictionary, not the size of the data
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //use free() to free memory that has been allocated to filling up the hash table.
    //free all nodes in
    //use valgrind to detect any leaked memory
    //$ valgrind ./speller texts/cat.txt
    //for help on how to read valgrind: $ help50 valgrind ./speller texts/cat.txt

    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *free_cursor = head;
        node *tmp_cursor = head;
        while (free_cursor != NULL)
        {
            free_cursor = free_cursor->next;
            free(tmp_cursor); //free the memory allocated at that address
            tmp_cursor = free_cursor;
        }
    }

    return true;
}
