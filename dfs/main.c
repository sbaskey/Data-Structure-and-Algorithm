#include <stdio.h>
#include <stdlib.h>
int vertex=0,edge=0,clk=0;
int previs[50],posvis[50],active[50];
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
    int source;
    scanf("%d",&vertex);
    printf("%d\n",vertex);
    scanf("%d",&edge);
    printf("%d\n",edge);
    createlist(edge);
    while(i<edge)
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
    clk=clk+1;
    previs[u]=clk;
    active[u]=1;
    struct node *p=adjacencyList[u];
    while(p)
    {
        if(previs[p->vertex]==0)
        {
            printf("tree edge is %d->%d\n",u,p->vertex);
            dfs1(p->vertex);
        }
        else if(previs[p->vertex]>previs[u])
        {
            printf("forward edge is %d->%d\n",u,p->vertex);
        }
        else if(active[p->vertex]==0) {
            printf("cross edge is %d->%d\n",u,p->vertex);  }
        else
        {
            printf("back edge is %d->%d\n",u,p->vertex);
        }


        p=p->next;
    }
    active[u]=0;
    clk=clk+1;
    posvis[u]=clk;

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
    for(int i=0; i<vertex; i++)
    {
        printf(" node %d:previsit %d  posvisit %d \n",i,previs[i],posvis[i]);
    }

    return 0;
}

