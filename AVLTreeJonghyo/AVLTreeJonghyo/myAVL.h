#pragma once
#include "stdafx.h"

using namespace std;

typedef enum { LH, EH, RH } BalFactor;
template <class ItemType>
struct TreeNode
{
	ItemType info;
	TreeNode *left;
	TreeNode *right;
	BalFactor bf;
};


template <class ItemType>
class TreeType
{
public:
	TreeType();
	~TreeType();
	void InsertItem(ItemType item);
	void Insert(TreeNode<ItemType>*& tree, ItemType item, bool & taller);
	void RightBalance(TreeNode<ItemType>*& tree, bool & taller);
	void LeftBalance(TreeNode<ItemType>*& tree, bool & taller);
	void RotateLeft(TreeNode<ItemType>*& tree);
	void RotateRight(TreeNode<ItemType>*& tree);
	void PrintTree();

private:
	TreeNode<ItemType> * root;

};


template <class ItemType>
TreeType<ItemType> ::TreeType()
{
	root = NULL;
}

template<class ItemType>
TreeType<ItemType> :: ~TreeType()
{
	Destroy(root);
}


template<class ItemType>
void Destroy(TreeNode<ItemType>*& tree)
{
	if (tree != NULL)
	{
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}



template <class ItemType>
void TreeType<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller = false;
	Insert(root, item, taller);
}


template <class ItemType>
void TreeType<ItemType> ::Insert(TreeNode<ItemType>*& tree, ItemType item, bool & taller)
// Inserts item into tree.			
// Post: item is in tree; search property is maintained.
{
	if (tree == NULL)
	{	// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->bf = EH;
		taller = true;
	}
	else if (strcmp(item.c_str(), tree->info.c_str()) == 0)
		cout << "\tDuplicate key is not allowed in AVL tree." << endl;
	else if (strcmp(item.c_str(), tree->info.c_str()) < 0)
	{
		Insert(tree->left, item, taller);
		// Insert into left subtree	if (taller)	
		switch (tree->bf)
		{
		case LH: LeftBalance(tree, taller);
			break;
		case EH: tree->bf = LH;
			break;
		case RH: tree->bf = EH;
			taller = false;
			break;
		}
	}

	else {
		// Insert into right subtree if (taller)
		Insert(tree->right, item, taller);
		switch (tree->bf)
		{
		case RH: RightBalance(tree, taller);
			break;
		case EH: tree->bf = RH;
			break;
		case LH: tree->bf = EH;
			taller = false;
			break;
		}
	}
}



template <class ItemType>
void TreeType<ItemType> ::RightBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * rs = tree->right;
	TreeNode<ItemType> * ls;

	switch (rs->bf)
	{
	case RH: tree->bf = rs->bf = EH;
		RotateLeft(tree);
		taller = false;
		break;

	case EH: cout << "\tTree already balanced " << endl;
		break;

	case LH: ls = rs->left;
		switch (ls->bf)
		{
		case RH: tree->bf = LH;
			rs->bf = EH;
			break;
		case EH: tree->bf = rs->bf = EH;
			break;
		case LH: tree->bf = EH;
			rs->bf = RH;
			break;
		}

		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}



template <class ItemType>
void TreeType<ItemType> ::LeftBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * ls = tree->left;
	TreeNode<ItemType> * rs;

	switch (ls->bf)
	{
	case LH: tree->bf = ls->bf = EH;
		RotateRight(tree);
		taller = false;
		break;
	case EH: cout << "\tTree already balanced " << endl;
		break;
	case RH: rs = ls->right;
		switch (rs->bf)
		{
		case LH: tree->bf = RH;
			ls->bf = EH;
			break;
		case EH: tree->bf = ls->bf = EH;
			break;
		case RH: tree->bf = EH;
			ls->bf = LH;
			break;
		}
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}



template <class ItemType>
void TreeType<ItemType> ::RotateLeft(TreeNode<ItemType> * & tree)
{
	TreeNode<ItemType> * rs;
	if (tree == NULL)
		cout << "It is impossible to rotate an 	empty tree in RotateLeft" << endl;

	else if (tree->right == NULL)
		cout << "It is impossible to make an empty subtree the root in RotateLeft" << endl;

	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}


template <class ItemType>
void TreeType<ItemType> ::RotateRight(TreeNode<ItemType> * & tree)
{
	TreeNode<ItemType> * ls;
	if (tree == NULL)
		cout << "It is impossible to rotate an empty tree in RotateRight" << endl;

	else if (tree->left == NULL)
		cout << "It is impossible to make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
}

// From here is all about print method

template<class ItemType>
void TreeType<ItemType>::PrintTree()
{
	Print(root);
}


template<class ItemType>
void Print(TreeNode<ItemType>* tree)

{
	if (tree != NULL)
	{
		Print(tree->left);
		cout << "\n\t" << tree->info;
		if (tree->bf == LH) { cout << ": ( LH )" << endl; }
		
		else if (tree->bf == EH) { cout << ": ( EH )" << endl; }
		
		else if (tree->bf == RH) { cout << ": ( RH )" << endl; }

		Print(tree->right);
	}
}