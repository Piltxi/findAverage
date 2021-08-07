#include "info.h"

struct elem {

    elem *next;
    elem *prev;

    infoType exam;
}; typedef elem * listNode;


infoType head (listNode);

listNode tail (listNode);
listNode prev (listNode);

static listNode newNode (infoType);
static listNode insertHead (listNode, listNode);
static listNode insertNode (listNode, listNode);

listNode delete_elem(listNode, listNode);
void  addNodeInList (listNode&, infoType);
void printList (listNode);
int countNodes (listNode); 