#pragma once
#include "vector.hpp"

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

Person p;
Person p1(p);
Person p2(p1);
Person p3(p2);
int main() {
	
	
}