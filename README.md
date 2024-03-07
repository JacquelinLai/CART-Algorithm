# CART Algorithm

## Mark: The content in this repo is copied from CS225ECProject organization which is funded by Jacquelin Lai and Tyler Heaney, the content within the repo is also created by Jacquelin Lai and Tyler Heaney.

## Citation
- Lewis, Roger. (2000). An Introduction to Classification and Regression Tree (CART) Analysis. 
- University of Illinois CS 225 Course Resources, "Own Machine Setup Instructions." https://courses.engr.illinois.edu/cs225/fa2023/resources/own-machine/

## Dataset Information

This project uses the "Disease_Symptoms.csv", CDC_Diabetes.csv", "Symptom_Checker.csv", and "Stroke_Data.csv" listed in the `data` folder, with the derived Xtest, XTrain, yTest, yTrain datasets, providing a comprehensive framework for symptom-based disease prediction.

### Dataset License

The "Disease_Symptoms.csv" and CDC_Diabetes.csv" are provided under the [CC0: Public Domain License](https://creativecommons.org/publicdomain/zero/1.0/). This means that the datasets are in the public domain, and you are free to use, modify, and distribute it for any purpose without restrictions.

"Symptom_Checker.csv" and "Stroke_Data.csv" are primarily employed for analytical and modeling purposes within the scope of this project. Given the dataset’s public availability on Kaggle and the nature of this project (educational), it is assumed to be appropriate for such use. However, it's noteworthy that the dataset lacks an explicit license, and as such, its use is governed by Kaggle’s terms of service and ethical data usage principles. All efforts have been made to ensure compliance with these guidelines.

Please review the license terms at the provided link for more details.

# Class Coding Environment Setup

In this project, we recommend using the class coding environment provided by the University of Illinois CS 225 course for consistency and compatibility. Here are the instructions to set up your environment:

Follow the instruction on https://courses.engr.illinois.edu/cs225/fa2023/resources/own-machine/

Please get these installed on your local machine:
- [Git](https://git-scm.com/)
- [Docker](https://www.docker.com/)

**Warning: There is a separate installer between Intel and M1 Macs! Macbook users, if you don't know how to check your chip type, click the apple icon on the left top corner and hit "About This Mac". Try not install the version 4.24.0**
- [VScode](https://code.visualstudio.com/)

# Running the Code
1. Create `build` directory in `code`
2. cd into `build` and run `cmake .. && make && ./main` to start the benchmarking program. Be aware this takes multiple minutes. A report of accuracy and speed is  saved to `output.txt` in `results`
3. run `./test` to run the tests.

To view and modify any source files, `code/entry` holds the main.cpp file, while `code/src` holds the CART and input source codes. Tests are held in `code/tests`

# Documents
You can find the reference paper, our proposal, final report and presentation, our devlog, and images of the manual caculations we used to prove our tests were accurate in `documents`

Here you can also find a python file we used to clean the datasets, `data_cleaning.py`

# Feedback
Mentor feedback is found in the `mentor` directory

# Troubleshooting

If you encounter any issues during the setup process, refer to the official course documentation or seek assistance from CS225 course instructor or teacher/course assistants.