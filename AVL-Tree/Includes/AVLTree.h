#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <memory>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <vector>

template <typename T>
class AVLTree
{
private:

	struct node
	{
		T data;
		node* leftChild;
		node* rightChild;
		size_t height;

		node(const T& element, node *lChild, node *rChild, size_t h = 0):
			data{element}, leftChild{lChild}, rightChild{rChild}, height{h} {}
	};

	node* root;

	void leftRotate(node* &node2)
	{
		node *node1 = node2->leftChild;
		node2->leftChild = node1->rightChild;
		node1->rightChild = node2;
		node2->height = maxSize(heightHelper(node2->leftChild), heightHelper(node2->rightChild)) + 1;
		node1->height = maxSize(static_cast<size_t>(heightHelper(node1->leftChild)), node2->height) + 1;
		node2 = node1;
	}

	const T& maxSize(const T& x, const T& y)
	{
		return (x < y) ? y : x;
	}

	void rightRotate(node* &node2)
	{
		node *node1 = node2->rightChild;
		node2->rightChild = node1->leftChild;
		node1->leftChild = node2;
		node2->height = maxSize(heightHelper(node2->rightChild), heightHelper(node2->leftChild) + 1);
		node1->height = maxSize(static_cast<size_t>(heightHelper(node1->rightChild)), node2->height) + 1;
		node2 = node1;
	}

	void doubleLeftRotate(node* &node3)
	{
		rightRotate(node3->leftChild);
		leftRotate(node3);
	}

	void doubleRightRotate(node* &node3)
	{
		leftRotate(node3->rightChild);
		rightRotate(node3);
	}

	void balance(node* &temp)
	{
		if(temp == nullptr)
		{
			return;
		}

		if(heightHelper(temp->leftChild) - heightHelper(temp->rightChild) > 1)
		{
			if(heightHelper(temp->leftChild->leftChild) >= heightHelper(temp->leftChild->rightChild))
			{
				leftRotate(temp);
			}
			else
			{
				doubleLeftRotate(temp);
			}
		}
		else
		{
			if(heightHelper(temp->rightChild) - heightHelper(temp->leftChild) > 1)
			{
				if(heightHelper(temp->rightChild->rightChild) >= heightHelper(temp->rightChild->leftChild))
				{
					rightRotate(temp);
				}
				else
				{
					doubleRightRotate(temp);
				}
			}
		}
		temp->height = maxSize(heightHelper(temp->leftChild), heightHelper(temp->rightChild)) + 1;
	}

	void insertHelper(const T& element, node* &temp)
	{
		if(findHelper(element, temp) == false)
		{
			if(temp == NULL)
			{
				temp = new node{element, nullptr, nullptr, 0};
			}
			else if(element < temp->data)
			{
				insertHelper(element, temp->leftChild);
			}
			else if(element > temp->data)
			{
				insertHelper(element, temp->rightChild);
			}
			balance(temp);
		}
		else
		{
			throw std::invalid_argument("Error, cannot insert same element twice");
		}
	}

	void removeHelper(const T& element, node* &temp)
	{
		if(temp == nullptr)
		{
			throw std::out_of_range("Out of range error, Tree is empty");
		}
		else
		{
			if(findHelper(element, temp))
			{
				if(element < temp->data)
				{
					removeHelper(element, temp->leftChild);
				}
				else if(element > temp->data)
				{
					removeHelper(element, temp->rightChild);
				}
				else if(temp->leftChild != nullptr && temp->rightChild != nullptr)
				{
					temp->data = findMin(temp->rightChild);
					removeHelper(temp->data, temp->rightChild);
				}
				else
				{
					node *oldNode = temp;
					temp = (temp->leftChild != nullptr) ? temp->leftChild : temp->rightChild;
					delete oldNode;
				}
				balance(temp);
			}
			else
			{
				throw std::invalid_argument("Error, cannot remove non-existing Element");
			}
		}
		
	}

	T findMin(node* minNode)
	{
		if(minNode != nullptr)
		{
			if(minNode->leftChild != nullptr)
			{
				return findMin(minNode->leftChild);
			}
			else
			{
				return minNode->data;
			}
		}
		else
		{
			throw std::out_of_range("Error, No elements");
		}
	}

	T findMax(node* maxNode)
	{
		if(maxNode != nullptr)
		{
			if(maxNode->rightChild != nullptr)
			{
				return findMax(maxNode->rightChild);
			}
			else
			{
				return maxNode->data;
			}
		}
		else
		{
			throw std::out_of_range("Error, No elements");
		}
	}

	int heightHelper(node *temp)
	{
		if (temp == nullptr)
		{
			return -1;
		}
		else
		{
			return static_cast<size_t> (temp->height);
		}
	}

	size_t getTreeHeightHelper(node *temp)
	{
		int emptyHeight = -1;
		if(temp == nullptr)
		{
			return static_cast<size_t>(emptyHeight);
		}
		else
		{
			return static_cast<size_t>(temp->height);
		}
	}

	bool findHelper(const T& element, node* &temp)
	{
		bool elementFound;
		if(temp == nullptr)
		{
			elementFound = false;
		}
		else if(element == temp->data)
		{
			elementFound = true;
		}
		else if(element < temp->data)
		{
			return findHelper(element, temp->leftChild);
		}
		else if(element > temp->data)
		{
			return findHelper(element, temp->rightChild);
		}
		return elementFound;
	}

	std::vector<T> preOrderHelper(node *temp, std::vector<T>& preVector)
	{
		if(temp != nullptr)
		{
			preVector.push_back(temp->data);
			preOrderHelper(temp->leftChild, preVector);
			preOrderHelper(temp->rightChild, preVector);
			return preVector;
		}
		else
		{
			return preVector;
		}
	}

	bool nodeExists(node *temp)
	{
		if(temp != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::vector<T> inOrderHelper(node *temp, std::vector<T>& inVector)
	{
		if(temp != NULL)
		{
			inOrderHelper(temp->leftChild, inVector);
			inVector.push_back(temp->data);
			inOrderHelper(temp->rightChild, inVector);
			return inVector;
		}
		else
		{
			return inVector;
		}
	}

	std::vector<T> postOrderHelper(node *temp, std::vector<T>& internalVector)
	{
		if(temp != nullptr)
		{
			postOrderHelper(temp->leftChild, internalVector);
			postOrderHelper(temp->rightChild, internalVector);
			internalVector.push_back(temp->data);
			return internalVector;
		}
		else
		{
			return internalVector;
		}
	}

public:

	AVLTree<T>()
	{
		root = nullptr;
	}

	~AVLTree<T>()
	{
		root = nullptr;
	}

	void insert(const T& element)
	{
		insertHelper(element, root);
	}

	void remove(const T& element)
	{
		removeHelper(element, root);
	}

	bool find(const T& element)
	{
		return findHelper(element, root);
	}

	std::vector<T> preOrderWalk()
	{
		std::vector<T> preVector;
		return preOrderHelper(root, preVector);
	}
	
	std::vector<T> inOrderWalk()
	{
		std::vector<T> inVector;
		return inOrderHelper(root, inVector);
	}
	
	std::vector<T> postOrderWalk()
	{
		std::vector<T> postVector;
		return postOrderHelper(root, postVector);
	}

	size_t getTreeHeight()
	{
		return getTreeHeightHelper(root);
	}

	T getMin()
	{
		return findMin(root);
	}

	T getMax()
	{
		return findMax(root);
	}
};
#endif