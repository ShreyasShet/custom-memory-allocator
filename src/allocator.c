#include <stdio.h>
#include "../include/allocator.h"
#include "allocator_internal.h"
#include "../include/helper.h"
#include "heap.h"
#include "../include/free_list.h"

char heap[HEAP_SIZE];
Header* heap_start = NULL;
Header* heap_end = NULL;
Node* head = NULL;

void* my_malloc(size_t size){
    if(heap_start == NULL){
        heap_start = heap_init();
        heap_end = heap_start;
    }
    size = ALIGN(size);
    size_t total = sizeof(Header) + size + sizeof(Footer);
    Node* t = head;
    /*block reuse*/
    while(t != NULL){
        Header* h = get_header(t);
        if(size <= get_size(h)){
            size_t remaining_size = get_size(h) - size;
            if(remaining_size >= sizeof(Footer) + sizeof(Header) + MIN_PAYLOAD_SIZE){
                head = delete_node(head, t);
                set_size(h, size);
                Footer* f = (Footer*)((char*)h + sizeof(Header) + get_size(h));
                f->size = get_size(h);
                /*block splitting*/
                Header* h2 = (Header*)((char*)f + sizeof(Footer));
                h2->size_and_flags = 0;
                set_size(h2, (remaining_size - sizeof(Header) - sizeof(Footer)));
                mark_free(h2);
                Footer* f2 = (Footer*)((char*)h2 + sizeof(Header) + get_size(h2));
                f2->size = get_size(h2);
                //insert remainder
                head = insert_at_head(head, h2);
            }
            mark_allocated(h);
            return (void*)(h + 1); 
        }
        t = t->next;
    }
    /*bump allocation*/
    if((char*)heap_end + total > &heap[HEAP_SIZE - sizeof(Header)])
        return NULL;
    Header* h1 = heap_end;
    mark_allocated(h1);
    set_size(h1, size);
    void* ptr = (char*)h1 + sizeof(Header);
    Footer* f1 = (Footer*)((char*)h1 + sizeof(Header) + size);
    f1->size = size;
    Header *epilogue = (Header *)((char *)f1 + sizeof(Footer));
    mark_allocated(epilogue);
    set_size(epilogue, 0);
    heap_end = epilogue;
    return ptr; 
}

void my_free(void* ptr){
    if (ptr == NULL)
        return;
    Header* h = (Header*)ptr - 1;
    mark_free(h);
    //forward coalescing
    Header* cur = h;
    Header* next = (Header*)((char*)cur + sizeof(Header) + get_size(cur) + sizeof(Footer));
    if(next < heap_end && !(is_allocated(next))){
        Node *t = (Node*)((char*)next + sizeof(Header));
        head = delete_node(head, t);
        size_t total = sizeof(Header) + get_size(next);
        set_size(cur, get_size(cur) + sizeof(Footer) + total);
        mark_free(cur);
        Footer* f = (Footer*)((char*)cur + sizeof(Header) + get_size(cur));
        f->size = get_size(cur);
        Node* t1 = (Node*)((char*)cur + sizeof(Header));
        t1->next = NULL;
        t1->prev = NULL;
    }
    //backward coalescing*/
    if(cur != heap_start){
        Footer* prev_footer = (Footer*)((char*)cur - sizeof(Footer));
        Header* prev = (Header*)((char*)cur - (sizeof(Footer) + prev_footer->size + sizeof(Header)));
        if(prev >= heap_start && !(is_allocated(prev))){
            Node *t = (Node*)((char*)prev + sizeof(Header));
            head = delete_node(head, t);
            size_t total = sizeof(Header) + get_size(cur);
            set_size(prev, get_size(prev) + sizeof(Footer) + total);
            cur = prev;
            mark_free(cur);
            Footer* f = (Footer*)((char*)cur + sizeof(Header) + get_size(cur));
            f->size = get_size(cur);
            Node* t1 = (Node*)((char*)cur + sizeof(Header));
            t1->next = NULL;
            t1->prev = NULL;
        }
    }
    //append to list
    head = insert_at_head(head, cur);
}

void heap_check(){
    Header* cur = heap_start;
    while(cur < heap_end){
        printf("Block @%p\n", cur + 1);
        printf("\tsize      = %d\n", get_size(cur));
        printf("\tallocated = %d\n", is_allocated(cur));
        printf("\tfooter    = %d\n", get_size(cur));
        cur = (Header*)((char*)cur + sizeof(Header) + get_size(cur) + sizeof(Footer));
    }
}

void print_list(){
    Node* t = head;
    while(t != NULL){
        printf("%d -> ", get_size(get_header(t)));
        t = t->next;
    }
}