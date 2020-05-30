#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <omp.h>
#include <ctime>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
std::vector<std::string> splitLinea(std::string linea) {
    // Se inicializa vector de tipo string, el cual será el que retornará la función
    std::vector<std::string> resultado;

    // Se inicializa variable tipo string en la cual se almacenarán cada puntaje
    std::string valor;
    // Bucle for que recorrerá la linea leída desde el archivo
    for(int i = 0; i < linea.length(); i++){
        // Se evalúa si la posicion i de linea es igual al caracter ';'
        if(linea[i] == ';' ){
            // Si la condición de cumple, se añade el elemento 'valor' al final del vector 'resultado'
            resultado.push_back(valor);
            // Se vacia el contenido del string 'valor'
            valor.clear();
        }else{
            // Se concatenan digitos. ejem: "1", "12", "123"
            valor += linea[i];
        }
    }
    resultado.push_back(valor);
    // Retorna el vector con los puntajes
    return resultado;
}


int main() {
    std::ifstream archivoLee("/home/lucas/Desktop/Taller-3/puntajes.csv");
    std::string linea;

    // datos 0=rut 1=nem 2=ranking 3=matematica 4=lenguaje 5=ciencias 6=historia
    std::vector<std::string> datos;
    float promedio1, promedio2, promedio3, promedio4, promedio5, promedio6;
    // cantidad de lineas para calcular promedio y otros
    long cantLinea = 0;
    // ciclo que ejecuta mientras el archivo tenga lineas
    while (getline(archivoLee, linea)) {
               
        datos = splitLinea(linea);        
        
        
        // CALCULO DE PROMEDIOS
        cantLinea += 1;
        // Promedio nem
        promedio1 += std::stoi(datos[1]);
        // Promedio ranking
        promedio2 += std::stoi(datos[2]);
        // Promedio matematica
        promedio3 += std::stoi(datos[3]);
        // Promedio lenguaje
        promedio4 += std::stoi(datos[4]);
        // promedio ciencias
        promedio5 += std::stoi(datos[5]);
        // Promedio historia
        promedio6 += std::stoi(datos[6]);
        
        
        
    }
    cout << "Promedio nem: " << promedio1 / cantLinea << endl;
    cout << "Promedio nem: " << promedio1 / cantLinea << endl;
    cout << "Promedio nem: " << promedio1 / cantLinea << endl;
    cout << "Promedio nem: " << promedio1 / cantLinea << endl;
    cout << "Promedio nem: " << promedio1 / cantLinea << endl;
    cout << "Promedio nem: " << promedio1 / cantLinea << endl;
    cout << "catnidad de lineas: " << cantLinea << endl;
    archivoLee.close();

}



