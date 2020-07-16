#pragma once
#include "const.h"

template <class T>
class TreeNode {
	T m_t;
	TreeNode* m_pLeftNode;
	TreeNode* m_pRightNode;
};

template <class T>
class Tree {
private:
	TreeNode<T>* m_node;
	DWORD m_size;

public:
	Tree();
	Tree(T& t);
	Tree(const Tree& tree);
	~Tree();
};

template<class T>
inline Tree<T>::Tree()
{
	m_node = new TreeNode<T>;
	memset(m_node, 0, sizeof TreeNode);
	m_size = 0;
}

template<class T>
inline Tree<T>::Tree(T& t)
{
	m_node = new TreeNode<T>;
	memcpy(m_node, &t, sizeof TreeNode);
	m_node.m_pLeftNode = NULL;
	m_node.m_pRightNode = NULL;
	m_size = 1;
}

template<class T>
inline Tree<T>::~Tree()
{
	TreeNode* node = m_node;
	while (node->m_t)
	{
		delete node;
	}

}
