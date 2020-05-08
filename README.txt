Liam Creedon
lcreedo1@jhu.edu

hw1 README

The biggest obstacle I faced for this assignment was figuring out how to clear the array so that it would not be printing duplicate words. I also needed to figure out how to handle cases of nonprintable characters, and when the user's input was finished. I used an integer to track when a non[rintable character meant the end of the user's input versus, say, a potential 'tab' character inside of the user's input.
A concern I had was when I ran my program on longer segments of input, the hexdump would print except for the last line. Once I entered 'ctrl + D', the program would output the last part of the hexdump. Upon testing against 'xxd -g 1', I realized that this is the expected behavior.
I tested on a few files, different inputs, as well as invalid files to check that error handling worked.


I failed most of the autograder tests once it was uploaded and found out that I had not handled cases where input was put into the buffer after the first few lines had already been printed. I fixed this bby adding an if statement that checked if the buffer still had characters in it or that the end marker for the overarching while loop was set.

I continued to fail tests after fixing the above issue and discovered there was a difference in the binary code for actual and expected tests. I discovered that my program was still printing the actual text for the buf array even after the EOF character had been reached. This was causing the binary versions to be slightly off.

I also forgot to account for extended ASCII so I had to change the char type to a signed char, change the statement that checked for EOF to check for -1, and modify my printf statement.

The last adjustment I made was to make sure to print '00' values which in my syntax --> if (buf[y]) , was not printing. I made sure to only print the 00 values when it was not an EOF character.
