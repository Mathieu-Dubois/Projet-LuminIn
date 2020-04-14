#include "liste.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <malloc.h>

node* l_make_node(void* data)
{
  node* noeud = (node*)malloc(sizeof(node));
  assert(noeud);

  noeud->previous = NULL;
  noeud->next = NULL;
  noeud->data = data;

   return noeud;
}

void l_free_node(node* n)
{
    if(n->data) free(n->data);
    free(n);
    return;
}

void l_free_list(node* n)
{
    node* nd = n;
    while (n->next != NULL){
        nd = n->next;
        free(n);
        n = nd;
    }
    free(n);

    return;
}

int l_length(node const* n)
{
    int x=0;
    if(n){
        x=1;
        while(n->next != NULL){
            n=n->next;  
        }

        while(n->previous != NULL){
            n=n->previous;  
            x=x+1;
        }


    } 
    return x;
}

node* l_head(node* n)
{
    if(n){
        while(n->previous != NULL){
            n = n->previous;
        }
        return n;
    }
    else return NULL;  
}

node* l_tail(node* n)
{
    if(n==NULL) return NULL;
    else{
        while(n->next!=NULL){
            n=n->next;
        }
    }
    return n;
}

node* l_skip(node* n, int i)
{
    int j, code;
    if (n != NULL){
        code = 0;
        if (i >= 0){    //Dans ce cas on avance
            j = 0;
            while (j<i && code == 0){
                n = n->next;
                if(n == NULL) code = 1;
                j++;
            }
        } else {        //Dans ce cas on recule
            j = 0;
            while (j>i && code == 0){
                n = n->previous;
                if(n == NULL) code = 1;
                j--;
            }
        }
    }
    if (code != 0) return NULL;
    return n;
}

node* l_append(node** p, node* tail)
{
    assert(p);
    if (*p == NULL){
        *p = tail;
    } else {
        tail->previous = l_tail(*p);
        l_tail(*p)->next = tail;
        tail->next = NULL;
    }
    return tail;
}

node* l_prepend(node** p, node* head)
{
    assert(p);
    if (*p == NULL){
        *p = head;
    } else {
        head->next = l_head(*p);
        l_head(*p)->previous = head;
        head->previous = NULL;
    }
    
    return head;
}

node* l_insert(node** p, node* body)
{
    assert(p);
    if(*p==NULL){
        *p=body;
    }
    else if((*p)->next==NULL){ 
        (*p)->next = body;
        body->next=NULL;
        body->previous=(*p);
    }
    else{
        body->next=(*p)->next;
        (*p)->next=body;
        (*p)->next->previous=*p;
        (*p)->next->next->previous=(*p)->next;
    }
    return body;
}

node* l_remove(node* n)
{
    node *tmp;
    if(n){
        if(n->previous != NULL && n->next != NULL){
            n->previous->next = n->next;
            n->next->previous = n->previous;
            tmp = n->next;
            free(n);
            return tmp;
        }
        else if(n->previous == NULL && n->next != NULL){
            n->next->previous = NULL;
            tmp = n->next;
            free(n);
            return tmp;
        }
        else if(n->next == NULL && n->previous != NULL){
            n->previous->next = NULL;
            free(n);
            return NULL;
        }
        else if (n->next == NULL && n->previous == NULL){
            free(n);
            return NULL;
        }
    }
    return NULL;
}
