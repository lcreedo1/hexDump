/*
 * CSF Fall 2019
 * Homework 1
 * Liam Creedon
 * lcreedo1@jhu.edu
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* The number of data bytes corresponding to one line of hexdump output. */
#define HEXDUMP_BUFSIZE 16

/* TODO: function prototypes */

int main(int argc, char **argv) {
    FILE *in;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        fprintf(stderr, "Reads from standard input if <filename> is omitted\n");
        return 1;
    }

    if (argc == 1) {
      in = stdin;
   } else {
        in = fopen(argv[1], "rb");
        /* TODO: report error and exit if input file couldn't be opened */
	if (in == NULL) {
	  fprintf(stderr, "File could not be opened\n");
	  return 1;
	}
    }

    char buf[HEXDUMP_BUFSIZE]; /* storage for data read from input */
    /*
     * TODO: read data from the file handle called "in" and print a hexdump
     * of its contents
     */
    //character read from buffer
    unsigned char c;
    //fgetc stored in here for sake of integer conversion
    int tempChar = 0;
    //signals when to end the while loop
    int end = 0;
    //queues the loop to end
    int qend = 0;
    //indicates the location of EOF character so that later loops only execute up to the EOF location in the buffer
    int lastP = 0;
    //only checks for EOF once, will not continue to update lastP
    int checkedEOF = 0;
    //updates location in hexadecimal
    int loc = 0;
    
    while (end == 0) {
      
      //empties buf
      memset(buf, 0, HEXDUMP_BUFSIZE);
      
      //resets lastP
      lastP = 0;
     
      //populates buf with first 16 chars from input
      for (int x = 0; x < HEXDUMP_BUFSIZE; x++) {
	tempChar = fgetc(in);
	//checks for EOF
	if (feof(in)) {
	  qend = 1;
	  if (!checkedEOF) {
	    lastP = x;
	    checkedEOF++;
	  }
	  //will terminate loop
	  x = HEXDUMP_BUFSIZE;
	} else { //fills buffer with input
	  c = tempChar;
	  buf[x] = c;
	}
      }

      //exit signal
      if (qend == 1) {
	end++;
      }
      
      //if buffer still has characters in it, or end is not 1, print info
      if (buf[0] || end != 1) {

      //prints location in hexadecimal	
	printf("%08x: ", loc);

	//prints each char converted to hexadecimal
	for (int y = 0; y < HEXDUMP_BUFSIZE; y++) {
	  if (buf[y]) { //if character has an ASCII val
	    printf("%02hhx ", buf[y]);
	  } else if (buf[y] == 00 && !lastP) { //if character is 00 and is not EOF
	    printf("00 ");
	  } else { //No char to print
	    printf("   ");
	  }
	}

	//prints extra space after hex values
	printf(" ");

	//prints actual words inputted by user
	for (int z = 0; z < HEXDUMP_BUFSIZE; z++) {
	  
	  //if char is a newline or tab, print a period and break
	  if (((!lastP) || (lastP > z)) && !isprint(buf[z])) {
	    printf(".");
	  } else { //print character inputted by user
	    printf("%c", buf[z]);
	  }
	  //will end for loop so extra spaces are not printed
	  if (lastP == z + 1) {
	    z = HEXDUMP_BUFSIZE;
	  }
	}
	//newline after text is printed
	printf("\n");

	//updates location
	loc += 16;
      }
    }
    fclose(in);
    return 0;
}
