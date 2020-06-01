import 'dart:io';
import 'dart:math';

double prom(List<int> l){
	var suma= 0;
	for(int i=0 ; i<l.length ; i++){
	suma = suma + l[i] ;
	}
  return suma/(l.length);
}

double desv(List<int> l , double prom){
double sum=0;
int i;
for(i=0 ; i< l.length ; i++){
	sum = sum + pow((l[i]-prom),2);
	}
return sqrt(sum/(l.length-1));	
}

double medi(List<int> l){
l.sort();
int med=0;
var largo = l.length;
if(largo%2 ==0){
med= ((l[(largo/2).truncate()] + l[((largo/2).truncate())+1])/2).truncate();
return med.toDouble();
}else{
med=l[(largo/2).truncate() + 1];
return med.toDouble();
}
}

int mod(List<int> l){
int aux = 0, frecact = 1, frecmax =0;
for(int i=1 ; i<l.length; i++){
	if(l[i] == l[i-1]){
	frecact++;
	}else{
		if(frecmax < frecact){
		frecmax = frecact;
		aux = l[i-1];
		frecact = 1;
		}else{
		frecact =1;
		}
	}
} 
return aux;
}


main(List<String> datos)async{

List<int> nem = new List();

List<int> rank = new List();

List<int> matematicas = new List();

List<int> lenguaje = new List();

List<int> ciencias = new List();

List<int> historia = new List();

List<int> moda = new List();

List<double> promedio = new List();

List<double> desviacion = new List();

List<double> mediana = new List();

List<String> linea = await new File(datos[0]).readAsLines();

for(int i=0 ; i<linea.length ; i++){

nem.add(int.parse(linea[i].substring(9,12)));

rank.add(int.parse(linea[i].substring(13,16)));

matematicas.add(int.parse(linea[i].substring(17,20)));

lenguaje.add(int.parse(linea[i].substring(21,24)));

ciencias.add(int.parse(linea[i].substring(25,28)));

historia.add(int.parse(linea[i].substring(29,32)));

}

promedio.add(prom(nem));
promedio.add(prom(rank));
promedio.add(prom(matematicas));
promedio.add(prom(lenguaje));
promedio.add(prom(ciencias));
promedio.add(prom(historia));

desviacion.add(desv(nem, promedio[0]));
desviacion.add(desv(rank, promedio[1]));
desviacion.add(desv(matematicas, promedio[2]));
desviacion.add(desv(lenguaje, promedio[3]));
desviacion.add(desv(ciencias, promedio[4]));
desviacion.add(desv(historia, promedio[5]));

mediana.add(medi(nem));
mediana.add(medi(rank));
mediana.add(medi(matematicas));
mediana.add(medi(lenguaje));
mediana.add(medi(ciencias));
mediana.add(medi(historia));

moda.add(mod(nem));
moda.add(mod(rank));
moda.add(mod(matematicas));
moda.add(mod(lenguaje));
moda.add(mod(ciencias));
moda.add(mod(historia));

print("=== Nem ===");
print("el promedio del nem es = ${promedio[0]}");
print("la desviacion del nem es = ${desviacion[0]}");
print("la mediana del nem es = ${mediana[0]}");
print("la moda del nem es = ${moda[0]}");

print("=== Ranking ===");
print("el promedio del ranking es = ${promedio[1]}");
print("la desviacion del rank es = ${desviacion[1]}");
print("la mediana del ranking es = ${mediana[1]}");
print("la moda del ranking es = ${moda[1]}");

print("=== Matematica ===");
print("el promedio de matematicas es = ${promedio[2]}");
print("la desviacion de matematicas es = ${desviacion[2]}");
print("la mediana de matematicas es = ${mediana[2]}");
print("la moda de matematicas es = ${moda[2]}");

print("=== Lenguaje ===");
print("el promedio de lenguaje es = ${promedio[3]}");
print("la desviacion de lenguaje es = ${desviacion[3]}");
print("la mediana de lenguaje es = ${mediana[3]}");
print("la moda de lenguaje es = ${moda[3]}");

print("=== Ciencias ===");
print("el promedio de ciencia es = ${promedio[4]}");
print("la desviacion de ciencias es = ${desviacion[4]}");
print("la mediana de ciencias es = ${mediana[4]}");
print("la moda de ciencias es = ${moda[4]}");

print("=== Historia ===");
print("el promedio de historia es = ${promedio[5]}");
print("la desviacion de historia es = ${desviacion[5]}");
print("la mediana de historia es = ${mediana[5]}");
print("la moda de historia es = ${moda[5]}");

print("=== Integrantes ===");
print("Lucas Carmona");
print("Yerko Foncea");
print("Brayan Parra");


}
