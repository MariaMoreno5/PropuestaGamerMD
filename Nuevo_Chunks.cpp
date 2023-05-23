#include <fstream>
#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <limits>
#include <chrono>

#include <fstream>
#include <random>


using namespace std;
using namespace chrono;



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

void divide_mmap(char* data, int &tamano, int n, int* chunks) { // Divide los chunks directamente en memoria
    char* endptr;
    for (int i = 0; i < tamano; i++) {
        *(chunks + i) = strtol(data, &endptr, 10);
        data = endptr;
    }
    int num_chunks = tamano / n + (tamano % n != 0); // Calcular el numero de chunks

    
   
}

void guardar_chunks_mmap(int* chunks, int tamano, int n, const string& filename) { // Guarda los chunks en el archivo
    ofstream archivo(filename);
    int num_chunks = tamano / n + (tamano % n != 0); // Calcular el numero de chunks
    int k = 0;
    while (k < tamano) {
        for (int j = 0; j < n; j++) {
            archivo << to_string(*(chunks + k)) << " ";
            k++;
            if (k >= tamano) {
                break;
            }
        }
        archivo << endl;
    }
    archivo.close();
}

void cargar_datos_mmap(int& tamano, char** data, const string& filename) { // carga toda la informacion desde el archivo de entrada
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        cerr << "Error: no se pudo abrir el archivo de entrada." << endl;
        exit(1); // verificamos que realmente exista el archivo. Esto en caso de error o corrupcion en el algoritmo principal
    }
    struct stat st;
    if (fstat(fd, &st) < 0) { // funcion del mmap para obtener la informacion del archivo_entrada
        cerr << "Error: no se pudo obtener el tamaño del archivo de entrada." << endl;
        exit(1);
    }
    *data = reinterpret_cast<char*>(mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (*data == MAP_FAILED) { //funcion del mmap para verificar que se mapeo exitosamente en memoria
        cerr << "Error: no se pudo mapear el archivo en memoria." << endl;
        exit(1);
    }
    char* endptr;
    tamano = strtol(*data, &endptr, 10); // el strtol es para convertir el numero en entero
    char* p = endptr;
    *data = p;
    close(fd);
}

int main() 
{

    char* data;
    string filename("entrada.txt");
    vector<int> myVector;
    int max_Vector, aleatorio, tamano, n;
    random_device n_aleatorio;
    mt19937 mt(n_aleatorio());
    uniform_int_distribution<int> dist(1, 500);

    cerr << "Por favor, ingrese un numero que indique el tamano del vector del archivo: ";
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
              
        //determina el número total de subvectores de tamaño "n"
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

 
    

    if(ifstream(filename)){
        /*do {
            cerr << "Tamano de los chunks: ";
            cin >> n;
            if (cin.fail() || n <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Debe ingresar un numero entero positivo." << endl;
            }





        }while (n <= 0);*/

            auto start_cargar_datos = high_resolution_clock::now();
            cargar_datos_mmap(tamano, &data, filename);
            auto end_cargar_datos = high_resolution_clock::now();
            duration<double> tiempo_cargar_datos = end_cargar_datos - start_cargar_datos;
            cout << "Archivo mapeado en memoria exitosamente. Tiempo de ejecución: " << tiempo_cargar_datos.count() << " segundos" << endl;

            /*auto start_divide_mmap = high_resolution_clock::now();
            int num_chunks = tamano / n + (tamano % n != 0); // Calcular el número de chunks
            int* chunks = new int[num_chunks * n];
            divide_mmap(data, tamano, n, chunks);
            auto end_divide_mmap = high_resolution_clock::now();
            duration<double> tiempo_divide_mmap = end_divide_mmap - start_divide_mmap;
            cout << "Datos divididos en " << n << " chunks en memoria. Tiempo de ejecución: " << tiempo_divide_mmap.count() << " segundos" << endl;

            auto start_guardar_chunks_mmap = high_resolution_clock::now();        
            guardar_chunks_mmap(chunks, tamano, n, "chunks.txt");
            auto end_guardar_chunks_mmap = high_resolution_clock::now();
            duration<double> tiempo_guardar_chunks_mmap = end_guardar_chunks_mmap - start_guardar_chunks_mmap;        
            cout << "Datos guardados en chunks.txt. Tiempo de ejecución: " << tiempo_guardar_chunks_mmap.count() << " segundos" << endl;

            auto end_total = high_resolution_clock::now();
            duration<double> tiempo_total = end_total - start_cargar_datos;
            cout << "Tiempo total de ejecución: " << tiempo_total.count() << " segundos" << endl;*/

            munmap(data, tamano * sizeof(int) + sizeof(int));
            //delete[] chunks;
        return 0;
    }else{
        cerr << "No ha generado el archivo de entrada " << filename << "." << endl;
        return 1;
    }

    cout << endl;
    getchar();
    return 0;
}









/*
int main() {

    

    
    
    
        

    
    cout << endl;
    getchar();
    return 0;
}*/