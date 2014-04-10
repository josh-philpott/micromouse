#include <stdlib.h>
//#include <stdio.h>

struct node{
  int x;
  struct node * next;
  struct node * prev;
};

struct node * root;
struct node * tail;

void push(int);
int pop();
int peek();
int isEmpty();