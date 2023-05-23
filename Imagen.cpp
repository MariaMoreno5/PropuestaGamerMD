#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

void archivo_entrada_mmap(int& width, int& height, char** data, const string& filename, int& fd) {
    fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        cout << "Error. No se puede abrir el archivo." << endl;
        exit(1);
    }
    struct stat st;
    if (fstat(fd, &st) < 0) {
        cout << "Error. No se puede abrir el archivo." << endl;
        exit(1);
    }
    *data = reinterpret_cast<char*>(mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (*data == MAP_FAILED) {
        cout << "Error: no se pudo mapear el archivo en memoria." << endl;
        exit(1);
    }

    char magic_number[3];
    sscanf(*data, "%2s\n%d %d\n", magic_number, &width, &height);

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <ruta de la imagen PPM>" << endl;
        return 1;
    }
    string filename = argv[1];
    int width, height, fd;
    char* data;
    archivo_entrada_mmap(width, height, &data, filename, fd);

    //Imprimir mensaje de exito
    cout <<"\n La imagen se cargo de forma exitosa.\n"  <<endl;
   
    // Aquí puedes procesar la imagen como desees.

    // Desmapear la memoria y cerrar el archivo.
    munmap(data, width * height * 3 + 15); // Asumiendo que la imagen es de 8 bits por canal.
    close(fd);

    return 0;
}