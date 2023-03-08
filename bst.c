#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
} node;

node *create_node(int data)
{
	node *new_node = malloc(sizeof(node));

	new_node->left = new_node->right = NULL;
	new_node->data = data;

	return new_node;
}

node *search(node *root, int data)
{
	if (root == NULL)
		return NULL;

	if (data == root->data)
		return root;
	else if (data < root->data)
		return search(root->left, data);
	else
		return search(root->right, data);
}

node *insert(node *root, int data)
{
	if (root == NULL)
		return create_node(data);

	if (data <= root->data)
	{
		insert(root->left, data);
		return root;
	}
	else
	{
		insert(root->right, data);
		return root;
	}
}

void delete(node *root, int data)
{
	node *temp;
	node *rep;

	temp = search(root, data);

	if (root == NULL || search == NULL)
		return;

	// Case 1: No child nodes.
	if (temp->left == temp->right == NULL)
	{
		free(temp);
		temp = NULL;
	}

	// Case 2: Two child nodes.
	if (temp->left != NULL && temp->right != NULL)
	{
		// Find largest element on lefthand side.
		rep = temp->left;

		while (rep->right != NULL)
			rep = rep->right;

		// Move rep value into location of temp and free.
		temp->data = rep->data;
		free(rep);
		rep = NULL;
	}

	// Case 3a: One child node, left side.
	if (temp->left != NULL)
	{
		rep = temp->left;
		free(temp);
		temp = rep;
	}

	// Case 3b: One child node, right side.
	else
	{
		rep = temp->right;
		free(temp);
		temp = rep;
	}
}

void inorder(node *root)
{
	if (root == NULL)
		return;

	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

int main(void)
{
	node *root;
	root = insert(root, 15);
	root = insert(root, 93);
	root = insert(root, 22);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 45);

	inorder(root);
}