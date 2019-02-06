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

int main(int argc, char const *argv[])
{
    char *fname = "./dictionaries/tiny"; 
    char ch[256];
    int offset = 0;
    int fd = 0;

    if (argc < 2)
    {
        printf("No File provided for reading\n");
        return 1;
    }

    fd = open(fname, O_RDWR, 0);

    if (fd == 0)
    {
        printf("Unable to open the file\n");
    }
    return 0;
}
