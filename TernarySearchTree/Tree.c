#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Tree.h"


// A utility function to create a new ternary search tree node
Node *newNode(char data)
{
    Node *temp = (Node *) malloc(sizeof(Node));

    temp->data = data;
    temp->isEndOfString = false;
    temp->left = temp->eq = temp->right = NULL;

    return temp;
}


// Function to insert a new word in a Ternary Search Tree
void insert(Node **root, char *word)
{
    // Base Case: Tree is empty.
    if (!(*root))
    {
        *root = newNode(*word);
    }

    // If current character of word is smaller than root's character, then insert this word in left subtree of root.
    if ((*word) < (*root)->data)
    {
        insert(&((*root)->left), word);
    } // If current character of word is greater than root's character, then insert this word in right subtree of root.
    else if ((*word) > (*root)->data)
    {
        insert(&((*root)->right), word);
    } // If current character of word is same as root's character.
    else
    {
        if (*(word + 1))
        {
            insert(&((*root)->eq), word + 1);
        }
        else // The last character of the word.
        {
            (*root)->isEndOfString = 1;
        }
    }
}


// A recursive function to traverse Ternary Search Tree.
void traverseTSTUtil(Node *root, char *buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree.
        traverseTSTUtil(root->left, buffer, depth);

        // Store the character of this node.
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth + 1] = '\0';
            printf("%s\n", buffer);
        }

        // Traverse the subtree using equal pointer (middle subtree).
        traverseTSTUtil(root->eq, buffer, depth + 1);

        // Finally, traverse the right subtree.
        traverseTSTUtil(root->right, buffer, depth);
    }
}


// The main function to traverse a Ternary Search Tree. It mainly uses traverseTSTUtil().
void traverseTST(Node *root)
{
    char buffer[CHAR_MAX];

    traverseTSTUtil(root, buffer, 0);
}


// Function to search a given word in TST.
int searchTST(Node *root, char *word)
{
    if (!root)
    {
        return 0;
    }

    if (*word < (root)->data)
    {
        return searchTST(root->left, word);
    }

    else if (*word > (root)->data)
    {
        return searchTST(root->right, word);
    }

    else
    {
        if (*(word + 1) == '\0')
        {
            return root->isEndOfString;
        }

        return searchTST(root->eq, word + 1);
    }
}