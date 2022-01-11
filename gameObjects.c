#include "gameObjects.h"

void initializeDeck(Deck* theDeck, char* brandName){
    theDeck -> brand = brandName; //firstly setting the brandname
    char arr[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'}; 
    //since they numbers are actual charecters I created an array for signing charecter to each card
    for(int i = 0; i < 13; i++){ //four suits each suit has 13 cards
        theDeck -> cards[i].suit = 0; //signing the first suit 
        theDeck -> cards[i].value = arr[i]; 
        //all the 13 card has the same suit but diffrent value and they are gettin signed with the array
    }
    for(int j = 13; j < 26 ; j++){
        theDeck -> cards[j].suit = 1;
        theDeck -> cards[j].value = arr[j-13];
    }
    for(int b = 26; b < 39; b++){
        theDeck -> cards[b].suit = 2;
            theDeck -> cards[b].value = arr[b-26];
    }
    for(int l = 39; l < 52; l++){
        theDeck -> cards[l].suit = 3;
        theDeck -> cards[l].value = arr[l-39];
    }

}

void shuffleDeck(Deck* theDeck){
    for(size_t i = 0; i < NUM_OF_CARDS_IN_DECK; i++){
        size_t j = i + rand() / (RAND_MAX / (NUM_OF_CARDS_IN_DECK - i) + 1);//used the asked method "algorithm"
        Card temp = theDeck -> cards[j];//swapping the cards
        theDeck -> cards[j] = theDeck -> cards[i];
        theDeck -> cards[i] = temp;
    }
}


void printDeck(const Deck* theDeck, bool faceUp){
    if(faceUp == true){//if statement for face up or down
        char arr[4][4] = {"\u2660", "\u2661", "\u2663", "\u2662"};
        //this array contains the suit charecter for all the cards (there are 4 suit types)
        char arr2[13] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};
        //this array is used to create the same "image" that was asked for the gameplay 
        //cols with letters
        printf("  ");
        for(int i = 0; i < 13; i++){//the for loop used for arr2 to create "image"
            printf(" %c ", arr2[i]);
        }
        printf("\n");//space down and printing the number for the first row asked as asked in the immage
        printf("0 ");
        for(int i = 0; i < 13; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   "); //if the card value 0 dont print it
            }
            else{
              printf("%c", theDeck -> cards[i].value); //print card vale charecter
              printf("%s ",  arr[theDeck -> cards[i].suit]); //the suit number is the index of the suit charecter arr2 
            }
        }
        printf("\n");
        printf("1 ");
        for(int i = 13; i < 26; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   ");
            }
            else{
              printf("%c", theDeck -> cards[i].value);
              printf("%s ",  arr[theDeck -> cards[i].suit]);
            }

        }
        printf("\n");
        printf("2 ");
        for(int i = 26; i < 39; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   ");
            }
            else{
              printf("%c", theDeck -> cards[i].value);
              printf("%s ",  arr[theDeck -> cards[i].suit]);
            }

        }
        printf("\n");
        printf("3 ");
        for(int i = 39; i < 52; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   ");
            }
            else{
              printf("%c", theDeck -> cards[i].value);
              printf("%s ",  arr[theDeck -> cards[i].suit]);
            }
        }
    }
  else if(faceUp == false){
        //similiar to facedown but it doesnt include the suit char but includes faceup char
        char arr2[13] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};
        printf("  ");
        for(int i = 0; i < 13; i++){
            printf(" %c ", arr2[i]);
        }
        printf("\n");
        printf("0 ");
        for(int i = 0; i < 13; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   ");
            }
            else{
                printf("%c\u218C ", '?');
            }
        }
        printf("\n");
        printf("1 ");
        for(int i = 13; i < 26; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   ");
            }
            else{
                printf("%c\u218C ", '?');
            }
        }
        printf("\n");
        printf("2 ");
        for(int i = 26; i < 39; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   ");
            }
            else{
                printf("%c\u218C ", '?');
            }
        }
        printf("\n");
        printf("3 ");
        for(int i = 39; i < 52; i++){
            if(theDeck -> cards[i].value == '0'){
                printf("   ");
            }
            else{
                printf("%c\u218C ", '?');
            }
        }
    }
}


void initializePlayer(Player* thePlayer, char* theName){
    thePlayer -> name = theName; //sets the name cards won are 0 and head and tail r NULL since the game is starting
    thePlayer -> cardsWon = 0;
    thePlayer -> winPile.head = NULL;
    thePlayer -> winPile.tail = NULL;
}

void clearPlayer(Player* thePlayer){
    clearCard_LList(&thePlayer-> winPile); //we have to first clear the winPile there is no other way to leave it out
    thePlayer -> winPile.head = NULL;//setting head and tail to NULL since its empty
    thePlayer -> winPile.tail = NULL;
}
