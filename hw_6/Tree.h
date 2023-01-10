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
* value - value to insert into new TreeNode
* size - size to be allocated for value
* compare_node - comparison function
*
* return : returns 1 if value added to tree successfully, 0 otherwise*/
int insert(Tree tree, void* value,size_t size,int (*compare_node)(const void* a, const void* b));

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
int deleteNode(Tree tree, void* value, size_t size, int (*compare_node)(const void*,const void*));

/*Deletes all TreeNodes of given Tree, sets Tree's elementCount to 0, and root to NULL
*
* tree - Tree to be deleted
*
* return : returns 1 if Tree deleted successfully, 0 otherwise*/
int deleteTree(Tree tree);
#endif