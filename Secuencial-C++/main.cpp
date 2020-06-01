#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
using namespace std;



/**
 *
 * \param Vector de tipo int con los respectivos puntajes
 * \param Largo del vector
 * \return Promedio de los puntajes
 *
 */  
double promedioPtjs(std::vector<int> vec, int largo) {

    double resultado;
    for (int i = 0; i < largo; i++){
        resultado += vec.at(i);
    }
    return resultado/largo;
}
/**
 *
 * \param Vector de tipo int con los respectivos puntajes
 * \param Largo del vector
 * \return Mediana de los puntajes del vector
 *
 */  
double  mediana(std::vector<int> vec, int largo){
    double resultado = 0.0;
    if(largo%2 == 0) {
        resultado = (vec.at(largo/2) + vec.at((largo/2)+1)) / 2;
    } else {
        resultado = vec.at((largo/2) + 1);
    }
    return resultado;
}
/**
 *
 * \param Vector de tipo int con los respectivos puntajes
 * \param Largo del vector
 * \param promedio del respecivo puntaje
 * \return Desviacion estandar de los puntajes
 *
 */  
double desvEstandar(std::vector<int> vec, int largo, double promedio) {
    double resultado = 0.0;
    for (int i = 0; i < largo; i++) {
        resultado += pow((vec.at(i) - promedio), 2) / (largo - 1);
    }
    
    return sqrt(resultado);

}

/**
 *
 * \param Cadena de tipo string leida desde el archivo
 * \return Vector de tipo entero con los respectivos puntajes
 *
 */     

std::vector<int> splitLinea(std::string linea) {
    std::vector<int> resultado;
    std::string valor;
    for(int i = 0; i < linea.size(); i++){
        if(linea[i] == ';' ){
            resultado.push_back(stoi(valor));
            valor.clear();
        }else{
            valor += linea[i];
        }
    }
    resultado.push_back(stoi(valor));
    return resultado;
}

/** 
 *
 * \param Vector de tipo entero
 * \param Largo del vector 
 * \return Puntaje que mas se repite en el vector
 *
 */     

int moda(std::vector<int> arr, int largo) {
    int num = 0, frecAct = 1, frecMax = 0;
    for(int i=1; i<largo; i++) {
        if(arr.at(i) == arr.at(i - 1)) {
            frecAct++;
        } else {
            if(frecMax < frecAct) {
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


/** 
 *
 * \param Vector a ordenar
 * \param Indice inicial del vector
 * \param Indice final del vector
 * \return 
 *
 */     

void quickSort(std::vector<int> *arreglo, int inicio, int fin){
    int InicioLocal= inicio, FinLocal=fin;
    float Temp, Pivote;
    if(fin>inicio)
    {
        Pivote= (*arreglo).at((inicio+fin)/2);
        while(InicioLocal<FinLocal)
        {
            while((InicioLocal<fin) && ((*arreglo).at(InicioLocal)<Pivote))  {++InicioLocal;}
            while((FinLocal>inicio) && ((*arreglo).at(FinLocal)>Pivote)) {--FinLocal;}
            if(InicioLocal<=FinLocal)
            {
                Temp=(*arreglo).at(InicioLocal);
                (*arreglo).at(InicioLocal)=(*arreglo).at(FinLocal);
                (*arreglo).at(FinLocal)=Temp;
                ++InicioLocal;
                --FinLocal;
            }
        }
        if(inicio<FinLocal) quickSort(arreglo,inicio,FinLocal);
        if(InicioLocal<fin) quickSort(arreglo,InicioLocal,fin);
    }
}

int main() {
    
    std::string path = "", linea = "" ;
    int nLineas = 0;

    std::cout << "Ingrese ruta de archivo a procesar: ";
    std::cin >> path;

    // APERTURA DE ARCHIVO DE LECTURA
    ifstream archivoEntrada(path);

    // SI NO SE LOGRA ABRIR EL ARCHIVO SE IMPRIME EL ERROR
    if(archivoEntrada.fail()) {
        std::cerr << "No se logro abrir el archivo!" << std::endl;
    } else { // SI SE ABRE SATISFACTORIAMENTE, HAZ LO SIGUIENTE
        std::vector<int> nem, ranking, matematica, lenguaje, historia, ciencias;
        for (linea; getline(archivoEntrada, linea);) {
            if(!linea.empty()){
                std::vector<int> datos = splitLinea(linea);
                nem.push_back(datos.at(1));
                ranking.push_back(datos.at(2));
                matematica.push_back(datos.at(3));
                lenguaje.push_back(datos.at(4));
                historia.push_back(datos.at(5));
                ciencias.push_back(datos.at(6));
                nLineas += 1;
            }
        }

        //SE ORDENAN LOS VECTORES PARA POSTERIORMENTE CALCULAR MODA, MEDIANA Y DESVIACION
        quickSort(&nem, 0, nLineas - 1);
        quickSort(&ranking, 0, nLineas - 1);
        quickSort(&matematica, 0, nLineas - 1);
        quickSort(&lenguaje, 0, nLineas - 1);
        quickSort(&historia, 0, nLineas - 1);
        quickSort(&ciencias, 0, nLineas - 1);
        
        double promNem = promedioPtjs(nem, nLineas);
        double promRank = promedioPtjs(ranking, nLineas);
        double promMate = promedioPtjs(matematica, nLineas);
        double promLeng = promedioPtjs(lenguaje, nLineas);
        double promHist = promedioPtjs(historia, nLineas);
        double promCien = promedioPtjs(ciencias, nLineas);

        // SE IMPRIMEN RESULTADOS
        std::cout << "=======================\n";    
        std::cout << 
            "Promedio: " << promedioPtjs(nem, nLineas) << "\n" <<  
            "Moda: " << moda(nem, nLineas) << "\n" << 
            "Desviacion estandar: " <<  desvEstandar(nem, nLineas, promNem) << "\n" << 
            "Mediana: " << mediana(nem, nLineas) << "\n";
        nem.clear();
        std::cout << "=======================\n";    
        std::cout << 
            "Promedio: " << promedioPtjs(ranking, nLineas) << "\n" << 
            "Moda: " << moda(ranking, nLineas) << "\n" << 
            "Desviacion estandar: " << desvEstandar(ranking, nLineas, promRank) << "\n" << 
            "Mediana: " << mediana(ranking, nLineas) << "\n";
        ranking.clear();
        std::cout << "=======================\n";    
        std::cout << 
            "Promedio: " << promedioPtjs(matematica, nLineas) << "\n" << 
            "Moda: " << moda(matematica, nLineas) << "\n" << 
            "Desviacion estandar: " << desvEstandar(matematica, nLineas, promMate) << "\n" << 
            "Mediana: " << mediana(matematica, nLineas) << "\n";
        matematica.clear();
        std::cout << "=======================\n";    
        std::cout << 
            "Promedio: " << promedioPtjs(lenguaje, nLineas) << "\n" << 
            "Moda: " << moda(lenguaje, nLineas) << "\n" << 
            "Desviacion estandar: " << desvEstandar(lenguaje, nLineas, promLeng) << "\n" << 
            "Mediana: " << mediana(lenguaje, nLineas) << "\n";
        lenguaje.clear();
        std::cout << "=======================\n";    
        std::cout << 
            "Promedio: " << promedioPtjs(historia, nLineas) << "\n" << 
            "Moda: " << moda(historia, nLineas) << "\n" << 
            "Desviacion estandar: " << desvEstandar(historia, nLineas, promHist) << "\n" << 
            "Mediana: " << mediana(historia, nLineas)<< "\n";
        historia.clear();
        std::cout << "=======================\n";    
        std::cout << 
            "Promedio: " << promedioPtjs(ciencias, nLineas) << "\n" << 
            "Moda: " << moda(ciencias, nLineas) << "\n" << 
            "Desviacion estandar: " << desvEstandar(ciencias, nLineas, promCien) << "\n" << 
            "Mediana: " << mediana(ciencias, nLineas) << "\n";     
        ciencias.clear();     
    }

    return 0;
}



