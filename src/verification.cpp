#include <cstdlib>
#include <iostream>
#include "verification.h"

/*****************************************************************************/

/* Vérification que le résultat de notre factorisation est correct.
 */

bool checkCorrect( double* A, double* L, double* U, int M, int N ){

    bool rc;
    
    /* Premier test : est-ce que les matrices sont bien triangulaires */

    rc = isUpper( U, M, M );
    if( !rc ) return false;

    rc = isLower( L, M, M );
    if( !rc ) return false;

    /* Deuxième test : est-ce que L*U donne A */

    double* tmp = (double*) malloc( M*N*sizeof( double ) );
    matmult( tmp, L, U, M, N, N );
    rc = matEqual( tmp, A, M, N );

    free( tmp );
    return rc;
}

/*****************************************************************************/

/* Teste si la matrice est triangulaire supérieure.
*/

bool isUpper( double* A, int M, int N ){
    for( auto i = 0 ; i < M ; i++ ){
        for( auto j = 0 ; j < i ; j++ ){
            if( ! isEqual( A[i*N + j], 0, PRECISION ) ) return false;            
        }
    }
    return true;    
}

/*****************************************************************************/

/* Teste si la matrice est triangulaire inférieure.
*/

bool isLower( double* A, int M, int N ){
    for( auto i = 0 ; i < M ; i++ ){
        for( auto j = i+1 ; j < N ; j++ ){
            if( ! isEqual( A[i*N + j], 0, PRECISION ) ) return false;            
        }
    }
    return true;    
}

/*****************************************************************************/

/* Teste si deux matrices sont égales à une certaine précision près.
 */

bool matEqual( double* A, double* B, int M, int N ){
    for( auto i = 0 ; i < M ; i++ ){
        for( auto j = 0 ; j < N ; j++ ){
            if( ! isEqual( A[i*N + j], B[i*N+j], PRECISION ) ) return false;            
        }
    }
    return true;
}

/*****************************************************************************/

/* Teste si deux valeurs sont égales à une certaine précision près.
 */

bool isEqual( double a, double b, double precision ){
    return abs( a - b ) < precision;    
}

/*****************************************************************************/

/* Multiplie une matrice L de taille M * N
   par une matrice U de taille N * K
   et met le résultat dans une matrice res de taille M * K
*/

void matmult( double* res, double* L, double* U, int M, int N, int K ){
    
    for( auto i = 0 ; i < M ; i++ ){ 
        for( auto j = 0 ; j < K ; j++ ){
            res[i * N + j ] = 0.0;
            for( auto k = 0 ; k < N ; k++ ){
                res[i * K + j ] += L[ i * N + k ] * U[ k * K + j ];
            }
        }
    }
}
