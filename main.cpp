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
    cout << '+' << std::string(7, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << '\n';
}

void printTableHead(const std::vector<double>& p) {
    printLine();

    cout << '|' << std::setw(5) << "q/P" << std::setw(3) << '|';
    for(auto item : p) cout << std::setw(9) << item << " |";
    cout << '\n';

    printLine();
}

void printTable(const std::vector<double>& p, const std::vector<double>& q,
        const std::vector<std::vector<double>>& table) {
    printTableHead(p);

    for(size_t i = 0; i < q.size(); ++i) {
        cout << '|' << std::setw(6) << q[i] << " |";
        for(size_t j = 0; j < p.size(); ++j) {
            cout << std::setw(9) << table[i][j] << " |";
        }
        cout << '\n';
    }

    printLine();
}

std::vector<std::vector<double>> pointsNumber(const std::vector<double>& p,
        const std::vector<double>& q) {
    std::vector<std::vector<double>> points(q.size());
    for(size_t i = 0; i < q.size(); ++i) {
        points[i].resize(p.size());
        for(size_t j = 0; j < p.size(); ++j) {
            points[i][j] = ceil(std::log(1 - p[j]) / std::log(1 - q[i]));
        }
    }

    return points;
}

double randomInRange(const double lower, const double upper) {
    return lower + rand() * 1./RAND_MAX * (upper - lower);
}

template<class Function>
std::vector<std::vector<double>> randomSearch(
        const std::vector<std::vector<double>>& numbers,
        const double lower, const double upper, Function func) {
    std::vector<std::vector<double>> table;
    table.resize(numbers.size());
    for(size_t i = 0; i < table.size(); ++i) {
        table[i].resize(numbers[i].size());
        for(size_t j = 0; j < table[i].size(); ++j) {
            table[i][j] = func(lower);
            for(size_t k = 0; k < numbers[i][j]; ++k) {
                double newValue = func(randomInRange(lower, upper));
                if(newValue < table[i][j]) {
                    table[i][j] = newValue;
                }
            }
        }
    }

    return table;
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
    cout << "Variant 4.\nFunction 1: cos(x)*th(x)\nInterval: ["
        << LOWER << " " << UPPER << "]\n"
        << "Function 2: cos(x)*th(x)*sin(5*x)\nInterval: ["
        << LOWER << " " << UPPER << "]\n";

    cout << "Table with number of points for each p and q:\n";
    auto points = pointsNumber(P_VALUES, Q_VALUES);
    printTable(P_VALUES, Q_VALUES, points);

    srand(time(nullptr));
    auto valuesForF = randomSearch(points, LOWER, UPPER, f);
    cout << "Table for function 1:\n";
    printTable(P_VALUES, Q_VALUES, valuesForF);
    auto valuesForF_ = randomSearch(points, LOWER, UPPER, f_);
    cout << "Table for function 2:\n";
    printTable(P_VALUES, Q_VALUES, valuesForF_);

    return 0;
}
