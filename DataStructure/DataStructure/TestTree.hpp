#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

class Monster
{
public:
	int ID;
	int Level;
	char Name[20];
public:
	Monster() {}
	Monster(int ID, int Level, char* Name)
	{
		this->ID = ID;
		this->Level = Level;
		memcpy(&this->Name, Name, strlen(Name) + 1);
	}
};

ostream& operator<<(ostream& cout, Monster& m) {
 	return cout << "[Monster:ID=" << m.ID << ",Level=" << m.Level << ",Name=" << m.Name;
}


template<class T>
class TreeNode {
public:
	T element;					//��ǰ�ڵ�洢������			
	TreeNode<T>* pLeft;					//ָ�����ӽڵ��ָ��			
	TreeNode<T>* pRight;					//ָ�����ӽڵ��ָ��			

	TreeNode(T& ele) {
		//��ʼ��Node�ڵ�							
		memset(&element, 0, sizeof(TreeNode));
		//ΪԪ�ظ�ֵ							
		memcpy(&element, &ele, sizeof(T));
		pLeft = pRight = NULL;
	}
};

template<class T>
class BSortTree {
public:
	BSortTree();					//���캯��			
	~BSortTree();					//��������			
public:
	void InOrderTraverse(TreeNode<T>* pNode);					//�������			
	void PreOrderTraverse(TreeNode<T>* pNode);					//ǰ�����			
	void PostOrderTraverse(TreeNode<T>* pNode);					//�������			
	TreeNode<T>* GetRoot();					//���ظ��ڵ�			
	int GetDepth(TreeNode<T>* pNode);					//����ĳ���ڵ�ĸ߶�/���			
private:
	void Init();
	void clear(TreeNode<T>* pNode);
private:
	TreeNode<T>* m_pRoot;					//�����ָ��			
	int size;					//����Ԫ���ܸ���			
};

template<class T>
BSortTree<T>::BSortTree()
{
	Init();
}
template<class T>
BSortTree<T>::~BSortTree() {

	//�ͷ����нڵ�ռ�								
	clear(m_pRoot);			//���ú��������ͷŽڵ��ڴ�
	size = 0;
}

template<class T>
void BSortTree<T>::Init()
{

	Monster m1(1, 1, (char*)"���");
	Monster m2(2, 2, (char*)"Ұ��");
	Monster m3(3, 3, (char*)"Ұ��");
	Monster m4(4, 4, (char*)"ʿ��");
	Monster m5(5, 5, (char*)"����");
	Monster m6(6, 6, (char*)"������");
	Monster m7(7, 7, (char*)"�������");
	Monster m8(8, 8, (char*)"���ֺú�");


	TreeNode<Monster>* n1 = new TreeNode<Monster>(m1);
	TreeNode<Monster>* n2 = new TreeNode<Monster>(m2);
	TreeNode<Monster>* n3 = new TreeNode<Monster>(m3);
	TreeNode<Monster>* n4 = new TreeNode<Monster>(m4);
	TreeNode<Monster>* n5 = new TreeNode<Monster>(m5);
	TreeNode<Monster>* n6 = new TreeNode<Monster>(m6);
	TreeNode<Monster>* n7 = new TreeNode<Monster>(m7);
	TreeNode<Monster>* n8 = new TreeNode<Monster>(m8);

	m_pRoot = n5;
	n5->pLeft = n4;
	n5->pRight = n6;
	n4->pLeft = n1;
	n1->pRight = n2;
	n1->pLeft = n8;
	n6->pLeft = n3;
	n3->pRight = n7;
	size = 8;
	/*
					5

				4		6

			1		 3

		8		 2		 7

	*/
}
template<class T>
inline void BSortTree<T>::clear(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return;
	}
	if (pNode->pLeft)
	{
		clear(pNode->pLeft);
	}
	if (pNode->pRight)
	{
		clear(pNode->pRight);
	}
	delete pNode;
}
template<class T>
TreeNode<T>* BSortTree<T>::GetRoot()
{
	return m_pRoot;
}
template<class T>
int BSortTree<T>::GetDepth(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return 0;
	}
	else
	{
		int m = GetDepth(pNode->pLeft);
		int n = GetDepth(pNode->pRight);
		return (m > n) ? (m + 1) : (n + 1);
	}
}
template<class T>
void BSortTree<T>::InOrderTraverse(TreeNode<T>* pNode)
{

	//����������й���,�г��ֵ�����								
	if (pNode == NULL)
	{
		return;
	}
	InOrderTraverse(pNode->pLeft);
	cout << pNode->element << endl;
	InOrderTraverse(pNode->pRight);
}

template<class T>
void BSortTree<T>::PreOrderTraverse(TreeNode<T>* pNode)
{

	//ǰ��������й���,�г��ֵ�����								
	if (pNode == NULL)
	{
		return;
	}
	cout << pNode->element << endl;
	PreOrderTraverse(pNode->pLeft);
	PreOrderTraverse(pNode->pRight);
}

template<class T>
void BSortTree<T>::PostOrderTraverse(TreeNode<T>* pNode)
{

	//����������й���,�г��ֵ�����				
	if (pNode == NULL)
	{
		return;
	}

	if (pNode->pLeft)
	{
		PostOrderTraverse(pNode->pLeft);
	}
	if (pNode->pRight) {
		PostOrderTraverse(pNode->pRight);
	}
	cout << pNode->element << endl;
}
