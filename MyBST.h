//
//  MyBST.h
//  Binary Search Tree
//
//  Created by Saeid on 12/9/15.
//  Copyright © 2015 Saeid. All rights reserved.
//

#ifndef MyBST_h
#define MyBST_h

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;

struct node {
    int data;
    node *root;
    node *left;
    node *right;
    node *parent;
    signed int height;
    signed int weight;
};

class MyBST {

    node *nill;
    int size;
    int *array;
    
public:
    MyBST() {
        nill = new node;
        nill->root = nill;
        nill->right = nullptr;
        nill->left = nullptr;
        nill->parent = nullptr;
        nill-> weight = NULL;
        nill->data = NULL;
        nill->height = -1;
        size = 0;
        array = nullptr;
    }
    
    bool insert(int);
    bool remove(int);
    int* traverse(string);
    int Size();
    void display();

private:
    void LRV(int*, node *);
    void LVR(int*, node *);
    void VLR(int*, node *);
    void left_rotate(node *);
    void right_rotate(node *);
    void fixAVL(node *);
    void fix_height_weight(node *);
    void rmnode(node*);
    void D(node *);
    
public:
    ~MyBST() {
        D(nill->root);
        delete nill;
        if (array != nullptr) delete array;
    }
};


int MyBST::Size() {
    return size;
}

void MyBST::left_rotate(node *x) {
    node *y = x->right;
    x->right = y->left;
    if (y->left != nill)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nill)
        nill->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    //fix height and weight
    fix_height_weight(x);
}

void MyBST::right_rotate(node *y) {
    node *x = y->left;
    y->left = x->right;
    if (x->right != nill)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nill)
        nill->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
    //fix height and weight
    fix_height_weight(y);
}

#include "nodestarQueue.h"

void MyBST::fixAVL(node *x) {
    if (x == nill) return;
    
    if (abs(x->weight) > 1) {
        if (x->weight * x->left->weight < 0 || x->weight * x->right->weight < 0) {
            if (x->weight < 0)
                left_rotate(x->left);
            else
                right_rotate(x->right);
            fixAVL(x);
        }
        else {
            if(x->weight < 0)
                right_rotate(x);
            else
                left_rotate(x);
        }
    }
    
    fixAVL(x->parent);
    return;
}

void MyBST::fix_height_weight(node *x) {
    if (x == nill) return;
    
    x->height = max(x->left->height, x->right->height) + 1;
    x->weight = x->right->height - x->left->height;
    
    fix_height_weight(x->parent);
    return;
}

bool MyBST::insert(int n) {
    //create node
    node *New = new node;
    New->data = n;
    New->left = nill;
    New->right = nill;
    New->height = 0;
    New->weight = 0;
    New->root = nullptr;
    
    if (!size) {
        //insert node
        nill->root = New;
        New->parent = nill;
        size++;
        
        return true;
    }
    
    node *tmp = nill->root;
    bool found = false;
    while (!found) {
        if (tmp->data > n) {
            if (tmp->left == nill) {
                //insert node
                tmp->left = New;
                New->parent = tmp;
                found = true;
            }
            else
                tmp = tmp->left;
        }
        else if (tmp->data < n) {
            if (tmp->right == nill) {
                //insert node
                tmp->right = New;
                New->parent = tmp;
                found = true;
            }
            else
                tmp = tmp->right;
        }
        else
            return false;
    }
    size++;
    
    //fix weight and hight
    fix_height_weight(New->parent);
    
    //fix AVL
    fixAVL(New->parent);
    
    return true;
}

void MyBST::rmnode(node* x) {
    if (x->right != nill && x->left != nill) {
        node *tmp = x->right;
        
        bool found = false;
        while (!found) {
            if (tmp->left == nill) found = true;
            else tmp = tmp->left;
        }
        x->data = tmp->data;
        node* temp = tmp->parent;
        rmnode(tmp);
        
        //fix weight and hight
        fix_height_weight(temp);
        
        //fix AVL
        fixAVL(temp);
        return;
    }
    else if (x->right == nill && x->left == nill) {
        if (x->parent == nill) {
            nill->root = nill;
            return;
        }
        else if (x == x->parent->left)
            x->parent->left = nill;
        else
            x->parent->right = nill;
        delete x;
        return;
    }
    else {
        if (x->parent == nill) {
            if (x->right != nill) {
                nill->root = x->right;
                x->right->parent = nill;
            }
            else {
                nill->root = x->left;
                x->left->parent = nill;
            }
            delete  x;
            return;
        }
        else if (x == x->parent->left) {
            if (x->right != nill) {
                x->parent->left = x->right;
                x->right->parent = x->parent;
            }
            else {
                x->parent->left = x->left;
                x->left->parent = x->parent;
            }
            delete  x;
            return;
        }
        else {
            if (x->right != nill) {
                x->parent->right = x->right;
                x->right->parent = x->parent;
            }
            else {
                x->parent->right = x->left;
                x->left->parent = x->parent;
            }
            delete  x;
            return;
        }
    }
}

bool MyBST::remove(int n) {
    if (!size) return false;
    
    node *tmp = nill->root;
    while (true) {
        if (tmp == nill) return false;
        
        if (tmp->data > n) tmp = tmp->left;
        else if (tmp->data < n) tmp = tmp->right;
        else {
            //remove node
            rmnode(tmp);
            size--;
            return true;
        }
    }
    
}

int* MyBST::traverse(string s) {
    if (array != nullptr) delete array;
    
    if (!size) return nullptr;
    
    if (!s.compare(string("vlr")) || !s.compare(string("VLR"))) {
        array = new int[size];
        int z = 0;
        
        VLR(&z, nill->root);
    }
    else if (!s.compare(string("lvr")) || !s.compare(string("LVR"))) {
        array = new int[size];
        int z = 0;
        
        LVR(&z, nill->root);
    }
    else if (!s.compare(string("lrv")) || !s.compare(string("LRV"))) {
        array = new int[size];
        int z = 0;
        
        LRV(&z, nill->root);
    }
    else return nullptr;
    return array;
}

void MyBST::VLR(int *i, node *ptr) {
    if(ptr == nill) return;
    
    int tmp = *i;
    array[tmp] = ptr->data;
    tmp++;
    *i = tmp;
    
    
    VLR(i, ptr->left);
    VLR(i, ptr->right);
}

void MyBST::LVR(int *i, node *ptr) {
    if(ptr == nill) return;
    
    LVR(i, ptr->left);
    
    int tmp = *i;
    array[tmp] = ptr->data;
    tmp++;
    *i = tmp;
    
    LVR(i, ptr->right);
}

void MyBST::LRV(int *i, node *ptr) {
    if(ptr == nill) return;
    
    LRV(i, ptr->left);
    LRV(i, ptr->right);
    
    int tmp = *i;
    array[tmp] = ptr->data;
    tmp++;
    *i = tmp;
}

void MyBST::display() {
    cout << endl;
    if (!size) {
        cout << "Tree Empty!" << endl;
        return;
    }
    
    nodeQueue q(size);
    bool done = false;
    node * tmp = nill->root;
    q.add(tmp);
    
    int i = 0;
    signed int n = -1;
    int temp = 20;
    do {
        i++;
        
        signed int tmp = log2(i);
        if (tmp != n) {
            n = tmp;
            temp -= 2;
            cout << endl;
            for (int j = 0; j < temp; j++) cout << ' ';
        }
        
        if (q.shownxt() == nill) {
            q.pop();
            cout << "  ";
        }
        else {
            q.add(q.shownxt()->left);
            q.add(q.shownxt()->right);
            cout << ' ' << q.pop()->data << ' ';
        }
        
        if (q.shownxt() == nullptr) done = true;
    }while (!done);
    
    return;
}

void MyBST::D(node *ptr) {
    if(ptr == nill) return;
    
    D(ptr->left);
    D(ptr->right);
    
    delete ptr;
}

#endif /* MyBST_h */
