#include "hashtable.h"
using namespace std;
int main() {
	HashTable ht(1, 64, 2);
	Student st1(1, "jeke", "peke");
	Student st2(0, "jeke", "peke");
	Student st3(3, "jeke", "peke");
	ht.insertKey(st1);
	ht.insertKey(st2);
	ht.insertKey(st3);
	Student st4(2, "jeke", "peke");
	ht.insertKey(st4);
	Student st5(5, "jeke", "peke");
	ht.insertKey(st5);
	Student st6(12, "jeke", "peke");
	ht.insertKey(st6);
	Student st7(15, "jeke", "peke");
	ht.insertKey(st7);
	Student st8(10, "jeke", "peke");
	ht.insertKey(st8);
	cout << ht;
}