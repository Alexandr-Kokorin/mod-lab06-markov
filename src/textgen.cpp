// Copyright 2024 Kokorin Alexandr

#include "textgen.h"
#include <time.h>
#include <random>
#include <deque>
#include <map>
#include <vector>
using namespace std;

textgen::textgen(const string& text, int prefixLength) {
    vector<string> table;
    int left = 0;
    for (int i = 0; i <= text.size(); i++) {
        if (text[i] == ' ' || i == text.size()) {
            string word;
            word.append(text, left, i - left);
            table.push_back(word);
            left = i + 1;
        }
    }
    for (int i = 0; i < prefixLength; i++) {
        prefix.push_back(table[i]);
    }
    for (int i = 0; i < table.size() - prefixLength; i++) {
        Prefix p;
        for (int j = 0; j < prefixLength; j++) {
            p.push_back(table[i + j]);
        }
        stateTable[p].push_back(table[i + prefixLength]);
    }
}

textgen::textgen(const map<Prefix, vector<string>>& stateTable) {
    this.stateTable = stateTable;
    if (!stateTable.empty()) {
        auto item = stateTable.begin();
        prefix = item->first;
    }
}

string textgen::generate(int maxgen) {
    string text;
    int seed = time(0);
    default_random_engine gen(seed);
    for (int i = 0; i < prefix.size(); i++) {
        text += prefix[i];
        text += ' ';
    }
    for (int i = 0; i < maxgen && stateTable.find(prefix) != stateTable.end(); i++) {
        vector<string> suffix = stateTable[prefix];
        if (!suffix.empty()) {
            uniform_int_distribution<> dist(0, suffix.size() - 1);
            int randomIndex = dist(gen);
            text += suffix[randomIndex] + ' ';
            prefix.pop_front();
            prefix.push_back(suffix[randomIndex]);
        }
        else {
            break;
        }
    }

    return text;
}