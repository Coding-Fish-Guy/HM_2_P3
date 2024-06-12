#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include "CMyVector.h"
#include <algorithm>

using namespace std;

int CMyVektor::get_dimension()const { return vec.size(); }

void CMyVektor::clr() {
	vec.clear();
}
void CMyVektor::set_dimension(int dimension, int value)
{
	vec.clear();
	vec.assign(dimension, value);
}

void CMyVektor::add_dimension(int value) {
	vec.push_back(value);
}

CMyVektor::CMyVektor(int dimension) {
	vec.assign(dimension, 0.0);
}

CMyVektor::CMyVektor(int dimension, double value) {
	vec.assign(dimension, value);
}

CMyVektor::~CMyVektor() {
	vec.clear();
}

CMyVektor::CMyVektor(const CMyVektor& orig) : vec{ orig.vec } {}

double CMyVektor::calc_length() {
	std::vector<double>::iterator it = vec.begin();
	double sum = 0;
	while (it != vec.end())
	{
		sum += (*it) * (*it);
		it++;
	}
	return  sqrt(sum);
}

CMyVektor& CMyVektor::operator=(const CMyVektor& orig)
{
	vec.clear();
	vec = orig.vec;
	return (*this);
}



double& CMyVektor::operator[](int i) {
	if (this->get_dimension()<=i || i<0)
	{
		throw out_of_range("Index negative or out of range");
	}
	return vec[i];
}


CMyVektor& CMyVektor::operator () (const std::vector<double>& v) {
	vec = v;
	return *this;
}


CMyVektor CMyVektor::operator+=(CMyVektor a) {
	
	int size = a.get_dimension();
	if (a.get_dimension()==this->get_dimension())
	{
		for (int i = 0; i != size; i++)
		{
			this->vec[i] += a.vec[i];
		}	
	}
	else
	{
		throw out_of_range("Failed: Dimensions not equal");
	}
	return *this;
}
CMyVektor CMyVektor::operator-=(CMyVektor a) {

	int size = a.get_dimension();
	if (a.get_dimension() == this->get_dimension())
	{
		for (int i = 0; i != size; i++)
		{
			this->vec[i] -= a.vec[i];
		}
	}
	else
	{
		throw out_of_range("Failed: Dimensions not equal");
	}
	return *this;
}
CMyVektor CMyVektor::operator*=(double lambda) {
	for (int i = 0; i < this->get_dimension(); i++)
	{
		this->vec[i] *= lambda;
	}
	return *this;
}

CMyVektor CMyVektor::operator+(CMyVektor a)
{
	return CMyVektor(*this) += a;
}
CMyVektor CMyVektor::operator-(CMyVektor a) {

	return CMyVektor(*this) -= a;
}
CMyVektor CMyVektor::operator*(double lambda)
{
	return CMyVektor(*this) *= lambda;
}

std::ostream& operator << (std::ostream& stream, CMyVektor& orig) {

	int precision = 10;
	string TrimmedString = "";
	int dimension = 1;
	string str = "( ";
	std::vector<double> ::iterator it = orig.vec.begin();
	auto itcopy = it;

	while (it!=orig.vec.end())
	{
		TrimmedString = std::to_string(*it).substr(0, to_string(*it).find(".") + precision);
		str += TrimmedString;

		if (dimension <orig.get_dimension())
		{
			str += ", ";
			dimension++;
		}
		it++;
	}
	str += " )";
	stream << str;
	return stream;
}

std::string CMyVektor::text() {
	string str = "( ";
	auto it = vec.begin();
	int dimension = 1;

	while (it != vec.end())
	{
		str += std::to_string(*it);
		if (dimension < this->get_dimension())
		{
			str += ", ";
			dimension++;
		}
		it++;
	}
	str += ")";
	return str;
}

std::string CMyVektor:: vertical_print() {

	auto it = vec.begin();
	string str = "";
	while (it!=vec.end())
	{
		str += to_string(*it) + "\n";
		it++;
	}
	return str;
}

void CMyVektor::print_pretty() {

	// "print pretty"
	for_each(vec.begin(), vec.end(), [](double x)->void {std::cout << "| " << x << " |" << endl; });

}


CMyVektor CMyVektor:: gradient(CMyVektor x, double (*funktion)(CMyVektor x), const double h) {

	auto subtrahend = funktion(x);
	CMyVektor minuend(x);
	CMyVektor grad(x.get_dimension());

	for (int i = 0; i < x.get_dimension(); i++)
	{
		minuend[i] += h;
		grad[i] = (funktion(minuend) - subtrahend) / h;
		minuend[i] = x[i]; // zurücksetzen des Minuenden

	}
	
	return grad;
}


double const H = 1e-8;
CMyVektor CMyVektor:: gradientenVerfahren(CMyVektor x, double (*funktion)(CMyVektor x), double lambda, int schritte) {
	int n;
	bool abbruchbedingung = false;
	cout << "Eingabe: [1] fuer Maximierung, [2] fuer Minimierung: ";
	cin >> n;

	if (n == 1)
	{
		std::cout << "VERFAHREN ZUR MAXIMIERUNG: " << std::endl;
		CMyVektor x_neu(x);
		CMyVektor grad(x);
		double f_x_neu = funktion(x);
		double f = funktion(x);
		double length = x.calc_length();
		double abbruch = 1e-5;
		for (int i = 0; i < schritte; i++)
		{
			f = funktion(x);
			grad = x.gradient(x, funktion, H);
			x_neu = x + (grad * lambda);
			f_x_neu = funktion(x_neu);
			length = grad.calc_length(); 

			if (length < abbruch)// Abbruchbedingung
			{
				abbruchbedingung=true;
				break;
			}

			std::cout << "Schritt " << i << ":" << std::endl << std::endl <<
				"x = " << x << std::endl <<
				"lambda = " << lambda << std::endl <<
				"f(x) = " << f << std::endl <<
				"grad f(x) = " << grad << std::endl <<
				"||grad f(x)|| = " << length << std::endl << std::endl <<
				"x_neu = " << x_neu << std::endl <<
				"f(x_neu) = " << f_x_neu << std::endl;
			std::cout << std::endl;


			if (f_x_neu > f) // Erster Fall falls f(x_neu)>f(x)
			{
				CMyVektor x_test;
				auto f_grad_x_test = f_x_neu;
				double test_lambda = lambda;
				test_lambda *= 2;
				x_test = x + (grad * test_lambda);
				f_grad_x_test = funktion(x_test);
				std::cout << "Test mit doppelter Schrittweite (lambda = " << test_lambda << "):" << std::endl <<
					"x_test = " << x_test << std::endl <<
					"f(x_test) = " << f_grad_x_test << std::endl << std::endl;

				if (f_grad_x_test > f_x_neu) //falls(x_test)>f(x_neu)
				{
					x = x_test;
					lambda = test_lambda;
					std::cout << "verdoppelte Schrittweite!" << std::endl << std::endl;
				}
				else
				{
					x = x_neu;
					std::cout << "behalte alte Schrittweite!" << std::endl << std::endl;
				}
			}
			else if (f_x_neu <= f) // falls f(x_neu)<= f(x) dann halbieren
			{
				double test_lambda = lambda;

				while (!(f_x_neu > f)) // solange halbieren bis f(x_neu) größer ist
				{
					test_lambda *= 0.5;
					std::cout << "halbiere Schrittweite (lambda = " << test_lambda << ") : " << std::endl;
					x_neu = x + (grad * test_lambda);
					f_x_neu = funktion(x_neu);

					std::cout << "x_neu = " << x_neu << std::endl <<
						"f(x_neu) = " << f_x_neu << std::endl << std::endl;
				}
				lambda = test_lambda;
				x = x_neu;
				std::cout << std::endl;
			}

		}
		f = funktion(x);
		grad = x.gradient(x, funktion, H);
		if (abbruchbedingung)
		{
			std::cout << "Ende wegen ||grad f(x)||<1e-5 bei " << std::endl;
		}
		else
		{
			std::cout << "Ende wegen Schrittweite." << std::endl;
		}
		std::cout<<
			"x = " << x << std::endl <<
			"lambda = " << lambda << std::endl <<
			"f(x) = " << f << std::endl <<
			"grad f(x) = " << grad << std::endl <<
			"||grad f(x)|| = " << grad.calc_length() << std::endl << std::endl;
		return x;
	}     
	else if (n==2)
	{
		std::cout << "VERFAHREN DER MINIMIERUNG" << std::endl;
		CMyVektor x_neu(x);
		CMyVektor grad(x);
		double f_x_neu = funktion(x);
		double f = funktion(x);
		double length = 0;
		double abbruch = 0.00001;

		for (int i = 0; i < schritte; i++)
		{
			f = funktion(x);
			grad = x.gradient(x, funktion, H);
			x_neu = x - (grad * lambda);
			f_x_neu = funktion(x_neu);

			length = grad.calc_length(); // Abbruchbedingung
			if (length < abbruch)
			{
				abbruchbedingung = true;
				break;
			}
			std::cout << "Schritt " << i << ":" << std::endl << std::endl <<
				"x = " << x << std::endl <<
				"lambda = " << lambda << std::endl <<
				"f(x) = " << f << std::endl <<
				"grad f(x) = " << grad << std::endl <<
				"||grad f(x)|| = " << grad.calc_length() << std::endl << std::endl <<
				"x_neu = " << x_neu << std::endl <<
				"f(x_neu) = " << f_x_neu << std::endl<<std::endl;

			if (f_x_neu < f) // Erster Fall falls f(x_neu)<f(x)
			{
				CMyVektor x_test;
				auto f_grad_x_test = f_x_neu;
				double test_lambda = lambda;
				test_lambda *= 2;
				x_test = x + (grad * test_lambda);
				f_grad_x_test = funktion(x_test);
				std::cout << "Test mit doppelter Schrittweite (lambda = " << test_lambda << "):" << std::endl <<
					"x_test = " << x_test << std::endl <<
					"f(x_test) = " << f_grad_x_test << std::endl << std::endl;

				if (f_grad_x_test < f_x_neu) //falls(x_test)<f(x_neu)
				{
					x = x_test;
					lambda = test_lambda;
					std::cout << "verdoppelte Schrittweite!" << std::endl << std::endl;
				}
				else
				{
					x = x_neu;
					std::cout << "behalte alte Schrittweite!" << std::endl << std::endl;
				}

			}
			else if (f_x_neu >= f) // falls f(x_neu)>= f(x) dann halbieren
			{
				double test_lambda = lambda;

				while (!(f_x_neu < f)) // solange halbieren bis f(x_neu) kleiner ist
				{
					test_lambda *= 0.5;
					std::cout << "halbiere Schrittweite (lambda = " << test_lambda << ") : " << std::endl;
					x_neu = x - (grad * test_lambda);
					f_x_neu = funktion(x_neu);

					std::cout << "x_neu = " << x_neu << std::endl <<
						"f(x_neu) = " << f_x_neu << std::endl << std::endl;
				}
				lambda = test_lambda;
				x = x_neu;
				std::cout << std::endl;
			}
			
		}
		f = funktion(x);
		grad = x.gradient(x, funktion, H);
		if (abbruchbedingung)
		{
			std::cout << "Ende wegen ||grad f(x)||<1e-5 bei " << std::endl;
		}
		else
		{
			std::cout << "Ende wegen Schrittweite." << std::endl;
		}
		std::cout << 
			"x = " << x << std::endl <<
			"lambda = " << lambda << std::endl <<
			"f(x) = " << f << std::endl <<
			"grad f(x) = " << grad << std::endl <<
			"||grad f(x)|| = " << grad.calc_length() << std::endl << std::endl;
		return x;
	}		  //
	else
	{
		cout << "Nummer ungueltig" << endl;
		return 0;
	}
}
/*
CMyVektor CMyVektor::newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x), int schritte) {

	if (x.get_dimension()!=2)
	{
		throw std::out_of_range("Dimension not 2");
	}

	CMyVektor x_copy = x;
	CMyVektor fx=funktion(x_copy);
	CMyVektor dx=x_copy;
	CMyMatrix jacob(2,x_copy.get_dimension());
	CMyMatrix inv_jacob=jacob;
	double abs_fx = 1e-5;
	int i = 0;
	while ((i<schritte)&&(fx.calc_length()>abs_fx))
	{
		
		jacob = jacob.jacobi(x_copy, funktion);
		inv_jacob = jacob.invers();
		dx = (inv_jacob * fx) * -1.0;
		std::cout << "Schritt: " << i << endl<<endl;
		std::cout <<  "x = " << x_copy << endl;
		std::cout << "f(x) = " << fx << endl;
		std::cout <<  "f'(x) = \n" << jacob << endl;
		std::cout <<  "(f'(x))^(-1) = \n" << inv_jacob << endl;
		std::cout <<  "dx = " << dx << endl;
		std::cout << "||f(x)|| = " << fx.calc_length() << endl;
		std::cout << endl;
		x_copy += dx;
		fx = funktion(x_copy);
		i++;
	}
	if (i>=schritte)
	{
		std::cout << endl;
		std::cout << "Ende wegen Schrittweite" << endl;
	}
	else
	{
		std::cout << endl;
		std::cout << "Ende wegen ||f(x)|| <1e-5 bei " << endl;
	}
	std::cout << "\t" << "x = " << x_copy << endl;
	std::cout << "\t" << "f(x) = " << fx << endl;
	std::cout << "\t" << "||f(x)|| = " << fx.calc_length() << endl;

	return  x_copy;
}
*/


