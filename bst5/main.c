/* Programmer's Name: Surendra Baskey
   Program Name: bst.c
   Program Description: Write a menu based program to implement a binary search tree.
   Date: 6/3/18 */

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
	struct node *left,*right,*parent;
};

struct node *root;

struct node* search(struct node* r, int item)
{
	if(r==NULL || r->key == item)
		return r;
	else if(item < r->key)
		return search(r->left,item);
	else
		return search(r->right,item);
}

struct node* insert(struct node* p, struct node* r, int item)
{
	if(r==NULL)
	{
		r=(struct node*)malloc(sizeof(struct node));
		r->parent=p;
		r->key=item;
		return r;
	}
	if(item < r->key)
		r->left=insert(r,r->left,item);
	else if(item > r->key)
		r->right=insert(r,r->right,item);
	return r;
}

struct node* findmin(struct node* r)
{
	if(r->left!=NULL)
		r=findmin(r->left);
	return r;
}

struct node* findmax(struct node* r)
{
	if(r->right!=NULL)
		r=findmax(r->right);
	return r;
}

void inorder(struct node* r)
{
	if(r==NULL)
		return;
	inorder(r->left);
	printf("%d  ", r->key);
	inorder(r->right);
}

void postorder(struct node* r)
{
	if(r==NULL)
		return;
	postorder(r->left);
	postorder(r->right);
	printf("%d  ", r->key);
}

struct node* predecessor(struct node* r)
{
	struct node *curr, *p;
	if(r->left!=NULL)
		return findmax(r->left);
	else
	{
		curr=r;
		p=r->parent;
		while(p!=NULL && curr==p->left)
		{
			curr=p;
			p=curr->parent;
		}
		return p;
	}
}

struct node* delete(struct node* r, int item)
{
	if(r==NULL)
		return r;
	if(item < r->key)
		r->left=delete(r->left,item);
	else if(item > r->key)
		r->right=delete(r->right,item);
	else
	{
		if(r->left==NULL && r->right==NULL)
		{
			free(r);
			return NULL;
		}
		else if(r->left==NULL)
		{
			struct node* t=r->right;
			t->parent=r->parent;
			free(r);
			return t;
		}
		else if(r->right==NULL)
		{
			struct node* t=r->left;
			t->parent=r->parent;
			free(r);
			return t;
		}
		else
		{
			struct node* y=predecessor(r);
			int pred=y->key;
			r->left=delete(root, pred);
			r->key=pred;
		}
	}
	return r;
}

void printtree(struct node* r, int space)
{
	int i;
    	if (r == NULL)
        	return;
    	space = space + 5;
    	printtree(r->right, space);
    	printf("\n");
    	for (i = 0; i < space; i++)
        	printf(" ");
    	printf("%d\n", r->key);
    	printtree(r->left, space);
}

int main()
{
	int ch,item;
	struct node *r,*r1;
	do
	{
		printf("\nMenu\n\n1. Search\n2. Insert\n3. Find Minimum\n4. InOrder Traversal\n5. PostOrder Traversal\n6. Find Predecessor\n7. Delete\n8. Display Tree\n9. Exit\n\n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: scanf("%d", &item);
				r=search(root,item);
				if(r==NULL)
					printf("Not Found\n");
				else
					printf("Found\n");
				break;
			case 2: scanf("%d", &item);
				root=insert(NULL,root,item);
				break;
			case 3: r=findmin(root);
				printf("Minimum is: %d\n", r->key);
				break;
			case 4: printf("InOrder Traversal:\n");
				inorder(root);
				printf("\n");
				break;
			case 5: printf("PostOrder Traversal:\n");
				postorder(root);
				printf("\n");
				break;
			case 6: scanf("%d", &item);
				r=search(root,item);
				if(r==NULL)
					printf("Number is not present in the tree\n");
				else
				{
					r1=findmin(root);
					if(r1->key==item)
						printf("No predecessor\n");
					else
					{
						r=predecessor(r);
						printf("Predecessor of %d is %d\n", item, r->key);
					}
				}
				break;
			case 7: scanf("%d", &item);
				r=search(root,item);
				if(r==NULL)
					printf("Number is not present in the tree\n");
				else
					r=delete(root,item);
				break;
			case 8: printf("\n");
				printtree(root, 1);
				printf("\n");
				break;
			case 9: break;
			default:printf("Invalid Choice\n");
				break;
		}
	}
	while(ch!=9);
	return 0;
}	 
	
	
