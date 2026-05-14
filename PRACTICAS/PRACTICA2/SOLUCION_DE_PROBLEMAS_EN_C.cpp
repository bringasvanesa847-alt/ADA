#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void removeDuplicatesJSON(const string& inputFile, const string& outputFile) {
    unordered_set<string> seen;
    vector<json> result;

    try {
        ifstream infile(inputFile);

        if (!infile.is_open()) {
            cout << "Error: no se pudo abrir el archivo" << endl;
            return;
        }

        json data;
        infile >> data;  
        // Tiempo: O(n)
        // Memoria: O(n)

        for (auto& t : data) {
            string tid = t["transaction_id"];

            if (seen.find(tid) == seen.end()) {
                // Busqueda O(1)

                seen.insert(tid);
                // Insercion O(1)

                result.push_back(t);
                // O(1)
            }
        }

        ofstream outfile(outputFile);
        outfile << json(result).dump(4);
        // Escritura O(n)

        cout << "Archivo JSON creado correctamente" << endl;

    } catch (...) {
        cout << "Error procesando el archivo" << endl;
    }
}

int main() {
    removeDuplicatesJSON("transaction_data.json", "output.json");
    return 0;
}