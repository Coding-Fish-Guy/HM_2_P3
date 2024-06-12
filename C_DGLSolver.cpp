#include "C_DGLSolver.h"
#include <iostream>
using namespace std;

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x) {

	CMyVektor sys;
	if (boolean_DGL_System)
	{
		sys = f_DGL_System(y, x);
	}
	else
	{
		int n = y.get_dimension();
		sys.set_dimension(n, 0);
		sys[n - 1] = f_DGL_nterOrdnung(y, x);
		
		for (int i = 0; i<n-1;i++)
		{
			sys[i] = y[i+1];
		}
	}
	return sys;
}


CMyVektor C_DGLSolver::euler(double x_start, double x_end, int schritte, CMyVektor y_start) 
{
	CMyVektor eul(y_start);
	CMyVektor ab = ableitungen(eul, x_start);

	double diff = x_end - x_start;
	double x = x_start;
	double weite_h = diff / (double)schritte;
	
	std::cout << "h = " << weite_h << endl << endl;
	for (int i = 0; i < schritte; i++)
	{
		
		x = x_start+(diff*i)/(double)schritte ;
		ab = ableitungen(eul, x);
		std::cout << "Schritt " << i << " :" << endl;
		std::cout << "\t x = " << x << endl;
		std::cout << "\t y = " << eul << endl;
		std::cout << "\t y'= " << ab << endl;

		eul += ableitungen(eul, x) * weite_h;
		
		int k = i;
		if (k + 1 == schritte)
		{
			x = (diff * ++k) / (double)schritte + x_start;
			std::cout << "Ende bei " << endl;
			std::cout << "\t x = " << x << endl;
			std::cout << "\t y = " << eul << endl;
		}
	}
	return eul;
}

CMyVektor C_DGLSolver::heun(double x_start, double x_end, int schritte, CMyVektor y_start) {

	CMyVektor heun(y_start);
	CMyVektor ab = ableitungen(heun, x_start);
	CMyVektor yt(y_start);
	CMyVektor yt_ab(y_start);
	CMyVektor y_mittel(y_start);

	double x = x_start;
	double diff = x_end - x_start;
	double weite_h = diff / (double)schritte;
	
	std::cout << "h = " << weite_h << endl << endl;
	for (int i = 0; i < schritte; i++)
	{
		x = (diff * i) / (double)schritte + x_start;
		ab = ableitungen(heun, x);
		yt= heun + ableitungen(heun, x) * weite_h;
		yt_ab = ableitungen(yt, x+ weite_h);
		y_mittel = (ab + yt_ab) * 0.5;
		
		std::cout << "Schritt " << i << " :" << endl;
		std::cout << "\t x = " << x << endl;
		std::cout << "\t y = " << heun << endl;
		std::cout << "\t y'_orig = " << ab << endl<<endl;
		std::cout << "\t y_Test = " << yt << endl;
		std::cout << "\t y'_Test = " << yt_ab << endl<<endl;
		std::cout << "\t y'_Mittel " << y_mittel << endl;

		heun +=  y_mittel * weite_h;
		x += weite_h;

		int k = i;
		if (k + 1 == schritte)
		{
			x = (diff * ++k) / (double)schritte + x_start;
			std::cout << "Ende bei " << endl;
			std::cout << "\t x = " << x << endl;
			std::cout << "\t y = " << heun << endl;
		}
	}
	return heun;
}