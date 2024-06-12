#pragma once
#include "CMyVector.h"

class C_DGLSolver {

private:
	CMyVektor(*f_DGL_System)(CMyVektor y, double x);
	double (*f_DGL_nterOrdnung)(CMyVektor y, double x);
	bool boolean_DGL_System = false;
	CMyVektor ableitungen(CMyVektor y, double x);

public:
	~C_DGLSolver()= default;
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x)) :f_DGL_System{ f_DGL_System }, boolean_DGL_System{ true }{};
	C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x)) : f_DGL_nterOrdnung{ f_DGL_nterOrdnung }, boolean_DGL_System{ false }{};

	CMyVektor euler(double x_start, double x_end, int schritte, CMyVektor y_start);
	CMyVektor heun(double x_start, double x_end, int schritte, CMyVektor y_start);
};