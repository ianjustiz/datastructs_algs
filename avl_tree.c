#include <stdio.h>
#include <stdlib.h>

typedef struct avl_node
{
	struct avl_node *left;
	struct avl_node *right;
	int height;
	int data;
} node;

int get_balance_factor(node *root)
{
	if (root == NULL || root->left == root->right)
		return 0;

	if (root->left == NULL)
		return -1 * root->right->height;

	if (root->right == NULL)
		return root->left->height;

	return root->left->height - root->right->height;
}

node *create_node(int data)
{
	node *new_node = malloc(sizeof(node));

	new_node->left = NULL;
	new_node->right = NULL;

	new_node->height = 0;
	new_node->data = data;

	return new_node;
}

node *left_rotation(node *root)
{
	node *old, *temp;

	if (root == NULL)
		return NULL;

	old = root;
	root = root->right;

	temp = root->left;

	root->left = old;
	old->right = temp;

	return root;
}

node *right_rotation(node *root)
{
	if (root == NULL)
		return NULL;

	old = root;
	root = root->left;

	temp = root->right;

	root->right = old;
	old->left = temp;

	return root;
}

node *insert_recursive(node *root, int data, int *height)
{
	int bf;
	int dir;

	if (root == NULL)
	{
		*height = 0;
		return create_node(data);
	}

	if (data <= root->data)
	{
		root->left = insert_recursive(root->left, data, height);
		*height++;
		dir = 1;
	}
	else
	{
		root->right = insert_recursive(root->right, data, height);
		*height++;
		dir = -1;
	}

	// Update height of current node, if needed.
	if (root->height < *height)
		root->height = height;

	bf = get_balance_factor(root);

	// If an unbalanced node is found,
	if (bf > 1 || bf < -1)
	{
		// Node was inserted left side -
		if (dir > 0)
		{
			// Opposite signs - 
			// (LR)
			if (get_balance_factor(root->left) < 0)
			{
				root->left = left_rotation(root->left);
				root = right_rotation(left);
			}

			// Matching signs (or balanced) -
			// (LL)
			else
			{
				root = right_rotation(root);
			}
		}

		// Node was inserted right side -
		else
		{
			// Opposite signs - 
			// (RL)
			if (get_balance_factor(root->right) > 0)
			{
				root->right = right_rotation(root->right);
				root = left_rotation(right);
			}

			// Matching signs (or balanced) -
			// (RR)
			else
			{
				left_rotation(root);
			}
		}
	}
}

node *insert(node *root, int data)
{
	int *height;

	height = malloc(sizeof(int));
	insert_recursive(root, data, height);

	free(height);
}