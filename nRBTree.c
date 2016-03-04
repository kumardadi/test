#include<stdio.h>
#include<stdlib.h>
 
enum node_color
{
	red, black
};
 
typedef struct RB_node
{
	int key;
	enum node_color color;
	struct RB_node *left,  *right, *parent;
 
}node;
 
 
void left_rotation(node *root,node *x)
{
	node *y;
	y = x->right;
	x->right=y->left;
	if(y->left != NULL)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL)
	{
		root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent = y;
	}
	else
	{
		x->parent = y ;
	}
	y->left = x ;
	x->parent = y;
}
 
void right_rotation(node *root,node *x)
{
	node *y;
	y = x->left;
	x->left=y->right;
	if(y->right != NULL)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL)
	{
		root = y;
	}
	else if (x == x->parent->right)
	{
		x->parent = y;
	}
	else
	{
		x->parent = y ;
	}
	y->right = x ;
	x->parent = y;
}
 
node tree_minimum(node *x)
{
	while(x->left !=NULL)
	{
		x = x->left;
	}
	return *x ;
}
 
void transplant(node *root, node *x, node *y)
{
	if(x->parent == NULL)
	{
		root = y ;
	}
	else if(x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	if(y !=NULL)
	{
		y->parent = x->parent;
	}
}
 
void RB_insert_fixup(node *root,node *z)
{
	node *y;
	while(z->parent && z->parent->color == red)
	{
		if(z->parent->color == z->parent->parent->color)
		{
			y = z->parent->parent->right;
			if(y->color == red)
			{
				z->parent->color = black;
				y->color = black;
				z->parent->parent->color = red;
				z = z->parent->parent;
			}
			else if(z == z->parent->right)
			{
				z = z->parent;
				left_rotation(root,z);
			}
			z->parent->color = black;
			z->parent->parent->color = red;
			right_rotation(root,z->parent->parent);
		}
		else
		{
			y = z->parent->parent->left;
			if(y->color == red)
			{
				z->parent->color = black;
				y->color = black;
				z->parent->parent->color = red;
				z = z->parent->parent;
			}
			else if(z == z->parent->left)
			{
				z = z->parent;
				right_rotation(root,z);
			}
			z->parent->color = black;
			z->parent->parent->color = red;
			left_rotation(root,z->parent->parent);
		}
	}
	root->color = black;
}
 
void RB_insert(node *root , node *z)
{
	node *x , *y;
	y = NULL;
	x = root;
	while(x != NULL)
	{
		y = x;
		if(z->key < x->key)
		{
			x = x->left;
		}
		else{
			x = x->left;
		}
	}
	z->parent = y;
	if(y == NULL)
	{
		root = z;
	}
	if(z&&y&&(z->key < y->key))
	{
		y->left = z;
	}
	else if(y){
		y->right = z;
	}
	z->left = NULL;
	z->right = NULL;
	z->color = red;
	RB_insert_fixup(root,z);
	printf("%d is inserted \n ",z->key);
}
 
void RB_delete_fixup(node *root, node *x)
{
	node *w;
	while(x != root && x->color == black)
	{
		if(x == x->parent->left)
		{
			w = x->parent->right;
			if(w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				left_rotation(root, x->parent);
				w = x->parent->right;
			}
			if(w->left->color == black && w->right->color == black)
			{
				w->color = red;
				x=x->parent;
			}
			else if(w->right->color == black)
			{
				w->left->color = black;
				w->color = red;
				right_rotation(root, w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = black;
			w->right->color = black;
			left_rotation(root, x->parent);
			x = root;
		}
		else
		{
			w = x->parent->left;
			if(w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				left_rotation(root, x->parent);
				w = x->parent->left;
			}
			if(w->right->color == black && w->left->color == black)
			{
				w->color = red;
				x=x->parent;
			}
			else if(w->left->color == black)
			{
				w->right->color = black;
				w->color = red;
				left_rotation(root, w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = black;
			w->left->color = black;
			right_rotation(root, x->parent);
			x = root;
		}
	}
	x->color = black;
}
 
void RB_delete(node *root,node *z)
{
	node *x, *y, *y_original;
	y = z;
	y_original=(node*)malloc(sizeof(node));
	y_original->color = y->color;
	if(z->left ==NULL)
	{
		x = z->right;
		transplant(root, z ,z->right);
	}
	else if(z->right == NULL)
	{
		x = z->left;
		transplant(root, z, z->left);
	}
	else
	{
		*y = tree_minimum(z->right);
		y_original->color = y->color;
		x = y->right;
		if(y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			transplant(root , y , y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(root, z , y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if(y_original->color == black)
	{
		RB_delete_fixup(root, x);
	}
	printf("%d is deleted \n ",z->key);
}
 
void main()
{
    node *root = NULL;
	int i=0,j=0;
	int arr[] = {21, 32, 4 , 7 , 8 ,29};
	while(i< 5)
	{
		node *temp=(node*)malloc(sizeof(node));
		temp->key=arr[i];
		RB_insert(root, temp);
		i++;
	}
	while(j< 2)
	{
		node *temp=(node*)malloc(sizeof(node));
		temp->key=arr[i];
		RB_delete(root, temp);
		j++;
	}
 
}
