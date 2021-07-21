#pragma once
#include <iostream>

using namespace std;

struct Link
{
	pair<int, int> val;
	Link* next;
	Link(int ival = 0, int jval = 0, Link * _next = nullptr):val(make_pair(ival, jval)), next(_next) {}
	void setNext(Link* _next) { next = _next; }
	void delNext() { next = nullptr; }
};

class List {
	Link* first;
	int N;
public:
	List() {
		N = 0; 
		first = nullptr;
	}

	int getN() { return N; }

	pair<int, int> getPair(int pos) {
		Link *p = first;
		for (int i = 0; i < pos - 1; i++)
			p = p->next;
		return p->val;
	}

	List(const List& p) {
		N = p.N;
		first = nullptr;
		if (p.first == nullptr) return;
		first = new Link(p.first->val.first, p.first->val.second);
		Link* t1, * t2;
		t1 = p.first->next;
		t2 = first;
		while (t1 != nullptr) {
			t2->next = new Link(t1->val.first, t1->val.second);
			t2 = t2->next;
			t1 = t1->next;
		}
	}

	void clean() {
		while (first != nullptr) {
			delFirst();
		}
	}

	~List() {
		clean();
	}

	void addFirst(pair<int, int> val) {
		Link* p_new;
		p_new = new Link(val.first, val.second, first);
		first = p_new;
		N++;
	}

	void delFirst() {
		if (first == nullptr) throw - 1;
		Link* p;
		p = first;
		first = first->next;
		delete p;
		N--;
	}

	void addLast(pair<int, int> val) {
		if (first == nullptr) addFirst(val);
		else {
			Link* p_new = new Link(val.first, val.second);
			Link* t = first;
			while (t->next != nullptr)
				t = t->next;
			t->setNext(p_new);
			N++;
		}
	}

	void del(int pos) {
		if (pos == 1) {
			delFirst();
			return;
		}
		Link* p = first, * p1;
		for (int i = 1; i < pos - 1; i++) {
			p = p->next;
		}
		p1 = p->next;
		p->next = p1->next;
		delete p1;
		N--;
	}
};