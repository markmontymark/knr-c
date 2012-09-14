#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorted_tree.h"


ordered_tree_str_t * ordered_tree_str_new(char * str)
{
	char * node_str = strdup(str);
	ordered_tree_str_t * node = malloc(sizeof(ordered_tree_str_t));
	node->str = node_str;
	node->count = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}


void ordered_tree_str_add(ordered_tree_str_t * node,char * str)
{
	int cmp = strcmp(str,node->str);

	if( cmp < 0 )
	{
		if( node->left == NULL )
			node->left = ordered_tree_str_new(str);
		else
			ordered_tree_str_add(node->left,str);
	}

	else if( cmp == 0 )
		node->count++;

	else
	{
		if( node->right == NULL )
			node->right = ordered_tree_str_new(str);
		else
			ordered_tree_str_add(node->right,str);
	}
}


void ordered_tree_str_traverse(ordered_tree_str_t * node,void (* func)(ordered_tree_str_t *) )
{
	if( node == NULL )
		return;

	if(node->left != NULL)
		ordered_tree_str_traverse(node->left,func);

	(*func)(node);

	if(node->right != NULL)
		ordered_tree_str_traverse(node->right,func);
}

void ordered_tree_str_free(ordered_tree_str_t * node)
{
	if( node == NULL)
		return;
	if(node->left != NULL)
		ordered_tree_str_free(node->left);
	if(node->right != NULL)
		ordered_tree_str_free(node->right);
	free(node->str);
	free(node);
}



ordered_tree_t * ordered_tree_new(void * data,void * ( * func_copy_ctor)(void *))
{
	void * node_data = (*func_copy_ctor)(data);
	ordered_tree_t * node = malloc(sizeof(ordered_tree_t));
	node->data = node_data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void ordered_tree_free(ordered_tree_t * node,void (*func_free)(void * data))
{
	if( node == NULL)
		return;
	if(node->left != NULL)
		ordered_tree_free(node->left,func_free);
	if(node->right != NULL)
		ordered_tree_free(node->right,func_free);
	(*func_free)(node->data);
	free(node->data); // or should node->data be free'd by func_free?
	free(node);
}

void ordered_tree_add(ordered_tree_t * node,ordered_tree_t * new_node, int (* func_comparator)(void * a,void * b))
{
	int cmp = (*func_comparator)(new_node->data,node->data);
	if( cmp < 0 )
	{
		if( node->left == NULL )
			node->left = new_node;
		else
			ordered_tree_add(node->left,new_node,func_comparator);
	}

	else if( cmp == 0 )
	{
		//node->count++;
		printf("how to handle add collisions?\n");
	}

	else
	{
		if( node->right == NULL )
			node->right = new_node;
		else
			ordered_tree_add(node->right,new_node,func_comparator);
	}
}

void ordered_tree_traverse(ordered_tree_t * node,void (* func)(void * data) )
{
	if( node == NULL )
		return;

	if(node->left != NULL)
		ordered_tree_traverse(node->left,func);

	(*func)(node->data);

	if(node->right != NULL)
		ordered_tree_traverse(node->right,func);
}




