#include <stdio.h>
#include <stdlib.h>
int vertex=0,edge=0,clk=0;
int temp,l,m;
int flag=0;
int previs[50],posvis[50],active[50],parent[20];

struct stack
{
    int data;
    struct stack *net;
};
struct stack *top=NULL;
void push(int data)
{
    if(top==NULL)
    {
        top=(struct stack*) malloc(sizeof(struct stack));
        top->data = data;
        top->net = NULL;
    }
    else
    {
        struct stack* temp=(struct stack*) malloc(sizeof(struct stack));
        temp->data = data;
        temp->net=top;
        top=temp;
    }
    return;
}
int  pop()
{
    int y;
    struct stack* temp;
    if(top==NULL)
        return 0;
    else
    {
        temp=(struct stack*) malloc(sizeof(struct stack));
        temp=top;
        top=top->net;
        y=temp->data;
        printf("%d\n",y);
        free(temp);
    }
    return y;
}
struct node {
    int vertex;
    struct node * next;
};
struct node * adjacencyList[20 ];
struct node * addnode(struct node * head, int des)
{
    struct node *newnode= (struct node *) malloc(sizeof(struct node));
    newnode->vertex=des;
    newnode->next=head;
    return newnode;
}
void createlist(int size)
{ int i;
    struct node * adjacencyList[edge ];
    for (i = 0; i < vertex; ++i) {
        adjacencyList[i] = NULL;
    }
}
void printlist(int n)
{
    for(int i=0; i<vertex; i++)
    {
        struct node *p=adjacencyList[i];
        printf("adjacency list for vertex %d",i);
        while(p)
        {
            printf("  %d->",p->vertex);
            p=p->next;
        }
        printf("\n");
    }
}
void scanfile()
{
    int k;
    int i=0;
    scanf("%d",&vertex);
    printf("%d\n",vertex);
    createlist(vertex);
    while(i<vertex)
    {
        scanf("%d",&k);
        if(k!=-1)
        {
            adjacencyList[i] = addnode(adjacencyList[i],k);
            printf("%d ",k);
        }
        else
        {
            i++;
            printf("\n");

        }
    }
}
void dfs1(int u)
{
    if(flag==1)
        return ;
    clk=clk+1;
    previs[u]=clk;
    active[u]=1;
    struct node *p=adjacencyList[u];
    while(p)
    {
        if(previs[p->vertex]==0)
        {
            parent[p->vertex]=u;
            dfs1(p->vertex);
        }
        else if(previs[p->vertex]>previs[u])
        {
            temp++;
        }
        else if(active[p->vertex]==0) {
            temp++; }
        else
        {
            flag=1;
            l=u;
            m=p->vertex;
        }


        p=p->next;
    }
    active[u]=0;
    clk=clk+1;
    posvis[u]=clk;
    push(u);

}
void printcycle(int l,int m)
{     int  cycle[20];
    int cnt=0;
    cycle[cnt++]=m;
    do { // through the while loop parent array is traversed bacward and nodes are printed in reverse order
        cycle[cnt++]=l;
        l=parent[l];
    } while (l!=m);

    cycle[cnt++]=m;
    cnt--;
    while(cnt>=0){
        printf("%d\n",cycle[cnt]);
        cnt--;}
}

int main()
{
    scanfile();
    printlist(edge);
    for(int i=0; i<edge; i++)
    {
        previs[i]=0;  // array to sote previsit of vertex
        posvis[i]=0;  //array to store postvisit of a vertex
        active[i]=0;  // array to store whethere a vertex is in the current stack or not
    }

    for(int i=0; i<vertex; i++)
    {
        if(previs[i]==0)

            dfs1(i);

    }
    if(flag==1)
    {
        printf("the input graph contains a cycle and the cycle is\n");
        printcycle(l,m);
    }
    else
    {
        printf("topology sorting order is\n");
        for(int i=0; i<vertex; i++)
        {
            pop();
        }
    }
    return 0;
}

