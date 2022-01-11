#include "card_LList.h"


Card_LList* createCard_LList(){
    Card_LList* new = malloc(sizeof(Card_LList));//using malloc to create the structure
    if(new == NULL){
        exit(0);
    }
    new -> head = NULL; //head and tail empty since the LList is just created empty
    new -> tail = NULL;
    return new;//return the address of first linked list
}

void clearCard_LList(Card_LList* theList){  
  while(theList -> head != NULL) //till head is not null frees the every space allocated for each node
    {
        Card_Node* temp = theList -> head -> next;
        free(theList->head);
        theList-> head = temp;
    }      
    theList -> head = NULL; 
    theList -> tail = NULL;

}

bool isEmptyCard_LList(Card_LList* theList){
    if(theList -> head == NULL && theList -> tail == NULL){
        return true;//checks if the head is null or tail is null if they are both null means its empty 
    }
    else{
        return false;
    }
}

void insertFrontCard_LList(Card_LList* theList, Card* theCard){
    Card_Node* new = malloc(sizeof(Card_Node));//allocate a space for the node
    if(new == NULL){//if it fails
        exit(0);
    }
    new -> card = theCard; // set the card of the node to the given card
    if(isEmptyCard_LList(theList)){
        new -> next = NULL;  //the next is null if the list is empty
        theList -> head = new;//both head and tail should point to this node since its the only node in LList
        theList -> tail = new;
    }
    else{
        Card_Node* temp = theList -> head; //if its mot empty since we inserting from front we move the head to the new's next
        //and we set the new to the actual head
        theList -> head = new;
        new -> next = temp;
    }
}

void insertEndCard_LList(Card_LList* theList, Card* theCard){
    Card_Node* new = malloc(sizeof(Card_Node)); //allocating space for the node
    if(new == NULL){// if it fails exit
        exit(0);
    }
    new -> card = theCard; //signing the given card to the null
    if(isEmptyCard_LList(theList)){
        new -> next = NULL; // if its empty same thing as the insertFront function
        theList -> head = new;
        theList -> tail = new;
    }
    else{
        theList -> tail -> next = new; // this time we move the tail to the next of the new and we make the new the tail
        theList -> tail = new;
        new -> next = NULL;
    }
}


Card* removeFrontCard_LList(Card_LList* theList){
    if(isEmptyCard_LList(theList)){//if its empty just returns null
        return NULL;
    }
    Card_Node* temp1 = theList -> head; // temp1 save address of head
    Card* temp = temp1 -> card; // temp has the card of the head
    if(theList -> head == theList -> tail){
        theList -> head = NULL; //this means that there is only one card and if that happens it sets both head and tail 
        //to null since it becomes empty
        theList -> tail = NULL;
    }
    else{
    	//if its not the last card sign the head to the next of the head
        theList -> head = theList -> head -> next;
    }
    temp1 = NULL; //the prof said we shouldnt free in this function cuz it might cuz issue so I just set the address to NULL
    return temp; //and returned the temp
}


Card* removeEndCard_LList(Card_LList* theList){  
    if(isEmptyCard_LList(theList)){ //same as above (remove front)
        return NULL;
    }
    Card_Node* secondLast = theList -> head; //have to write a while loop to second last
    while(secondLast -> next != theList -> tail){
        secondLast = secondLast -> next;
    }
    Card_Node* last = theList -> tail; //use to temp variables to have the last
    Card* last2 = last -> card;

    if(theList -> head == theList -> tail){ //similiar to above (remove front)
        theList -> head = NULL;
        theList -> tail = NULL;
    }
    else{
        theList -> tail = secondLast; //if its more than two set the tail to second last
    }
    last = NULL; //similiar to above
    return last2;

}