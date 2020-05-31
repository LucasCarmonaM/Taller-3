#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


/**
 *
 * \param Linea del archivo a separar por ';'
 * \return Vector de tipo entero con los respectivos puntajes
 *
 */     

vector<int> splitLinea(std::string linea) {
    vector<int> resultado;
    std::string valor;
    for(int i = 0; i < linea.size(); i++){
        if(linea[i] == ';' ){
            resultado.push_back(std::stoi(valor));
            valor.clear();
        }else{
            valor += linea[i];
        }
    }
    resultado.push_back(valor);
    return resultado;
}

/** 
 *
 * \param Vector de tipo entero
 * \param Largo del vector 
 * \return Puntaje que mas se repite en el vector
 *
 */     

int moda(vector<int> arr, int largo) {
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

void quickSort(vector<int> *arreglo, int inicio,int fin){
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
    
    std::cout << "Hello world" << std::endl;
    return 0;
}



