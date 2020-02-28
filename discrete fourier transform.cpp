#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>
#define N 4

using namespace std;
int main(){
    
    double E = exp(1.0);
    double x[N] = {1.0, 0.0, 0.0, 1.0};
    complex <double> j = {0.0, 1.0};

    for(int k = 0; k < N; k++){
        complex <double> sum = {0.0, 0.0};
        for(int i = 0; i < N; i++){
            sum += x[i]*pow(E, -j*double(k)*double(i)*2.0*M_PI/double(N));             
        }
        cout << sum << endl;
    }
    return 0;
}