#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int l=0;
int m,n,strt;
int dist[1000];
struct edge
{
    int src,des,w;
};
struct edge *list[10000];
struct edge* createlist(int src,int des,int w)
{
    struct edge*e=(struct edge*)malloc(sizeof(struct edge));
    e->src=src;
    e->des=des;
    e->w=w;
    list[l++]=e;
}
void bellmanford(int strt)
{
    for(int i=0; i<n; i++)
    {
        dist[i]=INT_MAX;
    }
    dist[strt]=0;
    for(int i=1; i<=n-1; i++)
    {
        for(int j=0; j<m; j++)
        {
            int u=list[j]->src;
            int v=list[j]->des;
            int w=list[j]->w;
            if(dist[u]!=INT_MAX && dist[u]+list[j]->w<dist[v])
            {
                dist[v]=dist[u]+list[j]->w;
            }
        }
    }
    for(int i=0; i<m; i++)
    {
        int u=list[i]->src;
        int v=list[i]->des;
        int w=list[i]->w;
        if(dist[u]!=INT_MAX && dist[u]+list[i]->w<dist[v])
            printf("graph contains a negative cycle");

    }

}
void scanfile()
{   int u,v,w;
    scanf("%d%d",&n,&m);
    for(int i=0; i<m; i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        createlist(u,v,w);
        //createlist(v,u,w);
    }
    scanf("%d",&strt);
}
int main()
{
    scanfile();
    bellmanford(strt);
    printf("%d%d%d\n",n,m,l);
    printf("shotest distance from the source vertex\n");
    for(int i=0; i<n; i++)
    {
        printf("%d--->%d\n",i,dist[i]);
    }
    return 0;
}