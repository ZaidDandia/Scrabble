# Scrabble

University: Ghulam Ishaq Khan Institute of Engineering Sciences and Technology\
Course: Data Structures and Algorithms (Lab)\
Course Instructor: Usama Arshad\
Group Members: Zaid Dandia (2021719), Eman Anjum (2021148), Ahmed Ali Abid (2021065)

## Command to run the project:
> g++ -o Scrabble.exe Scrabble.cpp\
> ./Scrabble.exe

## Data Structures used in the project:
>Queue\
>Linked List\
>Tries\
>Stack

## General Description on the Project:
>The following project is based on the game of Scrabble by using different data structures. The data structures which have been used for making this game are Linked List, Stacks, Queues, Arrays, and Trie. There is a library which contains the inventory of all those words which are applicable in our game and for that we have a words.txt file. Now, this .txt file have been stored in the Trie data structure. A Queue has been used to manage the inventory of the player. When the user enters the word, it gets stored in the Queue and after checking the existence of the word, it gets stored in another Trie, which stores the completed words on the board. Two arrays have been used: one contains the points or scores against the alphabets and the other stores the inventory of scrabble. A 2D array has also been used to make the scrabble board. Lastly a Linked List maintains the user turns and the sequence of playing.
