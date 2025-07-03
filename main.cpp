#include <iostream>
#include <fstream>
#include<cmath>
#include <vector>
#include <string>

using namespace std;

float wielomian_interpolacji(int n, vector<float> xi_column, vector<float> fxi_column, float x) {
    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        float li = 1.0;
        // Calculate Lagrange basis polynomial Li(x)
        for (int j = 0; j < n; j++) {
            if (j != i) {
                li *= (x - xi_column[j]) / (xi_column[i] - xi_column[j]);
            }
        }
        sum += li * fxi_column[i];
    }
    return sum;
}

float MES(int n, vector<float> xi_column_bez_w, vector<float> fxi_column_bez_w, vector<float> xi_column, vector<float> fxi_column, int nodes) {
    float diff = 0;
    for (int i = 0; i < n; i++) {
        float xi = xi_column_bez_w[i];
        float fxi = fxi_column_bez_w[i];

        float fxi_inter = wielomian_interpolacji(nodes, xi_column, fxi_column, xi);
        diff += pow(fxi - fxi_inter, 2);
    }
    float mse = diff / n;
    cout << "mse dla " << nodes << " to: " << mse << endl;
    return mse;
}

float function(float x) {
    float y = 1 / (1 + (float)pow(x, 2));
    return y;
}

void dodatkowe() {
    vector<float> x({ -5., -4., -3., -2., -1., 0., 1., 2., 3., 4., 5. });
    vector<float> y;

    for (int j = 0; j < x.size(); j++) {
        y.push_back(function(x[j]));
    }

    int min_node = INT_MAX;
    float min_mse = INT_MAX;

    // Test different numbers of interpolation nodes
    for (int i = x.size() - 1; i > 0; i--) {
        vector<float> x_sub(x.begin(), x.begin() + i);
        vector<float> y_sub(y.begin(), y.begin() + i);

        vector<float> x_rest(x.begin() + i, x.end());
        vector<float> y_rest(y.begin() + i, y.end());

        float mse = MES(i, x_sub, y_sub, x_rest, y_rest, x.size() - i);
        if (mse < min_mse) {
            min_mse = mse;
            min_node = x.size() - i;
        }
        cout << "MSE DLA " << x.size() - i << " rowne: " << mse << endl;
    }

    cout << "najmniejsze mse jest dla " << min_node << " wezlow rowne: " << min_mse;
}

int main() {
    ifstream myfile("dane.txt");
    if (!myfile.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return 1;
    }

    vector<float> xi_column, fxi_column;
    vector<float> xi_column_bez_w, fxi_column_bez_w;
    string tmp;

    // Read xi values
    while (myfile >> tmp) {
        if (tmp == "xi:") break;
    }

    int x = 0;
    int next = 0;
    float value;
    while (myfile >> value) {
        if (next == x) {
            xi_column.push_back(value);
            x += 5;
        }
        else {
            xi_column_bez_w.push_back(value);
        }
        next += 1;
        if (myfile.peek() == '\n') break;
    }

    x = 0;
    next = 0;

    // Read f(xi) values
    while (myfile >> tmp) {
        if (tmp == "f(xi):") break;
    }

    while (myfile >> value) {
        if (next == x) {
            fxi_column.push_back(value);
            x += 5;
        }
        else {
            fxi_column_bez_w.push_back(value);
        }
        next += 1;
        if (myfile.peek() == '\n') break;
    }

    size_t n = min(xi_column.size(), fxi_column.size());

    cout << "xi" << "         " << "f(xi)" << endl;
    for (size_t i = 0; i < n; i++) {
        cout << xi_column[i] << "   " << fxi_column[i] << endl;
    }
    myfile.close();

    dodatkowe();
    return 0;
}