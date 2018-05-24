#include "TreeNode.h"
#include "BinarySearchTree.h"
#include <string>
#include <iostream>

using namespace assignment3;

int main()
{
	BinarySearchTree<int> tree;

	bool bSearched = tree.Search(15);

	tree.Insert(std::make_unique<int>(10));
	tree.Insert(std::make_unique<int>(15));
	tree.Insert(std::make_unique<int>(5));
	tree.Insert(std::make_unique<int>(4));
	tree.Insert(std::make_unique<int>(19));
	tree.Insert(std::make_unique<int>(20));
	tree.Insert(std::make_unique<int>(17));
	tree.Insert(std::make_unique<int>(12));

	std::vector<int> v = tree.TraverseInOrder(tree.GetRootNode().lock());

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	std::cout << "--------------------------" << std::endl;

	bSearched = tree.Search(15);

	tree.Delete(5);

	v = tree.TraverseInOrder(tree.GetRootNode().lock());

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	std::cout << "--------------------------" << std::endl;

	bSearched = tree.Search(15);


	return 0;
}
