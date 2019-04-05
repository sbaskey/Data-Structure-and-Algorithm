#include <stdio.h>
#include <stdlib.h>
#define space 10
void swap(int *p,int *q)
{
    int temp=*p;
    *p=*q;
    *q=temp;
}
struct heapnode
{
    int value;
};
struct heap
{
    int size;
    int maxsize;
    int *array;
};
struct heapnode* createnode(int value)
{
    struct heapnode*node=(struct heapnode*)malloc(sizeof(struct heapnode));
    node->value=value;
    return node;
}
struct heap*buildheap(int maxsize)
{
    struct heap*h=(struct heap*)malloc(sizeof(struct heap));
    h->maxsize=maxsize;
    h->size=0;
    h->array=(int *)malloc(maxsize* sizeof(int));
    return h;
}
void heapify(struct heap* h, int key)
{
    int smallest, left, right;
    smallest = key;
    left = 2 * key + 1;
    right = 2 * key + 2;
    if (left < h->size &&  h->array[left] < h->array[smallest] )
            smallest = left;
    if (right < h->size &&   h->array[right] < h->array[smallest] )
         smallest = right;
    if (smallest!=key)
    {
        swap(&h->array[smallest], &h->array[key]);
        heapify(h,smallest);
    }
}
int  extractmin(struct heap*h)
{
        int root = h->array[0];
        h->array[0] = h->array[h->size-1];
        h->size--;
        heapify(h,0);
        printf(" %d ",root);
        return root;
}
void insertvalue(struct heap *h,int value)
{
  if(h->size==h->maxsize)
  {
      printf("no more elements can be inserted\n");
      return;
  }
    h->size++;
    int i=h->size-1;
    h->array[i]=value;
    while (i!=0 && h->array[i]< h->array[(i - 1) / 2]) //shift up is done in the loop
    {
        swap(&h->array[i],  &h->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
void decreasekey(struct heap*h,int key,int newvalue)
{   int i=key;
    h->array[key]=newvalue;
    while (i!=0 && h->array[i]< h->array[(i - 1) / 2]) //shift up is done in the loop
    {
        swap(&h->array[i],  &h->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

}
void printheap(struct heap*h)
{
    if(h->size==0)
    {
        printf("heap is empty\n");
        return;
    }
    for(int i=0; i<h->size; i++)
    {
        printf("%d ",h->array[i]);
    }
}
void heapsort(struct heap*h)
{    printf("sorted heap\n");
    while(h->size!=0)
    {
        extractmin(h);
    }
}
void printtree(struct heap*h,int i,int s)
{
   if(i>h->size-1)
       return;
    s=s+space;
    printtree(h,2*i+2,s);
    printf("\n");
    for(int c=space; c<s; c++){
        printf(" ");}
    printf("%d",h->array[i]);
    printtree(h,2*i+1,s);

}
int main()
{
    int n,k,max;
    printf("enter the maximum number of element in the heap");
    scanf("%d",&max);
    struct heap*h=buildheap(max);
    printf("enter the number elements you want to enter");
    scanf("%d",&n);
    printf("enter the elements in the heap\n");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&k);
        insertvalue(h,k);
    }
    printheap(h);
    printf("\n");
    //int m=extractmin(h);
    //printf("\n");
    //insertvalue(h,9);
    //decreasekey(h,1,-56);
    heapsort(h);
    //printf("\n");
    //printheap(h);
    printtree(h,0,0);
}
