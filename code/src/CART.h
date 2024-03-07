#pragma once
#include <set>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Cart {
public:
    struct Node {
        Node* left;
        Node* right;
        int splitting_feature;
        // int splitting_value;
        std::string value;
        /**
             * Node value constructor; sets children to point to NULL.
             * @param value The templated data value that the constructed
             *  node will hold.
             */
        Node():left(NULL),right(NULL),splitting_feature(-1),value(""){};
        Node(const std::string& val) : left(NULL), right(NULL), splitting_feature(-1), value(val) {}
        friend bool operator== (const Node& c1, const Node& c2) {
            if(c1.left==NULL&&c2.left==NULL) { //leaf
                return c1.value==c2.value;
            }
            return c1.splitting_feature==c2.splitting_feature;
        }
    };
   /** 
    * default constructor
    * not sure if it will be used
    */
    Cart();
   /** 
    * parameterized constructor
    * will set up decision tree
    *
    * @param classes vector of class labels for each entry in the dataset
    * @param data 2d vector where each column is a feature. Must have as many rows as classes has elements
    * this should be a rectangular 2d vector
    * @param depth the maximum height of the tree
    */
    Cart(vector<string> classes, vector<vector<int>> data, int depth);

   /**
    * function which uses build decision tree to classify a sample feature set
    * into a class
    *
    * @param sample vector of features to be classified
    */
    std::string Classify(std::vector<int>& sample);

    Node* getRoot() { return root; };


   /**
    * calculates Gini impurity of the dataset if split by the given feature
    *
    * Gini Impurity of a split is found by taking the weighted sum of the 
    * Gini Impurities of the resulting subsets, where the Gini Impurity of 
    * a set is equal to one minus the sum of the probabilities, squared, 
    * that a random element in the set has each class label. 
    * For example, the Gini Impurity of splitting {0,1,1,1} in the middle ( 0 1 | 1 1 ) 
    * would be .5 * (1 - (.5^2 + .5^2)) + .5 * (1 - (0^2 + 1^2)) = .25
    * 
    * @param classes vector of class labels for each entry in the dataset
    * @param data 2d vector whre each column is a feature. Must have as many rows as classes has elements
    * this should be a rectangular 2d vector
    * @param feature the index of the feature which should be split upon
    */
    double GiniImpurity(vector<pair<string,vector<int>>>::iterator begin,vector<pair<string,vector<int>>>::iterator end, int feature);
    

    Node* root;
    set<string> labels;
    int size;
    void ConstructTree(vector<pair<string,vector<int>>>::iterator begin,vector<pair<string,vector<int>>>::iterator end, int depth, Node* subroot);
    int findSplit(vector<pair<string,vector<int>>>::iterator begin,vector<pair<string,vector<int>>>::iterator end);
    string Classify(std::vector<int>& sample, Node* subroot);
};