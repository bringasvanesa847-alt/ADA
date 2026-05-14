// =========================================
// ALGORITMO DE HUFFMAN EN C++
// =========================================

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

// =========================================
// NODO DEL ÁRBOL
// =========================================

struct Node {

    char caracter;
    int frecuencia;

    Node* izquierda;
    Node* derecha;

    Node(char c, int f) {

        caracter = c;
        frecuencia = f;

        izquierda = nullptr;
        derecha = nullptr;
    }

    Node(char c, int f, Node* izq, Node* der) {

        caracter = c;
        frecuencia = f;

        izquierda = izq;
        derecha = der;
    }
};

// =========================================
// COMPARADOR PARA PRIORITY QUEUE
// =========================================

struct Compare {

    bool operator()(Node* a, Node* b) {

        return a->frecuencia > b->frecuencia;
    }
};

// =========================================
// CALCULAR FRECUENCIAS
// =========================================

unordered_map<char, int> calcularFrecuencias(const string& texto) {

    unordered_map<char, int> frecuencias;

    for (char c : texto) {
        frecuencias[c]++;
    }

    return frecuencias;
}

// =========================================
// CONSTRUIR ÁRBOL DE HUFFMAN
// =========================================

Node* construirArbolHuffman(
    unordered_map<char, int>& frecuencias
) {

    priority_queue<
        Node*,
        vector<Node*>,
        Compare
    > cola;

    // Crear nodos
    for (auto par : frecuencias) {

        cola.push(
            new Node(par.first, par.second)
        );
    }

    // Construir árbol
    while (cola.size() > 1) {

        Node* izquierda = cola.top();
        cola.pop();

        Node* derecha = cola.top();
        cola.pop();

        Node* combinado = new Node(
            '\0',
            izquierda->frecuencia + derecha->frecuencia,
            izquierda,
            derecha
        );

        cola.push(combinado);
    }

    return cola.top();
}

// =========================================
// GENERAR CÓDIGOS DE HUFFMAN
// =========================================

void generarCodigos(
    Node* raiz,
    string codigoActual,
    unordered_map<char, string>& codigos
) {

    if (raiz == nullptr) {
        return;
    }

    // Nodo hoja
    if (raiz->izquierda == nullptr &&
        raiz->derecha == nullptr) {

        codigos[raiz->caracter] = codigoActual;
    }

    // Izquierda = 0
    generarCodigos(
        raiz->izquierda,
        codigoActual + "0",
        codigos
    );

    // Derecha = 1
    generarCodigos(
        raiz->derecha,
        codigoActual + "1",
        codigos
    );
}

// =========================================
// CODIFICAR TEXTO
// =========================================

string codificarTexto(
    const string& texto,
    unordered_map<char, string>& codigos
) {

    string textoCodificado;

    for (char c : texto) {

        textoCodificado += codigos[c];
    }

    return textoCodificado;
}

// =========================================
// DECODIFICAR TEXTO
// =========================================

string decodificarTexto(
    const string& textoCodificado,
    Node* raiz
) {

    string textoDecodificado;

    Node* actual = raiz;

    for (char bit : textoCodificado) {

        if (bit == '0') {
            actual = actual->izquierda;
        }
        else {
            actual = actual->derecha;
        }

        // Nodo hoja
        if (actual->izquierda == nullptr &&
            actual->derecha == nullptr) {

            textoDecodificado += actual->caracter;

            actual = raiz;
        }
    }

    return textoDecodificado;
}

// =========================================
// FUNCIÓN PRINCIPAL
// =========================================

int main() {

    // =====================================
    // LEER ARCHIVO
    // =====================================

    string ruta = "DiarioTest.txt";

    ifstream archivo(ruta);

    if (!archivo.is_open()) {

        cout << "No se pudo abrir el archivo."
             << endl;

        return 1;
    }

    string texto;
    string linea;

    while (getline(archivo, linea)) {

        texto += linea;
        texto += '\n';
    }

    archivo.close();

    cout << "Texto original:\n" << endl;
    cout << texto << endl;

    // =====================================
    // FRECUENCIAS
    // =====================================

    unordered_map<char, int> frecuencias =
        calcularFrecuencias(texto);

    cout << "\nFrecuencias:\n" << endl;

    for (auto par : frecuencias) {

        cout << "'" << par.first
             << "': "
             << par.second
             << endl;
    }

    // =====================================
    // ÁRBOL HUFFMAN
    // =====================================

    Node* raiz =
        construirArbolHuffman(frecuencias);

    cout << "\nÁrbol de Huffman construido."
         << endl;

    // =====================================
    // GENERAR CÓDIGOS
    // =====================================

    unordered_map<char, string> codigos;

    generarCodigos(
        raiz,
        "",
        codigos
    );

    cout << "\nCódigos de Huffman:\n"
         << endl;

    for (auto par : codigos) {

        cout << "'" << par.first
             << "': "
             << par.second
             << endl;
    }

    // =====================================
    // CODIFICAR
    // =====================================

    string textoCodificado =
        codificarTexto(texto, codigos);

    cout << "\nTotal de bits codificados: "
         << textoCodificado.length()
         << endl;

    cout << "\nPrimeros 200 bits:\n"
         << endl;

    cout << textoCodificado.substr(0, 200)
         << endl;

    // =====================================
    // DECODIFICAR
    // =====================================

    string textoDecodificado =
        decodificarTexto(
            textoCodificado,
            raiz
        );

    cout << "\nTexto decodificado:\n"
         << endl;

    cout << textoDecodificado.substr(0, 200)
         << endl;

    // =====================================
    // VERIFICACIÓN
    // =====================================

    if (texto == textoDecodificado) {

        cout << "\nLa decodificación es correcta."
             << endl;
    }
    else {

        cout << "\nError en la decodificación."
             << endl;
    }

    return 0;
}