#include <string>
#include <iostream>
#include <fstream>//permite el manejo de ficheros
#include <vector>
#include <cstdlib>//permite la convertion de string a int
#include <sstream>//no sayudara mas adelante cuando tengamos que hacer un split
#include<stdlib.h>//nos ayudara a generar numeros aleatorios
#include<time.h>//tambien nos ayudara a generar numeros aleatorios
using namespace std;




void crearMatriz(int matriz[][1000], int filas)
{
  
  for(int r = 0; r < filas; r++){
  	for(int c = 0;c < filas; c++){
  		
        matriz[r][c] = 1 + rand() % ((filas * 10) - 1);
	  
	  } 
  }
    
 
}
void imprimirMatriz(int matriz[][1000], int filas)
{
  
  	for(int r = 0; r < filas; r++){
		for(int c = 0;c < filas; c++){
			cout<<matriz[r][c]<<" ";
		}
		cout<<endl;
	}
 
}
void multiplicacionMatrices(int matrizA[][1000],int matrizB[][1000], int matrizC[][1000], int filas)
{
	
	for (int i = 0 ; i < filas;i++)
    {
     	
	   for (int j  = 0;j < filas;j++)
       { 
	    
         for (int k = 0;k < filas;k++)
          {
          	  if(k == 0)
			  {
			  	matrizC[i][j] = 0;
			  }
		       matrizC[i][j] = matrizC[i][j] + (matrizA[i][k] * matrizB[k][j]);
          }
       }
    }
}

void EscribirMatrizArchivo(int matriz[][1000], int filas, string archivoMatriz)
{
	string file = archivoMatriz + ".txt";
	ofstream archivo(file.c_str());//la funcion "c_str()" convertira la cadena string en un const char*, solo por el momento
    
    for(int r = 0; r < filas; r++){
		for(int c = 0;c < filas; c++){
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

int *splitLineas(string lineas)
{
	std::string str(lineas);
    std::istringstream isstream(str);
	vector<string> palabras;
	
    while(!isstream.eof()){
        std::string tempStr;
        isstream >> tempStr;
		palabras.push_back(tempStr);
    }
    
    int numeros[palabras.size()];
	for(int i = 0; i < palabras.size();i++)
	{
		numeros[i] = atoi(palabras[i].c_str());
	}
	
		
	return numeros;
}
void ArmarMatriz(string archivoMatriz, int matriz[][1000], int filas ){
	string lineas =	LeerMatrizArchivo(archivoMatriz);
	int *numeros = splitLineas(lineas);
	int k = 0;
	for(int r = 0; r < filas; r++){
		for(int c = 0;c < filas; c++){
			matriz[r][c] = numeros[k];
			k++;
		}
	
	}
	cout<<archivoMatriz<<".txt"<<" Fue Leido Totalmente."<<endl;
}



int main() {
	int filas = 1000;
	int matrizA[filas][1000];
	int matrizB[filas][1000];
	int matrizC[filas][1000];
	
	if (!std::ifstream("matrizC.txt")){
		
		cout<<"-----------------------------------------"<<endl;
    	cout<<"--------Los Archivos Fueron Creados!--------"<<endl;
    	cout<<"-----------------------------------------"<<endl;
		crearMatriz(matrizA, filas);
		EscribirMatrizArchivo(matrizA, filas, "matrizA");
		crearMatriz(matrizB, filas);
		EscribirMatrizArchivo(matrizB, filas, "matrizB");
		multiplicacionMatrices(matrizA, matrizB, matrizC, filas);
		EscribirMatrizArchivo(matrizC, filas, "matrizC");
		
		cout<<"solo imprimiremos la matriz resultante."<<endl;
		ArmarMatriz("matrizC", matrizC, filas);
		//imprimirMatriz(matrizC, filas);
			
    }else {
    	
    	cout<<"-----------------------------------------"<<endl;
    	cout<<"--------Los Archivos ya Existian!--------"<<endl;
    	cout<<"-----------------------------------------"<<endl;
    		
		ArmarMatriz("matrizA", matrizA, filas);
		ArmarMatriz("matrizB", matrizB, filas);
			
		cout<<"solo imprimiremos la matriz resultante, que ha sido leida del archivo de la matriz resultante."<<endl;	
		cout<<"matriz C: "<<endl;
			
		ArmarMatriz("matrizC", matrizC, filas);
		//imprimirMatriz(matrizC, filas);
			
			
			
			
			
    }
	
	
	
      

 return 0;
}


