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
 * Last Modified: 02/05/198
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define DEUBG 1
#define MAXWORDLENGTH 15
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define DICTFILE "./dictionaries/tiny"
#define DICTWORDLEN 16

int ok(int fd, char *search_term);

int ok(int fd, char *search_term)
{
    char word[DICTWORDLEN+1];
    int result = 0; 

    
}

int main(int argc, char const *argv[])
{
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

    fd = open(DICTFILE, O_RDWR, 0);
    wordLen = strlen(argv[1]);

    if (fd < 0)
    {
        fprintf(stderr, "Error opening the file: %s\n", strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (wordLen >= MAXWORDLENGTH)
    {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        fprintf(stderr, "Max word size allowed is: %d\n", MAXWORDLENGTH);
        exit(EXIT_FAILURE);
    }

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

    word[DICTWORDLEN] = '\0';
    assert(word != NULL);

    if (DEUBG)
    {
        fprintf(stderr, "# word wanted=\"%s\"\n", word);
    }

    result = ok(fd, word);

    assert(result == 1 || result == 0);

    if (result == 0)
    {
        fprintf(stdout, "yes\n");
    }
    else
    {
        fprintf(stdout, "no\n");
    }

    close(fd); 

    return 0;
}
