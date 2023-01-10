#include "Tree.h"
#include <stdio.h>
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

/*Recursive helper function for function addNewNode
*
* root - root of given Tree
* value - value to add into new TreeNode
* size - size to be allocated for value
* compare_node - comparison function
*
* return : returns 1 if value added to tree successfully, 0 otherwise*/
int addNewNode_helper(TreeNode **root, void* value, size_t size, int (*compare_node)(const void* a,const void* b))
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
            return addNewNode_helper(&((*root)->left),value,size,compare_node);
        }
        else if(compare_node(value,(*root)->value) > 0)
        {
            return addNewNode_helper(&((*root)->right),value,size,compare_node);
        }
    }
    return 0;
}

/*Adds a new TreeNode containing given value to tree, and increments Tree's elementCount by 1 
*
* tree - given Tree
* value - value to add into new TreeNode
* size - size to be allocated for value
* compare_node - comparison function
*
* return : returns 1 if value added to tree successfully, 0 otherwise*/
int addNewNode(Tree tree, void* value, size_t size, int (*compare_node)(const void* a,const void* b))
{
    if(addNewNode_helper(&(tree->root),value,size,compare_node))
    {
        tree->elementCount++;
        return 1;
    }
    return 0;
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

/*Helper function for function removeNode
*
* root - root of given Tree
* value - value of TreeNode to be removed
* size - size of value
* compare_node - comparison function
*
* return : returns subtree without removed TreeNode*/
TreeNode* removeNode_helper(TreeNode* root, void* value,size_t size,int (*compare_node)(const void*,const void*))
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
int removeNode(Tree tree, void* value, size_t size, int (*compare_node)(const void*,const void*))
{
    Tree list;
    TreeNode* root; 
    list = findNode(tree,value,size,compare_node);
    if(!list) return 0;
    root = list->root;
    if(tree && root)
    {
        tree->root = removeNode_helper(tree->root,value,size,compare_node);
        if(tree->elementCount == 1) tree->root = NULL;
        tree->elementCount--;
        return 1;
    }
    return 0;
}

/*Recursive helper function to function freeTree
*
* root - root of Tree to be deleted
**/
void freeTree_helper(TreeNode* root)
{
    if (root == NULL) return;
    freeTree_helper(root->left);
    freeTree_helper(root->right);
    freeNode(root);
    root = NULL;
}

/*Deletes all TreeNodes of given Tree, sets Tree's elementCount to 0, and root to NULL
*
* tree - Tree to be deleted
*
* return : returns 1 if Tree deleted successfully, 0 otherwise*/
int freeTree(Tree tree)
{
    if(tree != NULL)
    {
        freeTree_helper(tree->root);
        tree->root = NULL;
        tree->elementCount = 0;
        return 1;
    }
    return 0;
}

/*Finds average of values of tree (sum of values divided by number of nodes)
*
* root - Tree root
* elementCount - number of nodes in the tree
* sum_node - function for determining value of node
*
* return : returns long double representing average of tree values*/
long double averageKey(TreeNode* root,int elementCount,long double (*sum_node)(const void*))
{
    if(!root) return 0;
    return ((sum_node(root->value))/(elementCount))+averageKey(root->right,elementCount,sum_node)+averageKey(root->left,elementCount,sum_node);
}

/*Helper function for treeToArray
*
* root - Tree root
* array - array into which to insert values of tree nodes
* arrSize - size of array
*
* return : returns an array of void* containing values of tree nodes*/
void** treeToArray_helper(TreeNode* root,void** array,size_t arrSize)
{
    if(!root) return array;
    treeToArray_helper(root->left,array,arrSize);
    {
        unsigned int i;
        for(i=0;i<arrSize;i++)
        {
            if(array[i] == NULL)
            {
                array[i] =root->value ;
                break;
            }
        }
    }
    treeToArray_helper(root->right,array,arrSize);
    return array;
}

/*Generates an array of values from given Tree
*
* tree - given Tree
* size - size of element in tree
*
* return : returns an array of void* containing values of tree nodes*/
void** treeToArray(Tree tree,size_t size)
{
    if(tree != NULL && tree->root != NULL)
    {
        void** array;
        int i;
        array = (void**)malloc(size*(tree->elementCount));
        if(!array) return NULL;
        for(i=0;i<tree->elementCount;i++) array[i] = NULL;
        return treeToArray_helper(tree->root,array,tree->elementCount);
    }
    return NULL;
}


/*Adds a value to the end of a linked list (in the form of a degenerated Tree) of TreeNodes
*
* list - given list (in the form of a degenerated Tree, where root is first element)
* value - value to add
* size - size of value
*
* return : returns 1 if successful, 0 otherwise*/
int addToEnd(Tree list, void* value,size_t size)
{
    if(list != NULL && value != NULL && size > 0)
    {
        if(list->root == NULL)
        {
            list->root = (TreeNode*)malloc(sizeof(TreeNode));
            list->root->value = malloc(size);
            if(!list->root || !list->root->value) return 0;
            memcpy(list->root->value,value,size);
            list->root->right = NULL;
            list->root->left = NULL;
            list->elementCount++;
            return 1;
        }
        else
        {
            TreeNode* scan;
            TreeNode* newNode;
            newNode = (TreeNode*)malloc(sizeof(TreeNode));
            newNode->value = malloc(size);
            if(!newNode || !newNode->value) return 0;
            memcpy(newNode->value,value,size);
            scan = findMax(list->root);
            scan->right = newNode;
            newNode->left = scan;
            list->elementCount++;
            return 1;
        }
    }
    return 0;
}


/*Recursive helper function to function findNode
*
* root - node
* list - linked list (in the form of a degenerated Tree)
* value - value of requested TreeNode
* size - size of value
* compare_node - comparison function
*
* return : returns requested TreeNode if successful, NULL otherwise*/
Tree findNode_helper(TreeNode* root,Tree list,void* value,size_t size,int (*compare_node)(const void* a ,const void* b))
{
    if(!root) return NULL;
    findNode_helper(root->left,list,value,size ,compare_node);
    if(compare_node(root->value,value) == 0) addToEnd(list,root->value,size);
    findNode_helper(root->right,list,value,size,compare_node);
    return list;
}

/*Finds all nodes in a given Tree which satisfy a condition according to a comparison function, and returns a linked list 
* (in the form of a degenerated Tree) of the nodes found
*
* tree - given Tree
* value - value of requested TreeNode
* size - size of value
* compare_node - comparison function
*
* return : returns a linked list (degenerated tree) of nodes found if successful, NULL otherwise*/
Tree findNode(Tree tree, void* value,size_t size,int (*compare_node)(const void* a ,const void* b))
{
    if(tree != NULL && tree->root != NULL && value != NULL)
    {
        Tree list;
        list = createTree();
        list = findNode_helper(tree->root,list,value,size,compare_node);
        if(list->root == NULL || list == NULL)
        {
            free(list);
            return NULL;
        }
        return list;
    }
    return NULL;
}

/*Helper function to function printTree
*
* root - Tree root
* print_value - function which prints the string representation of value in TreeNode
*
* return : returns 1 if successful, 0 otherwise*/
int printTree_helper(TreeNode* root, int (*print_value)(const void* value))
{
    if(!root) return 0;
    printTree_helper(root->left,print_value);
    print_value(root->value);
    printTree_helper(root->right,print_value);
    return 1;
}

/*Prints all string representations of values in given Tree, in Inorder traversal
*
* tree - given Tree
* print_value - function which prints the string representation of value in TreeNode
*
* return : returns 1 if successful, 0 otherwise and prints an a message*/
int printTree(Tree tree, int (*print_value)(const void* value))
{
    if(tree != NULL && tree->root != NULL)
    {
        return printTree_helper(tree->root,print_value);
    }
    else printf("\nTree null or empty\n");
    return 0;
}




