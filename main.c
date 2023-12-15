#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"leak_detector_c.h"

/*
  COP3502 Programming Assignment 4
  Written by: Ronit Mahalmani
*/

//max length of string + 1 for \0
#define MAXLEN 50 

//global file pointers
FILE *infile, *outfile;

//struct for item node
typedef struct itemNode 
{ 
  char name[MAXLEN]; 
  int count; 
  struct itemNode *left, *right; 
}itemNode; 

//struct for tree name node
typedef struct treeNameNode 
{ 
  char treeName[MAXLEN]; 
  struct treeNameNode *left, *right; 
  itemNode *theTree; 
}treeNameNode; 

//function prototypes
treeNameNode* createTreeNameNode(char name[MAXLEN]);
treeNameNode* buildNameTree(treeNameNode* root, int numNameTrees);
treeNameNode* insertTreeName(treeNameNode* root, treeNameNode* temp);
void inorderNameTree(treeNameNode* curPointer);
treeNameNode * searchNameNode(treeNameNode * root, char treeName[50]);
itemNode* insertItem(itemNode* root, itemNode* temp);
void traverse_in_traverse(treeNameNode *root);
void throughItemTree(itemNode* itemRoot);
itemNode* placeItemNode(treeNameNode *treeNameRoot, itemNode* itemRoot, int numInsertions);



itemNode* createItemNode(char itemName[MAXLEN], int count){
  //DMA an item node
  itemNode* itemNode = malloc(sizeof(itemNode));

  //copies item count and name to the right part of DMA'ed item struct
  strcpy(itemNode->name, itemName);
  itemNode->count = count;
  
  itemNode->left = NULL;
  itemNode->right = NULL;

  return itemNode;
}

itemNode* placeItemNode(treeNameNode *treeNameRoot, itemNode* itemRoot, int numInsertions){
  char treeName[50], itemName[MAXLEN];
  int count;

  itemNode* tempItemNode;
  treeNameNode* rightNameNode;
  
  for(int i = 0; i < numInsertions; i++){
    //scan elements from file
    fscanf(infile, "%s %s %d", treeName, itemName, &count);

    //treeNode to have correct pointer to point from treeNode->theTree to correct itemNode bst
    rightNameNode = searchNameNode(treeNameRoot, treeName);
    
    //temp item node to insert into itemNode bst
    tempItemNode = createItemNode(itemName, count);
    
    rightNameNode->theTree = insertItem(rightNameNode->theTree, tempItemNode);
    
  }
  return itemRoot;
}

itemNode* insertItem(itemNode* root, itemNode* temp){
  //if root is null than have the new DMA'ed item node to be the root of the item node BST
  
  if(root == NULL){ 
    
    return temp;
    
  }

  //if root is not null
    
  else{
    
    //go to left since the DMA'ed node's string is smaller than the root's string
    
    if(strcmp(root->name, temp->name) > 0){

      //check if anything is on left side

      if(root->left != NULL){
        
        root->left = insertItem(root->left, temp);
      }
        
      //left side has nothing
        
      else{
        root->left = temp; //assigns the DMA'ed node to the left side since it's null
      }
      
    }
      
    //go to right since string is greater than the "root"   
      
    else{
      
      //if right side has some value
      
      if(root->right != NULL){
        
        //insert to right side
        root->right = insertItem(root->right, temp);
        
      }
      else{
        root->right = temp; //assigns the DMA'ed node to the right side since it's null
      }
      
    }

    return root;
        
  }
  
}

//function that makes a new name tree node
treeNameNode* createTreeNameNode(char name[MAXLEN]){
  //dma a treeNameNode
  treeNameNode* nameNode = malloc(sizeof(treeNameNode)); 
  
  //copy string from in file to the treeName part of struct
  strcpy(nameNode->treeName, name);

  //assigns the remaining parts of the treeName struct to NULL
  nameNode->left = NULL;
  nameNode->right = NULL;
  nameNode->theTree = NULL;

  return nameNode;

}

treeNameNode* buildNameTree(treeNameNode* root, int numNameTrees){
  //temp root in order to insert into treeName BST
  treeNameNode* tempNode;

  //temp static array to tranfer into name part of treeNameNode struct
  char name[MAXLEN];

  //loop assigns name part and inserts a nameTree node by updating root with another temporary node
  for(int i = 0; i < numNameTrees; i++){
    fscanf(infile, "%s", name);
    tempNode = createTreeNameNode(name);
    root = insertTreeName(root, tempNode);
  }

  return root;
  
}

treeNameNode* insertTreeName(treeNameNode* root, treeNameNode* temp){
  //if root is null than have the new DMA'ed treeName node to be the root of the treeName BST
  
  if(root == NULL){ 
    
    return temp;
    
  }

  //if root is not null
    
  else{
    
    //go to left since the DMA'ed node's string is smaller than the root's string
    
    if(strcmp(root->treeName, temp->treeName) > 0){

      //check if anything is on left side

      if(root->left != NULL){
        
        root->left = insertTreeName(root->left, temp);
      }
        
      //left side has nothing
        
      else{
        root->left = temp; //assigns the DMA'ed node to the left side since it's null
      }
      
    }
      
    //go to right since string is greater than the "root"   
      
    else{
      
      //if right side has some value
      
      if(root->right != NULL){
        
        //insert to right side
        root->right = insertTreeName(root->right, temp);
        
      }
      else{
        root->right = temp; //assigns the DMA'ed node to the right side since it's null
      }
      
    }

    return root;
        
  }
  
}

void inorderNameTree(treeNameNode* curPointer){
  if(curPointer != NULL){
    
    //left->root->right
    inorderNameTree(curPointer->left);
    printf("%s ", curPointer->treeName);
    fprintf(outfile, "%s ", curPointer->treeName);
    inorderNameTree(curPointer->right);
  }
  
}

treeNameNode * searchNameNode(treeNameNode * root, char treeName[50]){
  //if no root then return null
  
  if(root == NULL){
    
    return root;
    
  }

  //there are nodes
    
  else{
    
    //if treeName has same string return that node
    
    if(strcmp(root->treeName, treeName) == 0){
      
      return root;
      
    }
    //if treeName string is smaller than tree name then go to left side
    
    if(strcmp(root->treeName, treeName) > 0){
      
      return searchNameNode(root->left, treeName);
      
    }
    //if treeName string is greater than tree name then go to right side
      
    else{
      
      return searchNameNode(root->right, treeName);
      
    }
    
  }  

}


void traverse_in_traverse(treeNameNode *root){
  if(root != NULL){
    
    //left->root->right
    traverse_in_traverse(root->left);
    printf("\n===%s===\n", root->treeName);
    fprintf(outfile,"\n===%s===\n", root->treeName);
    throughItemTree(root->theTree);
    traverse_in_traverse(root->right);
  }
}

void throughItemTree(itemNode* item){
  if(item != NULL){
    
    //left->root->right
    throughItemTree(item->left);
    printf("%s ", item->name);
    fprintf(outfile, "%s ", item->name);
    throughItemTree(item->right);

  }
}


//takes in treeNameNode of the correct type for searching
itemNode* searchquery(itemNode* itemNode, char itemName[MAXLEN]){
  
  //no items are in that tree
  if(itemNode == NULL){
    return NULL;
  }

  //there are items in the tree
  else{
    //if item node has same string as search item then return it
    
    if(strcmp(itemNode->name, itemName) == 0){
      
      return itemNode;
      
    }

    //if search item string is smaller than itemNode string go to left
    
    if(strcmp(itemNode->name, itemName) > 0){
      
      return searchquery(itemNode->left, itemName);
      
    }
    //if search item string is larger than itemNode string go to right
      
    else{
      
      return searchquery(itemNode->right, itemName);
      
    }
    
  }
  
}

//takes in correct Name Node of treeName input wants to add up
int count(itemNode* itemNode){
  
  
  //no nodes/base case
  if(itemNode == NULL){
    
    return 0;
    
  }
    
    
  else{
    //traverses through left and right side til one reaches null and then adds the subsequent count values 
    return itemNode->count + count(itemNode->left) + count(itemNode->right);
    
  }
  
}

int itemBefore(itemNode* node, char itemB4[50]){
  
  if(node == NULL || strcmp(node->name, itemB4) == 0){
    return 0;
  }
  
  if(strcmp(node->name, itemB4) > 0){
    return 1;
  }
  
  return  1 + itemBefore(node->left, itemB4) + itemBefore(node->right, itemB4);
  
  
    
}

int height(itemNode* node){
  if(node == NULL){
    return 0;
  }

  int rightHeight, leftHeight;
  
  rightHeight = height(node->right);
  
  leftHeight = height(node->left);
  
  if(leftHeight > rightHeight){
    return 1 + leftHeight;
  }
    
  else{
    return 1 + rightHeight;
  }
}

//returns parent node if there is one
itemNode* parentNode(itemNode* root, itemNode* deleteNode){
  
  //for null cases
  
  if(root == NULL || root == deleteNode){
    
    return NULL;
    
  }
  
  //root is parent of the node
  
  if(root->left == deleteNode || root->right == deleteNode){
    
    return root;
    
  }

  //find node's parent in left side of tree 
  
  if(strcmp(root->name, deleteNode->name) > 0){
    
    return parentNode(root->left, deleteNode);
    
  }

  //find node's parent in right side of tree 
  
  else if(strcmp(root->name, deleteNode->name) < 0){
    
    return parentNode(root->right, deleteNode);
    
  }
    
  
}

//finds the lowest value string in item struct

itemNode* minNode(itemNode* root){
  
  //left most item is lowest b/c the way BST is set up
  
  if(root->left == NULL){
    
    return root;
    
  }
//left side of tree has lowest string value thingy :)
    
  else{
    
    return minNode(root->left);
    
  }
  
}

//same thing as min node but for greatest values so you use right side this time 
itemNode* maxNode(itemNode* root){
  
  //right most item is highest b/c the way BST is set up
  
  if(root->right == NULL){
    
    return root;
    
  }
//right side of tree has highest string value thingy :)
    
  else{
    
    return maxNode(root->right);
    
  }
  
}

//1 if node is leaf
//0 if not isn't leaf

int isLeaf(itemNode* node){
  
  //sees if left and right links are null, if it is a leaf node
  
  return (node->left == NULL && node->right == NULL);
  
}

//1 if node has left child
//0 if nodes doesn't have left child

int hasOnlyLeftChild(itemNode* node){
  
  return (node->left != NULL && node->right == NULL);
  
}

//1 if node has right child
//0 if nodes doesn't have right child

int hasOnlyRightChild(itemNode* node){
  
  return (node->right != NULL && node->left == NULL);
  
}

//returns pointer to root after deletion

itemNode* delete(itemNode* root, char itemName[50]) {
  
  itemNode *delnode, *new_del_node, *save_node;
  itemNode *par;
  char saveName[50];

  //assigns node to node from input string
  delnode = searchquery(root, itemName); 


  //gets parent
  par = parentNode(root, delnode); 
  
  // if node to delete is  leaf node.
  
  if (isLeaf(delnode)) {
    
    // Deleting the only node in the tree.
    
    if (par == NULL) {
      
      free(root); 
      
      return NULL;
    }
    // Deletes node if left child.
    if (strcmp(root->name, itemName) > 0) {
      
      free(par->left); 
      
      par->left = NULL;
    }
      
    // Deletes  node if right child
      
    else {
      
      free(par->right); 
      
      par->right = NULL;
    }
    return root; // Return the root of the new tree.
  }
  // node to be deleted only has left child
  if (hasOnlyLeftChild(delnode)) {
    
    // Deleting the root node of the tree.
    
    if (par == NULL) {
      
      save_node = delnode->left;
      
      free(delnode); 
      
      return save_node; 
    }
    // Deletes node if left child.
    if (strcmp(root->name, itemName) > 0) {
      
      save_node = par->left; // store node for deletion
      
      par->left = par->left->left; // save it to somewhere else
      
      free(save_node); 
    }
    // Deletes node if right child.
    else {
      
      save_node = par->right; // store node for deletion
      
      par->right = par->right->left; // save it to somewhere else
      
      free(save_node); 
    }
    return root; 
  }
  // if deleted node is only right child
  
  if (hasOnlyRightChild(delnode)) {
    
    // Node to delete is the root node.
    
    if (par == NULL) {
      
      save_node = delnode->right;
      
      free(delnode);
      
      return save_node;
    }
    // Delete's the node if it is a left child.
    if (strcmp(root->name, itemName) > 0) {
      
      save_node = par->left;
      
      par->left = par->left->right;
      
      free(save_node);
    }
    // Delete's the node if it is a right child.
    else {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }
//node to delete has 2 children
  
  new_del_node = minNode(delnode->right);
  
  strcpy(saveName,new_del_node->name);
  
  delete(root, saveName);  // delete the name
  
  // reassign the savename
  strcpy(delnode->name, saveName);
  
  return root;
}

int reduceFunc(itemNode* correctItem, int reduceVal){
  
  correctItem->count = correctItem->count - reduceVal;

  return correctItem->count;
  
}

void deleteItemTree(itemNode* rootItem){
  if(rootItem == NULL){
    return ;
  }

  deleteItemTree(rootItem->left);
  deleteItemTree(rootItem->right);

  free(rootItem);
  
  
}





int main(void) {
  atexit(report_mem_leak); // memory leak

  // file I/O stuff
  infile = fopen("in.txt", "r");
  outfile = fopen("out.txt", "w");
  
  //variables
  int numNameTrees, totalInsertions, numQueries, reduceNum;

  treeNameNode* nameTreeRoot = NULL;
  itemNode* item = NULL;

  char queryType[50], queryTypeNameNode[50], queryTypeItemNode[50];
  char queryOperation[50], queryOperationName[50], queryOperationItem[50];

  treeNameNode* correctNameNode;
  itemNode* correctItemNode;
  
  fscanf(infile, "%d %d %d", &numNameTrees, &totalInsertions, &numQueries);


  nameTreeRoot = buildNameTree(nameTreeRoot, numNameTrees);

  placeItemNode(nameTreeRoot, item, totalInsertions);
  
  inorderNameTree(nameTreeRoot);

  

  traverse_in_traverse(nameTreeRoot);

  printf("\n");

  for(int i = 0; i < numQueries; i++){
    
    //scans the operation of the query
    fscanf(infile, "%s", queryOperation);

    //compares it to the predfined functions for each query operation 

    //if query operation is search
    
    if(strcmp(queryOperation, "search") == 0){
      
      //take input of what nameNode and item u are searching for
      fscanf(infile, "%s %s", queryOperationName, queryOperationItem);

      //assigns pointer for right treeName node if there is a name node
      correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);
      
      if(correctNameNode == NULL){
        
        printf("%s does not exist\n", queryOperationName);
        
      }
        
      //prints search finding based on item node result
      else{
        
        correctItemNode = searchquery(correctNameNode->theTree, queryOperationItem);
        
          if(correctItemNode == NULL){
            printf("%s not found in %s\n", queryOperationItem, correctNameNode->treeName);
          }
            
          else{
            printf("%d %s found in %s\n", correctItemNode->count, correctItemNode->name, correctNameNode->treeName);
            
          }
    }
      
 
  }
    
    //count queryOperation
      else if(strcmp(queryOperation, "count") == 0){
      
      //take input of what nameNode and item u are finding the num of b4 elements for
      fscanf(infile, "%s %s", queryOperationName, queryOperationItem);

      correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);

      if(correctNameNode != NULL){

      if(correctNameNode->theTree != NULL){
        int total = count(correctNameNode->theTree);

        printf("%s count %d\n", queryOperationName, total);
      }
      
    }
  }

    
      

    //item_before query operation
    else if(strcmp(queryOperation, "item_before") == 0){
      
      fscanf(infile, "%s %s", queryOperationName, queryOperationItem);
      
      correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);

      int beforeVal = itemBefore(correctNameNode->theTree, queryOperationItem);

      printf("item before %s: %d\n", queryOperationItem, beforeVal);

    }

    //height balance question
    else if(strcmp(queryOperation, "height_balance") == 0){
      fscanf(infile, "%s", queryOperationName);

      correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);

      int leftHeightVal = height(correctNameNode->theTree->left);
      int rightHeightVal = height(correctNameNode->theTree->right);
      if(correctNameNode != NULL){

      if(abs(leftHeightVal - rightHeightVal) > 1){
       printf("%s: left height %d, right height %d, difference %d, not balanced\n", correctNameNode->treeName, leftHeightVal - 1, rightHeightVal - 1, abs(leftHeightVal - rightHeightVal));
      }
        
      else{
        printf("%s: left height %d, right height %d, difference %d, balanced\n", correctNameNode->treeName, leftHeightVal - 1, rightHeightVal - 1, abs(leftHeightVal - rightHeightVal));
      }
}
            
    }
    
    //delete query
    else if(strcmp(queryOperation, "delete") == 0){
      
      fscanf(infile, "%s %s", queryOperationName, queryOperationItem);

      correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);

      correctItemNode = searchquery(correctNameNode->theTree, queryOperationItem);

      if(correctNameNode != NULL){

      itemNode* deleteFunc = delete(correctItemNode, queryOperationItem);

      if(deleteFunc != NULL){
        //sets the deleted node's count to 0 since it's being deleted
        correctItemNode->count = 0;
        printf("%s deleted from %s\n", queryOperationItem, correctNameNode->treeName);
      }
    }


  }

    //reduce func

    else if(strcmp(queryOperation, "reduce") == 0){
      
      fscanf(infile, "%s %s %d", queryOperationName, queryOperationItem, &reduceNum);

      if(correctNameNode != NULL){

      correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);

      correctItemNode = searchquery(correctNameNode->theTree, queryOperationItem);

      reduceFunc(correctItemNode, reduceNum);

      printf("%s reduced\n", queryOperationItem);
    }

    }

    else if(strcmp(queryOperation, "delete_name") == 0){
      
      fscanf(infile, "%s", queryOperationName);
      
      correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);

      if(correctNameNode != NULL){

      deleteItemTree(correctNameNode->theTree);

      free(correctNameNode);

      printf("%s deleted\n", queryOperationName);
    }
  }

      
      
    else{
      printf("Error\n");
    }
    


}
  
  /*
  treeNameNode* rightNameNode = searchNameNode(nameTreeRoot, "fruit");
  printf("%s\n", rightNameNode->theTree->name);
  int countTwo = count(rightNameNode->theTree);
  printf("%d", countTwo);
*/
  
  



  

  /*
  correctNameNode = searchNameNode(nameTreeRoot, queryOperationName);

      correctItemNode = searchquery(correctNameNode->theTree, queryOperationItem);

      //sets the deleted node's count to 0 since it's being deleted
      correctItemNode->count = 0;

      itemNode* deleteFunc = delete(correctItemNode, queryOperationItem);

      if(deleteFunc != NULL){
        
        printf("%s deleted from %s\n", queryOperationItem, correctNameNode->treeName);
      }


  */

  
  
  
  return 0;
}