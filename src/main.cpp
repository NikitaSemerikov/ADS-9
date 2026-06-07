// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::vector<std::vector<char>> perms = getAllPerms(tree);
    std::cout << "All permutations:\n";
    for (const std::vector<char>& perm : perms) {
        for (char c : perm) std::cout << c;
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "Permutations by index:\n";
    std::vector<char> p1 = getPerm1(tree, 1);
    std::cout << "getPerm1(1): ";
    for (char c : p1) std::cout << c;
    std::cout << "\n";

    std::vector<char> p2 = getPerm2(tree, 2);
    std::cout << "getPerm2(2): ";
    for (char c : p2) std::cout << c;
    std::cout << "\n\n";

    std::cout << "Computational experiment:\n";
    std::vector<int> sizes = {3, 4, 5};

    for (int n : sizes) {
        std::vector<char> test_input;
        for (int i = 0; i < n; ++i) {
            test_input.push_back('1' + i);
        }
        PMTree test_tree(test_input);

        std::chrono::high_resolution_clock::time_point start =
            std::chrono::high_resolution_clock::now();
        getAllPerms(test_tree);
        std::chrono::high_resolution_clock::time_point end =
            std::chrono::high_resolution_clock::now();
        std::chrono::microseconds time_all =
            std::chrono::duration_cast<std::chrono::microseconds>(
                end - start);

        start = std::chrono::high_resolution_clock::now();
        getPerm1(test_tree, 1);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds time_perm1 =
            std::chrono::duration_cast<std::chrono::microseconds>(
                end - start);

        start = std::chrono::high_resolution_clock::now();
        getPerm2(test_tree, 1);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds time_perm2 =
            std::chrono::duration_cast<std::chrono::microseconds>(
                end - start);

        std::cout << "n=" << n
                  << ", getAllPerms: " << time_all.count() << " us"
                  << ", getPerm1: " << time_perm1.count() << " us"
                  << ", getPerm2: " << time_perm2.count() << " us\n";
    }

    return 0;
}
