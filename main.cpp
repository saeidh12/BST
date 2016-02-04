//
//  main.cpp
//  Binary Search Tree
//
//  Created by Saeid on 12/9/15.
//  Copyright © 2015 Saeid. All rights reserved.
//



#include "MyBST.h"

int main(void) {
    MyBST T;
    int n, m;
    cout << "enter amount:";
    cin >> n;
    
    
    for (int i = 0; i < n; i++) {
        cin >> m;
        T.insert(m);
    }
    
    cout << "what to delete? (if nothing enter number not in tree)" << endl;
    
    bool done = false;
    
    do {
        int tmp;
        cin >> tmp;
        if (!T.remove(tmp))
            done = true;
    }while (!done);
    
    T.display();
    int* temp;
    cout << endl << "Pre-Order Traversal: ";
    temp = T.traverse("VLR");
    for (int i = 0; i < T.Size(); i++)
        cout << temp[i] << ' ';
    
    cout << endl << "In-Order Traversal: ";
    temp = T.traverse("LVR");
    for (int i = 0; i < T.Size(); i++)
        cout << temp[i] << ' ';
    
    cout << endl << "Post-Order Traversal: ";
    temp = T.traverse("LRV");
    for (int i = 0; i < T.Size(); i++)
        cout << temp[i] << ' ';
    
    cout << endl;
    return 0;
}
