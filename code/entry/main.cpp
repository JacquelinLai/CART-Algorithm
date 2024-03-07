#include <iostream>
#include <fstream>
#include <string>
#include "CART.h"
#include "input.cpp"
#include <ctime>
#include <iterator>
#include <random>

int main() {

    std::ofstream output("../../results/output.txt");
    output<<"Benchmarking:"<<std::endl<<std::endl;
    std::vector<std::vector<std::string>> Ys;
    std::vector<std::vector<std::vector<int>>> Xs;
    std::vector<std::vector<std::string>> Y_tests;
    std::vector<std::vector<std::vector<int>>> X_tests;
    std::vector<std::string> names = {"Test Dataset", "Disease Symptom Dataset", "Symptom Checker Dataset", "Stroke Dataset", "CDC Diabetes Dataset"};
    Ys.push_back(buildClasses("../../data/test_dataset_Y.csv"));
    Xs.push_back(buildData("../../data/test_dataset_X.csv"));
    Y_tests.push_back(buildClasses("../../data/test_dataset_Y.csv"));
    X_tests.push_back(buildData("../../data/test_dataset_X.csv"));

    Ys.push_back(buildClasses("../../data/Disease_symptom_yTrain.csv"));
    Xs.push_back(buildData("../../data/Disease_symptom_XTrain.csv"));
    Y_tests.push_back(buildClasses("../../data/Disease_symptom_yTest.csv"));
    X_tests.push_back(buildData("../../data/Disease_symptom_XTest.csv"));

    Ys.push_back(buildClasses("../../data/Symptom_Checker_yTrain.csv"));
    Xs.push_back(buildData("../../data/Symptom_Checker_XTrain.csv"));
    Y_tests.push_back(buildClasses("../../data/Symptom_Checker_yTest.csv"));
    X_tests.push_back(buildData("../../data/Symptom_Checker_XTest.csv"));

    Ys.push_back(buildClasses("../../data/Stroke_Data_yTrain.csv"));
    Xs.push_back(buildData("../../data/Stroke_Data_XTrain.csv"));
    Y_tests.push_back(buildClasses("../../data/Stroke_Data_yTest.csv"));
    X_tests.push_back(buildData("../../data/Stroke_Data_XTest.csv"));

    Ys.push_back(buildClasses("../../data/CDC_Diabetes_yTrain.csv"));
    Xs.push_back(buildData("../../data/CDC_Diabetes_XTrain.csv"));
    Y_tests.push_back(buildClasses("../../data/CDC_Diabetes_yTest.csv"));
    X_tests.push_back(buildData("../../data/CDC_Diabetes_XTest.csv"));
    output<<"Benchmark on number of elements/features, tree height capped at 4"<<std::endl<<std::endl;
    for(int i=0;i<5;i++) {
        
        output<<names[i]+": Build Tree\t\tElements: "+std::to_string(Ys[i].size())+"\t\tFeatures: "+std::to_string(Xs[i][0].size())<<std::endl;
        clock_t start = std::clock();
        Cart c(Ys[i],Xs[i],4);
        clock_t end = std::clock();
        output<<"Build time: "<<(double)(end-start)/CLOCKS_PER_SEC<<" seconds"<<std::endl<<std::endl;

        output<<names[i]+": Classify Samples\t\tElements: "+std::to_string(Y_tests[i].size())+"\t\tFeatures: "+std::to_string(X_tests[i][0].size())<<std::endl;
        int corr=0;
        int test=0;
        start=std::clock();
        for(unsigned int j=0;j<100;j++) {
            corr=0;
            test=0;
            for(unsigned int idx=0;idx<Y_tests[i].size();idx++) {
                std::string val = c.Classify(X_tests[i][idx]);
                if(val==Y_tests[i][idx]) {
                    corr++;
                }
                if(Y_tests[i][idx]==Y_tests[i][std::rand()%Y_tests[i].size()]) {
                    test++;
                }
            }
        }
        end=std::clock();
        output<<"Classify time: "<<(double)(end-start)/CLOCKS_PER_SEC<<" seconds for "+std::to_string(Y_tests[i].size()*100)+" samples, "<<(double)(end-start)/CLOCKS_PER_SEC/Y_tests[i].size()/100<<" seconds per sample"<<std::endl;
        output<<"Classify Accuracy: "<<(double)corr/Y_tests[i].size()<<"\t\tAccuracy of Random Guessing: "<<(double)test/Y_tests[i].size()<<std::endl<<std::endl;
        output<<"-----------------------------------------------------------------------------------------------------"<<std::endl<<std::endl;
    }
   return 0;
}