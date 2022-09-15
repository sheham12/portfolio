#include "HugeInteger.h"


//400313984
//magda shehata
//sheham12

HugeInteger::HugeInteger(const std::string& val) 
{
	int i, index;
	//outputs error message if val starts with 0
	neg = false;
	

	if (! ((val[0] == '-')|| (std::isdigit(val[0])) ) )
		throw std::invalid_argument("Invalid value for huge number");

	//remove leading zeros
	if (val[0] == '-')
	{
		neg = true;
		index = 1;
		while ((val[index] == '0') && ((val.length()-1) != index))
			index++;
	}
	else
	{
		index = 0;
		while ((val[index] == '0') && ((val.length()-1) != index))
			index++;
	}


	//outputs error message if val is one character that is not a digit
	if (val.length() == 1 && !std::isdigit(val[0]))
		throw std::invalid_argument("Invalid value for huge number");

	//outputs error message if val is 0 digits or less
	if (val.length() <= 0)
		throw std::invalid_argument("Invalid size of huge number");

	//outputs error message if a char in val is not a digit
	//except first char if it is a negative sign
	for (i = index;i < val.length();i++)
	{
		if (!std::isdigit(val[i]))
			throw std::invalid_argument("Invalid value for huge number");
	}
	
	//constructs a vectors using the values from the string val

	for ( i = index; i < val.length();i++)
		huge_int.push_back(val[i] - '0');

}

HugeInteger::HugeInteger(int n) 
{
	neg = false;
	//outputs error message if val is 0 digits or less
	if (n <= 0)
		throw std::invalid_argument("Invalid size of huge number");

	else
	{
		srand(time(NULL));
		bool sign = rand() % 2;
		if (sign == 1) 
		{
		//	huge_int.push_back(-1);
			neg = true;
		}

		int j = rand() % 10;
		while (j == 0) 
			j = rand() % 10;
		huge_int.push_back(j);


		for (int i = 0;i < n - 1;i++) 
		{
			huge_int.push_back(rand() % 10);
		}
	}
}


/********************************************************************************
*    huge_int      h     *        add               *           subtract        *
* *******************************************************************************
*        +         +     *      add_pos             *           sub_pos         *
*                        *                          *                           *
*        -         -     *      - add_pos           *          - sub_pos        *
*                        *                          *                           *
*        -         +     *      - sub_pos           *          - add_pos        *
*                        *                          *                           *
*        +         -     *      sub_pos             *          add_pos          *
* *******************************************************************************/


HugeInteger HugeInteger::add(const HugeInteger& h) 
{

	bool sign1 = neg;
	bool sign2 = h.neg;

	//if both are positive, use add
	if (sign1 == false && sign2 == false)
	{
		HugeInteger answer = pos_add(h);
		return answer;

	}
	//if both are negative, use add (change sign)
	 if (sign1 == true && sign2 == true)
	{
		HugeInteger answer = pos_add(h);
		answer.neg = (!answer.neg);
		return answer;
	}


	//if huge_int is negative, and h is positive, use subtract (change sign)
	
	 if (sign1 == false && sign2 == true)
	 {
		 HugeInteger answer = pos_subtract(h);
		 if (answer.huge_int[0]==0)
			 answer.neg = false;

		 return answer;
	 }	
	 
	 if (sign1 == true && sign2 == false)
	 {
		 HugeInteger answer = pos_subtract(h);
		 answer.neg = (!answer.neg);
		 if (answer.huge_int[0] == 0)
			 answer.neg = false;
		 return answer;
	 }
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	// TODO


	bool sign1 = neg;
	bool sign2 = h.neg;

	//if both are positive, use add
	if (sign1 == false && sign2 == false)
	{
		HugeInteger answer = pos_subtract(h);
		//answer.neg = (!answer.neg);
		if (answer.huge_int[0] == 0)
			answer.neg = false;
		return answer;
	}

	//if both are negative, use add (change sign)
	 if (sign1 == true && sign2 == true)
	{
		 HugeInteger answer = pos_subtract(h);
		 answer.neg = (!answer.neg);

		 if (answer.huge_int[0] == 0)
			 answer.neg = false;

		 return answer;
	}


	//if huge_int is negative, and h is positive, use subtract (change sign)
	
	 if (sign1 == false && sign2 == true)
	 {
		 HugeInteger answer = pos_add(h);
		 //answer.neg = (!answer.neg);
		 return answer;


	 }	
	 
	 if (sign1 == true && sign2 == false)
	 {
		 HugeInteger answer = pos_add(h);
		 answer.neg = (!answer.neg);

		 return answer;

	 }
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	std::vector <int> ::reverse_iterator it1, it2;
	//std::vector <int> answer;
	HugeInteger answer("0");
	std::vector <int> h_temp = h.huge_int;


	if (h_temp[0] == 0 || huge_int[0] == 0)
		return HugeInteger("0");
	
	int l1 = huge_int.size();
	int l2 = h_temp.size();
	int temp;
	it2 = h_temp.rbegin();


	for (int i = 0;i < l2;i++)
	{
		it1 = huge_int.rbegin();
		int carry = 0;
		std::vector <int> temp_ans;

		for (int j = (l1 - 1);j >= 0;j--)
		{
			temp = (*it1) * (*it2) + carry;

			if (temp > 9)
			{
				carry = (temp - temp % 10) / 10;
				temp = temp % 10;
			}
			temp_ans.insert(temp_ans.begin(), temp);
			if ((j == 0) && (carry != 0))
				temp_ans.insert(temp_ans.begin(), carry);
			it1++;
		}
		it2++;


		for (int k = i; k > 0; k--)
			temp_ans.push_back(0);

		//convert temp_ans into HugeInteger
		stringstream result;
		copy(temp_ans.begin(), temp_ans.end(), std::ostream_iterator<int>(result, ""));
		string n = result.str();
		HugeInteger huge_n(n);

		//add
		HugeInteger rep(1);
		rep = answer.pos_add(huge_n);
		(answer.huge_int).clear();
		answer.huge_int = rep.huge_int;

	}

	bool sign1 = neg;
	bool sign2 = h.neg;


	if (((sign1 == false) && (sign2 == false)) || ((sign1 == true) && (sign2 == true)))
		answer.neg = false;
	else
		answer.neg = true;
	return answer;
	
}



int HugeInteger::compareTo(const HugeInteger& h) {
	// TODO
	std::vector <int> h_temp = h.huge_int;

	int l1 = huge_int.size();
	int l2 = h.huge_int.size();
	
	bool sign1 = neg;
	bool sign2 = h.neg;

	if (sign1 == true && sign2 == false)
		return -1;
	if (sign1 == false && sign2 == true)
		return 1;
	if (sign1 == false && sign2 == false)
	{
		//check lengths
		if (l1 > l2)
			return 1;
		if (l1 < l2)
			return -1;
		if (l1 == l2)
		{
			//compare values
			for (int i = 0;i < l1;i++)
			{
				if (huge_int[i] > h_temp[i])
					return 1;
				if (huge_int[i] < h_temp[i])
					return -1;				
			}
			return 0;
		}
	}
	if (sign1 == true && sign2 == true)
	{
		//check lengths
		if (l1 > l2)
			return -1;
		if (l1 < l2)
			return 1;
		if (l1 == l2)
		{
			//compare values
			for (int i = 0;i < l1;i++)
			{
				if (huge_int[i] > h_temp[i])
					return -1;
				if (huge_int[i] < h_temp[i])
					return 1;
			}
			return 0;
		}
	}
	return 0;
}

std::string HugeInteger::toString() {
	// TODO
	std::string huge = "";

	//convert neg back into '-'
	if (neg) huge.push_back('-');


	//iterate through all digits
	for ( int j=0; j < huge_int.size();j++)
	{
		//convert digit to char and concatenate to string
		char digit = char(huge_int[j] + 48);
		huge.push_back(digit);
	}


	return huge;
	//return "";
}

HugeInteger HugeInteger::pos_add(const HugeInteger& h) {
	// TODO

	std::vector <int> ::reverse_iterator it1, it2;
	std::string answer = "";
	std::vector <int> h_temp = h.huge_int;


	int carry = 0;
	int l1 = huge_int.size();
	int l2 = h.huge_int.size();
	int temp, i;


	if (l1 < l2)
	{
		//make sure l1 is the larger huge integer and l2 is the smaller huge integer
		temp = l1;
		l1 = l2;
		l2 = temp;
		//make the each itirator start at the end of each vector (reserve begin)
		it1 = h_temp.rbegin();
		it2 = huge_int.rbegin();
	}
	else
	{
		it1 = huge_int.rbegin();
		it2 = h_temp.rbegin();
	}


	for (i = l1 - 1; i >= l1 - l2; i--)
	{
		//starting from the least significant digit, add each digit from each
		//huge integer and the carry (if one exists)
		temp = *it1 + *it2 + carry;
		if (temp > 9)
		{
			temp = temp % 10;
			carry = 1;
		}
		else
			carry = 0;
		//insert sum (without carry) into the answer string
		answer.insert(answer.begin(), char(temp + 48));
		it1++;
		it2++;

	}

	//add the left-over digits from the larger huge integer
	for (i = 0; i <= l1 - l2 - 1; i++)
	{
		temp = *it1 + carry;
		if (temp > 9)
		{
			temp = temp % 10;
			carry = 1;
		}
		else
			carry = 0;
		answer.insert(answer.begin(), temp + 48);
		it1++;
	}

	if (carry == 1)
		answer.insert(answer.begin(), 1 + 48);


	return (HugeInteger(answer));
	//return HugeInteger("");
}


HugeInteger HugeInteger::pos_subtract(const HugeInteger& h) {
	// TODO

	//define variables and iterators
	std::vector <int> ::reverse_iterator it1, it2, it3;
	std::vector <int> ::iterator it4;
	std::string answer = "";

	std::vector <int> h_temp = h.huge_int;
	std::vector <int> huge_temp = huge_int;

	int l1, l2;
	int temp, i;
	bool sign = false;

	bool sign1 = neg;
	bool sign2 = h.neg;

	//compare huge_int to h
	int compare = modcompareTo(h);

	//if they have the same value, difference is zero
	if (compare == 0)	
		return HugeInteger("0");


	if (compare == 1)

		//if huge_int has a larger value
	{
		it1 = huge_temp.rbegin();
		l1 = huge_temp.size();
		it2 = h_temp.rbegin();
		l2 = h_temp.size();
		it3 = huge_temp.rbegin();
	}

	//if h_temp has a larger value
	else
	{

		it1 = h_temp.rbegin();
		l1 = h_temp.size();
		it2 = huge_temp.rbegin();
		l2 = huge_temp.size();
		it3 = h_temp.rbegin();
		sign = true;

	}



	//where the digits overlap (least significant digits)
	for (i = l1 - 1; i >= l1 - l2; i--)
	{
		//starting from the least significant digit
		temp = *it1 - *it2;
		if (temp >= 0)
			answer.insert(answer.begin(), temp + 48);
		else if (temp < 0)
		{
			it3 = it1 + 1;
			int index = i - 1;
			while (*it3 == 0)
			{
				it3++;
				index--;
			}

			*it3 = *it3 - 1;

			if (compare == -1)
			{
				it4 = h_temp.begin() + index + 1;
			}
			else
				it4 = huge_temp.begin() + index + 1;

			
			temp = (*it1 + 10) - *it2;
			*it1 = *it1 + 10;
			answer.insert(answer.begin(), temp + 48);
			while (*it4 == 0)
			{
				*it4 = 9;
				it4++;
			}

		}
		it1++;
		it2++;
	}


		//left over digits
		for (i = 0; i <= l1 - l2 - 1; i++)
		{
			temp = *it1;
			answer.insert(answer.begin(), temp + 48);
			it1++;
		}
	
	while ((answer[0] == '0') && (answer.size() != 1))
		answer.erase(answer.begin());

	if(sign==true)
		answer.insert(answer.begin(), '-');

	return HugeInteger(answer);
}





int HugeInteger::modcompareTo(const HugeInteger& h) {
	std::vector <int> h_temp = h.huge_int;

	int l1 = huge_int.size();
	int l2 = h_temp.size();

		//check lengths
		if (l1 > l2)
			return 1;
		if (l1 < l2)
			return -1;
		if (l1 == l2)
		{
			//compare values
			for (int i = 0;i < l1;i++)
			{
				if (huge_int[i] > h_temp[i])
					return 1;
				if (huge_int[i] < h_temp[i])
					return -1;
			}
			return 0;
		}
	//return 0;
}






