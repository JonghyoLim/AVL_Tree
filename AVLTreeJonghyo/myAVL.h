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
	//Assignment1
	void InsertItem(ItemType item);
	void Insert(TreeNode<ItemType>*& tree, ItemType item, bool & taller);
	void RightBalance(TreeNode<ItemType>*& tree, bool & taller);
	void LeftBalance(TreeNode<ItemType>*& tree, bool & taller);
	void RotateLeft(TreeNode<ItemType>*& tree);
	void RotateRight(TreeNode<ItemType>*& tree);
	void PrintTree();

	//Assignment2
	void RetrieveItem(ItemType& item, bool& found);
	void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found);

	//Assignment3
	void DeleteItem(ItemType item, bool& found);
	void Delete(TreeNode<ItemType>*& tree, ItemType item, bool & shorter, bool& found);
	void DeleteNode(TreeNode <ItemType> * & tree, bool & shorter);
	void GetPredecessor(TreeNode<ItemType> * tree, ItemType & data);
	void DelRightBalance(TreeNode<ItemType> *& tree, bool & shorter);
	void DelLeftBalance(TreeNode<ItemType> *& tree, bool & shorter);
	void MakeEmpty();

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
void TreeType<ItemType>::MakeEmpty()
{
	Destroy(root);
	root = NULL;
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
void TreeType<ItemType> ::DeleteItem(ItemType item, bool& found )
// Calls recursive function Delete to delete item from tree.
{
	bool shorter;
	Delete(root, item, shorter, found); // added bool$ found to pass to Delete method
}


template <class ItemType>
void TreeType<ItemType> ::Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter , bool& found)
{
	if (tree != NULL)
	{
		if (strcmp(item.c_str(), tree->info.c_str()) < 0)
		{
			Delete(tree->left, item, shorter, found);
			// Look in left subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: tree->bf = EH;
					break;
				case EH: tree->bf = RH;
					shorter = false;
					break;
				case RH: DelRightBalance(tree, shorter);
				} // END SWITCH	
		}
		else if (strcmp(item.c_str(), tree->info.c_str()) > 0)
		{
			Delete(tree->right, item, shorter , found);
			// Look in right subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: DelLeftBalance(tree, shorter);
					break;
				case EH: tree->bf = LH; shorter = false;
					break;
				case RH: tree->bf = EH;
					break;
				} // END SWITCH
		}
		else
			//afterDeleteItemPrintItem(tree); // doesnt
			DeleteNode(tree, shorter);
		// Node found; call DeleteNode.
	} // END if (tree != NULL)


	else
	{
		found = false;
		cout << "\n\tNOTE: <" << item << "> not in the tree so cannot be deleted.\n";
	}
}


template <class ItemType>
void TreeType<ItemType>:: DeleteNode(TreeNode <ItemType> * & tree, bool & shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node 
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
	ItemType data;	
	TreeNode <ItemType> * tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		bool found = false;
		Delete(tree->left, data, shorter, found);
		
		// Delete the predecessor node
		if (shorter)
			switch (tree->bf)
			{
			case LH: tree->bf = EH;
				break;
			case EH: tree->bf = RH; shorter = false;
				break;
			case RH: DelRightBalance(tree, shorter);
			}
		
	}
}


template <class ItemType>
void TreeType<ItemType>:: GetPredecessor(TreeNode<ItemType> * tree, ItemType & data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;

	while (tree->right != NULL)
		tree = tree->right;

	data = tree->info;
}


template <class ItemType>
void TreeType<ItemType>:: DelRightBalance(TreeNode<ItemType> *& tree, bool & shorter)
{
	TreeNode<ItemType> * rs = tree->right;
	TreeNode<ItemType> * ls;
	switch (rs->bf)
	{
	case RH:	
		tree->bf = rs->bf = EH;
		RotateLeft(tree);
		shorter = true;
		break;
	case EH:	
		tree->bf = RH;
		rs->bf = LH;
		RotateLeft(tree);
		shorter = false; 
		break;
	case LH:	
		ls = rs->left;
		switch (ls->bf)
		{
		case RH:
			tree->bf = LH;
			rs->bf = EH; 
			break;
		case EH:	
			tree->bf = rs->bf = EH;
			break;
		case LH:	
			tree->bf = EH;
			rs->bf = RH;
			break;
		} // end switch

		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		shorter = true;
	}
}

template <class ItemType>
void TreeType<ItemType>::DelLeftBalance(TreeNode<ItemType> *& tree, bool & shorter)
{
	TreeNode<ItemType> * ls = tree->left;
	TreeNode<ItemType> * rs;
	switch (ls->bf)
	{
	case LH:	
		tree->bf = ls->bf = EH;
		RotateRight(tree);
		shorter = true; 
		break;
	case EH:	
		tree->bf = LH;
		ls->bf = RH;
		RotateRight(tree);
		shorter = false;
		break;
	case RH:	
		rs = ls->right;
		switch (rs->bf)
		{
		case LH:	
			tree->bf = RH;
			ls->bf = EH; 
			break;
		case EH:	
			tree->bf = ls->bf = EH;
			break;
		case RH:	
			tree->bf = EH;
			ls->bf = LH;
			break;
		} // end switch
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		shorter = true;
	}
}






template<class ItemType>
void TreeType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
	Retrieve(root, item, found);
}


template<class ItemType>
void TreeType<ItemType>::Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found)
{
	if (tree == NULL)
		found = false;

	else if (strcmp(item.c_str(), tree->info.c_str()) < 0)// strcmp(p1, p2) < 0
		Retrieve(tree->left, item, found);


	else if (strcmp(item.c_str(), tree->info.c_str()) > 0)// strcmp(p1, p2) > 0
		Retrieve(tree->right, item, found);
	else
	{
		PrintItem(tree);
		Retrieve(tree->left, item, found);
		Retrieve(tree->right, item, found);
		found = true;
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
		// Insert into left subtree	
		if (taller)	
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
		// Insert into right subtree
	
		Insert(tree->right, item, taller);
		if (taller)
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
		cout << "\tIt is impossible to rotate an empty tree in RotateLeft" << endl;

	else if (tree->right == NULL)
		cout << "\tIt is impossible to make an empty subtree the root in RotateLeft" << endl;

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
		cout << "\tIt is impossible to rotate an empty tree in RotateRight" << endl;

	else if (tree->left == NULL)
		cout << "\tIt is impossible to make an empty subtree the root in RotateRight" << endl;
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
		cout << "\n\t" << tree->info << ": ";

		string left, right;

		if (tree->left == NULL)
			left = "NULL";
		else left = tree->left->info;

		if (tree->right == NULL)
			right = "NULL";
		else right = tree->right->info;


		if (tree->bf == LH) { cout << " Left = " << left << ", Right = " << right << ", BF = LH " << endl; }

		else if (tree->bf == EH) { cout << " Left = " << left << ", Right = " << right << ", BF = EH " << endl; }

		else if (tree->bf == RH) { cout << " Left = " << left << ", Right = " << right << ", BF = RH " << endl; }

		Print(tree->right);
	}

}

	template<class ItemType>
	void PrintItem(TreeNode<ItemType>* tree)

	{
		cout << "\tYour searching letter: <" << tree->info <<">" << endl;
	}

