#include "student.h"

void Student::kopiraj(const Student& st)
{
	ime = st.ime;
	prezime = st.prezime;
	indeks = st.indeks;

	Elem* p = st.prijavljeniPredmeti, *q = nullptr;

	while (p) {
		Elem* noviCvor = new Elem{ p->sifra };
		if (!prijavljeniPredmeti) {
			prijavljeniPredmeti = noviCvor;
			q = prijavljeniPredmeti;
		}
		else {
			q->sled = noviCvor;
			q = noviCvor;
		}
		p = p->sled;
	}

}

void Student::premesti(Student& st)
{
	ime = st.ime;
	prezime = st.prezime;
	indeks = st.indeks;
	prijavljeniPredmeti = st.prijavljeniPredmeti;
	st.prijavljeniPredmeti = nullptr;
}

void Student::brisi()
{
	Elem* p = prijavljeniPredmeti;
	Elem *stari = nullptr;
	while (p) {
		stari = p;
		p = p->sled;
		delete(stari);
	}
	prijavljeniPredmeti = nullptr;
}

Student& Student::operator=(const Student& st)
{
	if (this != &st) {
		brisi();
		kopiraj(st);
	}
	return *this;
}

Student& Student::operator=(Student&& st)
{
	if (this != &st) {
		brisi();
		premesti(st);
	}
	return *this;
}

Student& Student::operator+=(string sifra)
{
	Elem* p = prijavljeniPredmeti;
	Elem* noviCvor = new Elem{ sifra };
	if (!p) {
		prijavljeniPredmeti = noviCvor;
	}
	else {
		while (p->sled)p = p->sled;
		p->sled = noviCvor;
	}
	return *this;
}

Student& Student::operator-=(string sifra)
{
	Elem* p = prijavljeniPredmeti, *q = nullptr, *stari = nullptr;
	while (p) {
		q = p;
		if (p->sifra == sifra)break;
		p = p->sled;
	}
	if (!p)return *this;
	stari = p;
	q->sled = p->sled;
	delete(stari);
}

ostream& operator<<(ostream& os, const Student& st)
{
	os << st.indeks << " " << st.ime << " " << st.prezime << " " << endl;
	Student::Elem* p = st.prijavljeniPredmeti;
	while (p) {
		os << p->sifra << "\t";
		p = p->sled;
	}
	os << endl;
	return os;
}