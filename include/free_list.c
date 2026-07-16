#include "../src/allocator_internal.h"

Node* insert_at_head(Node* head, Header* h){
    if (head == NULL){
        head = (Node*)((char*)h + sizeof(Header));
        head->next = NULL;
        head->prev = NULL;
    } else {
        Node* t = (Node*)((char*)h + sizeof(Header));
        t->next = head;
        head->prev = t;
        head = t;
    }
    return head;
}

Node* delete_node(Node* head, Node* t){
    if (t == NULL)
        return head;

    if (t->prev != NULL) 
        t->prev->next = t->next;
    else                    /*t is head*/
        head = t->next;

    if (t->next != NULL)
        t->next->prev = t->prev;

    t->next = NULL;
    t->prev = NULL;
    return head;
}