#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
	cx_mat A = randu<cx_mat>(5,5);
	cx_vec b = randu<cx_vec>(5);
	cx_vec x = solve(A,b);
	
	
	cout << "Matriz A : " << endl;
	cout << A << endl;
	
	cout << "Vetor B : " << endl;
	cout << b << endl;
	
	
	cout << "Solução Ax = B, X = : " << endl;
	cout << x << endl;
	
	cout << "Testando solução A*x = " << endl;
	cout << A*x << endl;
	
	return 0;

}
