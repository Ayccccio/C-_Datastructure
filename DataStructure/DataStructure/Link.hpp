#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

template <class T>
struct Node {
	Node* prevAddr;
	T element;
	Node* nextAddr;
};

template <class T>
class Link {
private:
	Node m_node;		//ͷ�ڵ�
	DWORD m_dwSize;		//��Ч�ڵ����

private:
	getNodeByIndex(DWORD index);	//ͨ��������ȡ�ڵ�

public:
	Link();
	Link(T& t);					//��t�ŵ��ڵ�������
	Link(const Link& link);		//��������
	~Link();					//����

public:
	BOOL empty();				//�ж�������Ч�ڵ��Ƿ�Ϊ��
	void clear();				//������нڵ�
	getElement(DWORD index);	//ͨ��������ȡԪ��
	getElementIndex(T& t);		//ͨ��Ԫ�ػ�ȡ����
	DWORD insert(T& t);			//������ͷ������Ԫ��
	DWORD insert(DWORD index, T& t);	//��ָ������λ�ò���Ԫ��
	DWORD delete(DWORD index);			//ɾ��ָ������λ�õ�Ԫ��
	DWORD size();						//��ȡ��ЧԪ�ظ���

};

template<class T>
inline Link<T>::Link()
{
	memset(&m_node, 0, sizeof Node);
	m_dwSize = 0;
}

template<class T>
inline Link<T>::Link(T& t)
{
	m_node.prevAddr = NULL;
	m_node.element = t;
	m_node.nextAddr = NULL;
	m_dwSize = 1;
}

template<class T>
inline Link<T>::Link(const Link& link)
{

}
