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

node* search(node* Ttree,int a)
{
  if(Ttree==NULL) return NULL;
  if(Ttree->p->time>a) Ttree->l=search(Ttree->l,a);
  if(Ttree->p->time<a) Ttree->r=search(Ttree->r,a);
  if(Ttree->p->time==a)
    {
      printf("key found\n");
      return Ttree;
    }
  return Ttree;
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

node* insert(node* Ttree,pro *a)
{
  node *temp=Ttree,*bTtree=Ttree;
  node * z=NULL;
  int y=0;
  while(1)
    {
      if(!temp)
	{
	  z=(node *)malloc(sizeof(node));
	  z->p=a;
	  z->l=z->r=NULL;
	  if(Ttree)
	    {
	      z->parent=bTtree;
	      if(bTtree->p->time<z->p->time)
		{
		  bTtree->r=z;
		}
	      else bTtree->l=z;
	    }
	  else
	    {
	      Ttree=z;
	      Ttree->parent=NULL;
	      bTtree=z;
	    }
	  z->color=1;
	  y=2;
	  break;
	}
      else if(temp->p->time>a->time)
	{
	  bTtree=temp;
	  temp=temp->l;
	}
      else if(temp->p->time<a->time)
	{
	  bTtree=temp;
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
  else pt=z;
  node *pp = NULL;
  node *gpp = NULL;  
  if(!pt->parent) pt->parent=(node*)malloc(sizeof(node));
  while ( (pt != Ttree) && (pt->color == 1) && (pt->parent->color == 1) )
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
		  Ttree=rotateL(Ttree, pp);
		  pt = pp;
		  pp = pt->parent;
		}
	      Ttree=rotateR(Ttree, gpp);
	      
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
		  Ttree=rotateR(Ttree, pp);
		  pt = pp;
		  pp = pt->parent;
		}
	      Ttree=rotateL(Ttree, gpp);
	      int tempo=pp->color;
	      pp->color=gpp->color;
	      gpp->color=tempo;
	      pt = pp;
	    }
	}
    }
  Ttree->color = 0;
  return Ttree;	
}

node* least_ET(node* Ttree)
{
  if(!Ttree) return NULL;
  if(!Ttree->l) return Ttree;
  else return least_ET(Ttree->l);
} 

node* deleteNode(node* root,int key,node *Ttree)
{
  if (!root) return NULL;
  if (key < root->p->priority)
    root->l = deleteNode(root->l, root->p->time,root);
  else if (key > root->p->priority)
    root->r = deleteNode(root->r, root->p->time,root);
  else
    {
      Ttree=(node*)malloc(sizeof(node));
      Ttree->l=Ttree->r=Ttree->parent=NULL;
      Ttree->color=root->color;
      Ttree->p=root->p;
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

node* deletefun(node *Ttree,node *temp)
{
  node *x=least_ET(Ttree);
  Ttree= deleteNode(Ttree,x->p->time,temp);
  return x;
}

void preorder(node *Ttree)
{
  if(!Ttree) return;
  else
    {
      printf(" [ %d ,%d ,%d %s ] ",Ttree->p->priority,Ttree->p->time,Ttree->p->pro_id,(Ttree->color==1)?"Red":"Black" );
      preorder(Ttree->l);
      preorder(Ttree->r);  
    }
}

void inorder(node *Ttree)
{
  if(!Ttree) return ;
  else
    {
      inorder(Ttree->l);
      printf(" [ %d ,%d ,%d %s ] ",Ttree->p->priority,Ttree->p->time,Ttree->p->pro_id,(Ttree->color==1)?"Red":"Black" );
      inorder(Ttree->r);    
    }   	
}

int main()
{
  int t=0;
  int n;
  int i,j;
  node *root=NULL;
  node *temp=NULL;
  pro *p=NULL;
  printf("Enter the value of n: ");
  scanf("%d",&n);
  for(i=0;i<n;i++)
    {
      p=(pro*)malloc(sizeof(pro));
      p->next=NULL;
      p->time=1+rand()%1000;
      p->pro_id=i;
      p->priority=1+rand()%4;
      temp=(node*)malloc(sizeof(node));
      temp->p=p;
      root=insert(root,p);
      j=t;
      t=t+(50*temp->p->priority);
      temp->p->time=temp->p->time-(50*temp->p->priority);
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

  printf("\nPreorder : ");
  preorder(root);
    
  printf("\n\nInorder : ");  
  inorder(root); 
  printf("\n");   
}
