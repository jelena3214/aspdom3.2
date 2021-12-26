#ifndef _student_h_
#define _student_h_

#include <iostream>
#include <string>

using namespace std;
class Student {
	long indeks;
	string ime, prezime;
	struct Elem {
		string sifra;
		Elem* sled;
		Elem(string s, Elem* sl = nullptr) : sifra(s), sled(sl) {};
	};
	Elem* prijavljeniPredmeti;

	void kopiraj(const Student& st);
	void premesti(Student& st);
	void brisi();
	void setIndex(int ind) { indeks = ind; }
	friend class HashTable;
public:
	Student(long indeks, string ime, string prezime) {
		this->indeks = indeks;
		this->ime = ime;
		this->prezime = prezime;
		this->prijavljeniPredmeti = nullptr;
	}
	Student(const Student& st) { kopiraj(st); }
	Student(Student&& st) { premesti(st); }
	~Student() { brisi(); }
	Student& operator=(const Student& st);
	Student& operator=(Student&& st);
	Student& operator+=(string sifra);
	Student& operator-=(string sifra);
	friend ostream& operator<<(ostream& os, const Student& st);
};
#endif // !_student_h_
