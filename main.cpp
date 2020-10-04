#include <cmath>
#include <iostream>

using std::cout;

double f(const double x) {
    return cos(x) * tanh(x);
}

double f_(const double x) {
    return f(x) * sin(5*x);
}


const double LOWER = -2.;
const double UPPER = 0.;
const double P_VALUES[] = {0.9, 0.91, 0.92, 0.93, 0.94,
                           0.95, 0.96, 0.97, 0.98, 0.99};
const double Q_VALUES[] = {0.005, 0.01, 0.015, 0.02, 0.025,
                           0.03, 0.035, 0.04, 0.045, 0.05,
                           0.055, 0.06, 0.065, 0.07, 0.075,
                           0.08, 0.085, 0.09, 0.095, 0.1};

int main() {

    return 0;
}
