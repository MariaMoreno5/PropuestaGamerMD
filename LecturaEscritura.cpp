#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {


    string inputFileName = "entrada.txt";
    string outputFileName = "salida.txt";
    
    // Abrir el archivo de entrada
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada: " << inputFileName << endl;
        return 1;
    }
    
    // Abrir el archivo de salida
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de salida: " << outputFileName << endl;
        return 1;
    }
    
    // Leer línea por línea del archivo de entrada y escribir en el archivo de salida
    string line;
    while (getline(inputFile, line)) {
        outputFile << line << endl;
    }
    
    // Cerrar los archivos
    inputFile.close();
    outputFile.close();
    
    return 0;
}