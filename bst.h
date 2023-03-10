
// Binary Search Tree in C

#ifndef _BST_H
#define _BST_H

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
} node;


node *create_node(int data);

node *search(node *root, int data);

node *insert(node *root, int data);

node *delete(node *root, int data);

void inorder(node *root);

#endif