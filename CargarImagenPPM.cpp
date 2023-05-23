#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Pixel {
    unsigned char r, g, b;
};

struct ImagePPM {
    int width;
    int height;
    int maxColorValue;
    std::vector<Pixel> pixels;
};

ImagePPM loadPPMImage(const std::string& filename) {
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        exit(1);
    }

    std::string magicNumber;
    inputFile >> magicNumber;
    if (magicNumber != "P6") {
        std::cerr << "Formato no soportado: " << magicNumber << std::endl;
        exit(1);
    }

    ImagePPM image;
    inputFile >> image.width >> image.height >> image.maxColorValue;
    inputFile.ignore(); // Ignora el salto de línea después del valor máximo de color

    image.pixels.resize(image.width * image.height);
    inputFile.read(reinterpret_cast<char*>(image.pixels.data()), image.width * image.height * 3);

    inputFile.close();
    return image;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo.ppm>" << std::endl;
        return 1;
    }

    ImagePPM image = loadPPMImage(argv[1]);
    std::cout << "La imagen fue cargada con éxito" << std::endl;

    return 0;
}
    