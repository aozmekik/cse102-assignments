## GEBZE TECHNICAL UNIVERSITY

## DEPARTMENT OF COMPUTER ENGINEERING

## CSE102 HW

In this homework, you are going to implement a program which encrypts, or decrypts
a given message. The message contains only English letters and they are all in
lowercase.

**Function:** void menu()
This is a menu function. User enters a choice to execute corresponding sub-program.
When 0 is chosen, the program stops. Whenever a sub-program is finished, your
program goes back to menu so that user can execute another sub-program. You are
going to use do-while loop and switch case to implement this function. The user
will have three different choices, i.e., {1, 2, or 0}. Any other input will be
invalid, and program must display menu again when a wrong input is entered.

Sample output if this function is:

1. Encrypt
2. Decrypt
0. Exit
Choice:

**Function:** void encrypt_open_msg()
This function reads content of open_msg.txt file, encrypts it, shows encrypted
message on screen and then writes to secret_msg.txt file. In encryption, function
asks for a key value that is actually a positive integer between 1 and 26 at the
beginning. Then, it reads a line of the message, reverses the line, and replaces
each character of the line by a corresponding letter in reverse direction. For
instance, assume that the key is 5 and line is one word that is “gebze”. Reverse of
“gebze” is “ezbeg”. “ezbeg” becomes “zuwzb” when function replaces each character
by 5 in reverse direction (e->z, z->u, b->w, e->z, g->b).

Sample input of the function (content of open_msg.txt):
gebze technical university.

Sample output of the function:
Key: 5
*zuwzb_ozxcidxvg_pidqzmndot

**Function:** void decrypt_secret_msg()
This function reads each line of the message contained in secret_msg.txt, decrypts
the secret line, shows the open line on screen and then writes the open line to
open_msg.txt file. Decryption of a secret message is obtained by reversing the
encryption operations.

Sample input of the function (content of secret_msg.txt):
*zuwzb_ozxcidxvg_pidqzmndot

Sample output of the function:
Key: 5
gebze technical university

**Function:** int find_size_of_line(char line[])
This function calculates number of characters in line[].

**Function:** void reverse_line(char line[], int line_lenght)
This function reverses content of line[].


## GEBZE TECHNICAL UNIVERSITY

## DEPARTMENT OF COMPUTER ENGINEERING

**Notes:**
 You are not allowed to use built-in string functions.
 Maximum line buffer is 1024.
 Space and dot is encrypted as _ and *, respectively. Decryption is the
reverse.

**Due Date:** Defined on Moodle.

**Submission Rule:** student_no.zip (includes the followings)
 student_no.c
 open_msg.txt
 secret_msg.txt

**Grading Policy:**

1. If you do not apply submission rule, you will get –20 points.
2. In case of cheating, each participant gets –100.
3. A code which does not compile or run (shows nothing) will be graded as 0
points.

**Contact:** mcelenlioglu@gtu.edu.tr


