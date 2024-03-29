#include "hashtable.h"
#include <algorithm>
//ENUM

//OVDE SVE UZIMAM P POSLEDNJIH BITOVA
bool HashTable::insertKey(Student& st)
{
	int size = pow(2, depth);
	int position = 0, addr, secondAdr = 0;
	long index = st.indeks;
	if (depth == p)return false; //p je max bitova kojih mozemo uzeti za hesiranje
	
	addr = getAdr(index);
	int n = 1;
	for (int i = 0; i < baket; i++) {
		if (table[addr]->elems.size() == 0) {
			Elem* newElem = new Elem{ index, &st };
			table[addr]->elems.push_back(newElem);
			table[addr]->baketLen = 1;
			table[addr]->pointers = 1;
			return true;
		}
		if (table[addr]->elems[i]->key == index) { //vec postojki kljuc
			cout << "Nije moguce ubacivanje, student vec postoji\n";
			return false;
		}
		else if (table[addr]->elems[i]->key == -1) { //prazno mesto
			if (emptyBaket(addr)) {
				table[addr]->pointers++;
			}
			table[addr]->elems[i]->st = &st;
			table[addr]->elems[i]->key = index;
			table[addr]->baketLen++;
			
			return true;
		}
	}
	

	//kada je baket pun prvo rehesiramo
	setB(1); //povecavamo broj bitova koje gledamo
	Baket* newBaket = new Baket;
	Elem* newElem = new Elem{ index, &st };

	vector<Elem*>allElems;
	for (int i = 0; i < baket; i++) {
		allElems.push_back(table[addr]->elems[i]);
	}
	allElems.push_back(newElem);

	
	Baket* temp = new Baket;
	for (int i = 0; i < table[addr]->elems.size(); i++) {
		temp->elems.push_back(table[addr]->elems[i]);
		temp->elems[i]->key = table[addr]->elems[i]->st->indeks;
		temp->elems[i]->st = table[addr]->elems[i]->st;
	}
	temp->baketLen = table[addr]->baketLen;
	temp->depthBaket = table[addr]->depthBaket;
	temp->pointers = table[addr]->pointers;

	int oldDepth = depth;
	while (true) {
		table[addr]->elems.clear();
		table[addr]->baketLen = 0;
		table[addr]->pointers = 0;
		table[addr]->depthBaket++;
		newBaket->baketLen = 0;
		newBaket->pointers = 0;
		newBaket->depthBaket = table[addr]->depthBaket;
		//rehasiranje

		int len = allElems.size(), newAddr, bit, oldlen = 0, newlen = 0, shift = table[addr]->depthBaket - 1;
		for (int i = 0; i < len; i++) {
			newAddr = getAdr(allElems[i]->key);
			if (newAddr == 0)bit = 0;
			else {
				bit = (newAddr >> shift) & 1; //izdvanjamo nti bit od kraja ako to treba onda samo newadr>>depth-1 and 1
			}
			if (bit == 0) {
				table[addr]->elems.push_back(allElems[i]);
				table[addr]->elems[oldlen++]->key = allElems[i]->st->indeks;
				table[addr]->baketLen++;
			}
			else {
				newBaket->elems.push_back(allElems[i]);
				newBaket->elems[newlen++]->key = allElems[i]->st->indeks;
				newBaket->baketLen++;
			}
		}

		if (depth > p) {
			cout << "Nije moguce ubacivanje\n";
			table[addr]->elems.clear();
			for (int i = 0; i < temp->elems.size(); i++) {
				table[addr]->elems.push_back(temp->elems[i]);
				table[addr]->elems[i]->key = temp->elems[i]->key;
				table[addr]->elems[i]->st = temp->elems[i]->st;
			}
			table[addr]->baketLen = temp->baketLen;
			table[addr]->depthBaket = temp->depthBaket;
			table[addr]->pointers = temp->pointers;
			depth = oldDepth - 1;
			return false;
		}

		if (newBaket->elems.size() > baket || table[addr]->elems.size() > baket) {//povecamo depth jer uzimamo jos jedan bit
			size = pow(2, depth);
			if (table[addr]->depthBaket > depth)depth = table[addr]->depthBaket;
			n++;

		}
		else {
			break;
		}
	}



	if (table[addr]->depthBaket == depth) {//sirimo

		int help = (n > 1 ? 1 : 0);
		size = pow(2, depth - n + help);
		int newSize = pow(2, depth);
		int k = 0;
		for (int i = size; i < newSize; i++) {
			if (k > table.size() - 1)k = 0;
			table.push_back(table[k++]);
		}
		for (int i = 0; i < size; i++) {
			table[i]->pointers += 1;
		}
		table[addr]->pointers += n - 1;
		
		int diff = newSize - size;
		newBaket->pointers++;
		table[addr + diff] = newBaket;
		return true;

	}
	else {
		setB(0);
		/*size = pow(2, depth);
		int i = -1, flagLow = 0;
		int l = size / 2;
		table[addr]->pointers++;
		if (addr + l < pow(2, depth - n))if (table[addr + l] == table[addr])i = addr + l; //novi kacimo na addr+1
		if (addr - l >= 0 && addr - l < pow(2, depth - n))
		{
			if (table[addr - l] == table[addr])i = addr, flagLow = 1; //novi kacimo na addr
		}
		if (!flagLow && i > 0) {
			table[i] = newBaket;
		}
		else {
			Baket* tmp = table[addr];
			
			//table[i-l] = tmp;
		}*/
		table[addr] = newBaket;
		newBaket->pointers++;
		
		return true;
	}
	
	return false;

}

Student* HashTable::findKey(long index)
{
	int addr = getAdr(index);
	if (addr > pow(2, depth)) {
		return nullptr;
	}
	for (int i = 0; i < baket; i++) {
		if (table[addr]->elems[i]->key == index) {
			return table[addr]->elems[i]->st;
		}
	}
	return nullptr;
}

bool HashTable::deleteKey(long index) {
	if (findKey(index) != nullptr) {
		int addr = getAdr(index);
		for (int i = 0; i < baket; i++) {
			if (table[addr]->elems[i]->key == index) {
				table[addr]->elems.erase(table[addr]->elems.begin() + i);
				break;
			}
		}
		int l = pow(2, startd);
		int size = pow(2, depth);
		
		int pos, flag = 0; //vidi da l treba while?
		while (true) {
			if (addr + l > 0 && addr + l < size) {
				pos = addr + l;
				flag = 1;
			}
			else if (addr - l >= 0) {
				pos = addr - l;
				flag = 1;
			}
			if (table[pos]->depthBaket == table[addr]->depthBaket && pos != addr)break;
			if (table[pos]->elems.size() == 0)break;
			l *= 2;
		}
		if (table[pos]->elems.size() == 0) {
			return true;
		}
		
		if (flag && table[addr]->elems.size() + table[pos]->elems.size() <= baket) {//spajamo
			Baket* b = new Baket;
			b->baketLen = 0;
			for (int i = 0; i < table[addr]->elems.size(); i++) {
				b->elems.push_back(table[addr]->elems[i]);
				b->baketLen++;
			}
			for (int i = 0; i < table[pos]->elems.size(); i++) {
				b->elems.push_back(table[pos]->elems[i]);
				b->baketLen++;
			}
		

			table[addr]->depthBaket--;
			table[pos]->depthBaket--;
			b->pointers = 0;
			b->depthBaket = table[addr]->depthBaket;
			b->pointers += table[addr]->pointers;
			b->pointers += table[pos]->pointers;
			
			int max = findMaxDepth(), i;
			if (depth > max) {
				int size = pow(2, depth);
				setB(0);
				int newSize = pow(2, depth);

				for (int i = newSize; i < size; i++) {
					table.pop_back();
				}
				int i = addr - newSize;
				if (i < 0) i = addr;
				table[i] = b;

				for (int i = 0; i < newSize; i++) {
					table[i]->pointers--;
				}

			}
			else {

				table[addr] = b;
				table[pos] = b;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

void HashTable::clear()
{
	int size = pow(2, depth);
	for (int i = 0; i < size; i++) { //sve ih stavlja na empty
		for (int j = 0; j < baket; j++) {
			table[i]->elems[j]->key = -1;
		}
	}
}

int HashTable::keyCount()
{
	int keys = 0;
	int size = pow(2, depth);
	vector<int>vec;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < table[i]->elems.size(); j++) {
			if(table[i]->elems[j]->key != -1)vec.push_back(table[i]->elems[j]->key);
		}
	}

	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());

	return vec.size();
}

int HashTable::tableSize()
{
	int size = pow(2, depth);
	return size*baket;
}

ostream& operator<<(ostream& os, const HashTable& ht)
{
	int size = pow(2, ht.depth);
	int i = 0;
	while(i < size) {
		os << i << ". " << "ulaz tabele sadrzi: \n";
		for (int j = 0; j < ht.table[i]->elems.size(); j++) {
			if (ht.table[i]->elems[j]->key != -1)os << ht.table[i]->elems[j]->key << "\t";
		}
		i++; //+= (ht.table[i]->pointers != 0 ? ht.table[i]->pointers : 1);
		os << endl;
	}
	return os;
}

double HashTable::fillRatio()
{
	double size = pow(2, depth);
	if (keyCount() == 0) return 0;
	return double(size / keyCount());
}

int HashTable::keysInPlace(int i)
{
	int num = 0;
	for (int s = 0; s < baket; s++) {
		if (table[i]->elems[s]->key != -1)num++;
	}
	return num;
}

/*HashTable::~HashTable()
{
	int size = pow(2, depth);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < table[i]->elems.size(); j++) {
			if (table[i]->elems[i]!=nullptr)delete(table[i]->elems[j]), table[i]->elems[j] = nullptr;
		}
		if (table[i] != nullptr && table[i]->elems.size() > 0)delete(table[i]), table[i] = nullptr;
	}
}*/
