// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include "textgen.h"
using namespace std;

class GenerateTest : public testing::Test {

TEST(GenerateTest, Prefix) {
    string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    textgen::Prefix prefix = { "Once", "there" };

    EXPECT_NE(gen.stateTable.find(prefix), gen.stateTable.end());
}

TEST(GenerateTest, Prefix_Suffix) {
    string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    textgen::Prefix prefix = { "Once", "there" };

    EXPECT_EQ(gen.stateTable[prefix][0], "lived");
}

TEST(GenerateTest, OnceSuffix) {
    string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    int maxgen = 1;
    string result = gen.generate(maxgen);

    EXPECT_EQ(result, "Once there lived ");
}

TEST(GenerateTest, VectorSuffix) {
    string text = "qwe rty uio a qwe rty uio b qwe rty uio c";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    int maxgen = 14;
    string result = gen.generate(maxgen);

    EXPECT_EQ(result, "qwe rty uio c ");
}

TEST(GenerateTest, Table) {
    string text = "qwe rty uio a qwe rty uio b qwe rty uio c";
    int prefixLength = 2;
    map<textgen::Prefix, vector<string>> stateTable = {
        {{"qwe", "rty"}, {"uio"}},
        {{"rty", "uio"}, {"a", "b"}},
        {{"uio", "a"}, {"qwe"}},
        {{"a", "qwe"}, {"rty"}}
    };

    textgen gen(stateTable);

    int maxgen = 2;
    string result = gen.generate(maxgen);

    EXPECT_EQ(result, "a qwe rty uio ");
}