#include <iostream>
#include <cstdlib>//libreria encargada de numeros aleatorios
#include <vector>
#include <fstream>//permite el manejo de ficheros
#include <sstream>
#include <omp.h>
using namespace std;

/*
	Software que crea 2 matrices ocupadas con numeros aleatorios. Estas son multiplicadas generando asi una tercera matriz, cuyo contenido es la multiplicación de las matrices
	generadas con numeros aleatorios.
	
	1. A través de una comparacián identificamos si existen archivos(matrizA, matrizB) que nos ayudaran en el proceso.
	2. Sí los archivos no existen existen: crea las matrices(matrizA, matrisB), las ocupa con numeros generados aleatoriamente, las multiplica para generar un tercera matriz(matrizC)
	   con la multiplicación las anteriores(matrizA y matrisB), escribe cada una de las matrices(matrizA y matrisB) en un archivo de texto diferente, y la muestra por pantalla el resultado. 
	   Terminando asi la ejecución del programa.
	3. Si los archivos existen. Leera los archivos de las matrices A y B, arma las matrices, las multiplica, y muestra en la pantalla el resultado de la multiplicación. 
	   Terminando asi la ejecución del programa. 
	   
	   
	   
	   
	   
	   
	   
	   cuellos de botella:  imprimirMatriz()
	   hotspots: llenarMatriz(), multiplicacionMatrices(), ecribirMatrizArchivo(), ArmarMatriz()
	   variables privadas: no poseo ya que solo paralelize ciclos for
	   bloques no paralelizables: LeerMatrizArchivo(), splitLineas()
	   tareas: 7
	   speedup: 
	   tiempo serial: 
	   tiempo paralelo:
*/

//funciones que se usaran durante todo el proceso

vector< vector<int> > llenarMatriz(int, int);
void imprimirMatriz(vector< vector<int> > matriz, int, int);
vector< vector<int> > multiplicacionMatrices(vector< vector<int> > matrizA, vector< vector<int> > matrizB, int, int);
void EscribirMatrizArchivo(vector< vector<int> > matrizA, int, int, string archivoMatriz);
string LeerMatrizArchivo(string archivoMatriz);
vector<int> splitLineas(string lineas);
vector< vector<int> > ArmarMatriz(string archivoMatriz, vector< vector<int> > matriz, int, int);



int main(){
	 //numero de hilos que usaremos
	 omp_set_num_threads(4);
	//constantes que seran usadas para las filas y columnas de las matrices.  
	const int FILAS = 20;
	const int COLUMNAS = 20;
	/*
		vectores que seran usados durante toda la ejecución del programa. A, B y C
	
	*/
	vector< vector<int> > matrizA;
	vector< vector<int> > matrizB;
	vector< vector<int> > matrizC;
	
	
	/*
		Este condicional nos ayudara a saber si	los archivos existen o no existen.
	*/
	if (!std::ifstream("matrizA.txt") && !std::ifstream("matrizB.txt") ){
		
		
		//pequeño mensaje para saber que operación es la que se esta realizando
		cout<<"-----------------------------------------"<<endl;
    	cout<<"--------Los Archivos Fueron Creados!--------"<<endl;
    	cout<<"-----------------------------------------"<<endl;
    		
    	//en esta parte se estan llenando las matrices 	
		matrizA = llenarMatriz(FILAS, COLUMNAS);
		matrizB = llenarMatriz(FILAS, COLUMNAS);
		
		/*en esta generando la tercera matriz, que es la matriz resultante
		  de la multiplicación de las anteriores
		*/
		matrizC = multiplicacionMatrices(matrizA, matrizB, FILAS, COLUMNAS);
		
		/*
		    EscribirMatrizArchivo() escribe las matrices a archivos llamados matrizA o matrizB
		
		*/
		EscribirMatrizArchivo(matrizA, FILAS, COLUMNAS, "matrizA");
		EscribirMatrizArchivo(matrizB, FILAS, COLUMNAS, "matrizB");
			
		//pequeño mensaje
		cout<<"--------Matriz resultante!---------------"<<endl;
		
		
	 	
	 	//	imprimiendo la matriz resultante 
		
		imprimirMatriz(matrizC, FILAS, COLUMNAS);
	
			/*
				en caso dado que los archivos existan.
			*/
    }else {
    	
    	cout<<"-----------------------------------------"<<endl;
    	cout<<"--------Los Archivos ya Existian!--------"<<endl;
    	cout<<"-----------------------------------------"<<endl;
    	
    	// se leeran las matrices generadas con numeros aleatorios de sus archivo
    	matrizA = ArmarMatriz("matrizA", matrizA, FILAS, COLUMNAS);
    	matrizB = ArmarMatriz("matrizB", matrizB, FILAS, COLUMNAS);
    	
    	//y posteriormente se multiplicaran generando asi la matrizC
		matrizC = multiplicacionMatrices(matrizA, matrizB, FILAS, COLUMNAS);
			
		cout<<"--------Matriz resultante!---------------"<<endl;
			
		//	imprimiendo la matriz resultante 
		imprimirMatriz(matrizC, FILAS, COLUMNAS);

    }
	
	
	return 0;
}

/*
	en esta parte se usaron vector de vectores(vector< vector<int> >) los cuales funcionan como matrices y durante todo el programa se usaron los mismos.
*/

vector< vector<int> > llenarMatriz(int filas, int columnas)
{
	
	vector< vector<int> > matriz;//declarando vector de vectores
	vector<int> fila;//declarando un vector normal
	int r;//variable que nos servira para almacenar numeros aleatorios momentaneamente
	
	for(int i = 0; i < filas; i++){
		//solo paralelizaremos esta parte for y no los dos ya que esta es la parte que hace el trabajo como tal. 
		#pragma omp parallel for schedule(static)
		for(int j = 0; j < columnas;j++){
			r = (rand() % 1000) + 1;//generando numero aleatorio
			fila.push_back(r);//almacenando numero aleatorio en un vector
		}
		matriz.push_back(fila);//almacenando vector en el vector de vectores
		fila.clear();//limpiando vector normal.
	}
	return matriz;//retornando matriz generada
	
}

//la siguiente función nos ayudara a mostrar por pantalla las matrices
void imprimirMatriz(vector< vector<int> > matriz, int filas, int columnas){
	
	for(int i = 0; i < filas; i++){	
	//paralelizamos esta parte para agilizar el proceso de impresion 
	   #pragma omp parallel for schedule(static)
		for(int j = 0; j < columnas;j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<endl;	
	}
}

//la siguiente función se encargara de multiplicar las matrices
vector< vector<int> > multiplicacionMatrices(vector< vector<int> > matrizA, vector< vector<int> > matrizB, int filas, int columnas)
{
	vector<int> matrizc;//vector normal
	int numero;// nos ayudara en generarel numero de cierta posicion de matriz
	vector< vector<int> > matrizC; //vector de vectores
	
	
		
	for (int i = 0 ; i < filas;i++)
    {
     	
	   for (int j  = 0;j < filas;j++)
       { 
       //paralelizamos esta parte para agilizar el proceso de la multiplicacion de las matrices
	   #pragma omp parallel for schedule(static)
	   /*
	   	este algoritmos nos ayuda en la multiplicacion de las matrices y todo lo almacena en una variable la cual es almacenada en cierta posición de una fila
	   	y luego esa fila cuando ya esta completa, es almacenada en la matriz.
	   			 	
	   */
         for (int k = 0;k < filas;k++)
          {
          	
          	  if(k == 0)
			  {
			  numero = 0;
			  }
		       numero = numero + (matrizA[i][k] * matrizB[k][j]);
          }
          matrizc.push_back(numero);//almacenando variable en la fila
       }
       matrizC.push_back(matrizc);//almacenado fila en martriz
       matrizc.clear();//limpiando fila para ser ocupada nuevamente
    }
    return matrizC;//retornando matriz generada
}

//ahora escribiremos la matriz en un archivo
void EscribirMatrizArchivo(vector< vector<int> > matriz, int filas, int columnas, string archivoMatriz)
{
	string file = archivoMatriz + ".txt";//nombre el archivo
	ofstream archivo(file.c_str());//la funcion "c_str()" convertira la cadena string en un const char*, solo por el momento
    
    for(int r = 0; r < filas; r++){
    #pragma omp for schedule(static)
    //escribiendo matriz en el archivo
		for(int c = 0;c < columnas; c++){
			archivo <<matriz[r][c]<<" ";
		}
		archivo<<endl;//saltos de lineas para que en el archivo aun se vea como una matriz
	}
    archivo.close();//cerrando archivo
    cout<<archivoMatriz<<" ha sido escrito!"<<endl;//mensaje por pantall
}

//ahora leeremos un archivo que posee una matriz
string LeerMatrizArchivo(string archivoMatriz)
{
	string lineas, linea;
	string file = archivoMatriz + ".txt";//nombre del archivo
	ifstream archivo(file.c_str());//la funcion "c_str()" convertira la cadena string en un const char*, solo por el momento
	while(getline(archivo, linea))//obtenemos linea por linea el archivo de texto
	{
		lineas+=linea;//esas lineas las vamos almacenando en una sola linea(string)
	}
   archivo.close();//cerramos el archivo
   return lineas;//y devolvemos esa linea(string) generada
}


//ahora haremos un split a la linea(string) que obtuvimos del archivo
vector<int> splitLineas(string lineas)
{
	
	/*
		esta parte nos ayudara a partir la linea cada vez que encuentre un espacio
	*/
	std::string str(lineas);//linea(string) que obtuvimos del archivo
    std::istringstream isstream(str);
	vector<int> numeros;//vector de enteros
	
	   	while(!isstream.eof()){
		        std::string tempStr;
		        isstream >> tempStr; //la almacena en una variable(tempStr)
				numeros.push_back(atoi(tempStr.c_str()));//a la variable tempStr la convertimos en un entero con la función atoi(), y la incluimos en el vector de enteros declarado 
		}
	
	return numeros;//y ese vector lo retornamos.
}

vector< vector<int> > ArmarMatriz(string archivoMatriz, vector< vector<int> > matriz, int filas, int columnas){
	string lineas =	LeerMatrizArchivo(archivoMatriz);//leemos el archivo para generar una sola linea
	vector<int> numeros = splitLineas(lineas);//rompemos esa linea cada ves que en contremos un espacio en ella. y cada parte la incluimos en un vector
	vector<int> fila;
	int numero = 0;
	int k = 0;

	for(int r = 0; r < filas; r++){
		//for paralelizado para agilizar el proceso de armar la matriz nuevamente
		#pragma omp for schedule(static)
		for(int c = 0;c < columnas; c++){
			numero = numeros[k];//cada parte de el vector que generamos con el split lo pasamos a una variable
			fila.push_back(numero);//que es incluida en una fila dela matriz
			k++;//lleva la iteracion de vector generado por el split
		}
		matriz.push_back(fila);//incluimos la fila en la matriz
		fila.clear();//limpiamos la fila
	}
	cout<<archivoMatriz<<".txt"<<" Fue Leido Totalmente."<<endl;//pasamos un mensaje por pantalla
	return matriz;//y retornamos la matriz
}



