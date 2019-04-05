#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void craetelist();
void scanfile();
int V,strt;
int dist[100],parent[100];
struct node {
    int vertex;
    int weight;
    struct node * next;
};
struct node * adjacencyList[20 ];
struct heapnode  // heap node contains vertex number and it distance from source
{
    int v;
    int dist;
};
struct heap
{
    int size;      //current size of heap
    int maxsize;  // maximumsize of heap of min heap
    int *pos;     // posision heapnodes in th array
    struct heapnode **array;  //arry of heap nodes
};
struct heapnode* newnode(int v, int dist)// function to create a node for the heap
{
    struct heapnode* node=
            (struct heapnode*) malloc(sizeof(struct heapnode));
    node->v = v;
    node->dist = dist;
    return node;
}
//  function to create a Min Heap
struct heap* buildheap(int maxsize)
{
    struct heap* h =
            (struct heap*) malloc(sizeof(struct heap));
    h->pos = (int *)malloc(maxsize* sizeof(int));
    h->size = 0;
    h->maxsize =maxsize;
    h->array=(struct heapnode**) malloc(maxsize * sizeof(struct heapnode*));
    return h;
}
// swap function
void swap(struct heapnode**p, struct heapnode**q)
{
    struct heapnode*temp=*p;
    *p=*q;
    *q=temp;
}
void heapify(struct heap* h, int index)
{
    int smallest, left, right;
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;
    if (left < h->size &&
        h->array[left]->dist < h->array[smallest]->dist )
        smallest = left;
    if (right < h->size &&
        h->array[right]->dist < h->array[smallest]->dist )
        smallest = right;
    if (smallest!=index)
    {
        // The nodes to be swapped in min heap
        struct  heapnode *smallestNode = h->array[smallest];
        struct  heapnode *idxNode = h->array[index];
        //  positions are swap
        h->pos[smallestNode->v] = index;
        h->pos[idxNode->v] = smallest;

        //  nodes are swaped
        swap(&h->array[smallest], &h->array[index]);

        heapify(h,smallest);
    }
}
// function to extract minimum node from heap
struct heapnode* extractMin(struct heap* h)
{    //first and last node are excahanged and are heapified
    struct heapnode*min= h->array[0];
    struct heapnode* lastNode = h->array[h->size - 1];
    h->array[0] = lastNode;
    h->pos[min->v] = h->size-1;
    h->pos[lastNode->v] = 0;
    h->size=h->size-1;
    heapify(h, 0);
    return min;
}
void decreaseKey(struct heap* h, int v, int dist)
{
    int i = h->pos[v];
    h->array[i]->dist = dist;
    while (i && h->array[i]->dist < h->array[(i - 1) / 2]->dist) //shift up is done in the loop
    {
        h->pos[h->array[i]->v] = (i-1)/2;
        h->pos[h->array[(i-1)/2]->v] = i;
        swap(&h->array[i],  &h->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
void dijkstra(int strt)
{
    struct heap* h = buildheap(V);//MINHEAP OF SIZE no of vertex is made
    for (int i= 0; i< V; i++)
    {
        dist[i] = INT_MAX;
        h->array[i] = newnode(i, dist[i]);
        h->pos[i] = i;
    }
    dist[strt]=0;
    decreaseKey(h, strt, dist[strt]);
    h->size = V;
    while(h->size!=0)
    {
        struct heapnode* Node = extractMin(h);
        int u = Node->v;
        struct node* p=adjacencyList[u] ;
        while (p!= NULL)
        {
            int v = p->vertex;
            if (h->pos[v] < h->size && dist[u] != INT_MAX && p->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + p->weight;
                parent[v]=u;
                decreaseKey(h, v, dist[v]); // new distance value is updated in the heap
            }
            p= p->next;
        }
    }
}
struct node * addnode(struct node * head, int des,int weight)
{
    struct node *newnode= (struct node *) malloc(sizeof(struct node));
    newnode->vertex=des;
    newnode->weight=weight;
    newnode->next=head;
    return newnode;
}
void createlist(int size)
{ int i;
    struct node * adjacencyList[V ];
    for (i = 0; i < V; ++i) {
        adjacencyList[i] = NULL;
    }
}
void scanfile()
{   char name[20];
    int i,e,k;
    int a[4];
    FILE *p;
    printf("enter input file name\n");
    scanf("%s",name);
    p=fopen(name,"r");
    if(p==0){printf("error in opening the file\n");
        return ;}
    fscanf(p,"%d",&V);
    fscanf(p,"%d",&e);
    createlist(V);
    for(int i=1; i<=e; i++)
    {
        k=0;
        while(k<3)
        {
            fscanf(p,"%d",&a[k]);
            k++;
        }// edges and edge weigt are used to make link list
        adjacencyList[a[0]] = addnode(adjacencyList[a[0]], a[1],a[2]);
        adjacencyList[a[1]] = addnode(adjacencyList[a[1]], a[0],a[2]);
    }
    fscanf(p,"%d",&strt);
    return;
}
int main()
{    scanfile();
    dijkstra(strt);
    printf("minimum distance of vertex from the start vertex\n");
    for (int i = 0; i < V; ++i) {
        printf("  start vertex %d vertex %d distance %d \t\t \n", strt, i, dist[i]);
    }
    for(int i=0; i<V; i++){
        if(i!=strt)
            printf("parent of %d is %d\n",i,parent[i]);
    }
}
