#include <iostream>
#include <cstring>
using namespace std; 

#include "list.h"

// #define ORDEREDLIST

infoType head (listNode _node) {return _node->exam;}

listNode tail (listNode _node) {return _node->next;}
listNode prev (listNode _node) {return _node->prev;}

static listNode newNode (infoType infoToInsert) {

    listNode _node = new elem;

    copyInfo (_node->exam, infoToInsert); 

    _node->next = NULL;
    _node->prev = NULL;

    return _node;
}

static listNode insertHead (listNode _nodes, listNode _nodeToInsert) {

    _nodeToInsert->next = _nodes;

    if (_nodes != NULL)
        _nodes->prev = _nodeToInsert;

    return _nodeToInsert;
}

#ifdef ORDEREDLIST
static listNode insertNode (listNode _nodes, listNode _nodeToInsert) {

    if (_nodes == NULL || _nodeToInsert->place.ip < _nodes->place.ip)
        return insertHead (_nodes, _nodeToInsert);

    else {
		
        listNode nodeTemp = _nodes;
		
        while (tail(nodeTemp) != NULL && _nodeToInsert->place.ip > tail(nodeTemp)->place.ip)
			 nodeTemp = tail(nodeTemp);
		
        _nodeToInsert->next = nodeTemp->next;
		
        if(nodeTemp->next != NULL)
			nodeTemp->next->prev = _nodeToInsert;
		
        nodeTemp->next = _nodeToInsert;
		_nodeToInsert->prev = nodeTemp;
		
        return _nodes;
    }
}
#endif

#ifndef ORDEREDLIST
listNode insertNode (listNode _nodes, listNode _nodeToInsert) {

    if (_nodes == NULL)
        return _nodeToInsert;  

    else {

        listNode nodeTemp = _nodes; 

        while (tail(nodeTemp) != NULL)
            nodeTemp = tail (nodeTemp); 

        _nodeToInsert->prev = nodeTemp; 
        nodeTemp->next = _nodeToInsert; 
        
        return _nodes; 
    }
}
#endif

listNode delete_elem(listNode l, listNode e){

    if(l==e)
        l=e->next;
    
    else 
        (e->prev)->next = e->next;
    
    if(e->next!=NULL)
        (e->next)->prev=e->prev;

    delete e;

    return l;
}

void addNodeInList (listNode& _nodes, infoType infoToInsert) {

    listNode _newNode = newNode (infoToInsert);
    _nodes = insertNode (_nodes, _newNode);
}

void printList (listNode _nodes) {

    if (_nodes != NULL){
        viewInfo (head(_nodes), cout);
        printList (tail (_nodes));
    }
}

int countNodes (listNode _nodes) {

    if (_nodes == NULL)
        return 0; 

    return 1 + countNodes (tail(_nodes)); 
}