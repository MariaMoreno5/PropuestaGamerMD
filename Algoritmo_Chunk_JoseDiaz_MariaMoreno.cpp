/*División de un vector con Chunks en lenguaje C++.
Proyecto de Arquitectura del Computador.
Profesor: José Canache
Alumnos: José Jesú Díaz Moreno y Maria Moreno 

Para dividir un vector usando chunks en C++, podemos seguir los siguientes pasos:

1.- Definir el vector de entrada con los elementos a dividir.
2.- Definir el tamaño de los subvectores o chunks.
3.- Determinar el número total de subvectores de tamaño n formado a partir del vector de entrada, utilizando 
    la siguiente fórmula: (v.size() - 1) / n + 1.
4.- Crear un array de vectores para almacenar los subvectores, utilizando la variable size calculada anteriormente.
5.- Iterar sobre el vector de entrada, y para cada iteración del bucle, procesar el siguiente conjunto de n 
    elementos y copiarlo a un nuevo vector utilizando el algoritmo copy.
6.- Asignar memoria para el subvector utilizando la función resize.
7.- Copiar elementos del rango de entrada al subvector utilizando la función copy.
8.- Dependiendo de la cantidad de elementos del vector origen, el último subvector puede contener menos elementos.
9.- Imprimir los sub-vectores utilizando la función print_Vector.
Dividir un vector en partes iguales puede ser más eficiente hacerlo por elementos en lugar de por subvectores.
Por lo que, al aplicar chunks en un vector por elementos puede ser más sencillo de implementar y entender en
algunos casos,especialmente si se trata de una tarea simple como imprimir los elementos del vector uno por uno.*/

#include <iostream>
#include <vector>
//#include <stdio.h>


using namespace std;

// Función de utilidad para imprimir un vector
template<typename T>

void print_Vector(vector<T> const &v)
{
    for (int i=0; i < v.size(); i++){
        if(v[i]<10){
            cout << " "<< v[i] << " ";
        }else{
            cout << v[i] << " ";            
        }
        
    }
 
    cout << endl;
}
 

int main()
{
    int max_Vector; //max_Vector indica el tamaño del vector que ingresará el usuario.
        
    cout << "\n Por favor, ingrese el tamano del vector:  ";
    cin >> max_Vector;
    
    if(max_Vector > 0){ 
   
    // divide el vector en sub-vectores cada uno de 10 elementos.
         int n = 10;
        vector<int> myVector(max_Vector);
        for(int i = 0; i < max_Vector; i++){
            myVector[i] = i;
        }
       
        // determina el número total de subvectores de tamaño "n"
        int size = (myVector.size() - 1) / n + 1;
 
        // crea una array de vectores para almacenar los subvectores
        vector<int> chunks[size];
 
        // cada iteración de este bucle procesa el siguiente conjunto de `n` elementos
        // y almacenarlo en un vector en el k'ésimo índice en `vec`
        for (int k = 0; k < size; ++k)
        {
            // obtener rango para el siguiente conjunto de `n` elementos
            auto start_itr = next(myVector.cbegin(), k*n);
            auto end_itr = next(myVector.cbegin(), k*n + n);
    
            // asignar memoria para el subvector
            chunks[k].resize(n);
    
            // código para manejar el último subvector como podría
            // contiene menos elementos
            if (k*n + n > myVector.size())
            {
                end_itr = myVector.cend();
                chunks[k].resize(myVector.size() - k*n);
            }
    
            // copia elementos del rango de entrada al subvector
            copy(start_itr, end_itr, chunks[k].begin());
        }
        cout << "\n El vector que ingreso es de " <<  max_Vector << " y se dividio en subvectores de 10 elementos." << endl;
        cout << "Aunque, es posible que el ultimo subvector tenga menos elementos. \n" << endl;
    
        // imprime los sub-vectores
        for (int i = 0; i < size; i++) {
            print_Vector(chunks[i]);
        }

    }else{
            
        cout << "Error. Ingreso un numero negativo. Por favor, ingrese un valor mayor a cero para el tamano del vector.";
       
    }
    return 0;
}
