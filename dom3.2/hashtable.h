#ifndef _hashtable_h_
#define _hashtable_h_

#include <iostream>
#include <vector>
#include "adressfunction.h"
#include "student.h"
#include<cmath>

using namespace std;

//Testiraj sve

class HashTable {
	int baket;
	int p; //p bita kljuca
	int depth; 
	int startd;

	struct Elem {
		Student *st;
		long key;
		
		Elem(long k, Student * s = nullptr) :st(s), key(k){};
	};

	struct Baket {
		vector<Elem*> elems;
		int depthBaket;
		int baketLen;
		int pointers;
	};

	vector <Baket*> table;

	int getAdr(long index) {
		return index % int(pow(2, depth)); //sta ovde raditi oko zaokruzivanja?
	}
	int keysInPlace(int i);
	void setB(int i) {
		if (i)depth++;
		else depth--;
	}
	bool emptyBaket(int addr) {
		for (int i = 0; i < baket; i++) {
			if (table[addr]->elems[i]->key != -1)return false;
		}
		return true;
	}

	int findMaxDepth() {
		int size = pow(2, depth);
		int max = 0;
		for (int i = 0; i < size; i++) {
			if (max < table[i]->depthBaket)max = table[i]->depthBaket;
		}
		return max;
	}


public:
	HashTable(int bak, int pp, int b) : baket(bak), p(pp), depth(b), startd(b) {
		int size = pow(2, depth);
		for (int i = 0; i < size; i++) {
			Baket* b = new Baket;
			b->depthBaket = depth;
			b->baketLen = 0;
			b->pointers = 0;
			for (int j = 0; j < baket; j++) {
				Elem* newElem = new Elem{ -1 };
				b->elems.push_back(newElem);
			}
			table.push_back(b);
		}
	};
	~HashTable();
	Student* findKey(long index);
	bool insertKey(Student& st);
	bool deleteKey(long index);
	void clear();
	int keyCount();
	int tableSize();
	friend ostream& operator<<(ostream& os, const HashTable& ht);
	double fillRatio();
};
#endif // !_hashtable_h_
