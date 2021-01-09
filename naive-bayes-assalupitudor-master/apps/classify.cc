// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <gflags/gflags.h>

#include <string>
#include <cstdlib>
#include <iostream>


// TODO(you): Change the code below for your project use case.

DEFINE_string( model_address, "data/model.txt", "The json file for a model, if you want to use your own");
DEFINE_bool(should_train, true, "Should the model be trained");
DEFINE_string(training_images, "data/trainingimages", "images to train on");
DEFINE_string(training_labels, "data/traininglabels", "labels to train on");
DEFINE_string(test_images, "data/testimages", "images to test on");
DEFINE_string(test_labels, "data/testlabels", "labels to test on");

//main method parser
std::string ParseData(string file_address) {
    string data;
    string line;
    std::ifstream input_file(file_address);
    if (input_file.is_open()) {
        while(std::getline(input_file, line)) {
            data += line;
        }
        input_file.close();
        return data;
    } else {
        return "";
    }
}

//main method
int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_should_train) {
        bayes::Model model;
        model.train(FLAGS_training_images, FLAGS_training_labels);
        std::ofstream(output_file);
        output_file.open("data/model.txt");
        output_file << model;
        output_file.close();
    }

    bayes::Model model;
    string model_data = ParseData(FLAGS_model_address);
    std::istringstream iss(model_data);
    iss >> model;

    model.train(FLAGS_training_images, FLAGS_training_labels);

    bayes::Classifier classifier;
    vector<int> classified_labels = classifier.Classify(FLAGS_test_images, model);
    std::cout << "finished classifiying" << std::endl;
    vector<int> ground_truth_labels = bayes::Classifier::ParseLabels("data/testlabels");
    //Find % matches...
    int matches = 0;
    for (int i = 0; i < classified_labels.size(); ++i) {
        if (classified_labels[i] == ground_truth_labels[i]) {
            ++matches;
        }
    }
    double percent_correct = ((double) matches) / classified_labels.size() * 100.0;
    std::cout << "Correct: " << percent_correct << "%" << std::endl;
    return EXIT_SUCCESS;

}