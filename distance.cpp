#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;


std::vector<int> cost_insert(26), cost_delete(26);
std::vector<std::vector<int>> cost_replace(26, std::vector<int>(26));
std::vector<std::vector<int>> cost_transpose(26, std::vector<int>(26));

void leer_fila(const std::string& filename, std::vector<int>& costs) {
    std::ifstream file(filename);
    for (int i = 0; i < 26; ++i) {
        file >> costs[i];
    }
}

void leer_matriz(const std::string& filename, std::vector<std::vector<int>>& costs) {
    std::ifstream file(filename);
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            file >> costs[i][j];
        }
    }
}

void lect_costos() {
    leer_fila("cost_insert.txt", cost_insert);
    leer_fila("cost_delete.txt", cost_delete);
    leer_matriz("cost_replace.txt", cost_replace);
    leer_matriz("cost_transpose.txt", cost_transpose);
}





int costo_ins(char b) {
    return cost_insert[b - 'a'];
}

int costo_del(char a) {
    return cost_delete[a - 'a'];
}

int costo_sub(char a, char b) {
    return cost_replace[a - 'a'][b - 'a'];
}

int costo_trans(char a, char b) {
    return cost_transpose[a - 'a'][b - 'a'];
}



//FUERZA BRUTA
int fb(const std::string& S1, const std::string& S2) {
    if (S1.empty()) {
        int cost = 0;
        for (char c : S2) cost += costo_ins(c);
        return cost;
    }
    if (S2.empty()) {
        int cost = 0;
        for (char c : S1) cost += costo_del(c);
        return cost;
    }
    int case1 = costo_ins(S2[0]) + fb(S1, S2.substr(1));
    int case2 = costo_del(S1[0]) + fb(S1.substr(1), S2);
    int case3 = costo_sub(S1[0], S2[0]) + fb(S1.substr(1), S2.substr(1));
    int case4 = INT_MAX;
    if (S1.size() > 1 && S2.size() > 1 && S1[0] == S2[1] && S1[1] == S2[0]) {
        case4 = costo_trans(S1[0], S1[1]) + fb(S1.substr(2), S2.substr(2));
    }
    return std::min({case1, case2, case3, case4});
}


//PROGRAMACION DINAMICA
int dp(const std::string& S1, const std::string& S2) {
    int n = S1.size(), m = S2.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) dp[i][0] = dp[i - 1][0] + costo_del(S1[i - 1]);
    for (int j = 1; j <= m; ++j) dp[0][j] = dp[0][j - 1] + costo_ins(S2[j - 1]);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = std::min({
                dp[i - 1][j] + costo_del(S1[i - 1]),
                dp[i][j - 1] + costo_ins(S2[j - 1]),
                dp[i - 1][j - 1] + costo_sub(S1[i - 1], S2[j - 1])
            });
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + costo_trans(S1[i - 2], S1[i - 1]));
            }
        }
    }
    return dp[n][m];
}

int main() {
    lect_costos();

    std::ifstream input("strings.txt");
    if (!input.is_open()) {
        std::cerr << "Error al abrir el archivo datasets.txt" << std::endl;
        return 1;
    }

    std::ofstream output("results.txt");
    if (!output.is_open()) {
        std::cerr << "Error al crear el archivo results.txt" << std::endl;
        return 1;
    }

    std::string S1, S2;

    while (std::getline(input, S1)) { 
        if (!std::getline(input, S2)) {
            std::cerr << "Formato de archivo incorrecto. Faltan pares S2 para algunas S1." << std::endl;
            break;
        }

        std::string linea;
        std::getline(input, linea);

        output << "S1 " << S1 << "\nS2 " << S2 << "\n";

        //FUERZA BRUTA
        auto start_fb = std::chrono::high_resolution_clock::now();
        int res_fb = fb(S1, S2);
        auto end_fb = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tiempo_bruta = end_fb - start_fb;

        //PROG DINAMICA
        auto start_dp = std::chrono::high_resolution_clock::now();
        int res_dp = dp(S1, S2);
        auto end_dp = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tiempo_dp = end_dp - start_dp;

        output << "con Fuerza Bruta: " << res_fb << "\n";
        output << "tiempo ejecución FB: " << tiempo_bruta.count() << " seg\n";
        output << "con Programación Dinámica: " << res_dp << "\n";
        output << "tiempo ejecución DP: " << tiempo_dp.count() << " seg\n";
        output << "----------------------------------------\n";
    }

    input.close();
    output.close();
    return 0;
}
