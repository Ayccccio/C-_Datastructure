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
	E* m_data;			//���ݴ��λ��
	DWORD m_dwLen;		//�����ܳ���
	DWORD m_dwIndex;	//��һ����������
private:
	BOOL expand();		//������������С
	

public:
	Vector<E>();				//Ĭ�Ϲ���,����������20
	Vector<E>(DWORD dwSize);	//�вι���,ָ������������
	~Vector<E>();				//��������
public:
	E* at(DWORD dwIndex);				//����ָ��������ȡԪ��
	DWORD push_back(E& element);		//�������������ЧԪ�غ������ָ��Ԫ��
	E& pop_back();						//ɾ�����һ��Ԫ��
	DWORD insert(DWORD dwIndex, E& element);		//��ָ������λ�ò���Ԫ��
	DWORD capacity();			//��ȡ�ڲ������»������Ӷ��ٸ�Ԫ��
	VOID clear();				//�������Ԫ��
	BOOL empty();				//�ж�����ȡ�Ƿ�Ϊ��
	DWORD erase(DWORD dwIndex);	//ɾ��ָ��λ��Ԫ��
	DWORD size();				//����������Ԫ������
	ostream& show();				//��ӡ��������Ԫ��

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
	DWORD newLen = m_dwLen * 1.2;	//��չ��С

	if (m_dwIndex == m_dwLen - 1)
	{
		tempData = new E[newLen];	//�����µ����ݴ洢����
		memcpy(tempData, m_data, sizeof E * m_dwIndex);	//�����������������ݵ�������

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
		while (i >= dwIndex)	//������������dwIndex��ʼ������ȫ������ƶ�һλ
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

