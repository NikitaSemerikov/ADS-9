// Copyright 2022 NNTU-CS
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <locale>
#include <vector>
#include "tree.h"

TreeNode::~TreeNode() {
    for (auto offspring : descendants) {
        delete offspring;
    }
}

void traverseAndCollect(TreeNode* currentNode, std::vector<char>& currentSequence,
                  std::vector<std::vector<char>>& allSequences) {
    if (!currentNode) return;

    currentSequence.push_back(currentNode->data);

    if (currentNode->descendants.empty()) {
        allSequences.push_back(currentSequence);
    } else {
        for (auto offspring : currentNode->descendants) {
            traverseAndCollect(offspring, currentSequence, allSequences);
        }
    }

    currentSequence.pop_back();
}

void PMTree::constructTree(TreeNode* parentNode, const std::vector<char>& remainingSymbols) {
    if (remainingSymbols.empty()) return;

    for (const char& symbol : remainingSymbols) {
        TreeNode* newChild = new TreeNode(symbol);
        parentNode->descendants.push_back(newChild);

        std::vector<char> updatedRemaining;
        for (const char& sym : remainingSymbols) {
            if (sym != symbol) {
                updatedRemaining.push_back(sym);
            }
        }

        constructTree(newChild, updatedRemaining);
    }
}

PMTree::PMTree(const std::vector<char>& inputSymbols) : origin(nullptr) {
    std::vector<char> sortedSymbols = inputSymbols;
    std::sort(sortedSymbols.begin(), sortedSymbols.end());
    origin = new TreeNode('\0');
    constructTree(origin, sortedSymbols);
}

PMTree::~PMTree() {
    delete origin;
}

std::vector<std::vector<char>> extractAllPermutations(const PMTree& permTree) {
    std::vector<std::vector<char>> allPermutations;
    std::vector<char> currentPermutation;

    for (auto firstLevel : permTree.getOrigin()->descendants) {
        traverseAndCollect(firstLevel, currentPermutation, allPermutations);
    }

    return allPermutations;
}

std::vector<char> fetchPermutationByNumber1(PMTree& permTree, int requestedNumber) {
    if (requestedNumber <= 0) return {};

    auto allPermutations = extractAllPermutations(permTree);
    if (requestedNumber > static_cast<int>(allPermutations.size())) {
        return {};
    }

    return allPermutations[requestedNumber - 1];
}

int calculateLeafCount(TreeNode* subtreeRoot) {
    if (!subtreeRoot) return 0;
    if (subtreeRoot->descendants.empty()) return 1;

    int totalLeaves = 0;
    for (auto offspring : subtreeRoot->descendants) {
        totalLeaves += calculateLeafCount(offspring);
    }
    return totalLeaves;
}

bool navigateToDesiredPermutation(TreeNode* currentPosition, int& remainingNumber, 
                                   std::vector<char>& accumulatedPath) {
    if (!currentPosition) return false;

    accumulatedPath.push_back(currentPosition->data);

    if (currentPosition->descendants.empty()) {
        if (remainingNumber == 1) {
            return true;
        } else {
            remainingNumber--;
            accumulatedPath.pop_back();
            return false;
        }
    }

    for (auto nextBranch : currentPosition->descendants) {
        int leavesInBranch = calculateLeafCount(nextBranch);
        if (remainingNumber <= leavesInBranch) {
            if (navigateToDesiredPermutation(nextBranch, remainingNumber, accumulatedPath)) {
                return true;
            }
        } else {
            remainingNumber -= leavesInBranch;
        }
    }

    accumulatedPath.pop_back();
    return false;
}

std::vector<char> fetchPermutationByNumber2(PMTree& permTree, int requestedNumber) {
    if (requestedNumber <= 0) return {};

    std::vector<char> foundPermutation;

    for (auto firstBranch : permTree.getOrigin()->descendants) {
        int leavesInFirstBranch = calculateLeafCount(firstBranch);
        if (requestedNumber <= leavesInFirstBranch) {
            int targetPosition = requestedNumber;
            if (navigateToDesiredPermutation(firstBranch, targetPosition, foundPermutation)) {
                return foundPermutation;
            }
        } else {
            requestedNumber -= leavesInFirstBranch;
        }
    }

    return {};
}
