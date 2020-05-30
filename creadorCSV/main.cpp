#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <random>


using namespace std;

int main() {
    ofstream file("puntajes.csv");
    srand((unsigned int) time(0));
    int nem, ranking, matematica, lenguaje, ciencias, historia;
#pragma omp parallel 
    {
#pragma omp for
        for (int i = 14916641; i <= 19932391; i++) {
            nem = (rand() % 225 + 475);
            ranking = (rand() % 225 + 475);
            matematica = (rand() % 225 + 475);
            lenguaje = (rand() % 225 + 475);
            ciencias = (rand() % 225 + 475);
            historia = (rand() % 225 + 475);
                    
#pragma omp critical
                    file << i << ";" << nem << ";" << ranking << ";" << matematica << ";" << lenguaje << ";" << ciencias << ";" << historia << endl;

        }
    }
    cout << "Termino" << endl;
    file.close();
    return 0;
}
