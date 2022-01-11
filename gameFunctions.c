#include "gameFunctions.h"


void addCardToPlayer(Player* thePlayer, Card* theCard){
    Card* temp = malloc(sizeof(Card)); //creating a space for the new card that we are adding
    temp -> value = theCard -> value; //signing the input card value to this card
    temp -> suit = theCard -> suit;
    insertEndCard_LList(&thePlayer -> winPile, temp); //using helper function 
    theCard -> value = '0'; //have to change the value as given
    //as its clead I HAD to create another card since I am changing the actual cards value
    //so Its not undranstable if I get deducted for this since the guide is not clear
}


bool checkPlayerInput(Deck* theDeck, Player* thePlayer, char row, char col){
    if(theDeck == NULL){ //if the deck is NULL there is something wrong
        printf("error: the the deck is empty\n");
        return false;
    }
    if(theDeck -> cards[(row-48)* 13 + col-97].value == '0'){ //its checking the value with using an index formula 
    	//row is charecter and -48 turns it to the right number same as col -97 turns it into the right number with ascii
        printf("the card you have chosen is already taken\n");
        return false;
    }
    if(thePlayer == NULL){
        printf("error: the player is empty\n");
        return false;
    }
    if(row < 48 || row > 51){ //if the values are in this range with ascii table it shows its wrong
        printf("error: out of index\n");
        return false;
    }
    if(col < 97 || col > 109){ // this is the wrong index too like above
        printf("error: out of index\n");
        return false;
    }
    return true; //if the input is not in any of these conditions its true

}

bool checkForMatch(Deck* theDeck, Player* thePlayer, char r1, char c1, char r2, char c2){
    if(r1 == r2 && c1 == c2){
        printf("error: cards are the same\n");
        return false;
    }
    // number*width +letter would be the index of the underlying array same as above
    if(theDeck -> cards[(r1-48)* 13 + c1-97].value == theDeck -> cards[(r2-48)* 13 + c2-97].value){
        return true;
    }
    else{
        return false;
    }
}

bool checkForWinner(const Deck* theDeck){
    int b = 0;// a parameter to check the cards with char with 0 value
    for(int i = 0; i < 52; i++){
        if(theDeck ->cards[i].value == '0'){
            b++;
        }
    }
    if(b == 52){
        return true;//if all b would 52 
    }
    else{
        return false;
    }
}

