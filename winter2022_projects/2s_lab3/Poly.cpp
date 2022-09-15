#include "Poly.h"

Poly::Poly()
{
	//constructor: creates the zero polynomial with degree equals -1
	head = new PolyNode(-1, 0.0, NULL);

}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	int i;
	// saving the degree of the polynomial in the head
	if (deg.size()!=0)
		head = new PolyNode(deg[0], 0, NULL);


	else
		head = new PolyNode(-1, 0.0, NULL);


	for (i = (deg.size() - 1); i >= 0; i--)
		head->next = new PolyNode(deg[i], coeff[i], head->next);
}

Poly::~Poly()
{
	//destructor
	//frees the memory allocated for the linked list nodes in a polynomial
	while (head)
	{
		PolyNode* tmp = head->next;
		//auto tmp = head->next;
		//head->next = tmp->next;
		delete head;
		head = tmp;
	}
}


void Poly::addMono(int i, double c)
{
	// TODO

	PolyNode* p;
	
	//if the node is zero
	if (c == 0.0)
		return;
	//if the node is zero
	if (i == -1)
		return;

	//if linked list is empty, insert node
	if (head->next == NULL)
	{
		//head->next = new PolyNode(i, c, head->next);
		head->next = new PolyNode(i, c, NULL);
		head->deg = head->next->deg;
		return;
	}

	
	for (p = head; p->next != NULL; p = p->next)
	{
		if ((p->next->deg) == i)
		{
			if (((p->next->coeff) + c) == 0)
			{
				//delete node
				PolyNode* tmp = p->next;
				//auto tmp = p->next;
				p->next = p->next->next;
				delete tmp;
				if (head->next == NULL)
					head->deg = -1;
				else
					head->deg = head->next->deg;
				return;
			}
			else
			{
				//modify node
				(p->next->coeff) = (p->next->coeff) + c;
				return;
			}
		}

		if ((p->next->deg) < i)
		{
			//insert node ahead
			PolyNode* tmp = new PolyNode(i, c, p->next);
			//auto tmp = new PolyNode(i, c, p->next);
			p->next = tmp;
			head->deg = head->next->deg;
			return;
		}
		/*
		if (p->next->next == NULL && (p->next->deg) > i)
		{
			//insert at the end of the list
			auto tmp = new PolyNode(i, c, NULL);
			p->next->next = tmp;
			head->deg = head->next->deg;
			return;
		}
		*/

	}
	//insert at the end of the list
	PolyNode* tmp2 = new PolyNode(i, c, NULL);
	//auto tmp = new PolyNode(i, c, NULL);
	p->next = tmp2;
	return;
}




void Poly::multiplyMono(int i, double c)
{
	// TODO
	PolyNode* p;
	
	//if the term is 0, delete terms in linked list
	if (c == 0.0)
	{
		while (head->next)
		{
			auto tmp = head->next;
			head->next = tmp->next;
			delete tmp;
		}
		head->deg = -1;
		head->coeff = 0;
		return;
	}


	if (head->next == NULL)
		return;


	for (p = head->next; p != NULL; p = p->next)
	{
		p->coeff= (p->coeff) * c;
		p->deg = (p->deg) + i;
	}
	head->deg+=i;
	return;
}

void Poly::multiplyPoly(const Poly& p)
{
	PolyNode* p2 = p.head;
	Poly dup;
	//duplicate this polynominal
	duplicate(dup);

	//clear this polynomial so it can store the multiplication
	while (head->next)
	{
		auto tmp = head->next;
		head->next = tmp->next;
		delete tmp;
	}

	while ((p2->next) != NULL)
	{
		Poly answer;
		dup.duplicate(answer);
		answer.multiplyMono(p2->next->deg, p2->next->coeff);
		addPoly(answer);
		p2 = p2->next;
	}
	if (head->next == NULL)
		head->deg = -1;
	else
		head->deg = head->next->deg;
	
}


void Poly::duplicate(Poly& outputPoly)
{

	//clear outputPoly
	while (outputPoly.head->next)
	{
		auto tmp = outputPoly.head->next;
		outputPoly.head->next = tmp->next;
		delete tmp;
	}
	delete outputPoly.head;

	//copy empty linked-list
	if (head->next == NULL)
	{
		outputPoly.head = new PolyNode(-1, 0, NULL);
		return;
	}

	//copy non-zero linked-list
	PolyNode* p=head->next;
	outputPoly.head = new PolyNode(head->deg, head->coeff, NULL);
	PolyNode* q=outputPoly.head;

	//insert last
	while (p !=NULL)
	{
		auto tmp=new PolyNode(p->deg, p->coeff, NULL);
		q->next = tmp;
		p = p->next;
		q = q->next;
	}


}

int Poly::getDegree()
{
	if (head->next == NULL)
		return (head->deg);
	else
		return (head->next->deg);    //change this after completing this function
}

int Poly::getTermsNo()
{
	int term_no=0;
	PolyNode* tmp=head;
	while (tmp->next)
	{
		tmp = tmp->next;
		term_no++;
	}
	return (term_no);//change this after completing this function
}

double Poly::evaluate(double x)
{
	double eval = 0.0;
	PolyNode* p;
	if (head->next == NULL)
		return eval;
	for (p = head->next; p != NULL; p = p->next)
		eval+=(p->coeff) *( pow(x, (double)(p->deg)));

	return eval;//change this after completing this function
}

std::string Poly::toString()
{
	// TODO
	std::string poly_str="";

	poly_str.append("degree="+to_string(head->deg)+"; ");
	PolyNode* p;
	for (p = head->next; p != NULL; p = p->next)
		poly_str.append("a(" + to_string(p->deg)+ ")=" + to_string(p->coeff) + "; ");

	return poly_str;//change this after completing this function
}


/*

void Poly::addPoly(const Poly& p)
{
	// define pointer that will traverse through both linked lists
	PolyNode* p1=head;
	PolyNode* p2=p.head;

	//iterate through both linked lists until the end
	while (( (p1->next) != NULL) && ( (p2->next) != NULL))

	{
		//if degree of the node from p2 is greater than
		//the degree of the node from p1, insert node node
		if ((p2->next->deg) > (p1->next->deg))
		{
			PolyNode* node = new PolyNode(p2->next->deg, p2->next->coeff, p1->next);
			p1->next = node;
			p1 = p1->next;
			p2 = p2->next;
		}

		else
		{
			if ((p2->next->deg) < (p1->next->deg))
			{
				//insert node ahead
				//auto tmp = new PolyNode(p2->next->deg, p2->next->coeff, p1->next);
				p1 = p1->next;
			}
			else
			{
				if (p1->next->deg  == p2->next->deg) 
				{
					p1->next->coeff += p2->next->coeff;
					if ((p1->next->coeff) == 0.0)
					{
						//delete node
						PolyNode* tmp = p1->next;
						p1->next = tmp->next;
						delete tmp;
						p2 = p2->next;
						continue;
					}
					else
					{
						p1 = p1->next;
						p2 = p2->next;
					}
				}
			}
		}
	}

	while (p2->next!=NULL)
	{
		//insert at the end of the list
		//PolyNode* tmp = new PolyNode(p2->next->deg, p2->next->coeff, NULL);
		PolyNode* tmp = new PolyNode(p2->next->deg, p2->next->coeff, NULL);
		
		//p1 = tmp;        

		p1->next = tmp;
		p1 = p1->next;

		p2 = p2->next;
	}
	if (head->next == NULL)
		head->deg = -1;
	else
		head->deg = head->next->deg;
	//head->deg = head->next->deg;
}

*/

void Poly::addPoly(const Poly& p)
{

	//if p is empty, return
	//PolyNode* ptr1 = head;
	PolyNode* ptr = p.head;

	if (ptr->next == NULL) {
		return;
	}

	//otherwise, traverse through p and add each node of p into this polynomial

	while (ptr->next != NULL)
	{
		addMono((ptr->next->deg), (ptr->next->coeff));
		ptr = ptr->next;
	}

	//redefine degree of polynomial in dummy node
	if (head->next == NULL)
	{
		head->deg = -1;
		head->coeff = 0;
	}
	else
		head->deg = head->next->deg;

}
