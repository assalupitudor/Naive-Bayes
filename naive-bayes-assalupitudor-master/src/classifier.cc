// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
using std::vector;
using std::string;
using std::ifstream;


namespace bayes {

    Classifier::Classifier() = default;

    //classifies into a vector of int
    vector<int> Classifier::Classify(const string& test_images_filename, Model model) {
        test_images = ParseImages(test_images_filename);
        for (size_t i = 0; i < test_images.size(); i++) {
            double max_prob = 0;
            int max_label = 0;
            for (size_t label = 0; label < kNumClasses; label++) {
                double prob = log(model.GetPrior(label));
                for (size_t row = 0; row < kImageSize; row++) {
                    for (size_t col = 0; col < kImageSize; col++) {
                        prob += log(model.GetConditionalProb(row, col, label,test_images[i].GetPixel(row, col)));
                    }
                }
                if (prob > max_prob) {
                    max_prob = prob;
                    max_label = label;
                }
            }
            test_labels.push_back(max_label);
        }
        return test_labels;
    }


    //parse images into a vector with Image object
    vector<Image> Classifier::ParseImages(const string& filename){
        vector<Image> images_vector;
        ifstream input_file(filename);
        int count = 0;
        string line;
        if (input_file.is_open()) {
            string image_string;
            while (getline(input_file, line)) {
                image_string += line;
                if (count == kImageSize - 1) {
                    std::istringstream iss(image_string);
                    Image image;
                    iss >> image;
                    images_vector.push_back(image);
                    image_string = "";
                    count = 0;
                } else {
                    ++count;
                }
            }
            input_file.close();
        } else {
            std::cout << "could not open the images file" << std::endl;
        }
        return images_vector;
    }

    //parse the labels into a vector corresponding to the images
    vector<int> Classifier::ParseLabels(const string& tr_labels_filename) {
        vector<int> labels;
        std::ifstream input_file(tr_labels_filename);
        if (input_file.is_open()) {
            std::string line;
            int class_type;
            while (std::getline(input_file, line)) {
                if (isdigit(line[0])) {
                    class_type = line[0] - '0';
                    labels.push_back(class_type);
                }
            }
            input_file.close();
        } else {
            std::cout << "could not open the label file" << std::endl;
        }
        return labels;
    }

}  // namespace bayes