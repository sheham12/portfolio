#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream> // string stream 
#include <iterator> // ostream_iterator 

using namespace std; 

class HugeInteger
{
private:
	// class state
	std::vector <int> huge_int;
	bool neg;


public:
	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
	HugeInteger pos_add(const HugeInteger& h);
	HugeInteger pos_subtract(const HugeInteger& h);
	int modcompareTo(const HugeInteger& h);



};

#endif /* HUGEINTEGER_H_ */
