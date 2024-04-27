// Copyright 2024 Kokorin Alexandr

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#pragma once
#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <string>
using namespace std;

class textgen {
public:
    typedef deque<string> Prefix;
    Prefix prefix;
    map<Prefix, vector<string> > stateTable;
public:
    textgen(const string& text, int prefixLength);
    textgen(const map<Prefix, vector<string>>& stateTable);
    string generate(int maxgen);
};
#endif  // INCLUDE_TEXTGEN_H_