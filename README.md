# cli-doubly-linked-list
This is a command-line application that demonstrates a dynamically allocated doubly linked list of sorted strings.


This program implements Insert, Member, Delete, and Free_list, stores a list of strings, and stores the strings in increasing alphabetical order. The list does not store duplicate strings and is efficient in two senses:
1. It minimizes the use of memory for the list. So the individual nodes in the list only store as many characters as are actually in the string (including the terminating null character).
2. It minimizes search times by exploiting the alphabetical ordering in the list. So Insert, Member, and Delete only search through the list as far as needed.

Each node in the list is linked to both its immediate successor and its immediate predecessor. The first node in the list has a NULL predecessor pointer, and the last node in the list has a NULL successor pointer. Furthermore, the list is defined by two pointers: a head pointer, which references the first node in the list, and a tail pointer which references the last node in the list.

Input to the program is the commands the user enters.

To run the program, download the code and navigate to the working directory. Open a terminal and enter `gcc doubly_linked_list.c` followed by `./a.out` to run.
