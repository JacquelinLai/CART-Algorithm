#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> buildData(const string& filename)
{
    vector<vector<int>> data;
    ifstream file(filename);
    string line;
    int width=-1;
    getline(file,line);
    while (getline(file, line)) { // get each data from the file rows by rows
        vector<int> row;
        stringstream ss(line); 
        string token;

        while (std::getline(ss, token, ',')) {
            try {
                int value = std::stoi(token);
                row.push_back(value);
            } catch (const std::invalid_argument&) {
                // If the token is not an integer, it's a string (header)
                throw std::invalid_argument("Dataset contains '"+token+"', which cannot be converted to an integer");
            }
        }

        if(width==-1)  {
            width=row.size();
        } else {
            if((int)row.size()!=width) {
                throw std::invalid_argument("Dataset is not rectangular");
            }
        }
        data.push_back(row);
    }

    return data;
}

vector<string> buildClasses(const string& filename)
{
    vector<string> data;
    ifstream file(filename);
    string line;
    bool isFirstRow = true;

    while (getline(file, line)) {
        // Skip the first line if it contains the header
        if (isFirstRow) {
            isFirstRow = false;
            continue;
        }

        data.push_back(line);
    }

    return data;
}