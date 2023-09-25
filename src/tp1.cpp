#include "tp1.h"
#include <iostream>
#include <vector>

using namespace std;

void gauss(double* a, double* b, double* x, int n, int m) {
    // Implementation of the gauss function goes here
    // You can use a, b, x, n, and m as needed.
}


std::string monnom() {
    return "Olivier Fontaine"; 
}

typedef vector<vector<double>> Matrix;

// Fonction pour effectuer la factorisation LU
void factorisationLU(const Matrix& A, Matrix& L, Matrix& U) {
    int n = A.size();
    L.resize(n, vector<double>(n, 0.0));
    U.resize(n, vector<double>(n, 0.0));

    // Décomposition LU
    for (int i = 0; i < n; i++) {
        // Matrice U
        for (int k = i; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        // Matrice L
        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1.0;
            } else {
                double sum = 0.0;
                for (int j = 0; j < i; j++) {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

int main() {
    // Exemple d'utilisation
    Matrix A = {{2.0, 1.0, 1.0},
                {4.0, 3.0, 3.0},
                {8.0, 7.0, 9.0}};

    Matrix L, U;
    factorisationLU(A, L, U);

    // Affichage des matrices L et U
    cout << "Matrice L :" << endl;
    for (const auto& row : L) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "Matrice U :" << endl;
    for (const auto& row : U) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}