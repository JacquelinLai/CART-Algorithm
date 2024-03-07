#include "CART.h"
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

Cart::Cart() {

}

Cart::Cart(vector<string> classes, vector<vector<int>> data, int depth) {
    labels = set<string>();
    size = classes.size();
    for(string s: classes) {
        labels.insert(s);
    }
    vector<pair<string, vector<int>>> dataset;
    for(int i=0;i<size;i++) {
        dataset.push_back(pair(classes[i],data[i]));
    }
    root = new Node();
    ConstructTree(dataset.begin(),dataset.end(),depth,root);
}

void Cart::ConstructTree(vector<pair<string,vector<int>>>::iterator begin,vector<pair<string,vector<int>>>::iterator end, int depth, Node* subroot) {
    if(depth==0) {
        // turn into impure leaf
        map<string,int> amounts;
        for(string s: labels) {
            amounts[s]=0;
        }
        for(auto i=begin;i!=end;i++) {
            amounts[i->first]++;
        }
        int max=0;
        string label;
        for(auto pair: amounts) {
            if(pair.second>max) {
                max=pair.second;
                label=pair.first;
            }
        }
        subroot->value=label;
        return;
    }
    bool isPure=true;
    for(auto i=begin;i!=end;i++) {
        if(i->first!=begin->first) {
            isPure=false;
            break;
        }
    }
    if(isPure) {
        //turn into pure leaf
        subroot->value=begin->first;
        return;
    }
    int feat = findSplit(begin, end);
    subroot->splitting_feature=feat;
    sort(begin,end,[&feat](auto &left, auto &right){
        return left.second[feat] > right.second[feat];
    });

    auto split = find_if(begin,end, [&feat](auto &elem){
        return elem.second[feat]==0;
    });
    subroot->left = new Node();
    ConstructTree(begin,split,depth-1,subroot->left);

    subroot->right = new Node();
    ConstructTree(split,end,depth-1,subroot->right);
}

string Cart::Classify(std::vector<int>& sample) {
    return Classify(sample, root);
}

string Cart::Classify(std::vector<int>& sample, Node* subroot) {
    if(subroot->left==NULL) {
        return subroot->value;
    }
    if(sample[subroot->splitting_feature]==1) {
        return Classify(sample, subroot->left);
    }
    return Classify(sample,subroot->right);
}


double Cart::GiniImpurity(vector<pair<string,vector<int>>>::iterator begin,vector<pair<string,vector<int>>>::iterator end, int feature) {
    int num_false=0;
    int num_true=0;
    map<string,int> r_amounts;
    map<string,int> l_amounts;
    int l_size=0;
    int r_size=0;
    for(string s: labels) {
        r_amounts[s]=0;
        l_amounts[s]=0;
    }
    for(auto i=begin;i!=end;i++) {
        if(i->second[feature]==1) { //left
            l_amounts[i->first]++;
            l_size++;
        } else {
            r_amounts[i->first]++;
            r_size++;
        }
    }
    double l=0; //find left Gini
    for(auto pairs: l_amounts) {
        l+=(double)pairs.second*pairs.second/l_size/l_size;
    }
    l=1-l;
    double r=0; //find right Gini
    for(auto pairs: r_amounts) {
        
        r+=(double)pairs.second*pairs.second/r_size/r_size;
        
    }
    r=1-r;
    

    //calculate weighted sum
    double out=(double)l_size/size*l+(double)r_size/size*r;
    return out;
}

int Cart::findSplit(vector<pair<string,vector<int>>>::iterator begin,vector<pair<string,vector<int>>>::iterator end) {
    int min_feature = 0;
    double min = 1;
    int idx=0;
    for(unsigned int i=0;i<begin->second.size();i++) {
        double curr = GiniImpurity(begin, end, idx);
        if(curr<min) {
            min=curr;
            min_feature=idx;
        }
        idx++;
    } 
    return min_feature;
}