#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <omp.h>
#include <ctime>
#include <string>
#include <time.h>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>


using namespace std;

void countSort(int array[], int size);

std::vector<std::string> splitLinea(std::string linea) {
    // Se inicializa vector de tipo string, el cual será el que retornará la función
    std::vector<std::string> resultado;

    // Se inicializa variable tipo string en la cual se almacenarán cada puntaje
    std::string valor;
    // Bucle for que recorrerá la linea leída desde el archivo
    for (int i = 0; i < linea.length(); i++) {
        // Se evalúa si la posicion i de linea es igual al caracter ';'
        if (linea[i] == ';') {
            // Si la condición de cumple, se añade el elemento 'valor' al final del vector 'resultado'
            resultado.push_back(valor);
            // Se vacia el contenido del string 'valor'
            valor.clear();
        } else {
            // Se concatenan digitos. ejem: "1", "12", "123"
            valor += linea[i];
        }
    }
    resultado.push_back(valor);
    // Retorna el vector con los puntajes
    return resultado;
}


// Counting sort in C++ programming

int main(int arc, char** argv) {

    std::ifstream archivoLee(argv[1]);
    std::string linea;



    // datos 0=rut 1=nem 2=ranking 3=matematica 4=lenguaje 5=ciencias 6=historia
    std::vector<std::string> datos;
    unsigned int promedio1, promedio2, promedio3, promedio4, promedio5, promedio6;
    // cantidad de lineas para calcular promedio y otros
    float cantLinea = 0;

    //Se crea el arreglo que contendra los datos
    //vector<int> arreglo;

    std::vector<unsigned int> arreglo1, arreglo2, arreglo3, arreglo4, arreglo5, arreglo6;
    arreglo1.clear();
    arreglo2.clear();
    arreglo3.clear();
    arreglo4.clear();
    arreglo5.clear();
    arreglo6.clear();

    // ciclo que ejecuta mientras el archivo tenga lineas

    int aux1, aux2, aux3, aux4, aux5, aux6;
    while (getline(archivoLee, linea)) {

        datos = splitLinea(linea);


        // CALCULO DE PROMEDIOS
        cantLinea += 1;
        
        
        // Se llenan auxiliares
        aux1 = (std::stoi(datos[1]));
        aux2 = (std::stoi(datos[2]));
        aux3 = (std::stoi(datos[3]));
        aux4 = (std::stoi(datos[4]));
        aux5 = (std::stoi(datos[5]));
        aux6 = (std::stoi(datos[6]));

        // Arreglos con datos 0=rut 1=nem 2=ranking 3=matematica 4=lenguaje 5=ciencias 6=historia
        arreglo1.push_back(aux1);
        arreglo2.push_back(aux2);
        arreglo3.push_back(aux3);
        arreglo4.push_back(aux4);
        arreglo5.push_back(aux5);
        arreglo6.push_back(aux6);

        // Promedio nem
        promedio1 += aux1;        
        
        
        // Promedio ranking
        promedio2 += aux2;
        
        // Promedio matematica
        promedio3 = promedio3 + aux3;
       
        // Promedio lenguaje
        promedio4 = promedio4 + aux4;
        
        // promedio ciencias
        promedio5 += aux5;
        
        // Promedio historia
        promedio6 += aux6;

    }
    archivoLee.close();

//    cout << "Promedio nem: " << datos[1] << endl;
//    cout << "Promedio nem: " << datos[2] << endl;
//    cout << "Promedio nem: " << datos[3] << endl;
//    cout << "Promedio nem: " << datos[4] << endl;
//    cout << "Promedio nem: " << datos[5] << endl;
//    cout << "Promedio nem: " << datos[6] << endl;
//    cout << "############################################" << endl;
//    
//    cout << "Promedio nem: " << promedio1 << endl;
//    
//    cout << "Promedio nem: " << promedio2 << endl;
//    
//    cout << "Promedio nem: " << promedio3 << endl;
//    
//    cout << "Promedio nem: " << promedio4 << endl;
//    
//    cout << "Promedio nem: " << promedio5 << endl;
//    
//    cout << "Promedio nem: " << promedio6 << endl;
//    
//    cout << "############################################" << endl;
    float prom1 = promedio1/cantLinea;
    float prom2 = promedio2/cantLinea;
    float prom3 = promedio3/cantLinea;
    float prom4 = promedio4/cantLinea;
    float prom5 = promedio5/cantLinea;
    float prom6 = promedio6/cantLinea;

//    cout << "Promedio nem: " << prom1 << endl;
//    cout << "Promedio ranking: " << prom2 << endl;
//    cout << "Promedio matematicas: " << prom3 << endl;
//    cout << "Promedio lenguaje: " << prom4 << endl;
//    cout << "Promedio ciencias: " << prom5 << endl;
//    cout << "Promedio historia: " << prom6 << endl;

    cout << "catnidad de lineas: " << cantLinea << endl;
    
    arreglo1.clear();
    arreglo2.clear();
    arreglo3.clear();
    arreglo4.clear();
    arreglo5.clear();
    arreglo6.clear();
    



    // Desviacion estandar
    float des1 = 0, des2 = 0, des3 = 0, des4 = 0, des5 = 0, des6 = 0;

    for (int i = 0; i <= cantLinea; i++) {

        des1 += pow((arreglo1[i] - prom1), 2) / (cantLinea - 1);
        des2 += pow((arreglo2[i] - prom2), 2) / (cantLinea - 1);
        des3 += pow((arreglo3[i] - prom3), 2) / (cantLinea - 1);
        des4 += pow((arreglo4[i] - prom4), 2) / (cantLinea - 1);
        des5 += pow((arreglo5[i] - prom5), 2) / (cantLinea - 1);
        des6 += pow((arreglo6[i] - prom6), 2) / (cantLinea - 1);
    }

    des1 = sqrt(des1);
    des2 = sqrt(des2);
    des3 = sqrt(des3);
    des4 = sqrt(des4);
    des5 = sqrt(des5);
    des6 = sqrt(des6);
//
//    cout << "Desviacion estandar nem: " << des1 << endl;
//    cout << "Desviacion estandar ranking: " << des2 << endl;
//    cout << "Desviacion estandar matematicas: " << des3 << endl;
//    cout << "Desviacion estandar lenguaje: " << des4 << endl;
//    cout << "Desviacion estandar ciencias: " << des5 << endl;
//    cout << "Desviacion estandar historia: " << des6 << endl;
    
    
    
    cout << "===Nem===\n" << "Promedio: " << prom1 << "\n" << "Desviacion estandar: " << des1 << endl;
    cout << "===Ranking===\n" << "Promedio: " << prom2 << "\n" << "Desviacion estandar: " << des2 << endl;
    cout << "===Matematica===\n" << "Promedio: " << prom3 << "\n" << "Desviacion estandar: " << des3 << endl;
    cout << "===Lenguaje===\n" << "Promedio: " << prom4 << "\n" << "Desviacion estandar: " << des4 << endl;
    cout << "===Ciencias===\n" << "Promedio: " << prom5 << "\n" << "Desviacion estandar: " << des5 << endl;
    cout << "===Historia===\n" << "Promedio: " << prom6 << "\n" << "Desviacion estandar: " << des6 << endl;
    cout << "===Integrantes===\nLucas Carmona.\nYerko Foncea.\nBrayan Parra." << endl;


}

void countSort(std::vector<unsigned int> array, int size) {
    // The size of count must be at least the (max+1) but
    // we cannot assign declare it as int count(max+1) in C++ as
    // it does not support dynamic memory allocation.
    // So, its size is provided statically.
    int output[10];
    int count[10];
    int max = array[0];

    // Find the largest element of the array
    for (int i = 1; i < size; i++) {
        if (array[i] > max)
            max = array[i];
    }

    // Initialize count array with all zeros.
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }
}



