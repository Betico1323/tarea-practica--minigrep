#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void findMatches(const string& line, const string& pattern, int& count, string& outputLine) {
    size_t pos = line.find(pattern);
    size_t start = 0;
    while (pos != string::npos) {
        // Añadir la parte de la línea antes del patrón
        outputLine += line.substr(start, pos - start);
        // Añadir el patrón en color
        outputLine += "\033[1;31m" + pattern + "\033[0m"; 
        // Contar la coincidencia
        count++;
        // Mover la posición de inicio
        start = pos + pattern.size();
        pos = line.find(pattern, start);
    }
    
    outputLine += line.substr(start);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <archivo> <palabra>" << endl;
        return 1;
    }

    string filename = argv[1];
    string pattern = argv[2];

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;
    int matchCount = 0;
    int lineMatchCount = 0;

    while (getline(file, line)) {
        lineNumber++;
        string outputLine;
        int count = 0;
        findMatches(line, pattern, count, outputLine);
        if (count > 0) {
            lineMatchCount++;
            matchCount += count;
            cout << "Linea " << lineNumber << ": " << outputLine << endl;
        }
    }

    cout << "Lineas con coincidencias: " << lineMatchCount << endl;
    cout << "Numero total de coincidencias : " << matchCount << endl;

    file.close();
    return 0;
}


//Para ejecutar el programa compilamos primero y desde la terminal pegamos la siguiente linea de codigo debajo y se usa de ejemplo la palabra mani

//./'Tarea.exe' C:\Users\betom\Desktop\Tarea\output\Prueba.txt mani

