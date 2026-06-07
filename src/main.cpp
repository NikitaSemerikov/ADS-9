// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include "tree.h"

int main() {
    std::vector<char> initialSet = {'1', '2', '3'};
    PMTree permutationTree(initialSet);

    std::vector<std::vector<char>> allPermutations = extractAllPermutations(permutationTree);
    std::cout << "All permutations:\n";
    for (const std::vector<char>& singlePerm : allPermutations) {
        for (char symbol : singlePerm) std::cout << symbol;
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "Permutations by index:\n";
    std::vector<char> firstPermutation = fetchPermutationByNumber1(permutationTree, 1);
    std::cout << "fetchPermutationByNumber1(1): ";
    for (char symbol : firstPermutation) std::cout << symbol;
    std::cout << "\n";

    std::vector<char> secondPermutation = fetchPermutationByNumber2(permutationTree, 2);
    std::cout << "fetchPermutationByNumber2(2): ";
    for (char symbol : secondPermutation) std::cout << symbol;
    std::cout << "\n\n";

    std::cout << "Computational experiment:\n";
    std::vector<int> dimensionSizes = {3, 4, 5};

    for (int currentSize : dimensionSizes) {
        std::vector<char> testData;
        for (int idx = 0; idx < currentSize; ++idx) testData.push_back('1' + idx);
        PMTree testTree(testData);

        std::chrono::high_resolution_clock::time_point startTime =
        std::chrono::high_resolution_clock::now();
        extractAllPermutations(testTree);
        std::chrono::high_resolution_clock::time_point endTime =
        std::chrono::high_resolution_clock::now();
        std::chrono::microseconds durationAll =
        std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        startTime = std::chrono::high_resolution_clock::now();
        fetchPermutationByNumber1(testTree, 1);
        endTime = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds durationPerm1 =
        std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        startTime = std::chrono::high_resolution_clock::now();
        fetchPermutationByNumber2(testTree, 1);
        endTime = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds durationPerm2 =
        std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        std::cout << "n=" << currentSize
                  << ", extractAllPermutations: " << durationAll.count() << " us"
                  << ", fetchPermutationByNumber1: " << durationPerm1.count() << " us"
                  << ", fetchPermutationByNumber2: " << durationPerm2.count() << " us\n";
    }

    return 0;
}
