#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

typedef struct _pro
{
  int time;
  int priority;
  int pro_id;
  struct _pro *next;
}pro;

typedef struct _node
{
  int color;
  struct _pro *p; 
  struct _node *l;
  struct _node *r;
  struct _node *parent;
}node;

node* search(node* tree,int a)
{
  if(tree==NULL) return NULL;
  if(tree->p->time>a) tree->l=search(tree->l,a);
  if(tree->p->time<a) tree->r=search(tree->r,a);
  if(tree->p->time==a)
    {
      printf("key found\n");
      return tree;
    }
  return tree;
}

node* rotateL(node *root, node *pt)
{
  node *p_r = pt->r;
  pt->r = p_r->l;
  if (pt->r)
    pt->r->parent = pt;
  p_r->parent = pt->parent;
  if (!pt->parent)
    root = p_r;
  else if (pt != pt->parent->l)
    pt->parent->r = p_r;
  else
    pt->parent->l = p_r;
  pt->parent = p_r;  
  p_r->l = pt;
  return root;
}

node* rotateR(node *root, node *pt)
{
  node *p_l = pt->l;
  pt->l = p_l->r;
  if (pt->l)
    pt->l->parent = pt;
  p_l->parent = pt->parent;
  if (!pt->parent)
    root = p_l;
  else if (pt != pt->parent->l)
    pt->parent->r = p_l;
  else
    pt->parent->l = p_l;
  p_l->r = pt;
  pt->parent = p_l;  
  return root; 
}

node* insert(node* tree,pro *a)
{
  node *temp=tree,*btree=tree;
  node * zee=NULL;
  int y=0;
  while(1)
    {
      if(temp==NULL)
	{
	  zee=(node *)malloc(sizeof(node));
	  zee->p=a;
	  zee->l=zee->r=NULL;
	  if(tree!=NULL)
	    {
	      zee->parent=btree;
	      if(btree->p->time<zee->p->time)
		{
		  btree->r=zee;
		}
	      else btree->l=zee;
	    }
	  else
	    {
	      tree=zee;
	      tree->parent=NULL;
	      btree=zee;
	    }
	  zee->color=1;
	  y=2;
	  break;
	}
      else if(temp->p->time>a->time)
	{
	  btree=temp;
	  temp=temp->l;
	}
      else if(temp->p->time<a->time)
	{
	  btree=temp;
	  temp=temp->r; 
	}
      else
	{
	  pro *x=temp->p;
	  while(x->next) x=x->next;
	  x->next=a;	
	  y=1;
	  break;
	} 
    }
  node *pt;
  if(y==1) pt=temp;
  else pt=zee;
  node *pp = NULL;
  node *gpp = NULL;  
  if(!pt->parent) pt->parent=(node*)malloc(sizeof(node));
  while ( (pt != tree) && (pt->color == 1) && (pt->parent->color == 1) )
    {
      pp = pt->parent;
      gpp = pt->parent->parent;
      if (pp == gpp->l)
	{
	  node *uncle_pt = gpp->r;
	  if (uncle_pt && uncle_pt->color == 1)
	    {
	      gpp->color = 1;
	      pp->color = 0;
	      uncle_pt->color = 0;
	      pt = gpp;
	    }
	  else
	    {
	      if (pt == pp->r)
		{
		  tree=rotateL(tree, pp);
		  pt = pp;
		  pp = pt->parent;
		}
	      tree=rotateR(tree, gpp);
	      
	      int tempo=pp->color;
	      pp->color=gpp->color;
	      gpp->color=tempo;
	      
	      pt = pp;
	    }
	}
      else
	{
	  node *uncle_pt = gpp->l;
	  if (uncle_pt && (uncle_pt->color == 1))
	    {
	      gpp->color = 1;
	      pp->color = 0;
	      uncle_pt->color = 0;
	      pt = gpp;
	    }
	  else
	    {
	      if (pt == pp->l)
		{
		  tree=rotateR(tree, pp);
		  pt = pp;
		  pp = pt->parent;
		}
	      tree=rotateL(tree, gpp);
	      int tempo=pp->color;
	      pp->color=gpp->color;
	      gpp->color=tempo;
	      pt = pp;
	    }
	}
    }
  tree->color = 0;
  return tree;	
}

node* least_ET(node* tree)
{
  if(!tree) return NULL;
  if(!tree->l) return tree;
  else return least_ET(tree->l);
} 

node* deleteNode(node* root,int key,node *tempo)
{
  if (!root) return NULL;
  if (key < root->p->priority)
    root->l = deleteNode(root->l, root->p->time,root);
  else if (key > root->p->priority)
    root->r = deleteNode(root->r, root->p->time,root);
  else
    {
      tempo=(node*)malloc(sizeof(node));
      tempo->l=tempo->r=tempo->parent=NULL;
      tempo->color=root->color;
      tempo->p=root->p;
      root->p=NULL;
      if (!root->l)
        {
	  node *temp = root->r;
	  free(root);
	  return temp;
        }
      else if (!root->r)
        {
	  node *temp = root->l;
	  free(root);
	  return temp;
        }
      node* temp = root->r;
      root->p->priority = temp->p->priority;
      root->r = deleteNode(root->r, temp->p->time,root);
    }
  return root;    
}

node* deletefun(node *tree,node *temp)
{
  node *x=least_ET(tree);
  tree= deleteNode(tree,x->p->time,temp);
  return x;
}

void preorder(node *tree)
{
  if(!tree) return;
  else
    {
      printf(" [ %d ,%d ,%d %s ] ",tree->p->priority,tree->p->time,tree->p->pro_id,(tree->color==1)?"Red":"Black" );
      preorder(tree->l);
      preorder(tree->r);  
    }
}

void inorder(node *tree)
{
  if(!tree) return ;
  else
    {
      inorder(tree->l);
      printf(" [ %d ,%d ,%d %s ] ",tree->p->priority,tree->p->time,tree->p->pro_id,(tree->color==1)?"Red":"Black" );
      inorder(tree->r);    
    }   	
}

int main()
{
  int t=0;
  int n,i,j;
  node *root=NULL,*temp=NULL;
  pro *p=NULL;
  printf("Enter the value of n: ");
  scanf("%d",&n);
  for(i=0;i<n;i++)
    {
      p=(pro*)malloc(sizeof(pro));
      p->next=NULL;
      p->pro_id=i;
      p->priority=1+rand()%4;
      temp=(node*)malloc(sizeof(node));
      temp->p=p;
      root=insert(root,p);
      j=t;
      t+=(50*temp->p->priority);
      temp->p->time-=(50*temp->p->priority);
      if(temp->p->time)
        {
	  printf("\nProcess %d scheduled at %d till %d \n",temp->p->pro_id,j,t);
	  root=insert(root,temp->p);
        }
      else 
        {
	  printf("\nProcess %d scheduled at %d till %d \n",temp->p->pro_id,j,t);
	}
    }

  printf("\nPreorder Traversal : ");
  preorder(root);
    
  printf("\n\nInorder Traversal : ");  
  inorder(root); 
  printf("\n");   
}
