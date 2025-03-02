#include "ArrayList.h"
#include "LinkedList.h"
#include "Util.h"

static int LeftEdge(ArrayList* edges) {
    for (int i = 0; i < edges->size; i++) {
        LinkedList* edge = edges->Get(edges, i);
        if (edge->size != 0)
            return i;
    }

    return -1;
}

static void GetTrail(LinkedList* trail, int node, ArrayList* edges) {
    trail->Append(trail, node);
    
    LinkedList* nextEdge = edges->Get(edges, node);
    if (nextEdge->size != 0) {
        int nextNode = nextEdge->head->value;
        nextEdge->Delete(nextEdge, nextEdge->head);
        GetTrail(trail, nextEdge, edges);
    }
}

static int GetUnfinishedNode(ArrayList* allEdges) {
    for (int i = 0; i < allEdges->size; i++) {
        LinkedList* edges = allEdges->Get(allEdges, i);
        if (edges->size != 0) {
            return i;
        }
    }

    return -1;
}

static int GetTrailHead(LinkedList* trail) {
    return (int)(trail->head->value);
}

static void ConcateTrail(LinkedListNode* this, LinkedList* toBeAppendedList) {
    LinkedListNode* head = toBeAppendedList->head->next;
    LinkedListNode* tail = toBeAppendedList->tail;

    if (this == this->_list->tail) {
        this->next = head;
        head->prev = this;
        this->_list->tail = tail;
    } else {
        tail->next = this->next;
        head->prev = this;
        this->next->prev = tail;
        this->next = head;
    }

    free(toBeAppendedList->head);
    free(toBeAppendedList);
}

static void EulerTrial(ArrayList* allEdges, int nodeCount, int odd1, int odd2) {
    LinkedList* allTrails = NewLinkedList();
    
    LinkedList* allTrailsTable[nodeCount];
    for (int i = 0; i < nodeCount; i++)
        allTrailsTable[i] = NULL; 

    int node = -1;
    LinkedList* trail = NULL;
    
    if (odd1 != -1) {
        trail = NewLinkedList();
        trail->Append(trail, odd1);
        trail->Append(trail, odd2);
        trail->Append(trail, odd1);

        LinkedList* list1 = allEdges->Get(allEdges, odd1);
        list1->DeleteByValue(list1, odd2);
        LinkedList* list2 = allEdges->Get(allEdges, odd2);
        list2->DeleteByValue(list2, odd1); 

        if (list1->size != 0) {
            node = list1->Get(list1, 0);
            list1->Delete(list1, list1->head);
            trail->Append(trail, node);
        }

        allTrails->Append(allTrails, trail);
        allTrailsTable[GetTrailHead(trail)] = trail;        
    }

    if (node == -1) {
        node = GetUnfinishedNode(allEdges);
        trail = NULL;
    }     

    while (node != -1) {
        if (trail == NULL) {
            trail = NewLinkedList();
            trail->Append(trail, node);
            allTrails->Append(allTrails, trail);
            allTrailsTable[GetTrailHead(trail)] = trail;
        }

        LinkedList* edges = allEdges->Get(allEdges, node);

        if (edges->size != 0) {
            node = edges->Get(edges, 0);
            edges->Delete(edges, edges->head);
            trail->Append(trail, node);
        } else {
            node = GetUnfinishedNode(allEdges);
            trail = NULL;
        }
    }

    /* debug print
    for (int i = 0; i < nodeCount; i++) {
        LinkedList* trail = allTrailsTable[i];
        if (trail != NULL)
            trail->Print(trail);
    }*/

    // merge all trails
    while (allTrails->size != 1) {
        LinkedList* trail = allTrails->Get(allTrails, 0);
        int head = GetTrailHead(trail);
        allTrailsTable[head] = NULL;

        for (LinkedListNode* n = trail->head; n != NULL; n = n->next)  {
            int node = n->value;
            LinkedList* trail2 = allTrailsTable[node];
            if (trail2 != NULL) {
                ConcateTrail(n, trail2);
                allTrailsTable[node] = NULL;
                allTrails->DeleteByValue(allTrails, trail2);
            }
        }
    }

    trail = allTrails->Get(allTrails, 0);
    trail->Print(trail);

    for (LinkedListNode* n = allTrails->head; n != NULL; n = n->next) {
        DeleteLinkedList(n->value);
    }

    DeleteLinkedList(allTrails);
}

static void EularTrailAllEven() {
    ArrayList* edges = NewArrayList();

    LinkedList* edges0 = NewLinkedList();
    edges0->Append(edges0, 1);
    edges0->Append(edges0, 2);
    edges0->Append(edges0, 3);
    edges0->Append(edges0, 4);
    edges->Append(edges, edges0);

    LinkedList* edges1 = NewLinkedList();
    edges1->Append(edges1, 0);
    edges1->Append(edges1, 2);
    edges1->Append(edges1, 3);
    edges1->Append(edges1, 4);
    edges->Append(edges, edges1);    

    LinkedList* edges2 = NewLinkedList();
    edges2->Append(edges2, 0);
    edges2->Append(edges2, 1);
    edges2->Append(edges2, 3);
    edges2->Append(edges2, 5);
    edges->Append(edges, edges2);  

    LinkedList* edges3 = NewLinkedList();
    edges3->Append(edges3, 0);
    edges3->Append(edges3, 1);
    edges3->Append(edges3, 2);
    edges3->Append(edges3, 4);
    edges->Append(edges, edges3);     

    LinkedList* edges4 = NewLinkedList();
    edges4->Append(edges4, 0);
    edges4->Append(edges4, 1);
    edges4->Append(edges4, 3);
    edges4->Append(edges4, 5);
    edges->Append(edges, edges4);            

    LinkedList* edges5 = NewLinkedList();
    edges5->Append(edges5, 2);
    edges5->Append(edges5, 4);
    edges->Append(edges, edges5);        

    EulerTrial(edges, 6, -1, -1);
    
    for (int i = 0; i < edges->size; i++)
        DeleteLinkedList(edges->Get(edges, i));
    DeleteArrayList(edges);
}

static void EularTrail2Odd() {
    ArrayList* edges = NewArrayList();

    LinkedList* edges0 = NewLinkedList();
    edges0->Append(edges0, 1);
    edges0->Append(edges0, 2);
    edges->Append(edges, edges0);

    LinkedList* edges1 = NewLinkedList();
    edges1->Append(edges1, 0);
    edges1->Append(edges1, 2);
    edges1->Append(edges1, 4);
    edges1->Append(edges1, 5);
    edges->Append(edges, edges1);    

    LinkedList* edges2 = NewLinkedList();
    edges2->Append(edges2, 0);
    edges2->Append(edges2, 1);
    edges2->Append(edges2, 3);
    edges2->Append(edges2, 5);
    edges->Append(edges, edges2);  

    LinkedList* edges3 = NewLinkedList();
    edges3->Append(edges3, 2);
    edges3->Append(edges3, 4);
    edges3->Append(edges3, 5);
    edges->Append(edges, edges3);     

    LinkedList* edges4 = NewLinkedList();
    edges4->Append(edges4, 1);
    edges4->Append(edges4, 3);
    edges4->Append(edges4, 5);
    edges->Append(edges, edges4);            

    LinkedList* edges5 = NewLinkedList();
    edges5->Append(edges5, 1);
    edges5->Append(edges5, 2);
    edges5->Append(edges5, 3);
    edges5->Append(edges5, 4);    
    edges->Append(edges, edges5);        

    EulerTrial(edges, 6, 3, 4);
    
    for (int i = 0; i < edges->size; i++)
        DeleteLinkedList(edges->Get(edges, i));
    DeleteArrayList(edges);
}

void _8_8_EulerTrial() {
    EularTrailAllEven();
    printf("\n");
    EularTrail2Odd();
}