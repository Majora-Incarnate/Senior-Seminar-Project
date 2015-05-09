#include "Object.h"



//====================================================================================//
//                                                                                    //
//                                                                                    //
//                                                                                    //
//                                                                                    //
//                                                                                    //
//                                                                                    //
// NOT MY OWN CODE, MODIFIED SLIGHTLY TO SUIT NEEDS, UNSURE OF AUTHOR                 //
// URL = http://www.sanfoundry.com/cpp-program-implement-self-balancing-binary-tree/  //
//                                                                                    //
//                                                                                    //
//                                                                                    //
//                                                                                    //
//                                                                                    //
//                                                                                    //
//====================================================================================//

 

class SBBSTNode
{
    public:
        Object * data;
        int height;
        SBBSTNode * left, * right;

        /* Constructor */
        SBBSTNode()
        {
            left = NULL;
            right = NULL;
            data = NULL;
            height = 0;
        }

 

        /* Constructor */
        SBBSTNode(Object * n)
        {
            left = NULL;
            right = NULL;
            data = n;
            height = 0;
        }



         ~SBBSTNode()
         {
            delete left;
            delete right;
         }

};



class SelfBalancingBinarySearchTree
{
    private:
        SBBSTNode *root;

    public:
         /* Constructor */
         SelfBalancingBinarySearchTree()
         {
             root = NULL;
         }



         ~SelfBalancingBinarySearchTree()
         {
            delete root;
         }

 

         /* Function to check if tree is empty */
         bool isEmpty()
         {
             return root == NULL;
         }

 

         /* Make the tree logically empty */
         void makeEmpty()
         {
             root = NULL;
         }

 

         /* Function to insert data */
         void insert(Object * data)
         {
             root = insert(data, root);
         }

 

         /* Function to get height of node */
         int height(SBBSTNode *t)
         {
             return t == NULL ? -1 : t->height;
         }

 

         /* Function to max of left/right node */
         int max(int lhs, int rhs)
         {
             return lhs > rhs ? lhs : rhs;
         }

 

         /* Function to insert data recursively */
         SBBSTNode *insert(Object * x, SBBSTNode *t)
         {
             if (t == NULL)
                 t = new SBBSTNode(x);

             else if (x < t->data)
             {
                 t->left = insert(x, t->left);
                 if (height(t->left) - height(t->right) == 2)
                 {
                     if (x < t->left->data)
                         t = rotateWithLeftChild(t);
                     else
                         t = doubleWithLeftChild(t);
                 }
             }

             else if (x > t->data)
             {
                 t->right = insert(x, t->right);
                 if (height(t->right) - height(t->left) == 2)
                 {
                     if (x > t->right->data)
                         t = rotateWithRightChild(t);
                     else
                         t = doubleWithRightChild(t);
                 }
             }
             t->height = max(height(t->left), height(t->right)) + 1;
             return t;
         }

 

         /* Rotate binary tree node with left child */
         SBBSTNode *rotateWithLeftChild(SBBSTNode* k2)
         {
             SBBSTNode *k1 = k2->left;
             k2->left = k1->right;
             k1->right = k2;
             k2->height = max(height(k2->left), height(k2->right)) + 1;
             k1->height = max(height(k1->left), k2->height) + 1;

             return k1;
         }

 

         /* Rotate binary tree node with right child */
         SBBSTNode *rotateWithRightChild(SBBSTNode *k1)
         {

             SBBSTNode *k2 = k1->right;
             k1->right = k2->left;
             k2->left = k1;
             k1->height = max(height(k1->left), height(k1->right)) + 1;
             k2->height = max(height(k2->right), k1->height) + 1;

             return k2;
         }

 

         /*
          * Double rotate binary tree node: first left child
          * with its right child; then node k3 with new left child
          */
         SBBSTNode *doubleWithLeftChild(SBBSTNode *k3)
         {
             k3->left = rotateWithRightChild(k3->left);
             return rotateWithLeftChild(k3);
         }

 

         /*
          * Double rotate binary tree node: first right child
          * with its left child; then node k1 with new right child
          */
         SBBSTNode *doubleWithRightChild(SBBSTNode *k1)
         {
             k1->right = rotateWithLeftChild(k1->right);
             return rotateWithRightChild(k1);
         }

 

         /* Functions to count number of nodes */
         int countNodes()
         {
             return countNodes(root);
         }

 

         int countNodes(SBBSTNode *r)
         {

             if (r == NULL)
                 return 0;
             else
             {
                 int l = 1;

                 l += countNodes(r->left);
                 l += countNodes(r->right);
                 return l;
             }
         }

 

         /* Functions to search for an element */
         bool search(Object * val)
         {
             return search(root, val);
         }

 

         bool search(SBBSTNode *r, Object * val)
         {
             bool found = false;

             while ((r != NULL) && !found)
             {

                 Object * rval = r->data;

                 if (val < rval)
                     r = r->left;
                 else if (val > rval)
                     r = r->right;
                 else
                 {
                     found = true;
                     break;
                 }

                 found = search(r, val);
             }
             return found;
         }
};