#pragma once
#include <windows.h>
#include <iostream>
#include "const.h"
using namespace std;

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
	Node<T>* m_node;		//ͷ�ڵ�
	DWORD m_dwSize;		//��Ч�ڵ����

public:
	Link();
	Link(T& t);					//��t��ӵ��ڵ�������
	Link(const Link& link);		//��������
	~Link();					//����

public:
	BOOL empty();				//�ж�������Ч�ڵ��Ƿ�Ϊ��
	void clear();				//������нڵ�
	T* getElement(DWORD index);	//ͨ��������ȡԪ��
	DWORD getElementIndex(T& t);//ͨ��Ԫ�ػ�ȡ����
	DWORD insert(T& t);			//������ͷ������Ԫ��
	DWORD insert(DWORD index, T& t);	//��ָ������λ�ò���Ԫ��
	DWORD erase(DWORD index);			//ɾ��ָ������λ�õ�Ԫ��
	DWORD size();						//��ȡ��ЧԪ�ظ���
	ostream& show();					//��ӡ�����е�Ԫ��

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
	while (tempNode != link.m_node)				//����link��ȸ���link��ȫ���ڵ�
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
	if (m_dwSize)
	{
		Node<T>* tempNode;
		do
		{
			tempNode = m_node->prevAddr;
			delete tempNode;
			if (*(DWORD*)m_node->nextAddr == 0xdddddddd) {
				delete m_node;
				break;
			}
			else {
				m_node = m_node->nextAddr;
			}
		} while (tempNode);
		m_dwSize = 0;
	}
}

template<class T>
inline T* Link<T>::getElement(DWORD index)
{
	if (index >= m_dwSize)	//�ж�������Χ
	{
		return NULL;
	}

	Node<T>* tempNode = m_node;
	DWORD i = 0;
	while (i < index)	//����index��,ȡ��index���ڵ�
	{
		tempNode = tempNode->nextAddr;
		i++;
	}
	return &tempNode->element;
}

template<class T>
inline DWORD Link<T>::getElementIndex(T& t)
{
	Node<T>* tempNode = m_node->nextAddr;
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
	return insert(m_dwSize,t);
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
	else if (index == 0 )
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
	else if(index == 1 && m_dwSize == 1) {
		node->prevAddr = m_node;
		node->nextAddr = m_node;
		m_node->prevAddr = node;
		m_node->nextAddr = node;
	}
	else {
		while (i < index)
		{
			tempNode = tempNode->nextAddr;
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
	if (index >= m_dwSize)		//�ж�������Χ
	{
		return INDEX_ERROR;
	}

	Node<T>* tempNode = m_node;
	DWORD i = 0;
	while (i < index)		//��ȡָ������λ�õĽڵ�
	{
		tempNode = tempNode->nextAddr;
		i++;
	}
	tempNode->prevAddr->nextAddr = tempNode->nextAddr;		//����ָ������λ�õĽڵ�����½ڵ��ָ��
	tempNode->nextAddr->prevAddr = tempNode->prevAddr;

	if (index == 0)		//�ж�ɾ�����Ƿ���ͷ�ڵ�
	{
		m_node = m_node->nextAddr;	
	}
	delete tempNode;	//�ͷ�ָ���ڵ�
	m_dwSize--;			//�ڵ������һ
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
	if (m_dwSize == 0)
	{
		return cout;
	}
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

