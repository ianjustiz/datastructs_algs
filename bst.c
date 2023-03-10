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
		root->left = insert(root->left, data);
		return root;
	}
	else
	{
		root->right = insert(root->right, data);
		return root;
	}
}

node *delete(node *root, int data)
{
	node *rep;
	int temp;

	if (root == NULL)
		return NULL;

	// Recursive calls to delete if not located at root.
	if (root->data > data)
	{
		root->left = delete(root->left, data);
		return root; 
	}
	else if (root->data < data)
	{
		root->right = delete(root->right, data);
		return root;
	}

	// Case 1: No child nodes.
	if (root->left == root->right)
	{
		free(root);
		return NULL;
	}

	// Case 2: Two child nodes.
	if (root->left != NULL && root->right != NULL)
	{
		// Find largest element on lefthand side.
		rep = root->left;

		while (rep->right != NULL)
			rep = rep->right;

		// Move rep value into location of temp and free.
		temp = rep->data;
		delete(root, temp);
		root->data = temp;

		return root;
	}

	// Case 3a: One child node, left side.
	if (root->left != NULL)
	{
		rep = root->left;
		free(root);
		return rep;
	}

	// Case 3b: One child node, right side.
	else
	{
		rep = root->right;
		free(root);
		return rep;
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

	root = delete(root, 15);

	root = delete(root, 7);

	inorder(root);
}