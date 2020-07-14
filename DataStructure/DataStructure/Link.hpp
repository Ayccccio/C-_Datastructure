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
	Node m_node;		//头节点
	DWORD m_dwSize;		//有效节点个数

private:
	getNodeByIndex(DWORD index);	//通过索引获取节点

public:
	Link();
	Link(T& t);					//将t放到节点数据区
	Link(const Link& link);		//拷贝构造
	~Link();					//析构

public:
	BOOL empty();				//判断链表有效节点是否为空
	void clear();				//清除所有节点
	getElement(DWORD index);	//通过索引获取元素
	getElementIndex(T& t);		//通过元素获取索引
	DWORD insert(T& t);			//在链表头部插入元素
	DWORD insert(DWORD index, T& t);	//在指定索引位置插入元素
	DWORD delete(DWORD index);			//删除指定索引位置的元素
	DWORD size();						//获取有效元素个数

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
