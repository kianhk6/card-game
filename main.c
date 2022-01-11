#include <stdio.h>
#include <stdlib.h> //for the use of system and srand and rand
#include "gameObjects.h"
#include "gameFunctions.h"

#define MAX_CHAR_NUMBER 16 //each input should have at most 15 characters


void getText(char *v, int s){//a helper function that saves the input using fget
  fgets(v, sizeof(char) * s, stdin);
  sscanf(v, "%[^\n]", v);
}

//each input should have at most 15 characters

//a helper function that clears the screen, works for both unix and Windows,
//though behaviour might be different.
//reference: https://stackoverflow.com/questions/2347770/
//            how-do-you-clear-the-console-screen-in-c
void clear() {
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("printf '\33[H\33[2J'");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

int main() {
  //set the random seed to 0, it'll generate the same sequence
  //normally it is srand(time(NULL)) so the seed is different in every run
  //using 0 makes it deterministic so it is easier to mark
  //do not change it
  srand(0);

  //variables to store user input
  char userInput1[MAX_CHAR_NUMBER];
  char userInput2[MAX_CHAR_NUMBER];
  // int whereInDeck = 0; //handy for indexing which card based on user input

  //set up the players
  Player player1, player2;
  initializePlayer(&player1, "Player 1");
  initializePlayer(&player2, "Player 2");
  // Player* currentPlayer = &player1; //this pointer remembers who's turn it is

  //set up the deck: initalize & shuffle
  Deck myDeck;
  initializeDeck(&myDeck, "Bicycle");
  shuffleDeck(&myDeck);

  printDeck(&myDeck, true); //print the shuffled deck, face up
  printf("\n");
  clear(); //clear the screen

  /*
  Implement this part for the game to work.
  It is essentially a do-while loop that repeatedly print the deck,
  ask for user inputs, and do some checking. Ends if someone wins.
  */
  int i = 1; //this is the parameter that checks which players turn it is
  //if odd player 1 if even player 2 at the end of each players turn it gets added

  do{
    /////////////////////
    // 1 Round
    ////////////////////
    //Step 1: print the shuffled deck, face down
        if(i%2 != 0){
            printDeck(&myDeck, false);
            //Step 2: print who's turn it is by showing the player's name
            printf("\n%s's turn.\n", player1.name);
            //Step 3.1 get first input from player,
            // keep asking until the input is valid (hint: use a do-while loop)
            // you can assume that the format is correct (a digit<space>a letter)
            do{
                printf("pick the first card you to turn (e.g., 0 a) then press enter: ");
                getText( userInput1, 16); //it was given that its upto 16 charecters
            }while (!checkPlayerInput(&myDeck, &player1,  userInput1[0],  userInput1[2])); //the 0 and 2 index is the row and col
        
            do{
                printf("pick the second card you to turn (e.g., 0 a) then press enter: \n");
                getText(userInput2, 16);
            } while (!checkPlayerInput(&myDeck, &player1,  userInput2[0],  userInput2[2]));
                
            char arr[4][4] = {"\u2660", "\u2661", "\u2663", "\u2662"}; //created array with the suit char to print it on screen
            printf("the first card picked: %c",  myDeck.cards[(userInput1[0]-48)* 13 + userInput1[2]-97].value);
            // number*width +letter would be the index of the underlying array  -48 and -97 since its an char and this makes it to actual wanted integer
            printf("%s\n", arr[myDeck.cards[(userInput1[0]-48)* 13 + userInput1[2]-97].suit]);
            printf("the first card picked: %c",  myDeck.cards[(userInput2[0]-48)* 13 + userInput2[2]-97].value);
            printf("%s\n", arr[myDeck.cards[(userInput2[0]-48)* 13 + userInput2[2]-97].suit]);

            //Step 5: call the checkForMatch function to see if the player has picked
            // a matching pair. If so, print the corresponding message and add the cards
            // to the player's winning pile (Player.winPile).
            // Keep the current player as a match leads to an extra round.
            // Otherwise, print the corresponding message and switch player.
            if(checkForMatch(&myDeck, &player1, userInput1[0],  userInput1[2],  userInput2[0],  userInput2[2])){
                printf("%s has found a match! earns a extra turn\n", player1.name);
                player1.cardsWon++; //increasing the value of cards one by 2 since if the matching cards are found we add 2 cards
                player1.cardsWon++;
                addCardToPlayer(&player1, &myDeck.cards[(userInput2[0]-48)* 13 + userInput2[2]-97]); //adding the card to player
                addCardToPlayer(&player1, &myDeck.cards[(userInput1[0]-48)* 13 + userInput1[2]-97]);
                i++;
            }
            else{
                printf("%s has not found a match\n", player1.name);
            }
            i++;
        }
        else{ //same thing but this for player 2
            printDeck(&myDeck, false);
            //Step 2: print who's turn it is by showing the player's name
            printf("\n%s's turn.\n", player2.name);
            //Step 3.1 get first input from player,
            // keep asking until the input is valid (hint: use a do-while loop)
            // you can assume that the format is correct (a digit<space>a letter)
            do{
                printf("pick the first card you to turn (e.g., 0 a) then press enter: ");
                getText( userInput1, 16);
            }while (!checkPlayerInput(&myDeck, &player2,  userInput1[0],  userInput1[2]));
        
            do{
                printf("pick the second card you to turn (e.g., 0 a) then press enter: \n");
                getText(userInput2, 16);
            } while (!checkPlayerInput(&myDeck, &player2,  userInput2[0],  userInput2[2]));
                
            char arr[4][4] = {"\u2660", "\u2661", "\u2663", "\u2662"};
            printf("the first card picked: %c",  myDeck.cards[(userInput1[0]-48)* 13 + userInput1[2]-97].value);
            printf("%s\n", arr[myDeck.cards[(userInput1[0]-48)* 13 + userInput1[2]-97].suit]);

            printf("the first card picked: %c",  myDeck.cards[(userInput2[0]-48)* 13 + userInput2[2]-97].value);
            printf("%s\n", arr[myDeck.cards[(userInput2[0]-48)* 13 + userInput2[2]-97].suit]);

            //Step 5: call the checkForMatch function to see if the player has picked
            // a matching pair. If so, print the corresponding message and add the cards
            // to the player's winning pile (Player.winPile).
            // Keep the current player as a match leads to an extra round.
            // Otherwise, print the corresponding message and switch player.
            if(checkForMatch(&myDeck, &player2, userInput1[0],  userInput1[2],  userInput2[0],  userInput2[2])){
                printf("%s has found a match! earns a extra turn\n", player2.name);
                player2.cardsWon++;
                player2.cardsWon++;
                addCardToPlayer(&player2, &myDeck.cards[(userInput2[0]-48)* 13 + userInput2[2]-97]);
                addCardToPlayer(&player2, &myDeck.cards[(userInput1[0]-48)* 13 + userInput1[2]-97]);
                i++;
            }
            else{
                printf("%s has not found a match\n", player2.name);
            }
            i++;
        }
    } while (!checkForWinner(&myDeck));

  //Step 6: find out who won the game and announce the winner
  printf("%s has won %d cards\n", player1.name, player1.cardsWon);
  printf("%s has won %d cards\n", player2.name, player2.cardsWon);
  if(player2.cardsWon > player1.cardsWon){
      printf("%s has won!\n", player2.name);
  }
  else if(player2.cardsWon < player1.cardsWon){
      printf("%s has won!\n", player1.name);
  }
  else{
      printf("its a tie!!!!!!\n");
  }

  //clears
  clearPlayer(&player1);
  clearPlayer(&player2);


  return 0;
}
