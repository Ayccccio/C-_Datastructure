#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

#define SUCCESS 1
#define ERROR -1
#define MALLOC_ERROR -2
#define INDEX_ERROR -3

template <class E>
class Vector
{
private:
	E* m_data;			//数据存放位置
	DWORD m_dwLen;		//数据总长度
	DWORD m_dwIndex;	//下一个可用索引
private:
	BOOL expand();		//扩充数据区大小
	

public:
	Vector<E>();				//默认构造,数据区长度20
	Vector<E>(DWORD dwSize);	//有参构造,指定数据区长度
	~Vector<E>();				//析构函数
public:
	E* at(DWORD dwIndex);				//根据指定索引获取元素
	DWORD push_back(E& element);		//在数据区最后有效元素后面添加指定元素
	E& pop_back();						//删除最后一个元素
	DWORD insert(DWORD dwIndex, E& element);		//在指定索引位置插入元素
	DWORD capacity();			//获取在不增容下还能增加多少个元素
	VOID clear();				//清除所有元素
	BOOL empty();				//判断数据取是否为空
	DWORD erase(DWORD dwIndex);	//删除指定位置元素
	DWORD size();				//返回数据区元素数量
	ostream& show();				//打印数据区中元素

	E& operator[](DWORD index);
};



template <class E>
E& Vector<E>::operator[](DWORD index)
{
	return this->m_data[index];
}



template<class E>
BOOL Vector<E>::expand()
{
	E* tempData;
	DWORD newLen = m_dwLen * 1.2;	//扩展大小

	if (m_dwIndex == m_dwLen - 1)
	{
		tempData = new E[newLen];	//申请新的数据存储区域
		memcpy(tempData, m_data, sizeof E * m_dwIndex);	//拷贝旧数据区域数据到新区域

		m_dwLen = newLen;
		delete m_data;
		return SUCCESS;
	}
	return ERROR;
}

template<class E>
Vector<E>::Vector()
{
	this->m_dwLen = 20;
	this->m_dwIndex = 0;
	this->m_data = new E[this->m_dwLen];
}

template<class E>
Vector<E>::Vector(DWORD dwSize)
{
	this->m_dwLen = dwSize;
	this->m_dwIndex = 0;
	this->m_data = new E[this->m_dwLen];
}

template<class E>
Vector<E>::~Vector()
{
	if (m_data)
	{
		delete[] m_data;
		m_data = NULL;
	}
}

template<class E>
E* Vector<E>::at(DWORD dwIndex)
{
	if (dwIndex >= this->m_dwIndex)
	{
		return NULL;
	}
	return &this->m_data[dwIndex];
}

template<class E>
DWORD Vector<E>::push_back(E& element)
{
	expand();
	this->m_data[this->m_dwIndex] = element;
	this->m_dwIndex++;
	return SUCCESS;
}

template<class E>
E& Vector<E>::pop_back()
{
	this->m_dwIndex--;
	return m_data[m_dwIndex + 1];
}

template<class E>
DWORD Vector<E>::insert(DWORD dwIndex, E& element)
{
	expand();
	DWORD i = m_dwIndex - 1;
	if (dwIndex > m_dwIndex)
	{
		return INDEX_ERROR;
	}
	else if (dwIndex == m_dwIndex) {
		m_data[m_dwIndex] = element;
	}
	else {
		while (i >= dwIndex)	//将数据区域中dwIndex开始的数据全部向后移动一位
		{
			this->m_data[i + 1] = this->m_data[i];
			i--;
		}
		m_data[dwIndex] = element;
	}
	m_dwIndex++;
	return SUCCESS;
}

template<class E>
DWORD Vector<E>::capacity()
{
	return m_dwLen - m_dwIndex;
}

template<class E>
VOID Vector<E>::clear()
{
	m_dwIndex = 0;
}

template<class E>
BOOL Vector<E>::empty()
{
	return m_dwIndex == 0;
}

template<class E>
DWORD Vector<E>::erase(DWORD dwIndex)
{
	if (dwIndex >= m_dwIndex)
	{
		return INDEX_ERROR;
	}
	while (dwIndex < m_dwIndex)
	{
		m_data[dwIndex] = m_data[dwIndex + 1];
		dwIndex++;
	}
	m_dwIndex--;
	return SUCCESS;
}

template<class E>
DWORD Vector<E>::size()
{
	return m_dwIndex - 1;
}

template<class E>
ostream& Vector<E>::show()
{
	DWORD i = 0;
	DWORD index = m_dwIndex - 1;
	cout << "{";
	while (i < m_dwIndex)
	{
		cout << m_data[i];
		if (i != index)
		{
			cout << ",";
		}
		i++;
	}
	cout << "}";
	return cout;
}

