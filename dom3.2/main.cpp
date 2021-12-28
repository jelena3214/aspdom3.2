#include "hashtable.h"
using namespace std;
int main() {

	/*HashTable* ht = nullptr;
	Student* st = nullptr;

	while (true) {
		string menu = "\nUnesite neku od opcija:\n"
			"1. Kreiraj hes tabelu \n"
			"2. Kreiraj studenta \n"
			"3. Dodajte studentu predmet \n"
			"4. Ubaci studenta u hes tabelu \n"
			"5. Izbrisi studenta iz hes tabele \n"
			"6. Pronadji studenta u tabeli i ispisi ga\n"
			"7. Isprazni hes tabelu \n"
			"8. Broj kljuceva u hes tabeli \n"
			"9. Velicina hes tabele \n"
			"10. Popunjenost hes tabele \n"
			"11. Ispisi hes tabelu \n"
			"12. Kraj programa \n";
		cout << menu;
		int choice;
		cin >> choice;

		if (choice == 1) {
			int baket, p, d;
			cout << "Unesite velicinu baketa \n";
			cin >> baket;
			cout << "Unesite pocetnu dubinu \n ";
			cin >> d;
			cout << "Unesite p \n ";
			cin >> p;
			ht = new HashTable(baket, p, d);
		}
		if (choice == 2) {
			int indeks;
			string ime, prezime;
			cout << "Unesite indeks studenta \n";
			cin >> indeks;
			cout << "Unesite ime studenta\n";
			cin >> ime;
			cout << "Unesite prezime studenta \n";
			cin >> prezime;
			st = new Student(indeks, ime, prezime);
		}
		if (choice == 3) {
			cout << "Unesite sifru predmeta \n";
			string sifra;
			cin >> sifra;
			*st += sifra;
		}
		if (choice == 4) {
			ht->insertKey(*st);
		}
		if (choice == 5) {
			cout << "Unesite indeks studenta kojeg brisete iz tabele\n";
			int indeks;
			cin >> indeks;
			if (!ht->deleteKey(indeks))cout << "Nije moguce brisanje \n";
		}
		if (choice == 6) {
			int indeks;
			cout << "Unesite indeks studenta kog trazite u tabeli\n";
			cin >> indeks;
			Student* s = ht->findKey(indeks);
			if (s != nullptr)cout << *s << endl;
			else cout << "Nema tog studenta u tabeli \n";
		}
		if (choice == 7) {
			ht->clear();
		}
		if (choice == 8) {
			cout << ht->keyCount() << endl;;
		}
		if (choice == 9) {
			cout << ht->tableSize() << endl;
		}
		if (choice == 10) {
			cout << ht->fillRatio() << endl;
		}
		if (choice == 11) {
			cout << *ht << endl;
		}
		if (choice == 12) {
			exit(0);
		}
	}*/
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
	Student st6(13, "jeke", "peke");
	ht.insertKey(st6);
	ht.deleteKey(5);
	ht.deleteKey(13);
	
	Student st7(6, "jeke", "peke");
	ht.insertKey(st7);
	Student st8(10, "jeke", "peke");
	ht.insertKey(st8);
	Student st9(9, "jeke", "peke");
	ht.insertKey(st9);
	Student st19(4, "jeke", "peke");
	ht.insertKey(st19);
	//if(ht.findKey(5))cout << *ht.findKey(5);
	ht.deleteKey(0);
	ht.deleteKey(10);
	ht.deleteKey(9);
	
	/*ht.deleteKey(13);
	ht.deleteKey(13);
	
	Student st10(11, "jeke", "peke");
	ht.insertKey(st10);
	Student st11(18, "jeke", "peke");
	ht.insertKey(st11);
	//ht.deleteKey(50);
	//ht.deleteKey(22);
	
	//Student st12(48, "jeke", "peke");
	//ht.insertKey(st12);
	Student st13(275, "jeke", "peke");
	ht.insertKey(st13);
	Student st14(89, "jeke", "peke");
	ht.insertKey(st14); */
	cout << ht;
}