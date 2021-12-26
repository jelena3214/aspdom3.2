#ifndef _quadratichashing_h_
#define _quadratichashing_h_
#include "adressfunction.h"

class QuadraticHashing :public AdressFunction{
	int c;
public:
	QuadraticHashing(int cc) :c(cc) {};
	int getAdress(long key, int adress, int attempt, int size) override {
		return (adress + c * attempt * attempt)%size;
	}
	~QuadraticHashing() {};
};
#endif // !_quadratichashing_h_
