#ifndef POLY_H_
#define POLY_H_

#include "PolyNode.h"


class Poly
{
private:
	// must contain this private field, and you can define other private fields
	PolyNode* head = NULL;

public:
	//constructors and destructors are done
	Poly();
	Poly(const std::vector<int>& deg, const std::vector<double>& coeff);
	~Poly();
	

	void addMono(int i, double c);
	void addPoly(const Poly& p);
	void multiplyMono(int i, double c);
	void multiplyPoly(const Poly& p);
	void duplicate(Poly& outputPoly);
	int getDegree();                       //done
	int getTermsNo();                      //done   
	double evaluate(double x);             //done
	std::string toString();                //done



	// used for testing
	PolyNode* getHead() {
		return head;
	};
};

#endif /* POLY_H_ */
