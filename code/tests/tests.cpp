#include <catch2/catch_test_macros.hpp>
#include <string>
#include "CART.h"
#include "input.cpp"
#include <cmath>
#include <utility>

using namespace std;

Cart ManualBuild();
Cart ManualBuildImpure();
bool SubtreesAreEqual(Cart::Node* t1, Cart::Node* t2);

TEST_CASE("Build Data", "[buildData]") {
    auto data=buildData("../../data/test_dataset_X.csv");
    vector<vector<int>> x = {
                            {1,1,1,1},
                            {1,1,0,0},
                            {1,0,1,0},
                            {0,1,1,1},
                            {0,1,0,1},
                            {0,1,1,0},
                            {0,1,0,0},
                            {0,0,1,1},
                            {0,0,0,1},
                            {0,0,1,0},
                            {0,0,0,0}
                            };
    REQUIRE(data == x);
}

TEST_CASE("Build Class", "[buildClass]") {
    vector<string> classes=buildClasses("../../data/test_dataset_Y.csv");
    vector<string> y = {"0","0","0","1","1","1","2","2","2","2","2"};
    cout<<classes.size()<<endl;
    
    REQUIRE(y==classes);
}

TEST_CASE("Gini Impurity", "[GiniImpurity]") {
    vector<string> classes=buildClasses("../../data/test_dataset_Y.csv");
    auto data=buildData("../../data/test_dataset_X.csv");
    vector<pair<string, vector<int>>> dataset;
    for(unsigned int i=0;i<classes.size();i++) {
        dataset.push_back(pair(classes[i],data[i]));
    }
    Cart cart = Cart(classes,data,5);
    //vector<double> expectedImpurities = {round(15.0/44*100)/100,round(431.0/900*100)/100,round(34.0/55*100)/100,round(103.0/165*100)/100};

    vector<double> foundImpurities = {cart.GiniImpurity(dataset.begin(),dataset.end(),0),cart.GiniImpurity(dataset.begin(),dataset.end(),1),cart.GiniImpurity(dataset.begin(),dataset.end(),2),cart.GiniImpurity(dataset.begin(),dataset.end(),3)};
    vector<double> expectedImpurities = {15.0/44,431.0/900,34.0/55,103.0/165};
    for(int i=0;i<4;i++) {
        REQUIRE(std::abs(foundImpurities[i]-expectedImpurities[i])<.001);
    }


    //REQUIRE(expectedImpurities==foundImpurities);
}

TEST_CASE("Construct Tree", "[Cart]") {
    vector<string> classes=buildClasses("../../data/test_dataset_Y.csv");
    auto data=buildData("../../data/test_dataset_X.csv");
    Cart expected = ManualBuild();

    Cart built = Cart(classes,data,10);
    cout<<built.root->left->value<<endl;
    REQUIRE(SubtreesAreEqual(built.root,expected.root));
}

TEST_CASE("Construct Tree with Impure Leaves", "[Cart]") {
    vector<string> classes=buildClasses("../../data/test_dataset_Y.csv");
    auto data=buildData("../../data/test_dataset_X.csv");
    Cart expected = ManualBuildImpure();

    Cart built = Cart(classes,data,2);
    cout<<built.root->left->value<<endl;
    REQUIRE(SubtreesAreEqual(built.root,expected.root));
}

TEST_CASE("Classify", "[Classify]") {
    // auto data=buildData("../../data/test_dataset_X.csv");
    // auto classes=buildClasses("../../data/test_dataset_Y.csv");
    std::vector<int> sample = {0,1,0,1};
    std::string expectedLabel = "1";
    Cart cart = ManualBuild();

    std::string label = cart.Classify(sample);

    REQUIRE(label==expectedLabel);
}


Cart ManualBuild() {
    Cart cart = Cart();

    cart.root = new Cart::Node();
    cart.root->left = new Cart::Node("0"); 
    Cart::Node* bottomLeft = cart.root->left; // leaf node
    cart.root->splitting_feature = 0; 

    cart.root->right = new Cart::Node();
    Cart::Node* right_ = cart.root->right;
    right_->splitting_feature = 1;

    right_->right = new Cart::Node("2"); 
    Cart::Node* right_2 = right_->right; // leaf node

    right_->left = new Cart::Node();
    Cart::Node* left_1 = right_->left;
    left_1->splitting_feature = 2;

    left_1->left = new Cart::Node("1"); 
    Cart::Node* left_2 = left_1->left; // leaf node

    left_1->right = new Cart::Node();
    Cart::Node* right_3 = left_1->right; 
    right_3->splitting_feature = 3;

    right_3->right = new Cart::Node("2");
    Cart::Node* right_4 = right_3->right; // leaf node
    
    right_3->left = new Cart::Node("1"); 
    Cart::Node* left_3 = right_3->left; // leaf node

    return cart;
}

Cart ManualBuildImpure() {
    Cart cart = Cart();

    cart.root = new Cart::Node();
    cart.root->left = new Cart::Node("0"); 
    Cart::Node* bottomLeft = cart.root->left; // leaf node
    cart.root->splitting_feature = 0; 

    cart.root->right = new Cart::Node();
    Cart::Node* right_ = cart.root->right;
    right_->splitting_feature = 1;

    right_->right = new Cart::Node("2"); 
    Cart::Node* right_2 = right_->right; // leaf node

    right_->left = new Cart::Node("1");
    Cart::Node* left_1 = right_->left;

    return cart;
}

bool SubtreesAreEqual(Cart::Node* t1, Cart::Node* t2) {
    if(t1==NULL && t2==NULL) {
        return true;
    }
    if(t1==NULL||t2==NULL) {
        return false;
    }
    return t1->splitting_feature==t2->splitting_feature && t1->value==t2->value && SubtreesAreEqual(t1->left,t2->left) && SubtreesAreEqual(t1->right,t2->right);
}