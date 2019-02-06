# Overview 
A program (in C) targeted at the Linux platform which checks whether a specified word, passed as an argument to the executable, exists in a dictionary or not. The specified dictionary is webster and on the website.
  
 image

- Format is 1 word per line
- Lines are in ascending sorted order
- Each line is 16 characters long
- Use binary search


# Program Interface

```bash
 ./ok search_term
    Where: search_term is the desired word you are searching for.
    The program should return ‘yes’ if the word exists in the dictionary
    or ‘no’ if it does not.
```

# Specifications

- Only use of the i/o methods lseek, read, write, open and close. For debugging printf and string comparission strcmp is utilized.
- All entered words truncated to 16 characters.
- Two vairables defined, one that specifies the dictionary's location and name and another that specifies the word length in the dictionary. 
- Errors are catched and printed with appropriate messages. errno.h and string.h libraries utilized for error catching. 

# Makefile
- all: compiles everything together and produces an executable
- clean: removes all object and temporary files
- run: command for running your executable

