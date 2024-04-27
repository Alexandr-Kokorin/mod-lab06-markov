// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include "textgen.h"

class GenerateTest : public testing::Test {};

TEST(GenerateTest, Prefix) {
    std::string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    textgen::Prefix prefix = { "Once", "there" };

    EXPECT_NE(gen.stateTable.find(prefix), gen.stateTable.end());
}

TEST(GenerateTest, Prefix_Suffix) {
    std::string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    textgen::Prefix prefix = { "Once", "there" };

    EXPECT_EQ(gen.stateTable[prefix][0], "lived");
}

TEST(GenerateTest, OnceSuffix) {
    std::string text = "Once there lived an old man and old woman";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    int maxgen = 1;
    std::string result = gen.generate(maxgen);

    EXPECT_EQ(result, "Once there lived ");
}

TEST(GenerateTest, VectorSuffix) {
    std::string text = "aa bb cc x aa bb cc y aa bb cc z";
    int prefixLength = 2;

    textgen gen(text, prefixLength);

    int maxgen = 2;
    std::string result = gen.generate(maxgen);

    EXPECT_EQ(result, "aa bb cc y ");
}

TEST(GenerateTest, Table) {
    std::string text = "aa bb cc x aa bb cc y aa bb cc z";
    int prefixLength = 2;
    std::map<textgen::Prefix, std::vector<std::string>> stateTable = {
        {{"aa", "bb"}, {"cc"}},
        {{"bb", "cc"}, {"x", "y"}},
        {{"cc", "x"}, {"aa"}},
        {{"x", "aa"}, {"bb"}}
    };

    textgen gen(stateTable);

    int maxgen = 2;
    std::string result = gen.generate(maxgen);

    EXPECT_EQ(result, "aa bb cc y ");
}
