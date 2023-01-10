#ifndef TREE_H
#define TREE_H
#include <stddef.h>

typedef struct treeNode
{
    struct treeNode* left;
    struct treeNode* right;
    void* value;
} TreeNode;

typedef struct tree
{
    struct treeNode* root;
    int elementCount;
}tree;

typedef struct tree* Tree;

/*Generates an empty Tree, with root set to NULL
*
* return : returns empty Tree*/
Tree createTree();

/*Adds a new TreeNode containing given value to tree, and increments Tree's elementCount by 1 
*
* tree - given Tree
* value - value to add into new TreeNode
* size - size to be allocated for value
* compare_node - comparison function
*
* return : returns 1 if value added to tree successfully, 0 otherwise*/
int addNewNode(Tree tree, void* value,size_t size,int (*compare_node)(const void* a, const void* b));

/*Frees memory allocated to TreeNode
*
* node - given TreeNode
*
* return : returns 1 if successful, 0 otherwise*/
int freeNode(TreeNode* node);

/*Searches for a TreeNode with given value in given Tree
*
* tree - given Tree
* value - value of requested TreeNode
* compare_node - comparison function
*
* return : returns requested TreeNode if successful, NULL otherwise*/
TreeNode* search(Tree tree, void* value, int (*compare_node)(const void* a ,const void* b));

/*Finds minimal element in Tree with given root
*
* root - root of Tree
*
* return : returns leftmost (minimal value) TreeNode in Tree*/
TreeNode* findMin(TreeNode* root);

/*Finds maximal element in Tree with given root
*
* root - root of Tree
*
* return : returns rightmost (maximal value) TreeNode in Tree*/
TreeNode* findMax(TreeNode* root);

/*Deletes a TreeNode with given value, and decrements Tree's elementCount
*
* tree - given Tree
* value - value of TreeNode to be removed
* size - size of value
* compare_node - comparison function
*
* return : returns 1 if TreeNode was removed successfully, 0 otherwise*/
int removeNode(Tree tree, void* value, size_t size, int (*compare_node)(const void*,const void*));

/*Deletes all TreeNodes of given Tree, sets Tree's elementCount to 0, and root to NULL
*
* tree - Tree to be deleted
*
* return : returns 1 if Tree deleted successfully, 0 otherwise*/
int freeTree(Tree tree);

/*Finds average of values of tree (sum of values divided by number of nodes)
*
* root - Tree root
* elementCount - number of nodes in the tree
* sum_node - function for determining value of node
*
* return : returns long double representing average of tree values*/
long double averageKey(TreeNode* root,int elementCount,long double (*sum_node)(const void*));

/*Generates an array of values from given Tree
*
* tree - given Tree
* size - size of element in tree
*
* return : returns an array of void* containing values of tree nodes*/
void** treeToArray(Tree tree,size_t size);

/*Finds all nodes in a given Tree which satisfy a condition according to a comparison function, and returns a linked list 
* (in the form of a degenerated Tree) of the nodes found
*
* tree - given Tree
* value - value of requested TreeNode
* size - size of value
* compare_node - comparison function
*
* return : returns a linked list (degenerated tree) of nodes found if successful, NULL otherwise*/
Tree findNode(Tree tree, void* value,size_t size ,int (*compare_node)(const void* a ,const void* b));

/*Prints all string representations of values in given Tree, in Inorder traversal
*
* tree - given Tree
* print_value - function which prints the string representation of value in TreeNode
*
* return : returns 1 if successful, 0 otherwise and prints an a message*/
int printTree(Tree tree, int (*print_value)(const void* value));

#endif