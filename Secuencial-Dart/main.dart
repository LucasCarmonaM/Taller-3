import 'dart:async';
import 'dart:io';
import 'dart:convert';
import 'dart:math';


double promedioPtjs(List<int> vec) {
    int sumatoria = 0;
    int i;
    for (i = 0; i < vec.length; i++){
        sumatoria += vec[i];
    }
    return sumatoria/vec.length;
}

double mediana(List<int> vec, int largo){

    double resultado = 0;
    if(largo%2 == 0) {
        resultado = ((vec.elementAt(largo~/2) + vec.elementAt((largo~/2)+1)) / 2);
    } else {
        resultado = (vec.elementAt((largo~/2) + 1)).toDouble();
    }
    return resultado;
}

double desvEstandar(List<int> vec, int largo, double promedio) {
    double resultado = 0.0;
    for (int i = 0; i < largo; i++) {
        resultado += pow((vec.elementAt(i) - promedio), 2) / (largo - 1);
    }
    return sqrt(resultado);
}

int getPtje(String line, int index) {
  return  int.parse(line.split(';').sublist(1)[index]); 
}

int moda(List<int> arr, int largo) {
    int num = 0, frecAct = 1, frecMax = 0;
    for(int i=1; i<largo; i++) {
        if(arr.elementAt(i) == arr.elementAt(i - 1)) {
            frecAct++;
        } else {
            if(frecMax < frecAct) {
                frecMax = frecAct;
                num = arr.elementAt(i - 1);
                frecAct = 1;
            } else {
                frecAct = 1;
            }
        }
    }
    return num;
}

void main(List<String> arguments) {

  List<int> nem = List<int>();
  List<int> ranking = List<int>();
  List<int> matematica = List<int>();
  List<int> lenguaje = List<int>();
  List<int> historia = List<int>();
  List<int> ciencias = List<int>();
  
  int contador = 0;

  final file = new File(arguments[0]);

  Stream<List<int>> inputStream = file.openRead();

  inputStream 
    .transform(utf8.decoder)       // Decode bytes to UTF-8.
    .transform(new LineSplitter()) // Convert stream to individual lines.
    .listen((String  line) {        // Process results.
        nem.add(getPtje(line, 0));
        ranking.add(getPtje(line, 1));
        matematica.add(getPtje(line, 2));
        lenguaje.add(getPtje(line, 3));
        historia.add(getPtje(line, 4));
        ciencias.add(getPtje(line, 5));
        contador++;
      },
      onDone: () {
          /* Se ordenan las listas */
          nem.sort();
          ranking.sort();
          matematica.sort();
          lenguaje.sort();
          historia.sort();
          ciencias.sort();

          /* Se obtienen los promedios de cada puntaje */
          double nemProm, rankProm, mateProm, histProm, lengProm, cienProm;
          rankProm = promedioPtjs(ranking);
          mateProm = promedioPtjs(matematica);
          histProm = promedioPtjs(lenguaje);
          lengProm = promedioPtjs(historia);
          cienProm = promedioPtjs(ciencias);
          nemProm = promedioPtjs(nem);
          
          print("===========================");
          print("\t***NEM***");
          print("Promedio: ${nemProm} \nDesviacion: ${desvEstandar(nem, contador, nemProm)} \n Mediana: ${mediana(nem, contador)} \nModa: ${moda(nem, contador)}");
          nem.clear();
          print("===========================");
          print("\t***RANKING***");
          print("Promedio: ${rankProm} \nDesviacion: ${desvEstandar(ranking, contador, rankProm)} \nMediana: ${mediana(nem, contador)} \nModa: ${moda(nem, contador)}");
          ranking.clear();
          print("===========================");
          print("\t***MATEMATICA***");
          print("Promedio matematica: ${mateProm} \nDesviacion: ${desvEstandar(matematica, contador, mateProm)} \nMediana: ${mediana(matematica, contador)} \nModa: ${moda(matematica, contador)}");
          matematica.clear();
          print("===========================");
          print("\t***LENGUAJE***");
          print("Promedio lenguaje: ${lengProm} \nDesviacion: ${desvEstandar(lenguaje, contador, lengProm)} \nMediana: ${mediana(lenguaje, contador)} \nModa: ${moda(lenguaje, contador)}");
          lenguaje.clear();
          print("===========================");
          print("\t***HISTORIA***");
          print("Promedio historia: ${histProm} \nDesviacion: ${desvEstandar(historia, contador, histProm)} \nMediana: ${mediana(historia, contador)} \nModa: ${moda(historia, contador)}");
          historia.clear();
          print("===========================");
          print("\t***CIENCIAS***");
          print("Promedio historia: ${cienProm} \nDesviacion: ${desvEstandar(ciencias, contador, cienProm)} \nMediana: ${mediana(ciencias, contador)} \nModa: ${moda(ciencias, contador)}");
          ciencias.clear();
          print("===========================");

         },
      onError: (e) { print(e.toString()); });

}