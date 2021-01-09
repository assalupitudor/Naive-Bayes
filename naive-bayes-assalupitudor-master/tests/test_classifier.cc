// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/image.h>
#include <iostream>
#include <vector>

using std::vector;
using bayes::Classifier;
//using bayes::Image;

TEST_CASE("Parsing images", "[parse-images]") {
    vector<bayes::Image> test_images_vector;
    test_images_vector = Classifier::ParseImages("data/tester", 1);
    std::string parse_output;
    std:: string required_output =
            "0000000000000000000000000000\n"
            "0000000000000000000000000000\n"
            "0000000000000000000000000000\n"
            "0000000000000000000000000000\n"
            "0000000000000000000000000000\n"
            "0000000000000000111111110000\n"
            "0000000011111111111111110000\n"
            "0000000111111111111111100000\n"
            "0000000011111111110000000000\n"
            "0000000011111100110000000000\n"
            "0000000000011100000000000000\n"
            "0000000000011100000000000000\n"
            "0000000000001110000000000000\n"
            "0000000000001111100000000000\n"
            "0000000000000111111000000000\n"
            "0000000000000011111100000000\n"
            "0000000000000000111100000000\n"
            "0000000000000000011110000000\n"
            "0000000000000011111100000000\n"
            "0000000000001111111100000000\n"
            "0000000000111111111000000000\n"
            "0000000011111111100000000000\n"
            "0000000111111110000000000000\n"
            "0000111111111000000000000000\n"
            "0000111111100000000000000000\n"
            "0000000000000000000000000000\n"
            "0000000000000000000000000000\n"
            "0000000000000000000000000000\n";
    for (int row = 0; row < 28; row++) {
        for (int col = 0; col < 28; col++) {
            parse_output +=  std::to_string(test_images_vector[0].GetPixelAt(row, col));
        }
        parse_output += "\n";
    }
    REQUIRE(parse_output == required_output);
}


