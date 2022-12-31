#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <algorithm>
#include <cstdlib>
using namespace std;
#include "Tries.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"

struct Coordinates  // a structure for coordinates of a charter on the scrrable board 
{
    int Row;
    int Column;
};
bool searchWord(Trie t, char arr[15][15], Trie C) //it searches the entred string or word in the board and compare if it is
{                                                 //valid or not by searching it in library of word of a scrabble game
    bool found = false;
    bool already = false;
    t.initialise();

    // this searches for  the word in horizontal fashion so that points can be alloted and a proper word can be accepted 
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            string temp = "";
            for (int k = j; k < 15; k++)
            {
                if (arr[i][k] != ' ')
                    temp += arr[i][k];
                else
                {
                    continue;
                }
                if (t.searchString(temp))// check if string sexit in library of scrabble and complete words as well
                {
                    if (!C.searchString(temp))
                    {
                        C.Insert(temp);
                        found = true;
                    }
                    else
                    {
                        already = true;
                    }
                }
            }
        }
    }
    // this searches for  the word in vertical fashion so that points can be alloted and a proper word can be accepted
    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 15; i++)
        {
            string temp = "";
            for (int k = i; k < 15; k++)
            {
                if (arr[k][j] != ' ')
                    temp += arr[k][j];
                else
                {
                    continue;
                }
                if (t.searchString(temp))  // check if string sexit in library of scrabble and complete words as well
                {
                    if (!C.searchString(temp))
                    {
                        found = true;
                    }
                    else
                    {
                        already = true;
                    }
                }
            }
        }
    }
    return found;
}
class Scrabble  // class that holds all the functions regarding the gamme tthat are requiered to play the game
{
private:
    Trie t; //to store all the library of scrabble
    Trie CompletedWords; // to  store all the enterded complete words on the board
    Queue<char> Inventory; // a queue that is used to mange inventory of a player
    int players;// stores no of players 
    char array[101] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'D', 'D', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'F', 'F', 'F', 'G', 'G', 'G', 'H', 'H', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'J', 'K', 'L', 'L', 'L', 'L', 'M', 'M', 'N', 'N', 'N', 'N', 'N', 'N', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'P', 'P', 'Q', 'Q', 'R', 'R', 'R', 'R', 'R', 'R', 'S', 'S', 'S', 'S', 'T', 'T', 'T', 'T', 'T', 'T', 'U', 'U', 'U', 'U', 'V', 'V', 'W', 'W', 'X', 'Y', 'Y', 'Z', 'Z'};
    //this array stores full inventory of the scrrable

    int Points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; // every alphabet has a unique score this
    //array has all the scores stored to the equivalent alphabets 

    LinkedList<int> l; // maintains the user turs and sequence of playing
    LinkedList<char> *Words = new LinkedList<char>[players];// initalizing inventory of all the players that they will  have access off during the game 
    char Board[15][15]; // a 2-D array used to make the scrable board 
    int *Score;//keep track of score
    int *turn;// keep track of the turn 

public:
    Scrabble() // constructor 
    {
        t.initialise();// initialize the tries to work with 
        srand(time(0));
        random_shuffle(array, array + 100);// randomly shuffles the array of elements 101 so  that it can be distributed among users 
        for (int i = 0; i < 100; i++) // it moves the whole inventory to the queue for t use in the game
        {
            Inventory.enQueue(array[i]);
        }

        // this makes us enter number of players in the game where we makle sure they are between 2-4 players at a time not more or less than that 
        cout << "Enter the number of players: ";
        cin >> players;
        while (players > 4 || players <= 1)
        {
            cout << "Please Enter a number between 2 and 4: ";
            cin >> players;
        }
        Score = new int[players]; // an array that will maintain score of the players 
        for (int i = 0; i < players; i++)// initialize the score with 0
        {
            Score[i] = 0;
        }

        int min = 1000;
        int position = 0;
        turn = new int[players]; //initailize an array to maintain turns 
        for (int i = 0; i < players; i++)  // thhis randomly selects a player to play the first turn 
        {
            int temp = rand() % 26;
            turn[i] = temp;
            char c = temp + 97;
            if (turn[i] < min)
            {
                min = turn[i];
                position = i + 1;
            }
        }
        cout << "Player " << position << " plays first" << endl;
        l.Insert(position); // makes user enter position where they want to enter the alphabet 
        for (int i = 0; i < players; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                Words[i].Insert(Inventory.getFront());
                Inventory.deQueue();
            }
        }

        for (int i = 0; i < players; i++)
        {
            if (i + 1 != position)
                l.Insert(i + 1);
        }

        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                Board[i][j] = ' ';
            }
        }
    }
    void PrintBoard() // prints the board so that it all can be displaed after user makes an input or not 
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                cout << "| " << Board[i][j] << " ";
            }
            cout << "|" << endl;
        }
    }
    void playGame()
    {
        while (1)
        {
            Queue<char> CurrentWord;
            char choice = 'Y';
            int CurrentTurn = l.showFront();
            l.DeleteFront();
            l.Insert(CurrentTurn);
            int row, column;
            char c;
            Stack<Coordinates> Stored;
            while (1)
            {
                cout << "Player " << CurrentTurn << " turn: " << endl;
                cout << "Your Word Inventory: ";
                Words[CurrentTurn - 1].Display(); // currentTurns tells whoes turn it is 
                PrintBoard();
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter Column: ";
                cin >> column;
                cin >> c;

                while (Board[row - 1][column - 1] != ' ')
                {
                    cout << "Already Full. Try again" << endl; // if row or column is all ready full we cant enter anything at that point
                    cout << "Enter row: ";
                    cin >> row;                                //so we re enter.
                    cout << "Enter column: ";
                    cin >> column;
                    cout << "Enter the Letter: ";
                    cin >> c;
                }
                while (!Words[CurrentTurn - 1].search(c)) // we search if te word entered by the user exists in the scrrable library or not 
                {                                         //if not user enters againn and the first entry is nullified
                    cout << "Letter not in your inventory! Please try again." << endl;
                    cout << "Enter the Letter : " << endl;
                    cin >> c;
                }
                {
                    Coordinates C;
                    C.Row = row - 1;
                    C.Column = column - 1;
                    Stored.insert(C);
                    CurrentWord.enQueue(c);
                    Board[row - 1][column - 1] = c;
                    cout << "Do you want Enter again(Y/N): ";
                    cin >> choice;

                    if (choice == 'N') // this means user doesnt want to enter any other charcter so  that word is complete to check if present or not
                    {
                        if (searchWord(t, Board, CompletedWords))
                        {
                            int temp1 = CurrentWord.getLength();
                            for (int i = 0; i < temp1; i++)
                            {
                                Words[CurrentTurn - 1].Delete(CurrentWord.getFront());
                                Words[CurrentTurn - 1].Insert(Inventory.getFront());
                                Inventory.deQueue();
                                int Letter = Points[int(CurrentWord.getFront() - 'A')];
                                Score[CurrentTurn - 1] += Letter;
                                CurrentWord.deQueue();
                            }
                            break;
                        }
                         // if word is not found in the scrabble library
                        {
                            choice = 'Y'; // error message is printed
                            cout << "The word Entered is not in the Dictionary Please try another word." << endl;
                            int temp1 = CurrentWord.getLength();
                            Stored.Display();
                            for (int i = 0; i < temp1; i++)
                            {
                                Coordinates temp = Stored.getTop();
                                Stored.pop();
                                Board[temp.Row][temp.Column] = ' ';
                                CurrentWord.deQueue();
                            }
                            PrintBoard();
                        }
                    }
                }
                cout << "Press Any Key to continue...." << endl;
                cin.ignore().get();
                system("clear");// clears the console so  that we dont move down on the console every time a new round is  started
            }
            cout << "Score: " << Score[CurrentTurn - 1] << endl;
            PrintBoard();
            if (Inventory.isEmpty())
            {
                break;
            }
        }
        int max = 0;
        int Winner = 0;
        for (int i = 0; i < players; i++) // finding the winner of the game 
        {
            if (Score[i] > max)
            {
                max = Score[i];
                Winner = i;// winner 
            }
        }
        cout << "Winner is: " << Winner + 1 << endl;
    }
};
int main()
{
    Scrabble S; // decleraation of a class in main function
    S.playGame();// function to start playing the game 
}
