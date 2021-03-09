Assignment Spec

Handwriting recognition is the ability of a computer to interpret hand written text as the characters. In this assignment we will be trying to recognize numbers from images using a Naive Bayes classifier.

Naive Bayes classifiers are a family of probabilistic classifiers that are based on Bayes’ theorem. These algorithms work by combining the probabilities that an instance belongs to a class based on the value of a set of features. In this case, we will be testing if an image belongs to the class of the digits 0 to 9 based on the state of the pixels in the images.

It's not a requirement that you understand the math to complete this assignment, but learning a bit more about it might help.

Gradescope

You will need to submit your GitHub repository to Gradescope. There is a linter which is run on each submission; the results of the linter will be viewable by your code moderator when grading.

Getting Started

Get your copy of the assignment repo here: https://classroom.github.com/a/CD4zg1Uo.

The rubric can be found here.

We've changed the format of the CMake project a bit:

We have included gflags to help you parse command-line arguments. See the apps/classify.cc file for an example. Using this library is not required.
We have included nlohmann/json to help you (de)serialize your models if you decide to use JSON. Again, using this library is not required.
The CMake test configuration has been enhanced to run all of your tests from all of your test files. The target name is test-bayes. Make sure you only define CATCH_CONFIG_MAIN in one test file.
Part 0: The Data Files

For this assignment you will also need a set of pre-labeled data files that we will use for training and validation data, which you can download here.

The .zip file contains a few text files:

readme.txt: a description of the files in the .zip
testimages: 1000 images for validation/testing purposes
testlabels: the correct classification for each testing image
trainingimages: 5000 images for model training purposes
traininglabels: the correct classification for each training image
Do not commit these files to your Git repo! Instead, make sure they're blacklisted using the .gitignore. If do you accidentally commit them to your repo, you should remove them with git rm -r --cached.

You're going to build a Naive Bayes classification model that can classify unknown images as a number 0-9. Each image consists of 28 lines of 28 ASCII characters, in other words, they're 28x28. 
An individual character in an image will either be ' ' (a single space) for a white pixel, a '+' for a gray pixel, or a '#' for a black pixel. For simplicity's sake we're going to assume that white pixels are "not shaded" (0) and gray or black pixels are "shaded" (1).

Each image has a classification in the corresponding labels file; one classification per line.

Design hint: you might find your code from the previous assignment for reading in files to be useful, as well as using operator overloading for certain classes.

Part 1: Training the Classifier

So, we have a set of 28x28 images, and a set of corresponding labels that tell us what number 0-9 that image is. What do we do with this information?

Bayes' theorem is a statistical formula that describes the conditional probability that an event A will happen, given that some other event B already happened. It looks like this:


P(A∣B)= P(B∣A)P(A)/P(B)
​	
 
Or, "the probability that A will happen given that B happened, is the probability that B will happen given that A happened, times the probability that A will happen (independently), all divided by the probability that B will happen (independently)."

The goal of the training stage is to teach the computer the likelihood that a pixel is either shaded (1) or not shaded (0) for each one of the classes

In other words, we want be able to answer "what is the probability that a given pixel is shaded, given that it's supposed to be 0-9"?

You'll need to make a model that can answer questions like, "what is the probability that pixel (3, 17) is shaded when we were only looking at images that were a 7?" 
We've given you some starter code to help you out with this, though you're allowed (and encouraged!) to delete/modify/rename/move this code as you wish.


 
Given how we will use these probabilities we need to ensure that they are not zero, since if they are, it will cause them to cancel out any non-zero probability from other features. To do this we will use a technique called Laplace Smoothing. 
This technique works by adding a small positive value k to the numerator above, and k·V to the denominator (where V is the number of possible values (shaded or not shaded) our feature can take on, so 2). 
The higher the value of k, the stronger the smoothing is. So for our binary features that would give us:


You can experiment with different values of k (say, from 0.1 to 10) and find the one that gives the highest classification accuracy.

You also need to compute the priors, or the probability of each class 0-9 occurring independently of any features in the images. 


 
In other words, being able to answer questions like, "if I grab a random image, what's the probability that I'll get a 9?"

With the training done you will have an empirically generated set of probabilities that can be referred to as the model, which we will use to do classification on unknown data. 
This model, once generated, can be used in the future without needing to be regenerated; this is why we will require you to be able to save and load a calculated model to keep the runtime costs low.

Note: Do not train on the testing images! They are for validating the accuracy of your model only.

Testing hint: We have provided you with a tiny sample set of data in your tests/data/ folder that you test the behavior of your code!

Part 2: Classification

To classify the unknown images using the trained model you will perform maximum a posteriori (MAP) classification of the test data using the trained model. 
This technique computes the posterior probability of each class for the particular image, and then classifies the image as belonging to the class which has the highest posterior probability. 
Since we assume that all the probabilities are all independent of each other (this is the "naive" part in Naive Bayes), we can compute the probability that the image belongs to the class by 
simply multiplying all the probabilities together and dividing by the probability of the feature set. Finally, since we don’t actually need the probability but merely to be able to compare the values we can ignore the probability of the feature set


There's a problem with doing this, though. These probabilities are all going to be less than 1.0, which means if you multiply them all together they're going to get really small really fast and you'll run into the problem of Arithmetic Underflow. 
Since we don't actually care about the value (only which one is the largest), we can get around this by taking the log and adding instead of multiplying

  is the feature value of the input data. You can use the priors and probabilities from your model to calculate these posterior probabilites (look at Bayes' theorem!)

Once you have a posterior probability for your image for each class from 0-9 you should classify the image as the class with the highest posterior probability. For example for an input P, if we had the posterior probabilities:

class | posterior probability
------+----------------------
 0    | 0.3141
 1    | 0.432
 2    | 0.0
 3    | 0.0
 4    | 0.4
 5    | 0.004
 6    | 0.1
 7    | 0.2
 8    | 0.7
 9    | 0.5
we'd classify P as an 8, because that's the class with the highest posterior probability.

Part 3: Validation

What good is a classifier if you don't know how accurate it is? We've given you a set of testingimages and testinglabels; use your program to classify each of the testingimages with your generated model and compare the result to the actual label, and print out the accuracy of your Naive Bayes classifier.
