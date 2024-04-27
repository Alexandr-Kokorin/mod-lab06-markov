// Copyright 2024 Kokorin Alexandr

#include <iostream>
#include <fstream>
#include <sstream>
#include "textgen.h"
using namespace std;

int main() {
    const int NREF = 2;
    const int MAXGEN = 1000;
    string text = "Once there lived an old man and old woman";
    textgen gen(text, NREF);
    text = gen.generate(MAXGEN);
    cout << text;
}