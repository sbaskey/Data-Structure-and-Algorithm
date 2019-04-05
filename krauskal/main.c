#include <stdio.h>
#include <stdlib.h>
int m,n;
int s,a=0;
struct edge
{
    int src,des,w;
};
struct edge *edgeList[20];
struct edge *tempList[20];
struct edge* makeedge(int src,int des,int w)
{
    struct edge*e=(struct edge*)malloc(sizeof(struct edge));
    e->src=src;
    e->des=des;
    e->w=w;
    edgeList[s++]=e;
    return e;
}
struct node
{
    int v,rank;
    struct node*parent;
};
struct node *List[20];
struct node *set[20];
struct node* makenode(int v)
{
    struct node* p=(struct node* )malloc(sizeof(struct node));
    p->v=v;
    p->rank=0;
    p->parent=p;
    List[a++]=p;
    return p;
}
void subset(int v)
{
    struct node*p=makenode(v);
    set[v]=p->parent;
}
struct node* findset(struct node  *p)
{
    if(p->parent!=p)
    {
        p->parent=findset(p->parent);
    }
    return p->parent;
}
void link(struct node *p,struct node *q)
{
    if(p->rank>q->rank)
        q->parent=p;
    else
    {
        p->parent=q;
        if(p->rank==q->rank)
            q->rank=q->rank+1;
    }
}
void unionn(struct node *p,struct node*q)
{
    struct node *x=findset(p);
    struct node *y=findset(q);
    if(x!=y)
        link(x,y);
}
void scanfile()
{
    int i,u,v,w;
    scanf("%d%d",&n,&m);
    for(int i=0; i<n; i++)
        subset(i);
    for(int i=0; i<m; i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        makeedge(u,v,w);
    }
}
void merge(int left, int right){
    int mid = (left + right)/2;
    for(int i = left; i<=right; i++)
        tempList[i] = edgeList[i];
    int u = left;
    int v = mid + 1;
    int k = u;
    while (u != mid+1 && v != right+1){
        struct edge *e1 = tempList[u];
        struct edge *e2 = tempList[v];
        if(e1->w<e2->w){
            edgeList[k++] = tempList[u++];
        }else{
            edgeList[k++] = tempList[v++];
        }
    }
    while(u != mid+1){
        edgeList[k++] = tempList[u++];
    }
    while(v != right+1){
        edgeList[k++] = tempList[v++];
    }
}
void sort(int left, int right){
    if(left < right){
        sort(left, (left+right)/2);
        sort((left+right)/2 + 1, right);
        merge(left, right);
    }
}
int main()
{
    scanfile();
    sort(0,m-1);
    for(int v=0; v<a; v++)
    {
        struct node*p=List[v];
        if(p!=NULL){
            printf("verterx %d parent %d rank %d\n",p->v,p->parent->v,p->rank);}
    }
    printf("%d\n",s);
    for(int i=0; i<m; i++)
    {
        struct edge*e=edgeList[i];
        if(e!=NULL){
            printf("source %d des %d w %d\n",e->src,e->des,e->w);}
        else
            printf("%d  ",9);
    }
    return 0;
}