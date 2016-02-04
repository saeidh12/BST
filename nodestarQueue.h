//
//  nodestarQueue.h
//  Binary Search Tree
//
//  Created by Saeid on 12/10/15.
//  Copyright © 2015 Saeid. All rights reserved.
//

#ifndef nodestarQueue_h
#define nodestarQueue_h

class nodeQueue {
    node **queue;
    int numfull;
    int qfirst;
    int qlast;
    int size;
    
    
public:
    nodeQueue() {
        queue = new node*[10];
        numfull = 0;
        qfirst = 0;
        qlast = -1;
        size = 10;
    }
    nodeQueue(int n) {
        if (n == 0) n = 5;
        queue = new node*[n];
        numfull = 0;
        qfirst = 0;
        qlast = -1;
        size = n;
    }
    ~nodeQueue() {
        delete queue;
    }
    bool add(node*);
    node* pop(void);
    node* shownxt(void);
    
};

bool nodeQueue::add(node* n) {
    if (size == numfull)
        return false;
    if (qlast + 1 == size) {
        queue[0] = n;
        qlast = 0;
    }
    else {
        queue[qlast + 1] = n;
        qlast++;
    }
    numfull++;
    return true;
}

node* nodeQueue::pop(void) {
    if (!numfull)
        return nullptr;
    node* n = queue[qfirst];
    if (qfirst + 1 == size)
        qfirst = 0;
    else
        qfirst++;
    numfull--;
    return n;
}

node* nodeQueue::shownxt(void) {
    if (numfull)
        return queue[qfirst];
    return nullptr;
}

#endif /* nodestarQueue_h */
