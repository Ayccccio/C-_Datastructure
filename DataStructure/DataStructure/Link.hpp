#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

#define SUCCESS 1
#define ERROR -1
#define MALLOC_ERROR -2
#define INDEX_ERROR -3

template <class T>
struct Node {
	Node* prevAddr;
	T element;
	Node* nextAddr;
	Node();
	Node(T& t);
	Node(const Node<T>& node);
};

template<class T>
inline Node<T>::Node()
{
	memset(this, 0, sizeof Node<T>);
}

template<class T>
inline Node<T>::Node(T& t)
{
	memset(this, 0, sizeof Node<T>);
	element = t;
}

template<class T>
inline Node<T>::Node(const  Node<T>& node)
{
	element = node.element;
	prevAddr = node.prevAddr;
	nextAddr = node.nextAddr;
}



template <class T>
class Link {
private:
	Node<T>* m_node;		//头节点
	DWORD m_dwSize;		//有效节点个数

public:
	Link();
	Link(T& t);					//将t添加到节点数据区
	Link(const Link& link);		//拷贝构造
	~Link();					//析构

public:
	BOOL empty();				//判断链表有效节点是否为空
	void clear();				//清除所有节点
	T& getElement(DWORD index);	//通过索引获取元素
	DWORD getElementIndex(T& t);//通过元素获取索引
	DWORD insert(T& t);			//在链表头部插入元素
	DWORD insert(DWORD index, T& t);	//在指定索引位置插入元素
	DWORD erase(DWORD index);			//删除指定索引位置的元素
	DWORD size();						//获取有效元素个数
	ostream& show();					//打印链表中的元素

};

template<class T>
inline Link<T>::Link()
{
	m_node = NULL;
	m_dwSize = 0;
}

template<class T>
inline Link<T>::Link(T& t)
{
	m_node = new Node<T>();
	m_node.element = t;
	m_dwSize = 1;
}

template<class T>
inline Link<T>::Link(const Link& link)
{
	Node* tempNode = link.m_node.nextAddr;		
	while (tempNode != link.m_node)				//遍历link深度复制link的全部节点
	{
		m_node = new Node<T>();
		memcpy(m_node, link.m_node, sizeof Node<T>);
		tempNode = tempNode->nextAddr;
	}
	m_dwSize = link.m_dwSize;
}

template<class T>
inline Link<T>::~Link()
{
	clear();
}

template<class T>
inline BOOL Link<T>::empty()
{
	return m_dwSize;
}

template<class T>
inline void Link<T>::clear()
{
	Node<T>* tempNode = m_node->nextAddr;
	while (tempNode != m_node)				//循环遍历节点
	{
		tempNode = tempNode->nextAddr;		//先指向下一个
		delete tempNode->prevAddr;			//在释放上一个
	}
	delete m_node;			//释放头节点
}

template<class T>
inline T& Link<T>::getElement(DWORD index)
{
	if (index >= m_dwSize)	//判断索引范围
	{
		return NULL;
	}

	Node* tempNode = m_node;
	DWORD i = 0;
	while (i < index)	//遍历index次,取第index个节点
	{
		tempNode = tempNode->nextAddr;
		i++;
	}
	return tempNode->element;
}

template<class T>
inline DWORD Link<T>::getElementIndex(T& t)
{
	Node* tempNode = m_node.nextAddr;
	DWORD i = 0;
	while(tempNode != m_node)
	{
		if (tempNode->element == t)
		{
			return i;
		}
		tempNode = tempNode->nextAddr;
		i++;
	}
	return ERROR;
}

template<class T>
inline DWORD Link<T>::insert(T& t)
{
	return insert(0,t);
}

template<class T>
inline DWORD Link<T>::insert(DWORD index, T& t)
{
	Node<T>* node = new Node<T>(t);
	Node<T>* tempNode = m_node;
	DWORD i = 0;
	if (index > m_dwSize)
	{
		return INDEX_ERROR;
	}
	if (index = 0 )
	{
		if (m_dwSize == 1) {
			node->prevAddr = m_node;
			node->nextAddr = m_node;
			m_node->prevAddr = node;
			m_node->nextAddr = node;
		}
		else if(m_dwSize > 1){
			node->prevAddr = m_node->prevAddr;
			node->nextAddr = m_node;
			m_node->prevAddr->nextAddr = node;
			m_node->prevAddr = node;
		}
		m_node = node;
	}
	if else(index == 1 && m_dwSize == 1) {
		node->prevAddr = m_node;
		node->nextAddr = m_node;
		m_node->prevAddr = node;
		m_node->nextAddr = node;
	}
	else {
		while (i < index)
		{
			tempNode = tempNode.nextAddr;
			i++;
		}
		node->prevAddr = tempNode->prevAddr;
		node->nextAddr = tempNode;
		tempNode->prevAddr->nextAddr = node;
		tempNode->prevAddr = node;
	}
	m_dwSize++;
	return SUCCESS;
}

template<class T>
inline DWORD Link<T>::erase(DWORD index)
{
	if (index >= m_dwSize)
	{
		return INDEX_ERROR;
	}

	Node<T>* tempNode = m_node;
	DWORD i = 0;
	while (i < index)
	{
		tempNode = tempNode->nextAddr;
	}
	tempNode->prevAddr->nextAddr = tempNode->nextAddr;
	tempNode->nextAddr->prevAddr = tempNode->prevAddr;
	delete tempNode;
	return SUCCESS;
}

template<class T>
inline DWORD Link<T>::size()
{
	return m_dwSize;
}

template<class T>
inline ostream& Link<T>::show()
{
	Node<T>* tempNode = m_node->nextAddr;
	cout << "{";
	cout << (*m_node).element;
	while (tempNode != m_node && tempNode)
	{
		cout << ",";
		cout << tempNode->element;
		tempNode = tempNode->nextAddr;
	}
	cout << "}";
	return cout;
}

