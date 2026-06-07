// Copyright 2022 NNTU-CS

#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <fstream>

void printPermutation(const std::vector<char>& perm, const std::string& label) {
    std::cout << label << ": ";
    for (char c : perm) {
        std::cout << c;
    }
    std::cout << std::endl;
}

template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

int generateRandomPermNumber(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    long long maxPerms = 1;
    for (int i = 2; i <= n; ++i) {
        maxPerms *= i;
    }
    std::uniform_int_distribution<long long> dist(1, maxPerms);
    return static_cast<int>(dist(gen));
}

void runExperiment() {
    std::ofstream dataFile("experiment_data.csv");
    dataFile << "n,getAllPerms_time_ms,getPerm1_time_ms,getPerm2_time_ms\n";

    std::cout << "\n=== ВЫЧИСЛИТЕЛЬНЫЙ ЭКСПЕРИМЕНТ ===\n";
    std::cout << std::setw(10) << "n"
              << std::setw(20) << "getAllPerms (ms)"
              << std::setw(20) << "getPerm1 (ms)"
              << std::setw(20) << "getPerm2 (ms)\n";
    std::cout << std::string(70, '-') << std::endl;

    for (int n = 2; n <= 10; ++n) {
        std::vector<char> symbols;
        for (int i = 0; i < n; ++i) {
            symbols.push_back('1' + i);
        }

        std::cout << "Построение дерева для n=" << n << "..." << std::endl;
        PMTree tree(symbols);

        int permNumber = generateRandomPermNumber(n);
        std::cout << "  Случайный номер перестановки: " << permNumber << std::endl;

        double timeAllPerms = measureTime([&]() {
            getAllPerms(tree);
        });

        double timePerm1 = measureTime([&]() {
            getPerm1(tree, permNumber);
        });

        double timePerm2 = measureTime([&]() {
            getPerm2(tree, permNumber);
        });

        std::cout << std::setw(10) << n
                  << std::setw(20) << std::fixed << std::setprecision(3) << timeAllPerms
                  << std::setw(20) << timePerm1
                  << std::setw(20) << timePerm2 << std::endl;

        dataFile << n << ","
                 << timeAllPerms << ","
                 << timePerm1 << ","
                 << timePerm2 << "\n";
    }

    dataFile.close();
    
    std::cout << "\nЭксперимент завершен.\n";
    std::cout << "Данные сохранены в файл experiment_data.csv\n";
    std::cout << "Постройте график зависимости времени от n, используя эти данные.\n";
    std::cout << "Рекомендуется использовать логарифмический масштаб вертикальной оси.\n";
}

int main() {
    std::cout << "=== ЗАДАНИЕ №1: Построение дерева ===\n";
    std::vector<char> in1 = {'1', '2', '3'};
    PMTree tree1(in1);
    std::cout << "Дерево для {'1','2','3'} успешно создано\n\n";

    std::cout << "=== ЗАДАНИЕ №2: getAllPerms ===\n";
    std::vector<std::vector<char>> perms = getAllPerms(tree1);
    std::cout << "Все перестановки для {'1','2','3'}:\n";
    for (size_t i = 0; i < perms.size(); ++i) {
        printPermutation(perms[i], "  Перестановка " + std::to_string(i + 1));
    }
    std::cout << "\n";

    std::cout << "=== ЗАДАНИЕ №3: getPerm1 и getPerm2 ===\n";
    
    std::vector<char> perm1 = getPerm1(tree1, 1);
    printPermutation(perm1, "getPerm1(tree, 1)");
    
    std::vector<char> perm2 = getPerm2(tree1, 2);
    printPermutation(perm2, "getPerm2(tree, 2)");
    
    std::vector<char> perm3 = getPerm1(tree1, 5);
    printPermutation(perm3, "getPerm1(tree, 5)");
    
    std::vector<char> perm4 = getPerm2(tree1, 6);
    printPermutation(perm4, "getPerm2(tree, 6)");
    
    std::vector<char> permInvalid = getPerm2(tree1, 10);
    printPermutation(permInvalid, "getPerm2(tree, 10) (не существует)");
    std::cout << "\n";

    std::cout << "=== Демонстрация для 4 символов ===\n";
    std::vector<char> in2 = {'1', '3', '5', '7'};
    PMTree tree2(in2);

    std::cout << "Первые 5 перестановок для {'1','3','5','7'}:\n";
    for (int i = 1; i <= 5; ++i) {
        std::vector<char> p = getPerm2(tree2, i);
        printPermutation(p, "  №" + std::to_string(i));
    }
    std::cout << "\n";

    runExperiment();

    return 0;
}
