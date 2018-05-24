#pragma once

#include <memory>
#include <vector>
#include <iostream>

namespace assignment3
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree
	{
	public:
		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		std::shared_ptr<TreeNode<T>> mRoot;
	};

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<TreeNode<T>>(std::move(data));
		}
		else
		{
			std::shared_ptr<TreeNode<T>> currentNode = mRoot;
			std::shared_ptr<TreeNode<T>> nextNode = mRoot;
			bool left = true;
			while (nextNode != nullptr)
			{
				currentNode = nextNode;
				if (*data <= *currentNode->Data)
				{
					nextNode = currentNode->Left;
					left = true;
				}
				else
				{
					nextNode = currentNode->Right;
					left = false;
				}
			}
			nextNode = std::make_shared<TreeNode<T>>(currentNode, std::move(data));
			if (left)
			{
				currentNode->Left = nextNode;
			}
			else
			{
				currentNode->Right = nextNode;
			}
		}
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		std::shared_ptr<TreeNode<T>> currentNode = mRoot;
		while (currentNode != nullptr)
		{
			if (data == *currentNode->Data)
			{
				return true;
			}
			else if (data < *currentNode->Data)
			{
				currentNode = currentNode->Left;
			}
			else
			{
				currentNode = currentNode->Right;
			}
		}
		return false;
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		if (Search(data))
		{
			std::shared_ptr<TreeNode<T>> currentNode = mRoot;
			std::shared_ptr<TreeNode<T>> previousNode = mRoot;
			bool left = false;
			while (data != *currentNode->Data)
			{
				previousNode = currentNode;
				if (data < *currentNode->Data)
				{
					left = true;
					currentNode = currentNode->Left;
				}
				else
				{
					left = false;
					currentNode = currentNode->Right;
				}
			}
			if (currentNode->Left == nullptr && currentNode->Right == nullptr)
			{
				//Just delete the TreeNode
				if (left)
				{
					previousNode->Left = nullptr;
				}
				else
				{
					previousNode->Right = nullptr;
				}

			}
			else if (currentNode->Left != nullptr && currentNode->Right == nullptr)
			{
				//Only left TreeNode Exists
				currentNode = currentNode->Left;
				if (left)
				{
					previousNode->Left = currentNode;
				}
				else
				{
					previousNode->Right = currentNode;
				}
				currentNode->Parent = previousNode;
			}
			else if (currentNode->Left == nullptr && currentNode->Right != nullptr)
			{
				//Only Right TreeNode Exists
				currentNode = currentNode->Right;
				if (left)
				{
					previousNode->Left = currentNode;
				}
				else
				{
					previousNode->Right = currentNode;
				}
				currentNode->Parent = previousNode;
			}
			else
			{
				//Both exists
				std::shared_ptr<TreeNode<T>> leftMostPrevious = currentNode;
				std::shared_ptr<TreeNode<T>> leftMostNode = currentNode->Right;
				while (leftMostNode->Left != nullptr)
				{
					leftMostPrevious = leftMostNode;
					leftMostNode = leftMostNode->Left;
				}
				//Remove leftMost from the end
				std::shared_ptr<TreeNode<T>> temp = leftMostNode->Right;
				if (temp != nullptr)
				{
					if (leftMostPrevious != currentNode)
					{
						leftMostPrevious->Left = temp;
						temp->Parent = leftMostPrevious;
					}
				}

				//Move LeftMost to correct position
				if (left)
				{
					previousNode->Left = leftMostNode;

				}
				else
				{
					previousNode->Right = leftMostNode;
				}
				leftMostNode->Parent = previousNode;
				leftMostNode->Left = currentNode->Left;

				if (currentNode->Right != leftMostNode)
				{
					leftMostNode->Right = currentNode->Right;
				}
				else
				{
					currentNode->Right = nullptr;
				}
				if (currentNode->Left != nullptr)
				{
					temp = currentNode->Left;
					temp->Parent = leftMostNode;
				}
				if (currentNode->Right != nullptr)
				{
					temp = currentNode->Right;
					temp->Parent = leftMostNode;
				}
			}
			return true;
		}
		return false;
	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRoot;
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> inOrderVector;
		std::vector<T> rightVector;

		if (startNode == nullptr)
		{
			return inOrderVector;
		}
		else
		{

			inOrderVector = TraverseInOrder(startNode->Left);
			inOrderVector.push_back(*startNode->Data);
			rightVector = TraverseInOrder(startNode->Right);

			for (auto i : rightVector)
			{
				inOrderVector.push_back(i);
			}
		}
		return inOrderVector;
	}
}
