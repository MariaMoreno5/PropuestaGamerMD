#include <fstream>
#include <string>
#include <random>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <limits>
#include <sys/mman.h>

using namespace std;




// Función de utilidad para imprimir un vector
template<typename T>

//Imprime el vector
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


//Se realiza el mapeo cargando la informacion desde el archivo de entrada

void archivo_entrada_mmap(int& tamano, char** data, const string& filename) { 
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        cout << "Error. No se puede abrir el archivo." << endl;
        exit(1); //En caso de error, se verifica que el archivo exista. 
    }
    struct stat st;
    //Esta funcion del mmap sirve para obtener la informacion del archivo de entrada
    if (fstat(fd, &st) < 0) { 
        cout << "Error. No se puede abrir el archivo." << endl;
        exit(1);
    }
    *data = reinterpret_cast<char*>(mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    //Esta funcion del mmap sirve para verificar que se mapeo exitosamente en memoria
    if (*data == MAP_FAILED) { 
        cout << "Error: no se pudo mapear el archivo en memoria." << endl;
        exit(1);
    }
    
}

int main() 
{

    char* data; //Se declara una variable llamada data de tipo puntero a caracter
    //Se esta creando una variable filename de tipo string y se esta asignando el valor de entrada.txt a dicha variable
    string filename("entrada.txt"); 
    vector<int> myVector;   //Se declara una variable llamada myVector que es un vector de enteros
    //Se declaran 4 variables tipo enteros. max_Vector, es el nombre del vector, mientras que aleatorio, tamano y n, son variables enteras adicionales
    int max_Vector, aleatorio, tamano, n, max_VectorAux; 
    //Esta linea de codigo utiliza la clase ramdon__device para declarar una variable llamada n_aleatoriop ara determinar numeros aleatorios
    random_device n_aleatorio; 
    //El mt19937 mt(n_aleatorio()), define un objeto de la clase mt, que utiliza un generador de numeros aleatorios 
    mt19937 mt(n_aleatorio());
    uniform_int_distribution<int> dist(1, 500);

    cout << "\nPor favor, ingrese un numero que indique el tamano del vector del archivo: ";
    cin >> max_Vector;

    max_VectorAux = max_Vector;
    
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

    //Abre nuestro archivo de entrada y verifica si se abrió correctamente.
    ifstream entrada_file(filename);
    if (!entrada_file.is_open()) {
        cout << "\nNo se pudo abrir el archivo.\n"
             << filename << "'" << endl;    //Nombre del archivo, entrada_file
        return EXIT_FAILURE;    //Fallo de salida
    }
    //Leer el contenido del archivo en un vector de enteros.
    while (entrada_file >>  max_Vector) {
        myVector.push_back( max_Vector);
    }
    entrada_file.close();   //Cerramos el archivo de entrada
    
    if(max_VectorAux > 0){ 
        int n = 0; 


        if(max_VectorAux < 500000){
            //Divide el vector en sub-vectores cada uno de 10 elementos.
            n = 10;
  
        }else{
            //Maximo 2.500.000. para que corra.
            //Divide el vector en 4 sub-vectores.
            n = max_VectorAux/4;
        }
        //Determina el número total de subvectores de tamaño "n"
        int size = (myVector.size() - 1) / n + 1;

        //Crea una array de vectores para almacenar los subvectores, chunks
        vector<int> chunks[size];

        for (int k = 0; k < size; ++k)
        {
            //Obtener rango para el siguiente conjunto de `n` elementos
            auto start_itr = next(myVector.cbegin(), k*n);
            auto end_itr = next(myVector.cbegin(), k*n + n);
    
            //Asignar memoria para el subvector y resize para el tamano del vector
            chunks[k].resize(n);
    
            //Código para manejar el último subvector, contiene menos elementos
            if (k*n + n > myVector.size())
            {
                end_itr = myVector.cend();
                chunks[k].resize(myVector.size() - k*n);
            }
    
            //Copia elementos del rango de entrada al subvector
            copy(start_itr, end_itr, chunks[k].begin());
        }

        cout << " \nEl numero ingresado es el tamano del vector dividido en " << n << " elementos por subvector." << endl;

        //Imprime los sub-vectores
        /*for (int i = 0; i < size; i++) {
            print_Vector(chunks[i]);
        }*/
        //Crea un archivo de salida y lo abre en modo escritura
        ofstream salida_file("salida.txt");

        //Escribe los elementos del vector en el archivo de salida
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
        //Cierra el archivo de salida
        
        salida_file.close();
    }else{
            
        cout << "\nError. Ingreso un numero negativo. Por favor, ingrese un valor mayor a cero para el tamano del vector.";
       
    }

    //El ifstream es para leer los datos del archivo de entrada
    if(ifstream(filename))
    {
        
        archivo_entrada_mmap(tamano, &data, filename);
        cout << "\nEl archivo se ha mapeado en memoria de forma exitosa. \n";
        
        return 0;

    }else{
        cout << "\nEl archivo de entrada no se ha generado." << filename << "." << endl;
        return 1;
    }

    cout << endl;
    getchar();
    return 0;
}






