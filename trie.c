#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct trieNode
{
	int count;
	struct trieNode *nodes[26];
} trieNode;

trieNode *createNode(int count)
{
	trieNode *node;
	int i;

	node = malloc(sizeof(trieNode));
	node->count = count;

	for (i = 0; i < 26; i++)
		node->nodes[i] = NULL;

	return node;
}

trieNode *addString(trieNode *root, char *str)
{
	int i, ch;
	trieNode *curr;

	if (root == NULL)
		root = createNode(1);

	curr = root;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isalpha(str[i]))
			break;
		
		ch = tolower(str[i]) - 'a';

		if (curr->nodes[ch] == NULL)
			curr->nodes[ch] = createNode(0);

		curr = curr->nodes[ch];
	}

	curr->count++;

	return root;
}

int isContained(trieNode *root, char *str)
{
	int i, ch;
	trieNode *curr;

	if (root == NULL)
		return str == NULL || *str == '\0';

	curr = root;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isalpha(str[i]))
			return 0;
		
		ch = tolower(str[i]) - 'a';
		curr = curr->nodes[ch];

		if (curr == NULL)
			return 0;
	}

	if (curr->count > 0)
		return 1;

	return 0;
}

// Main Method (for testing only)
int main(void)
{
	trieNode *cool = createNode(0);

	printf("test\n\n");
	fflush(stdout);

	cool = addString(cool, "hello");

	if (isContained(cool, "hell"))
		printf("nice\n");
	else
		printf("oh no!\n");
}