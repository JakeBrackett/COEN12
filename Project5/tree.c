//
//  tree.c
//  
//
//  Created by jacob ryan brackett on 5/21/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

struct tree{
    int data;
    struct tree *right;
    struct tree *left;
    struct tree *parent;
};

static void detach(struct tree *child){
    if(child->parent == NULL)
        return;
    if(child == child->parent->right){
        child->parent->right = NULL;
        return;
    }
    if(child == child->parent->left){
        child->parent->left = NULL;
        return;
    }
}

struct tree *createTree(int data, struct tree *left, struct tree *right){
    struct tree *tr;
    tr = malloc(sizeof(struct tree));
    assert(tr != NULL);
    tr->parent = NULL;
    tr->left = left;
    tr->right = right;
    tr->data = data;
    if(right != NULL){
        detach(right);
        right->parent = tr;
    }
    if(left != NULL){
        detach(left);
        left->parent = tr;
    }
    return tr;
}

void destroyTree(struct tree *root){
    if(root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

int getData(struct tree *root){
    assert(root != NULL);
    return root->data;
}

struct tree *getLeft(struct tree *root){
    assert(root != NULL);
    return root->left;
}

struct tree *getRight(struct tree *root){
    assert(root != NULL);
    return root->right;
}

struct tree *getParent(struct tree *root){
    assert(root != NULL);
    return root->parent;
}

void setLeft(struct tree *root, struct tree *left){
    if(root->left != NULL)
        root->left->parent = NULL;
    root->left = left;
    if(left != NULL){
        detach(left);
        left->parent = root;
    }
}

void setRight(struct tree *root, struct tree *right){
    if(root->right != NULL)
        root->right->parent = NULL;
    root->right = right;
    if(right != NULL){
        detach(right);
        right->parent = root;
    }
}