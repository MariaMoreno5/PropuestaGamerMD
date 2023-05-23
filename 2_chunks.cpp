#include <iostream>
#include <fstream>
#include <random>


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

int main() {

    string filename("entrada.txt");
    vector<int> myVector;
    int max_Vector, aleatorio;
    random_device n_aleatorio;
    mt19937 mt(n_aleatorio());
    uniform_int_distribution<int> dist(1, 500);
    cout << "Por favor, ingrese un numero que indique el tamano del vector del archivo: ";
    cin >> max_Vector;
    // Genera el archivo
    ofstream archivo("entrada.txt");
    archivo << max_Vector << ' ' <<endl; // tamaño en la primera posicion
    // llena el archivo
    for (int i = 0; i < max_Vector; ++i) {
        aleatorio = dist(n_aleatorio);
        archivo << aleatorio << " ";

    }

    archivo << endl;
    archivo.close();//cierra el archivo

    //Abrir el archivo de entrada y verificar si se abrió correctamente.
    ifstream entrada_file(filename);
    if (!entrada_file.is_open()) {
        cerr << "No se pudo abrir el archivo."
             << filename << "'" << endl;    //Nombre del archivo, entrada_file
        return EXIT_FAILURE;    //Fallo de salida
    }
    
    //Leer el contenido del archivo en un vector de enteros.
    while (entrada_file >>  max_Vector) {
        myVector.push_back( max_Vector);
    }
    entrada_file.close();   //Cerramos el archivo de entrada
    
    if(max_Vector > 0){ 
   
     //divide el vector en sub-vectores cada uno de 10 elementos.
        int n = 10;
              
    // determina el número total de subvectores de tamaño "n"
        int size = (myVector.size() - 1) / n + 1;
 
        // crea una array de vectores para almacenar los subvectores, chunks
        vector<int> chunks[size];
 
       
        for (int k = 0; k < size; ++k)
        {
            // obtener rango para el siguiente conjunto de `n` elementos
            auto start_itr = next(myVector.cbegin(), k*n);
            auto end_itr = next(myVector.cbegin(), k*n + n);
    
            // asignar memoria para el subvector y resize para el tamano del vector
            chunks[k].resize(n);
    
            // código para manejar el último subvector, contiene menos elementos
            if (k*n + n > myVector.size())
            {
                end_itr = myVector.cend();
                chunks[k].resize(myVector.size() - k*n);
            }
    
            // copia elementos del rango de entrada al subvector
            copy(start_itr, end_itr, chunks[k].begin());
        }
        cout << " \nEl numero que ingreso es el tamano del vector que se divide en subvectores de 10 elementos." << endl;
        cout << "Aunque, es posible que el ultimo subvector tenga menos elementos. \n" << endl;
    
        // imprime los sub-vectores
        for (int i = 0; i < size; i++) {
            print_Vector(chunks[i]);
        }
        // Crear un archivo de salida y abrirlo en modo escritura
        ofstream salida_file("salida.txt");

        // Escribir los elementos del vector en el archivo de salida
        for (int i = 0; i < size; ++i) {
            vector<int> vector_aux=chunks[i];
            for (int j=0; j < vector_aux.size(); j++){

                if(vector_aux[j]<10){
                    salida_file << " "<< vector_aux[j] << " ";
                }else{
                    salida_file << vector_aux[j] << " ";            
                }
                
            }
            salida_file << "\n";
        }
        // Cerrar el archivo de salida
        
        salida_file.close();
    }else{
            
        cout << "Error. Ingreso un numero negativo. Por favor, ingrese un valor mayor a cero para el tamano del vector.";
       
    }

    
    cout << endl;
    getchar();
    return 0;
}