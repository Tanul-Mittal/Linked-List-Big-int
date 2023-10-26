#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node* next;
};
struct BigInteger{
    struct node *L;
};
void display(struct node* );
struct node * frontzeroterminator(struct node * );
struct node * reverse(struct node *);
int compare(struct node *, struct node *);
void inserthead(struct node** , int );
struct node * convert(char *);
struct node* addition(struct node *,struct node* );
struct node * multiply(struct node *, struct node *);
struct node* Subtraction(struct node*,struct node *);
struct node* division(struct node* ,struct node *);
struct BigInteger initialize(char *);
struct BigInteger add(struct BigInteger ,struct BigInteger );
struct BigInteger sub(struct BigInteger ,struct BigInteger );
struct BigInteger mul(struct BigInteger ,struct BigInteger );
struct BigInteger div1(struct BigInteger ,struct BigInteger );


#endif
