#include "hashtable.h"
//ENUM

//TO DO: BRISANJE(SAZIMANJE), PRETRAGA, UBACIVANJE KAD SVI OVU U ISTI BAKET, destruktor

//STA AKO SVI PONOVO U ISTI BAKET, IDE SE PO JOS JEDAN BIT
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
		if (table[addr]->elems[i]->key == index) { //vec postojki kljuc
			return false;
		}
		else if (table[addr]->elems[i]->key == -1) { //prazno mesto
			table[addr]->elems[i]->st = &st;
			table[addr]->elems[i]->key = index;
			table[addr]->baketLen++;
			table[addr]->pointers++;
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
			//numofbits = log2(newAddr) + 1;
			if (newAddr == 0)bit = 0;
			else {
				bit = (newAddr >> shift) & 1; //izdvanjamo nti bit od kraja ako to treba onda samo newadr>>depth-1 and 1
			}
			if (bit == 0) {
				table[addr]->elems.push_back(allElems[i]);
				table[addr]->elems[oldlen++]->key = allElems[i]->key;
				table[addr]->baketLen++;
			}
			else {
				newBaket->elems.push_back(allElems[i]);
				newBaket->elems[newlen++]->key = allElems[i]->key;
				newBaket->baketLen++;
			}
		}

		if (newBaket->elems.size() > baket || table[addr]->elems.size() > baket) {//povecamo depth jer uzimamo jos jedan bit
			size = pow(2, depth);
			if (n > 2)setB(1);
			n++;

		}
		else if (depth > p) {
			cout << "Nije moguce ubacivanje\n";
			return false;
			break;
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

	}
	else {
		int i = 0;
		int l = size / 2;
		table[addr]->pointers++;
		if (addr + l < pow(2, depth - n))if (table[addr + l] == table[addr])i = addr + 1; //novi kacimo na addr+1
		if (addr - l < pow(2, depth - n))if (table[addr - l] == table[addr])i = addr; //novi kacimo na addr
		table[i] = newBaket;
		newBaket->pointers++;
		setB(0);
		return true;
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
	for (int i = 0; i < size; i++) {
		keys += keysInPlace(i);
	}
	return keys;
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
		for (int j = 0; j < ht.baket; j++) {
			if (ht.table[i]->elems[j]->key != -1)os << ht.table[i]->elems[j]->key << "\t";
		}
		i++; //+= (ht.table[i]->pointers != 0 ? ht.table[i]->pointers : 1);
		os << endl;
	}
	return os;
}

double HashTable::fillRatio()
{
	int size = pow(2, depth);
	return size / keyCount();
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
		for (int j = 0; j < baket; j++) {
			if (table[i]!=nullptr && table[i]->elems.size()>0)delete(table[i]->elems[j]), table[i]->elems[j] = nullptr;
		}
		if (table[i] != nullptr && table[i]->elems.size() > 0)delete(table[i]), table[i] = nullptr;
	}
}*/

/*
	
		//prepovezivanje
		if (table[addr]->depthBaket == depth || n > 1) {
			//sirenje tabele
			int help = (n > 1 ? 1 : 0);
			size = pow(2, depth - n + help);
			int newSize = pow(2, depth);
			for (int i = size; i < newSize; i++) {
				Baket* b = new Baket;
				table.push_back(b);
			}


			vector<Baket*> allBaket;
			int i = 0;
			while (i <= addr) {
				allBaket.push_back(table[i]);
				i += (table[i]->pointers != 0 ? table[i]->pointers : 1);
			}
			allBaket.push_back(newBaket);

			while (i < size) {
				allBaket.push_back(table[i]);
				i += (table[i]->pointers != 0 ? table[i]->pointers : 1);
			}
			int oldsize = size;
			size = pow(2, depth);
			int k = allBaket.size(), len = 0;
			for (int i = 0; i < k; i++) {
				if (allBaket[i]->pointers == 0) {
					table[len] = allBaket[i];
					table[len + oldsize] = allBaket[i+1];
					table[len + oldsize]->pointers++;
					table[len++]->pointers++;
					i++;
					continue;
				}
				//int l = allBaket[i]->pointers * 2;
				//for (int j = 0; j < l; j++) {
					//table[len] = allBaket[i];
					//table[len++]->pointers++;
				//}
				table[len] = allBaket[i];
				table[len+oldsize] = allBaket[i];
				table[len + oldsize]->pointers++;
				table[len++]->pointers++;
				
			}
			return true;
		}
		else {
			int i = 0;
			int l = size / 2;
			if(addr+l < pow(2,depth-n))if (table[addr + l] == table[addr])i = addr+1; //novi kacimo na addr+1
			if (addr - l < pow(2, depth-n))if (table[addr - l] == table[addr])i = addr; //novi kacimo na addr
			table[i] = newBaket;
			newBaket->pointers++;
			setB(0);
			return true;
		}
	}
	
	return false;*/