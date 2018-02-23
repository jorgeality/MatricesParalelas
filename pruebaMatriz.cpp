#include <iostream>
#include <cstdlib>//libreria encargada de numeros aleatorios
#include <vector>
#include <fstream>//permite el manejo de ficheros
#include <sstream>
using namespace std;


vector< vector<int> > llenarMatriz(int, int);
void imprimirMatriz(vector< vector<int> > matriz, int, int);
vector< vector<int> > multiplicacionMatrices(vector< vector<int> > matrizA, vector< vector<int> > matrizB, int, int);
void EscribirMatrizArchivo(vector< vector<int> > matrizA, int, int, string archivoMatriz);
string LeerMatrizArchivo(string archivoMatriz);
vector<int> splitLineas(string lineas);
vector< vector<int> > ArmarMatriz(string archivoMatriz, vector< vector<int> > matriz, int, int);



int main(){
	
	const int FILAS = 1000;
	const int COLUMNAS = 1000;
	
	vector< vector<int> > matrizA;
	vector< vector<int> > matrizB;
	vector< vector<int> > matrizC;
	
	if (!std::ifstream("matrizC.txt")){
		
		cout<<"-----------------------------------------"<<endl;
    	cout<<"--------Los Archivos Fueron Creados!--------"<<endl;
    	cout<<"-----------------------------------------"<<endl;
    	
		matrizA = llenarMatriz(FILAS, COLUMNAS);
		matrizB = llenarMatriz(FILAS, COLUMNAS);
		matrizC = multiplicacionMatrices(matrizA, matrizB, FILAS, COLUMNAS);
		
		
		EscribirMatrizArchivo(matrizA, FILAS, COLUMNAS, "matrizA");
		EscribirMatrizArchivo(matrizB, FILAS, COLUMNAS, "matrizB");
		EscribirMatrizArchivo(matrizC, FILAS, COLUMNAS, "matrizC");	
		
		cout<<"solo imprimiremos la matriz resultante. las otras se pueden ver en los archivos creados"<<endl;
		matrizC = ArmarMatriz("matrizC", matrizC, FILAS, COLUMNAS);
		imprimirMatriz(matrizC, FILAS, COLUMNAS);
		
			
    }else {
    	
    	cout<<"-----------------------------------------"<<endl;
    	cout<<"--------Los Archivos ya Existian!--------"<<endl;
    	cout<<"-----------------------------------------"<<endl;
    		
		
			
		cout<<"solo imprimiremos la matriz resultante, que ha sido leida del archivo de la matriz ya escrito."<<endl;	
		cout<<"matriz C: "<<endl;
			
		matrizC = ArmarMatriz("matrizC", matrizC, FILAS, COLUMNAS);
		imprimirMatriz(matrizC, FILAS, COLUMNAS);

    }
	
	
	return 0;
}

vector< vector<int> > llenarMatriz(int filas, int columnas)
{
	
	vector< vector<int> > matriz;
	vector<int> fila;
	int r;
	for(int i = 0; i < filas; i++){
		
		for(int j = 0; j < columnas;j++){
			r = (rand() % 1000) + 1;
			fila.push_back(r);
		}
		matriz.push_back(fila);
		fila.clear();
	}
	return matriz;
	
}
void imprimirMatriz(vector< vector<int> > matriz, int filas, int columnas){
	for(int i = 0; i < filas; i++){		
		for(int j = 0; j < columnas;j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<endl;	
	}
}
vector< vector<int> > multiplicacionMatrices(vector< vector<int> > matrizA, vector< vector<int> > matrizB, int filas, int columnas)
{
	vector<int> matrizc;
	int numero;
	vector< vector<int> > matrizC;
	for (int i = 0 ; i < filas;i++)
    {
     	
	   for (int j  = 0;j < filas;j++)
       { 
	    
         for (int k = 0;k < filas;k++)
          {
          	  if(k == 0)
			  {
			  numero = 0;
			  }
		       numero = numero + (matrizA[i][k] * matrizB[k][j]);
          }
          matrizc.push_back(numero);
       }
       matrizC.push_back(matrizc);
       matrizc.clear();
    }
    return matrizC;
}

void EscribirMatrizArchivo(vector< vector<int> > matriz, int filas, int columnas, string archivoMatriz)
{
	string file = archivoMatriz + ".txt";
	ofstream archivo(file.c_str());//la funcion "c_str()" convertira la cadena string en un const char*, solo por el momento
    
    for(int r = 0; r < filas; r++){
		for(int c = 0;c < columnas; c++){
			archivo <<matriz[r][c]<<" ";
		}
		archivo<<endl;
	}
    archivo.close();
    cout<<archivoMatriz<<" ha sido escrito!"<<endl;
}


string LeerMatrizArchivo(string archivoMatriz)
{
	string lineas, linea;
	string file = archivoMatriz + ".txt";
	ifstream archivo(file.c_str());//la funcion "c_str()" convertira la cadena string en un const char*, solo por el momento
	while(getline(archivo, linea))
	{
		lineas+=linea;
	}
   archivo.close();
   return lineas;
}



vector<int> splitLineas(string lineas)
{
	std::string str(lineas);
    std::istringstream isstream(str);
	vector<int> numeros;
    
	while(!isstream.eof()){
        std::string tempStr;
        isstream >> tempStr;
		numeros.push_back(atoi(tempStr.c_str()));
    }
    
	return numeros;
}

vector< vector<int> > ArmarMatriz(string archivoMatriz, vector< vector<int> > matriz, int filas, int columnas){
	string lineas =	LeerMatrizArchivo(archivoMatriz);
	vector<int> numeros = splitLineas(lineas);
	vector<int> fila;
	int numero = 0;
	int k = 0;
	for(int r = 0; r < filas; r++){
		for(int c = 0;c < columnas; c++){
			numero = numeros[k];
			fila.push_back(numero) ;
			k++;
		}
		matriz.push_back(fila);
		fila.clear();
	}
	cout<<archivoMatriz<<".txt"<<" Fue Leido Totalmente."<<endl;
	return matriz;
}



