// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

namespace bayes {

    constexpr size_t kNumTests = 1000;

    class Classifier{
    private:
        vector<Image> test_images;
        vector<int> test_labels;

    public:
        Classifier();
        static vector<Image> ParseImages(const string& filename);
        static vector<int> ParseLabels(const string& tr_labels_filename);
        vector<int> Classify(const string& test_images_filename, Model model);
    };

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_
