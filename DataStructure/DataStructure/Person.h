#pragma once
#include <iostream>
using namespace std;

class Person
{
public:
	int id;
	int age;
	bool sex;
public:
	Person() {
		age = 18;
		sex = 0;
		id = 1;
	}
	Person(const Person& p) {
		id = p.id + 1;
		age = p.age;
		sex = p.sex;
	}
	BOOL operator==(Person& p) {
		if (id == p.id && age == p.age && sex == p.sex)
		{
			return TRUE;
		}
		return FALSE;
	}
};

ostream& operator<<(ostream& cout, Person& p) {
	cout << "[Person:id=" << p.id << ",sex=" << p.sex << ",age=" << p.age << "]";
	return cout;
}

