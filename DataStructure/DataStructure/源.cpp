#pragma once
#include "vector.hpp"
#include "Link.hpp"
#include "Person.h"

Person p;
Person p1(p);
Person p2(p1);
Person p3(p2);

void vectorTest() {
	Vector<Person>* v = new Vector<Person>[10];

	v->push_back(p);
	v->push_back(p1);
	v->push_back(p2);
	v->push_back(p3);
	v->show() << endl;
	v->pop_back();
	cout << "µÚ0¸öÔªËØ:" << *v->at(0) << endl;
	v->show() << endl;
	cout << v->insert(5, p) << endl;
	v->show() << endl;
	cout << v->capacity() << endl;
	cout << v->empty() << endl;
	cout << v->erase(0) << endl;
	v->show() << endl;
	v->clear();
	v->show() << endl;

	delete[] v;
}

void linkTest() {
	Link<Person>* link = new Link<Person>;
	link->insert(p);
	link->insert(p1);
	link->insert(p2);
	link->insert(p3);
	link->show() << endl;

	link->erase(0);
	link->erase(5);
	link->show() << endl;

	cout << link->empty() << endl;

	cout << *link->getElement(0) << endl;
	cout << *link->getElement(1) << endl;
	cout << *link->getElement(2) << endl;
	cout << link->getElement(3) << endl;

	cout << link->getElementIndex(p2) << endl;

	cout << link->size() << endl;

	link->clear();
	link->show() << endl;

	delete link;
}
int main() {
	
	linkTest();
}