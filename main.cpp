#include "C_DGLSolver.h"
#include <iostream>
using namespace std;

CMyVektor DGLSystem(CMyVektor y, double x)
{
	CMyVektor result;
	result.set_dimension(2, 0);
	result[0] = (2.0 * y[1]) - (x * y[0]);
	result[1] = (y[0] * y[1]) - (2.0 * (x * x * x));
	return result;
}

double DGLdritterOrdnung(CMyVektor y, double x)
{
	double result = (2.0 * x * y[1] * y[2]) + (2.0 * (y[0] * y[0]) * y[1]);
	return result;
}

int main() {

	C_DGLSolver dgl(DGLSystem);
	CMyVektor y;
	y.set_dimension(2, 0); y[0] = 0; y[1] = 1;
	int schritte = 10;
	vector<double> v_eul;
	vector<double> v_heun;

	while (schritte < 1000)
	{
		v_eul.push_back((dgl.euler(0, 2, 100, y)[0]) - 0.5);
		//v_heun.push_back((dgl.heun(0, 2, 100, y)[0]) - 0.5);
		schritte *= 10;
	}


/*
	C_DGLSolver dgl(DGLdritterOrdnung);
	CMyVektor y;
	y.set_dimension(3, 0); y[0] = 1; y[1] = -1; y[2] = 2;
	int schritte = 10;
	vector<double> v_eul;
	vector<double> v_heun;
	
	std::cout.setstate(std::ios_base::failbit);
	while (schritte<=10000)
	{
		v_eul.push_back((dgl.euler(1, 2, schritte, y)[0]) - 0.5);
		v_heun.push_back((dgl.heun(1, 2, schritte, y)[0]) - 0.5);
		schritte *= 10;
	}
	std::cout.clear();

	
	auto it1 = v_eul.begin();
	auto it2 = v_heun.begin();
	schritte = 10;
	
	while (it1!=v_eul.end()&&it2!=v_heun.end())
	{
		cout << "Abweichung bei Euler bei " << schritte << " Schritten: " << *it1 << endl;
		cout << "Abweichung bei Heun bei " << schritte << " Schritten: " << *it2 << endl;
		schritte *= 10;
		it1++;
		it2++;
	}
	*/
}