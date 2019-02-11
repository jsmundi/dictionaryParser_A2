/*
 *
 * ok.c
 * 
 * Assignment 2
 * CS 360
 * 
 * Author: JT Mundi
 * 
 * Date Created: 02/05/19
 * Last Modified: 02/11/19
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXWORDLENGTH 15
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

/* Dynamic varialbes change according to need */
#define DEBUG 1
#define DICTFILE "./dictionaries/tiny"
#define DICTWORDLEN 16

int ok(int fd, char *searchTerm);

/* 
 * int ok(int fd, char *searchTerm);
 * 
 * Peform binacy search on search term in the file 
 * Perform bitwise operations to approximate the location
 * in file for search term.
 * Check the search term against file words, if not 
 * found manipulate top and bottom.
 * If word found return 1 else 0
 * 
 */

int ok(int fd, char *searchTerm)
{
    char word[DICTWORDLEN + 1];
    int result = 0;
    int top = 0;
    int middle = 0;
    int bottom = 0;

    //Seek end
    top = lseek(fd, 0, SEEK_END);

    //Bitwise Divide by 16
    top = top >> 4;

    while (bottom < top)
    {
        //Bitwise Divide by 2
        middle = (top + bottom) >> 1;

        if (DEBUG)
        {
            fprintf(stderr, "# search range: bottom=%d, top=%d\n", bottom, top);
        }

        //Set offset to middle multiplied by 16
        lseek(fd, middle << 4, SEEK_SET);

        //Assert lseek is valid
        assert(read(fd, word, DICTWORDLEN) != 1);

        //Terminate word with null
        word[DICTWORDLEN - 1] = '\0';

        if (DEBUG)
        {
            fprintf(stderr, "# middle=%d, word have=\"%s\"\n", middle, word);
        }

        //Perfrom String Compare
        result = strcmp(searchTerm, word);

        if (result < 0)
        {
            if (DEBUG)
            {
                fprintf(stderr, "# test: want < have\n");
            }
            top = middle;
        }
        else if (result > 0)
        {
            if (DEBUG)
            {
                fprintf(stderr, "# test: want > have\n");
            }
            bottom = middle + 1;
        }
        else
        {
            if (DEBUG)
            {
                fprintf(stderr, "# test: want = have\n");
            }
            //Found
            return 1;
        }

        //Assert lseek is valid
        assert(lseek(fd, 0, SEEK_SET) != -1);
    }

    //Not found
    return 0;
}

int main(int argc, char const *argv[])
{
    //Check for corrent amount of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        fprintf(stderr, "Interface: ./ok <search_term>");
        exit(EXIT_FAILURE);
    }

    int fd = 0;
    int wordLen = 9;
    int result = 1;
    char word[DICTWORDLEN + 1];

    //Open file in read only
    fd = open(DICTFILE, O_RDWR, 0);
    wordLen = strlen(argv[1]);

    //Check if file opened correctly 
    if (fd < 0)
    {
        fprintf(stderr, "Error opening the file: %s\n", strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }

    //Check for valid word length
    if (wordLen >= MAXWORDLENGTH)
    {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        fprintf(stderr, "Max word size allowed is: %d\n", MAXWORDLENGTH);
        exit(EXIT_FAILURE);
    }

    //Copy the word from user input to char word
    for (size_t i = 0; i < MAXWORDLENGTH; i++)
    {
        if (i < wordLen)
        {
            word[i] = argv[1][i];
        }
        else
        {
            word[i] = ' ';
        }
    }

    //Terminate word with null
    word[DICTWORDLEN] = '\0';
    assert(word != NULL);

    if (DEBUG)
    {
        fprintf(stderr, "# word wanted=\"%s\"\n", word);
    }

    //Perform binary search on the search term 
    result = ok(fd, word);

    //Check for valid return
    assert(result == 1 || result == 0);

    //Yes if 1 else NO
    if (result == 1)
    {
        fprintf(stdout, "yes\n");
    }
    else
    {
        fprintf(stdout, "no\n");
    }

    //Close the file 
    close(fd);

    return 0;
}
