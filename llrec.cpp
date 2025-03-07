#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    // if list is empty then both lists become null
    if(head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }
    
    // take the first node from list
    Node* curr = head;         // this is the node we are working on
    head = head->next;         // move head to the next node
    curr->next = NULL;         // break the link from this node
    
    // call the function recursively on the rest of the list
    Node* smallRec;            // will hold the small list from recursion
    Node* largeRec;            // will hold the large list from recursion
    llpivot(head, smallRec, largeRec, pivot);
    
    // check the value of the current node to decide where it goes
    if(curr->val <= pivot) {
        curr->next = smallRec;
        smallRec = curr;
    } else {
        curr->next = largeRec;
        largeRec = curr;
    }
    
    // set the output lists to the results from recursion
    smaller = smallRec;
    larger = largeRec;
}

