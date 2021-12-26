#include "hashtable.h"
//ENUM
Student* HashTable::findKey(long index)
{

}

bool HashTable::insertKey(Student& st)
{
	
}

bool HashTable::deleteKey(long index)
{
	
}

void HashTable::clear()
{
	int size = depth * pow(2, depth);
	for (int i = 0; i < size; i++) { //sve ih stavlja na empty
		for (int j = 0; j < baket; j++) {
			table[i][j]->key = 0;
			table[i][j]->st = nullptr;
		}
	}
}

int HashTable::keyCount()
{
	int keys = 0;
	int size = depth * pow(2, depth);
	for (int i = 0; i < size; i++) {
		keys += keysInPlace(i);
	}
	return keys;
}

int HashTable::tableSize()
{
	int size = depth * pow(2, depth);
	return size*baket;
}

ostream& operator<<(ostream& os, const HashTable& ht)
{
	int size = ht.depth * pow(2, ht.depth);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < ht.baket; j++) {
			if (ht.table[i][j]->key == -1) os << "DELETED" << "  ";
			else if (ht.table[i][j]->key == 0) os << "EMPTY" << "  ";
			else os << ht.table[i][j]->key << "  ";
		}
		os << endl;
	}
	return os;
}

double HashTable::fillRatio()
{
	int size = depth * pow(2, depth);
	return size / keyCount();
}

int HashTable::keysInPlace(int i)
{
	int num = 0;
	for (int s = 0; s < baket; s++) {
		if ((table[i][s]->key != -1) && (table[i][s]->key != 0))num++;
	}
	return num;
}

HashTable::~HashTable()
{
	int size = depth * pow(2, depth);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < baket; j++) {
			delete(table[i][j]);
		}
	}
}