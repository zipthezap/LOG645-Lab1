#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <dlfcn.h>
#include <x86intrin.h>

#include "verification.h"
#include "tp1.h"

#define FUNC_NOM "monnom"
#define FUNC_GAUSS "gauss"
#define DEFAULTM 16
#define DEFAULTN 16
#define SEED 0
#define NBREP 10

#define RAND(a,b) a + ( ( b - a + 1 ) * (double)rand() ) / (double) RAND_MAX

namespace fs = std::filesystem;

typedef std::string (*func_name_t)(void);
typedef void (*func_gauss_t) (double*, double*, double*, int, int );

bool openLib( std::string, int, int );
void testFunction( func_gauss_t, int, int );
double performance( func_gauss_t, int, int );
void initMatrix( double*, int, int );
void initMatrices( double*, double*, double*, int, int );

int main( int argc, char** argv ){

    std::string path = ".";
    std::string libpath;
    bool rc;
    int M = DEFAULTM, N = DEFAULTN;

    if( argc > 1 ){
        M = std::atoi( argv[1] );
        if( argc > 2 ){
            N = std::atoi( argv[2] );
        } else {
            N = M;
        }
    } 

    for( const auto & entry : fs::directory_iterator( path ) ){

        /* On ouvre tous les sous-répertoires du répertoire courant */

        if( fs::is_directory( entry  )){
            std::cout << "J'entre dans le répertoire " << entry.path() << std::endl;

            /* On ouvre la lib, et on la teste */

            libpath = entry.path().string() + std::string( "/libtp1.so" );
            rc = openLib( libpath, M, N );
        }
    }

    return EXIT_SUCCESS;
}

/*****************************************************************************/

/* Teste une librairie : l'ouvre, teste la fonction, et mesure la performance.
 */

bool openLib( std::string libpath, int M, int N ){
    void* found;
    func_name_t  func_nom;
    func_gauss_t func_gauss;

    /* J'ouvre la lib */
    
    void* handle = dlopen( libpath.c_str(), RTLD_LAZY );
    if( !handle ){
        std::cout << "Je n'arrive pas à ouvrir la bibliothèque " << libpath << "." << std::endl;
        return false;
    }
    
    /* Je cherche les deux fonctions qui m'intéressent */
    
    found = dlsym( handle, FUNC_NOM );
    if( !found ){
        std::cout << "La fonction " << FUNC_NOM << " est manquante." << std::endl;
    } else {
        func_nom   = (func_name_t) found; 
        std::cout << func_nom() << "\t";
    }
    found = dlsym( handle, FUNC_GAUSS );
    if( !found ){
        std::cout << -1 << "\t La fonction " << FUNC_GAUSS << " est manquante." << std::endl;
    } else {
        func_gauss = (func_gauss_t) found;
        testFunction( func_gauss, M, N );
    }
    
    dlclose( handle );
    return true;
}

/*****************************************************************************/

/* Teste la correction de la fonction
 */

void testFunction( func_gauss_t gaussfun, int M, int N ){
    double* A = (double*) malloc( M*N*sizeof( double ) );
    double* L = (double*) malloc( M*M*sizeof( double ) );
    double* U = (double*) malloc( M*N*sizeof( double ) );
    double res = -1;
    
    /* On initialise toutes les matrices. */

    initMatrices( A, L, U, M, N );

    /* On appelle une première fois */

    gaussfun( A, L, U, M, N );
    
    /* On vérifie que le résultat est correct */

    if( checkCorrect( A, L, U, M, N ) ){
        std::cout << "Le résultat est correct :-)\t";

        /* On mesure la performance */

        res = performance( gaussfun, M, N );
        std::cout << res << std::endl;
        
    } else {
        std::cout << "Le résultat est faux    :-(" << std::endl;
    }

    /* On a fini, on libère tout */

    free( A );
    free( L );
    free( U );
}

/*****************************************************************************/

/* Mesure la performance de la fonction
 */

double performance( func_gauss_t gaussfun, int M, int N ){
    double* A = (double*) malloc( M*N*sizeof( double ) );
    double* L = (double*) malloc( M*M*sizeof( double ) );
    double* U = (double*) malloc( M*N*sizeof( double ) );
    double perf = 0.0;
    
    /* On initialise toutes les matrices. */

    initMatrices( A, L, U, M, N );

    /* On appelle une première fois (échauffement) */

    gaussfun( A, L, U, M, N );

    for( auto i = 0 ; i < NBREP ; i++ ){

        /* On reset U et L */

        initMatrix( L, M, M );
        initMatrix( U, M, N );

        /* Et on exécute */

        auto start = __rdtsc();
        gaussfun( A, L, U, M, N );
        auto end = __rdtsc();

        perf += ( end - start );        
    }
    
    /* On a fini, on libère tout */

    free( A );
    free( L );
    free( U );

    return perf;
}

/*****************************************************************************/

/* On initialise la matrice A. On initialise aussi L et U, parce qu'on ne fait 
   pas d'hypothèse sur ce qu'elles contiennent. 
   Tout le monde a la même graine. 
*/

void initMatrices( double* A, double* L, double* U, int M, int N ){
    srand( SEED );
    initMatrix( A, M, N );
    initMatrix( L, M, M );
    initMatrix( U, M, N );
}

/*****************************************************************************/

/* Initialise une matrice avec des valeurs aléatoires.
*/

void initMatrix( double* mat, int lines, int cols ){
    for( int i = 0 ; i < lines*cols ; i++ ){
        mat[i] = RAND( -100, 100 );
    }
}

