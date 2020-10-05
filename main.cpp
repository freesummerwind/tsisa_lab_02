#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using std::cout;

double f(const double x) {
    return cos(x) * tanh(x);
}

double f_(const double x) {
    return f(x) * sin(5*x);
}

void printLine() {
    cout << '+' << std::string(7, '-') << '+' << std::string(6, '-')
         << '+' << std::string(6, '-') << '+' << std::string(6, '-')
         << '+' << std::string(6, '-') << '+' << std::string(6, '-')
         << '+' << std::string(6, '-') << '+' << std::string(6, '-')
         << '+' << std::string(6, '-') << '+' << std::string(6, '-')
         << '+' << std::string(6, '-') << '+' << '\n';
}

void printTableHead(const std::vector<double>& p) {
    printLine();

    cout << '|' << std::setw(5) << "q/P" << std::setw(3) << '|';
    for(auto item : p) cout << std::setw(5) << item << " |";
    cout << '\n';

    printLine();
}

void printTable(const std::vector<double>& p, const std::vector<double>& q,
        const std::vector<std::vector<int>>& table) {
    printTableHead(p);

    for(size_t i = 0; i < q.size(); ++i) {
        cout << '|' << std::setw(6) << q[i] << " |";
        for(size_t j = 0; j < p.size(); ++j) {
            cout << std::setw(5) << table[i][j] << " |";
        }
        cout << '\n';
    }

    printLine();
}

std::vector<std::vector<int>> pointsNumber(const std::vector<double>& p, const std::vector<double>& q) {
    std::vector<std::vector<int>> points(q.size());
    for(size_t i = 0; i < q.size(); ++i) {
        points[i].resize(p.size());
        for(size_t j = 0; j < p.size(); ++j) {
            points[i][j] = ceil(std::log(1 - p[j]) / std::log(1 - q[i]));
        }
    }

    printTable(p, q, points);

    return points;
}

double randomInRange(const double lower, const double upper) {
    return lower + rand() * 1./RAND_MAX * (upper - lower);
}

const double LOWER = -2.;
const double UPPER = 0.;
const std::vector<double> P_VALUES = {0.9, 0.91, 0.92, 0.93, 0.94,
                           0.95, 0.96, 0.97, 0.98, 0.99};
const std::vector<double> Q_VALUES = {0.005, 0.01, 0.015, 0.02, 0.025,
                           0.03, 0.035, 0.04, 0.045, 0.05,
                           0.055, 0.06, 0.065, 0.07, 0.075,
                           0.08, 0.085, 0.09, 0.095, 0.1};

int main() {

    auto points = pointsNumber(P_VALUES, Q_VALUES);

    return 0;
}
