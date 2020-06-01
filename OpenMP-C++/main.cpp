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
#include <omp.h>

using namespace std;



void countSort(int array[], int size);
std::vector<unsigned int> splitLinea(std::string linea);
int moda(vector<unsigned int> arr, int largo);
void quickSort(vector<unsigned int> *arreglo, int inicio, int fin);
float mediana(vector<unsigned int> arr, int largo);

int main(int arc, char** argv) {

    // Se abre el archivo en modo lectura y se le da el parametro que se recibe por la terminal,
    // este corresponde a la direccion donde se encuentra el archivo csv
    std::ifstream archivoLee(argv[1]);
    std::string linea;

    // datos 0=rut 1=nem 2=ranking 3=matematica 4=lenguaje 5=ciencias 6=historia
    // Esti es global para pracitvamente todos los indices de las variables
    std::vector<unsigned int> datos;

    // Sumas de cada puntaje en vector 0=rut(No los suma) 1=nem 2=ranking 3=matematica 4=lenguaje 5=ciencias 6=historia
    std::vector<unsigned int> sumasPtjs;
    std::vector<unsigned int> modas;
    std::vector<float> medianas;

    for (int i = 0; i < 7; i++) {
        sumasPtjs.push_back(0);
        modas.push_back(0);
        medianas.push_back(0);
    }
    // cantidad de lineas para calcular promedio y otros
    float cantLinea = 0;

    //Se crea el arreglo que contendra los datos
    //vector<int> arreglo;

    std::vector<unsigned int> arreglo1, arreglo2, arreglo3, arreglo4, arreglo5, arreglo6;



    // Auxiliares que reciviran los valores cada linea que se lee.
    int aux1, aux2, aux3, aux4, aux5, aux6;


    // ciclo que ejecuta mientras el archivo tenga lineas
#pragma omp parallel
    {
#pragma omp single     
        for (linea; getline(archivoLee, linea);) {
            
            // CALCULO DE PROMEDIOS
#pragma omp task
            {
                cantLinea += 1;
                datos = splitLinea(linea);
            }
            // Se llenan auxiliares
#pragma omp taskwait
            {
                aux1 = (datos[1]);
                aux2 = (datos[2]);
                aux3 = (datos[3]);
                aux4 = (datos[4]);
                aux5 = (datos[5]);
                aux6 = (datos[6]);
            }

            // Limpia vector al que se le realiza el split con los datos de cada linea
#pragma omp taskwait
            {
                datos.clear();
            }

            // Arreglos con datos 0=rut 1=nem 2=ranking 3=matematica 4=lenguaje 5=ciencias 6=historia
#pragma omp taskwait
            {
                arreglo1.push_back(aux1);
                arreglo2.push_back(aux2);
                arreglo3.push_back(aux3);
                arreglo4.push_back(aux4);
                arreglo5.push_back(aux5);
                arreglo6.push_back(aux6);
            }
#pragma omp taskwait
            
            {
                // suma para el promedio nem
                sumasPtjs.at(1) += aux1;
                // suma para el promedio ranking
                sumasPtjs.at(2) += aux2;
                // suma para el promedio matematica
                sumasPtjs.at(3) += aux3;
                // suma para el promedio lenguaje
                sumasPtjs.at(4) += aux4;
                // suma para el promedio ciencias
                sumasPtjs.at(5) += aux5;
                // suma para el promedio historia
                sumasPtjs.at(6) += aux6;
            }
        }
    }

    cout << "termina de leer " << endl;


#pragma omp parallel
    {
        // ordenamiento del arreglos
#pragma omp single
        {
            #pragma omp task
            {quickSort(&arreglo1, 0, cantLinea - 1);}
            #pragma omp task
            {quickSort(&arreglo2, 0, cantLinea - 1);}
            #pragma omp task
            {quickSort(&arreglo3, 0, cantLinea - 1);}
            #pragma omp task
            {quickSort(&arreglo4, 0, cantLinea - 1);}
            #pragma omp task
            {quickSort(&arreglo5, 0, cantLinea - 1);}
            #pragma omp task
            {quickSort(&arreglo6, 0, cantLinea - 1);}
        }
        
    }
#pragma omp parallel
    {
#pragma omp single
        {
            //Calculo de modas
            #pragma omp task
            {modas.at(1) = moda(arreglo1, cantLinea);}
            #pragma omp task
            {modas.at(2) = moda(arreglo2, cantLinea);}
            #pragma omp task
            {modas.at(3) = moda(arreglo3, cantLinea);}
            #pragma omp task
            {modas.at(4) = moda(arreglo4, cantLinea);}
            #pragma omp task
            {modas.at(5) = moda(arreglo5, cantLinea);}
            #pragma omp task
            {modas.at(6) = moda(arreglo6, cantLinea);}            
        }
    }

#pragma omp parallel  
    {
#pragma omp single
        {
            //Calculo de medianas
            #pragma omp task
            {medianas.at(1) = mediana(arreglo1, cantLinea);}
            #pragma omp task
            {medianas.at(2) = mediana(arreglo1, cantLinea);}
            #pragma omp task
            {medianas.at(3) = mediana(arreglo1, cantLinea);}
            #pragma omp task
            {medianas.at(4) = mediana(arreglo1, cantLinea);}
            #pragma omp task
            {medianas.at(5) = mediana(arreglo1, cantLinea);}
            #pragma omp task
            {medianas.at(6) = mediana(arreglo1, cantLinea);}
        }
    }





archivoLee.close();


float prom1 = sumasPtjs.at(1) / cantLinea;
float prom2 = sumasPtjs.at(2) / cantLinea;
float prom3 = sumasPtjs.at(3) / cantLinea;
float prom4 = sumasPtjs.at(4) / cantLinea;
float prom5 = sumasPtjs.at(5) / cantLinea;
float prom6 = sumasPtjs.at(6) / cantLinea;

//    cout << "Promedio nem: " << prom1 << endl;
//    cout << "Promedio ranking: " << prom2 << endl;
//    cout << "Promedio matematicas: " << prom3 << endl;
//    cout << "Promedio lenguaje: " << prom4 << endl;
//    cout << "Promedio ciencias: " << prom5 << endl;
//    cout << "Promedio historia: " << prom6 << endl;

cout << "catnidad de lineas: " << cantLinea << endl;

// Desviacion estandar
float des1 = 0, des2 = 0, des3 = 0, des4 = 0, des5 = 0, des6 = 0;
int auxLinea = cantLinea;
#pragma omp parallel
#pragma omp single
for (int j = 0; j <= auxLinea; j += 1) {
#pragma omp task
    des1 += pow((arreglo1[j] - prom1), 2);
#pragma omp task        
    des2 += pow((arreglo2[j] - prom2), 2);
#pragma omp task
    des3 += pow((arreglo3[j] - prom3), 2);
#pragma omp task
    des4 += pow((arreglo4[j] - prom4), 2);
#pragma omp task
    des5 += pow((arreglo5[j] - prom5), 2);
#pragma omp task
    des6 += pow((arreglo6[j] - prom6), 2);
}





arreglo1.clear();
arreglo2.clear();
arreglo3.clear();
arreglo4.clear();
arreglo5.clear();
arreglo6.clear();

des1 = sqrt(des1 / (cantLinea - 1));

des2 = sqrt(des2 / (cantLinea - 1));

des3 = sqrt(des3 / (cantLinea - 1));

des4 = sqrt(des4 / (cantLinea - 1));

des5 = sqrt(des5 / (cantLinea - 1));

des6 = sqrt(des6 / (cantLinea - 1));




cout << "===Nem===\n" << "Promedio: " << prom1 << "\n" << "Desviacion estandar: " << des1 << "\n" << "Moda: " << modas.at(1) << "\n" << "Mediana: " << medianas.at(1) << endl;
cout << "===Ranking===\n" << "Promedio: " << prom2 << "\n" << "Desviacion estandar: " << des2 << "\n" << "Moda: " << modas.at(2) << "\n" << "Mediana: " << medianas.at(2) << endl;
cout << "===Matematica===\n" << "Promedio: " << prom3 << "\n" << "Desviacion estandar: " << des3 << "\n" << "Moda: " << modas.at(3) << "\n" << "Mediana: " << medianas.at(3) << endl;
cout << "===Lenguaje===\n" << "Promedio: " << prom4 << "\n" << "Desviacion estandar: " << des4 << "\n" << "Moda: " << modas.at(4) << "\n" << "Mediana: " << medianas.at(4) << endl;
cout << "===Ciencias===\n" << "Promedio: " << prom5 << "\n" << "Desviacion estandar: " << des5 << "\n" << "Moda: " << modas.at(5) << "\n" << "Mediana: " << medianas.at(5) << endl;
cout << "===Historia===\n" << "Promedio: " << prom6 << "\n" << "Desviacion estandar: " << des6 << "\n" << "Moda: " << modas.at(6) << "\n" << "Mediana: " << medianas.at(6) << endl;
cout << "===Integrantes===\nLucas Carmona.\nYerko Foncea.\nBrayan Parra." << endl;


}


// Funcion que separa strings entre los punto y coma

std::vector<unsigned int> splitLinea(std::string linea) {
    // Se inicializa vector de tipo string, el cual será el que retornará la función
    std::vector<unsigned int> resultado;

    // Se inicializa variable tipo string en la cual se almacenarán cada puntaje
    std::string valor;
    // Bucle for que recorrerá la linea leída desde el archivo
    for (int i = 0; i < linea.length(); i++) {
        // Se evalúa si la posicion i de linea es igual al caracter ';'
        if (linea[i] == ';') {
            // Si la condición de cumple, se añade el elemento 'valor' al final del vector 'resultado'
            resultado.push_back(std::stoi(valor));
            // Se vacia el contenido del string 'valor'
            valor.clear();
        } else {
            // Se concatenan digitos. ejem: "1", "12", "123"
            valor += linea[i];
        }
    }
    resultado.push_back(std::stoi(valor));
    // Retorna el vector con los puntajes
    return resultado;
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

int moda(vector<unsigned int> arr, int largo) {
    int num = 0, frecAct = 1, frecMax = 0;

    for (int i = 1; i < largo; i++) {
        if (arr.at(i) == arr.at(i - 1)) {
            frecAct++;
        } else {
            if (frecMax < frecAct) {
                frecMax = frecAct;
                num = arr.at(i - 1);
                frecAct = 1;
            } else {
                frecAct = 1;
            }
        }
    }
    return num;
}

void quickSort(vector<unsigned int> *arreglo, int inicio, int fin) {
    int InicioLocal = inicio, FinLocal = fin;
    float Temp, Pivote;
    if (fin > inicio) {
        Pivote = (*arreglo).at((inicio + fin) / 2);
        while (InicioLocal < FinLocal) {
            while ((InicioLocal < fin) && ((*arreglo).at(InicioLocal) < Pivote)) {
                ++InicioLocal;
            }
            while ((FinLocal > inicio) && ((*arreglo).at(FinLocal) > Pivote)) {
                --FinLocal;
            }
            if (InicioLocal <= FinLocal) {
                Temp = (*arreglo).at(InicioLocal);
                (*arreglo).at(InicioLocal) = (*arreglo).at(FinLocal);
                (*arreglo).at(FinLocal) = Temp;
                ++InicioLocal;
                --FinLocal;
            }
        }
        if (inicio < FinLocal) quickSort(arreglo, inicio, FinLocal);
        if (InicioLocal < fin) quickSort(arreglo, InicioLocal, fin);
    }
}

float mediana(vector<unsigned int> arr, int largo) {
    float mediana;
    if (largo % 2 != 0) {
        mediana = arr[((largo - 1) / 2) + 1];
        return mediana;
    } else {
        mediana = (arr[(largo - 1) / 2]) + arr[(largo - 1 / 2) + 1] / 2;
        return mediana;
    }
}