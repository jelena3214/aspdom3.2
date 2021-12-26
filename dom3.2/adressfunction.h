#ifndef _adressfunction_h_
#define _adressfunction_h_

class AdressFunction {
public:
	virtual int getAdress(long key, int adress, int attempt, int size) = 0;
	virtual ~AdressFunction() {};
};
#endif // !_adressfunction_h_
