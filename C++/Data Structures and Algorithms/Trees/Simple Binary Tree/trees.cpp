#include <stdio.h>
#include <iostream>
#include <string.h>


class NodeItem
{
private:

	int value;

public:	

	int getValue()					
	{	
		return this->value;	
	}
	
	void setValue(int value)	
	{ 
		this->value = value;	
	}

	NodeItem(int value)
	{
		setValue(value);
	}	
};

//-------------------------------------------------------------------------------
// The main thing is a node
typedef struct t_node
{
	t_node* left;
	t_node* right;
	NodeItem* item;
} t_node;

//-------------------------------------------------------------------------------
void BinTree_insert(t_node* bintree, NodeItem* item);

//-------------------------------------------------------------------------------
void insert_node(t_node** node, NodeItem* item)
{
	if (*node != NULL)		
		BinTree_insert(*node, item);
	else
	{	
		*node = new t_node();
		(*node)->item = item;
		(*node)->left = NULL;
		(*node)->right = NULL;
	}	
}
//-------------------------------------------------------------------------------
// the left node shall be smaller or equal to the parent node
// the right node bigger
void BinTree_insert(t_node* bintree, NodeItem* item)
{		
	if (item->getValue() > bintree->item->getValue())
		insert_node(&bintree->right, item);
	else								
		insert_node(&bintree->left, item);
}

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	t_node* BinTree = new t_node();	

	// root node
	BinTree->item = new NodeItem(5);
	BinTree->left = NULL;
	BinTree->right = NULL;

	// build up the tree
	BinTree_insert(BinTree, new NodeItem(2));
	BinTree_insert(BinTree, new NodeItem(3));
	BinTree_insert(BinTree, new NodeItem(6));
	BinTree_insert(BinTree, new NodeItem(7));

	std::cout << "Node " << BinTree->right->item->getValue();

	int n;
	std::cin >> n;
}
