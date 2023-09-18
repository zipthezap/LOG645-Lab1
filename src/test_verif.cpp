#include <cstdlib>
#include <iostream>

#include "verification.h"

/* Programme qui teste les tests de correction */

int main( ){

    double A[16]{             9, 3, 5, 1,
            5, 7, 8, 2,
            3, 3, 7, 1,
            2, 6, 3, 6,
            };

    /* Obtenus avec Octave */

    double L_res[16] = { 1.0, 0, 0, 0, 
        0.5556, 1.0, 0, 0,
        0.3333,   0.3750,   1.0, 0,
        0.2222,   1.0, -0.9877, 1.0 };

    double U_res[16] = {9.0, 3.0, 5.0, 1.0,
        0,   5.3333,   5.2222,   1.4444,
        0,        0,   3.3750,   0.1250,
        0,        0,        0,   4.4568 };

    double identity[16] = { 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};
    
    bool b;

    std::cout << "oui est " << true << ", non est " << false << std::endl;
    
    b = isUpper( U_res, 4, 4 );
    std::cout << "U triangulaire supérieure ? (normalement oui) " << b << std::endl;

    b = isLower( L_res, 4, 4 );
    std::cout << "L triangulaire inférieure ? (normalement oui) " << b << std::endl;

    b = isUpper( A, 4, 4 );
    std::cout << "A triangulaire supérieure ? (normalement non) " << b << std::endl;

    b = isLower( A, 4, 4 );
    std::cout << "A triangulaire inférieure ? (normalement non) " << b << std::endl;

    b = checkCorrect( A, L_res, U_res, 4, 4 );
    std::cout << "Résultat du calcul correct ? (normalement oui c'est Octave qui l'a fait) " << b << std::endl;
    
    b = checkCorrect( A, identity, U_res, 4, 4 );
    std::cout << "Un autre résultat correct ? (normalement non) " << b << std::endl;
    
    return EXIT_SUCCESS;
}
