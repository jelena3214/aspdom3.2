#ifndef _hashtable_h_
#define _hashtable_h_

#include <iostream>
#include <vector>
#include "adressfunction.h"
#include "student.h"
#include<cmath>
#include "quadratichashing.h"

using namespace std;

//VIRTUALNI DESTRUKTOR, KOPIRAJUCI PREMESTAJUCI??
//CUVATI STUDENTE U TABELI ILI ODVOJITI KLJUC I INFO?
//Testiraj sve

class HashTable {
	AdressFunction *collisionFunction;
	int baket;
	int p; //p bita kljuca
	int depth;  

	struct Elem {
		Student *st;
		long key;
		Elem(long k, Student* s = nullptr) :st(s), key(k){};
	};

	vector <vector<Elem*>> table;

	int getAdr(long index) {
		return index % int(pow(2, p)); //sta ovde raditi oko zaokruzivanja?
	}
	int keysInPlace(int i);

public:
	HashTable(int bak, int pp, AdressFunction* addressFunction, int b) : baket(bak), p(pp), collisionFunction(addressFunction), depth(b) {
		int size = depth * pow(2, depth);
		for (int i = 0; i < size; i++) {
			vector<Elem*> vec;
			for (int j = 0; j < baket; j++) {
				Elem* newElem = new Elem{ 0 };
				vec.push_back(newElem);
			}
			table.push_back(vec);
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
