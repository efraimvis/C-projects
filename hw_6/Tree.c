#include "Tree.h"
#include <stdlib.h>
#include <string.h>


/*Generates an empty Tree, with root set to NULL
*
* return : returns empty Tree*/
Tree createTree()
{
    Tree tree;
    tree = (Tree)malloc(sizeof(struct tree));
    if(!tree) return NULL;
    tree->root = NULL;
    tree->elementCount = 0;
    return tree;
}

/*Frees memory allocated to TreeNode
*
* node - given TreeNode
*
* return : returns 1 if successful, 0 otherwise*/
int freeNode(TreeNode* node)
{
    if(node != NULL)
    {   
        free(node->value);
        free(node);
        return 1;
    }
    return 0;
}

/*Recursive helper function for function insert
*
* root - root of given Tree
* value - value to insert into new TreeNode
* size - size to be allocated for value
* compare_node - comparison function
*
* return : returns 1 if value added to tree successfully, 0 otherwise*/
int insert_helper(TreeNode **root, void* value, size_t size, int (*compare_node)(const void* a,const void* b))
{
    if(*root == NULL)
    {
        *root = (TreeNode*)malloc(sizeof(TreeNode));
        if(!(*root))
        { 
            free(*root);
            return 0;
        }
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->value = malloc(size);
        if(!((*root)->value))
        {
            free((*root)->value);
            return 0;
        }
        memcpy((*root)->value,value,size);
        return 1;
    }
    else
    {
        if(compare_node(value,(*root)->value) < 0)
        {
            return insert_helper(&((*root)->left),value,size,compare_node);
        }
        else if(compare_node(value,(*root)->value) > 0)
        {
            return insert_helper(&((*root)->right),value,size,compare_node);
        }
    }
    return 0;
}

/*Adds a new TreeNode containing given value to tree, and increments Tree's elementCount by 1 
*
* tree - given Tree
* value - value to insert into new TreeNode
* size - size to be allocated for value
* compare_node - comparison function
*
* return : returns 1 if value added to tree successfully, 0 otherwise*/
int insert(Tree tree, void* value, size_t size, int (*compare_node)(const void* a,const void* b))
{
    if(insert_helper(&(tree->root),value,size,compare_node))
    {
        tree->elementCount++;
        return 1;
    }
    return 0;
}

/*Recursive helper function to function search
*
* root - node
* value - value of requested TreeNode
* compare_node - comparison function
*
* return : returns requested TreeNode if successful, NULL otherwise*/
TreeNode* search_helper(TreeNode* root, void* value, int (*compare_node)(const void* a ,const void* b))
{
    if (root == NULL) return NULL;
    else if (compare_node(value,root->value) > 0) return search_helper(root->right, value, compare_node);
    else if (compare_node(value,root->value) < 0) return search_helper(root->left, value, compare_node);
    else return root;
}

/*Searches for a TreeNode with given value in given Tree
*
* tree - given Tree
* value - value of requested TreeNode
* compare_node - comparison function
*
* return : returns requested TreeNode if successful, NULL otherwise*/
TreeNode* search(Tree tree, void* value, int (*compare_node)(const void* a ,const void* b))
{
    return search_helper(tree->root,value,compare_node);
}

/*Finds minimal element in Tree with given root
*
* root - root of Tree
*
* return : returns leftmost (minimal value) TreeNode in Tree*/
TreeNode* findMin(TreeNode* root) 
{
    if(!root || !(root->left)) return root;
    return findMin(root->left);
}

/*Finds maximal element in Tree with given root
*
* root - root of Tree
*
* return : returns rightmost (maximal value) TreeNode in Tree*/
TreeNode* findMax(TreeNode* root)
{
    if(!root || !(root->right)) return root;
    else return findMax(root->right);
}

/*Helper function for function deleteNode
*
* root - root of given Tree
* value - value of TreeNode to be removed
* size - size of value
* compare_node - comparison function
*
* return : returns subtree without removed TreeNode*/
TreeNode* deleteNode_helper(TreeNode* root, void* value,size_t size,int (*compare_node)(const void*,const void*))
{   
    TreeNode* curr;
    TreeNode* prev;

    curr = root;
    prev = NULL;

    while (curr != NULL && compare_node(curr->value,value) != 0)
    {
        prev = curr;
        if(compare_node(value,curr->value) < 0) curr = curr->left;
        else  curr = curr->right;
    }
    if (curr == NULL)
    {
        return root;
    }
    if (curr->left == NULL || curr->right == NULL)
    {
        TreeNode* newCurr;
        if (curr->left == NULL) newCurr = curr->right;
        else newCurr = curr->left;
        if (prev == NULL) return newCurr;
        if (curr == prev->left) prev->left = newCurr;
        else prev->right = newCurr;
        freeNode(curr);
    }
    else
    {
        TreeNode* p;
        TreeNode* temp;
        p = NULL;
        temp = curr->right;
        while (temp->left != NULL)
        {
            p = temp;
            temp = temp->left;
        }
        if (p != NULL)  p->left = temp->right;
        else curr->right = temp->right;
        memcpy(curr->value,temp->value,size);
        freeNode(temp);
    }
    return root;
}

/*Deletes a TreeNode with given value, and decrements Tree's elementCount
*
* tree - given Tree
* value - value of TreeNode to be removed
* size - size of value
* compare_node - comparison function
*
* return : returns 1 if TreeNode was removed successfully, 0 otherwise*/
int deleteNode(Tree tree, void* value, size_t size, int (*compare_node)(const void*,const void*))
{
    TreeNode* root = search(tree,value,compare_node);
    if(tree && root)
    {
        tree->root = deleteNode_helper(tree->root,value,size,compare_node);
        if(tree->elementCount == 1) tree->root = NULL;
        tree->elementCount--;
        return 1;
    }
    return 0;
}

/*Recursive helper function to function deleteTree
*
* root - root of Tree to be deleted
**/
void deleteTree_helper(TreeNode* root)
{
    if (root == NULL) return;
    deleteTree_helper(root->left);
    deleteTree_helper(root->right);
    freeNode(root);
    root = NULL;
}

/*Deletes all TreeNodes of given Tree, sets Tree's elementCount to 0, and root to NULL
*
* tree - Tree to be deleted
*
* return : returns 1 if Tree deleted successfully, 0 otherwise*/
int deleteTree(Tree tree)
{
    if(tree != NULL)
    {
        deleteTree_helper(tree->root);
        tree->root = NULL;
        tree->elementCount = 0;
        return 1;
    }
    return 0;
}


