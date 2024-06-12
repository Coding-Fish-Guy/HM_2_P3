#pragma once
#include <vector>
#include <string>

class CMyVektor {
private:
	std::vector<double> vec;

public:
	CMyVektor() {}
	CMyVektor(int dimension);
	CMyVektor(int dimension, double value);
	~CMyVektor();
	CMyVektor(const CMyVektor& orig);
	void set_dimension(int dimension, int value);
	void add_dimension(int value);
	void clr();
	int get_dimension()const;
	double calc_length();
	void print_pretty();
	std::string text();
	std::string vertical_print();
	CMyVektor& operator=(const CMyVektor& orig);
	double & operator[](int index);
	CMyVektor& operator () (const std::vector<double>& v);
	CMyVektor operator+=(CMyVektor a);
	CMyVektor operator-=(CMyVektor a);
	CMyVektor operator*=(double lambda);
	CMyVektor operator+(CMyVektor a);
	CMyVektor operator-(CMyVektor a);
	CMyVektor operator*(double lambda);
	friend std::ostream& operator << (std::ostream& stream, CMyVektor& orig);
	CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x), const double h);
	CMyVektor gradientenVerfahren(CMyVektor x, double (*funktion)(CMyVektor x), double lambda, int schritte);
	CMyVektor newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x), int schritte);


};
