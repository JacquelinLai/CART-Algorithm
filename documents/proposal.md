# Proposal: CART Model for Disease Prediction based on Symptoms


## Warning
This proposal outlines the development of a predictive model for disease diagnosis based on symptoms using the provided dataset. It is essential to approach medical data analysis with caution, as incorrect predictions can have severe consequences. The model should be used as a supportive tool and not as a sole diagnostic tool. Always consult with qualified medical professionals for accurate diagnosis and treatment.


## Academic Reference
The proposed project mainly draws inspiration from one research paper and one dataset related to disease prediction and decision tree-based models for medical diagnosis. Key academic references include:

**Literature**:
- Lewis, Roger. (2000). An Introduction to Classification and Regression Tree (CART) Analysis. 

**Environment Set-up Instruction**:
- University of Illinois CS 225 Course Resources, "Own Machine Setup Instructions." https://courses.engr.illinois.edu/cs225/fa2023/resources/own-machine/

**Dataset**:
- "Disease Symptoms and Patient Profile Dataset", imported as "Disease_symptom.csv". Kaggle. https://www.kaggle.com/datasets/uom190346a/disease-symptoms-and-patient-profile-dataset/data. Accessed Oct.31, 2023.
- "Diabetes Health Indicators Dataset", imported as "CDC_Diabetes.csv". Kaggle. https://www.kaggle.com/datasets/alexteboul/diabetes-health-indicators-dataset. Accessed Oct.31, 2023.
- "Symptom_checker", concatenated and imported as "Symptom_Checker.csv". Kaggle. https://www.kaggle.com/datasets/rabisingh/symptom-checker. Accessed Oct.31, 2023.
- "Stroke dataset", imported as "Stroke_Data.csv". Kaggle. https://www.kaggle.com/datasets/nikhilalakku/stroke-dataset. Accessed Dec.1, 2023.


## Algorithm Summary
The proposed algorithm for this project is the Classification and Regression Trees (CART) algorithm. CART is a robust decision tree-based machine learning technique suitable for both classification and regression tasks. In this context, we aim to use CART for disease classification based on patient symptoms. The algorithm summary includes:

- Utilizing GIni Impurity to measure the best way to split a dataset into two subsets such that each is closer to being of a single classification.
- Utilizing above splitting function to build a decision tree to map symptom patterns to disease classes.
- Traversing the built decision tree to find what disease most likely causes a set of symptoms. 
- Evaluating the model's performance using appropriate metrics (e.g., accuracy, precision, recall) and considering medical domain-specific evaluation criteria.

## Function I/O

### 1) Tree Constructor
`Cart::Cart(std::vector<std::string> classes, std::vector<std::vector<int>> data, int depth)`

Input:
- **@param classes** -- A vector of the class to which each row of the dataset is assigned
- **@param data** -- The dataset provided contains information on patients and their symptoms. It could include features such as patient age, gender, and various symptoms.
- **@param depth** -- the decision tree will stop recursing when the tree has this height, if it hasn't already completely purified the dataset

The constructor for our classification and regression tree takes the dataset as input and builds the decision tree by recursively splitting it by the feature which minimizes Gini Impurity. It continues to split the subsets until 'pure' (Gini Impurity = 0) sets are formed, or until reaching the depth parameter. A set is pure if all elements belong to a single class, so a CART that does not reach the max depth will have correctly classified every element in the dataset. If the height is reached, the resulting class label for that subset is simply the class the majority of elements in the subset.

Gini Impurity of a split is found by taking the weighted sum of the Gini Impurities of the resulting subsets, where the Gini Impurity of a set is equal to one minus the sum of the probabilities, squared, that a random element in the set has each class label. For example, the Gini Impurity of splitting {0,1,1,1} in the middle ( 0 1 | 1 1 ) would be .5 * (1 - (.5^2 + .5^2)) + .5 * (1 - (0^2 + 1^2)) = .25

Our tests one and two test that the tree is created correctly. The first tests that the algorithm successfully calculates which split variable has the best (meaning minimum) Gini Impurity, while the second tests that the constructor successfully recurses through the dataset and builds the decision tree correctly. The Gini test calculates the Gini Impurity of splitting the full test dataset by each feature, and compares these values to values calculated by hand. The second test builds the decision tree from the test dataset and compares the ToString output to how the tree should be structured, as found by manual calculations. 

For these tests, the Calculations.pdf file shows the hand-calculated values for Gini Impurity for each feature during each recursive step, and what the tree should look like, given these steps.

### 2) Sample Classifier
`std::string Cart::Classify(std::vector<int> sample)`

Input:
- **@param sample** -- A set of features which will be classified by the decision tree

Output:
- **@returns** -- the string value of the class the CART calculates the sample most likely belongs to

The classifier function traverses the decision tree until it reaches a leaf node. It returns the value of this node, which is the class the sample most likely falls under. At each decision node, there will be a feature the data splits on. The function traverses to the left if that feature is 1 for the sample, and traverses the right otherwise.

Our third test ensures that the classifier successfully labels samples. Following the tree built by hand, our test sample {0,1,0,1} should traverse the entire height of the tree before being classified in class 2.

## Data Description

### Datasets Overview:
- **Source**: 
    1. The first dataset(Disease_symptom.csv) is obtained from Kaggle and contains 349 rows of patient profiles with associated symptoms and disease diagnoses. It is originally already a csv file. Magnitude: 2
        - Disease_symptom_XTrain shape:  (279, 13), Magnitude: 2
        - Disease_symptom_yTrain shape:  (279, 1), Magnitude: 2
        - Disease_symptom_XTest shape:  (70, 13), Magnitude: 1
        - Disease_symptom_yTest shape:  (70, 1), Magnitude: 1
    2. The second dataset(CDC_Diabetes.csv) is obtained from Kaggle and contains 507360 rows of patient profiles with associated features and Diabetes diagnoses. It is originally already a csv file.
        - CDC_Diabetes shape:  (507360, 22), Magnitude: 5
        - CDC_Diabetes_XTrain shape:  (202944, 15), Magnitude: 5
        - CDC_Diabetes_yTrain shape:  (202944, 1), Magnitude: 5
        - CDC_Diabetes_XTest shape:  (50736, 15), Magnitude: 4
        - CDC_Diabetes_yTest shape:  (50736, 1), Magnitude: 4
    3. The third dataset(Symptom_Checker.csv) is obtained from Kaggle and contains 4961 rows of patient profiles with associated symptoms and disease diagnoses. It is originally already a csv file.
        - Symptom_Checker shape:  (4961, 133), Magnitude: 3
        - Symptom_Checker_XTrain shape:  (3968, 132), Magnitude: 3
        - Symptom_Checker_yTrain shape:  (3968, 1), Magnitude: 3
        - Symptom_Checker_XTest shape:  (993, 132), Magnitude: 2
        - Symptom_Checker_yTest shape:  (993, 1), Magnitude: 2
    4. The fourth dataset(Stroke_Data.csv) is obtained from Kaggle and contains 41938 rows of patient profiles with associated symptoms and disease diagnoses. It is originally already a csv file.
        - Stroke_Data shape:  (3968, 132), Magnitude: 4
        - Stroke_Data_XTrain shape:  (33550, 22), Magnitude: 4
        - Stroke_Data_yTrain shape:  (33550, 1), Magnitude: 4
        - Stroke_Data_XTest shape:  (8388, 22), Magnitude: 3
        - Stroke_Data_yTest shape:  (8388, 1), Magnitude: 3
    5. The test dataset (test_dataset.csv) was made by ourselves through manual calculations. It has 11 rows, 4 features and 3 classes (0, 1, and 2). Each feature is either 0 or 1.
        - test_dataset_X shape: (11, 4), Magnitude: 1
        - test_dataset_Y shape: (11, 1), Magnitude: 1

- **Preparation for Data Cleaning**: 
    - Set up a python virtual environment to clean the data
    - Installed python in the container
    - Used pip to install the numpy, pandas, sklearn packages, and ucimlrepo


### First Dataset Overview:
- **Source**: 
    The dataset (Disease_symptom.csv) is obtained from Kaggle and contains 349 rows of patient profiles with associated symptoms and disease diagnoses. It is originally already a csv file.

- **Features**: The dataset includes patient demographic information (age, gender), symptom data (binary values indicating symptom presence or absence).
- **Target**: The target variable is a categorical variable (string) representing different diseases diagnosis.

- **Column and Usage**:
    - Disease: The name of the disease or medical condition.
    - Fever: Indicates whether the patient has a fever (Yes/No).
    - Cough: Indicates whether the patient has a cough (Yes/No).
    - Fatigue: Indicates whether the patient experiences fatigue (Yes/No).
    - Difficulty Breathing: Indicates whether the patient has difficulty breathing (Yes/No).
    - Age: The age of the patient in years.
    - Gender: The gender of the patient (Male/Female).
    - Blood Pressure: The blood pressure level of the patient (Normal/High).
    - Cholesterol Level: The cholesterol level of the patient (Normal/High).
    - Outcome Variable: The outcome variable indicating the result of the diagnosis or assessment for the specific disease (Positive/Negative).

- **Data Preprocessing**:

    - **Data Cleaning**: Addressing missing values in the dataset.

    - **Variables Transformation**: This dataset contains both boolean and continuous variables. Since we are only focusing on the classification task, we will transform all the continuous variables into boolean variables. 

        - For boolean variable columns 
            - "Fever", "Cough", "Fatigue", "Difficulty Breathing":
                - 0(No) or 1(Yes)
            - "Outcome Variable": 
                - 0(Negative) or 1(Positive)
            - "Gender":
                - 0(Female) or 1(Male)
            - "Age":
                - 0(age <= 43 years) or 1(age > 43 years)
            - "Blood Pressure": 
                - "Low": 0(No) or 1(Yes)
                - "Normal": 0(No) or 1(Yes)
                - "High": 0(No) or 1(Yes)
            - "Cholesterol Level": 
                - "Low": 0(No) or 1(Yes)
                - "Normal": 0(No) or 1(Yes)
                - "High": 0(No) or 1(Yes)

    - **Feature Engineering**: Extracting relevant features and encoding categorical variables.
        - Data Split: Splitting the dataset into training and testing sets (80% for training, 20% for testing).

### Second Dataset Overview:
- **Source**: 
    The CDC_Diabetes.csv is obtained from Kaggle and contains 507360 rows of patient profiles with associated features and Diabetes diagnoses. It is originally already a csv file.

- **Features**: ['HighBP', 'HighChol', 'CholCheck', 'Smoker', 'Stroke',
       'HeartDiseaseorAttack', 'PhysActivity', 'Fruits', 'Veggies',
       'HvyAlcoholConsump', 'AnyHealthcare', 'NoDocbcCost', 'DiffWalk', 'Sex',
       'Age']
- **Target**: The target variable is a binary variable representing whether the patient is having diabetes(1) or not(0).

- **Column and Usage**:
    - Diabetes_binary: Target; Binary; 0 = no diabetes, 1 = pre-diabetes or diabetes
    - HighBP: Feature; Binary; 0 = no high BP, 1 = high BP
    - HighChol:	Feature; Binary; 0 = no high cholesterol, 1 = high cholesterol
    - CholCheck: Feature; Binary; 0 = no cholesterol check in 5 years, 1 = yes cholesterol check in 5 years
    - Smoker: Feature; Binary; Have you smoked at least 100 cigarettes in your entire life? [Note: 5 packs = 100 cigarettes], 0 = no, 1 = yes
    - Stroke: Feature; Binary; (Ever told) you had a stroke. 0 = no 1 = yes
    - HeartDiseaseorAttack: Feature; Binary; coronary heart disease (CHD) or myocardial infarction (MI) 0 = no, 1 = yes
    - PhysActivity: Feature; Binary; physical activity in past 30 days - not including job 0 = no 1 = yes
    - Fruits: Feature; Binary; Consume Fruit 1 or more times per day 0 = no, 1 = yes
    - Veggies: Feature; Binary;	Consume Vegetables 1 or more times per day 0 = no, 1 = yes
    - HvyAlcoholConsump: Feature; Binary; Heavy drinkers (adult men having more than 14 drinks per week and adult women having more than 7 drinks per week) 0 = no, 1 = yes
    - AnyHealthcare: Feature; Binary; Have any kind of health care coverage, including health insurance, prepaid plans such as HMO, etc. 0 = no, 1 = yes
    - NoDocbcCost: Feature; Binary; Was there a time in the past 12 months when you needed to see a doctor but could not because of cost? 0 = no, 1 = yes
    - DiffWalk: Feature; Binary; Do you have serious difficulty walking or climbing stairs? 0 = no, 1 = yes
    - Sex: Feature; Binary; Sex	0 = female, 1 = male
    - Age: The age categories of the patient in years (level 1 to 13). 1 = Age Level <= 8, 2 = Age Level > 8.  

- **Data Preprocessing**:

    - **Data Cleaning**: 
        - Addressing missing values in the dataset.
        - Removed columns ['BMI', 'GenHlth', 'MentHlth', 'PhysHlth', 'Education', 'Income'], since they're not binary variables and not hugely related to the prediction training and results.

    - **Feature Engineering**: Extracting relevant features and encoding binary variables.
        - Data Split: Splitting the dataset into training and testing sets (80% for training, 20% for testing).

### Third Dataset Overview:
- **Source**: 
    - The Symptom_Checker.csv is obtained from Kaggle and were originally two separate files, one is named Testing.csv and the other is named Training.csv.
        - In order to maintain better readability and neat naming of the data sets in the data folder, I merged the two data sets (because their column names are the same), and then produced a large file named "Symptom_Checker .csv". Since this data integration is additional, it is not written in the document of data_cleaning.py.
    - There are 4961 rows of patient profiles with associated features and Diabetes diagnoses. It is originally already a csv file.

- **Features**: ['swelled_lymph_nodes', 'nausea', 'knee_pain', 'pain_in_anal_region', 'stiff_neck', 'passage_of_gases', 'blister', 'sunken_eyes', 'red_spots_over_body', 'mood_swings', 'muscle_wasting', 'neck_pain', 'muscle_weakness', 'lethargy', 'fluid_overload', 'runny_nose', 'spinning_movements', 'watering_from_eyes', 'pain_behind_the_eyes', 'excessive_hunger', 'fatigue', 'blood_in_sputum', 'dark_urine', 'prominent_veins_on_calf', 'weakness_of_one_body_side', 'family_history', 'swollen_blood_vessels', 'small_dents_in_nails', 'dischromic _patches', 'dehydration', 'irregular_sugar_level', 'diarrhoea', 'patches_in_throat', 'swollen_legs', 'swelling_joints', 'yellow_urine', 'ulcers_on_tongue', 'mucoid_sputum', 'chills', 'rusty_sputum', 'polyuria', 'muscle_pain', 'cold_hands_and_feets', 'bladder_discomfort', 'back_pain', 'anxiety', 'brittle_nails', 'stomach_pain', 'continuous_sneezing', 'swelling_of_stomach', 'congestion', 'abnormal_menstruation', 'spotting_ urination', 'mild_fever', 'distention_of_abdomen', 'headache', 'palpitations', 'pain_during_bowel_movements', 'skin_peeling', 'extra_marital_contacts', 'history_of_alcohol_consumption', 'malaise', 'inflammatory_nails', 'increased_appetite', 'movement_stiffness', 'breathlessness', 'loss_of_appetite', 'acute_liver_failure', 'loss_of_smell', 'swollen_extremeties', 'loss_of_balance', 'weight_loss', 'scurring', 'indigestion', 'receiving_unsterile_injections', 'acidity', 'receiving_blood_transfusion', 'sweating', 'bloody_stool', 'enlarged_thyroid', 'altered_sensorium', 'redness_of_eyes', 'obesity', 'blackheads', 'vomiting', 'depression', 'chest_pain', 'dizziness', 'weight_gain', 'unsteadiness', 'cough', 'weakness_in_limbs', 'cramps', 'coma', 'fluid_overload.1', 'restlessness', 'red_sore_around_nose', 'lack_of_concentration', 'slurred_speech', 'irritability', 'throat_irritation', 'yellow_crust_ooze', 'itching', 'pus_filled_pimples', 'phlegm', 'yellowish_skin', 'high_fever', 'bruising', 'stomach_bleeding', 'foul_smell_of urine', 'painful_walking', 'blurred_and_distorted_vision', 'silver_like_dusting', 'skin_rash', 'puffy_face_and_eyes', 'nodal_skin_eruptions', 'irritation_in_anus', 'continuous_feel_of_urine', 'sinus_pressure', 'drying_and_tingling_lips', 'shivering', 'hip_joint_pain', 'yellowing_of_eyes', 'constipation', 'belly_pain', 'abdominal_pain', 'toxic_look_(typhos)', 'burning_micturition', 'internal_itching', 'fast_heart_rate', 'joint_pain', 'visual_disturbances']
- **Target**: The target variable is a categorical variable (string) representing different diseases diagnosis.

- **Column and Usage**:
    Every feature columns contain binary variables.

- **Data Preprocessing**:

    - **Data Cleaning**: 
        - Addressing missing values in the dataset.

    - **Feature Engineering**: Extracting relevant features and encoding categorical variables.
        - Data Split: Splitting the dataset into training and testing sets (80% for training, 20% for testing).

### Fourth Dataset Overview
- **Source**:
    - Stroke_Data.csv was obtained from Kaggle. It is originally already a csv file.
- **Features**: ['married', 'hypertension', 'heart_disease', 'Gender_Female',
       'Gender_Male', 'Gender_Other', 'Age_Adults', 'Age_Children',
       'Age_Elderly', 'Age_Mid-Adults', 'Age_Teens', 'Occupation_A',
       'Occupation_B', 'Occupation_C', 'Occupation_D', 'Occupation_E',
       'Residence_Rural', 'Residence_Urban', 'Smoking_Status_Unknown',
       'Smoking_Status_formerly smoked', 'Smoking_Status_never smoked',
       'Smoking_Status_smokes']
- **Target**: ['stroke']

- **Column and Usage**:
    'id': Should be removed, irrelevant
    'gender': Splits to 3 columns ['Gender_Female',
       'Gender_Male', 'Gender_Other']
    'age': Splits to 5 columns ['Age_Adults', 'Age_Children',
       'Age_Elderly', 'Age_Mid-Adults', 'Age_Teens']
    'married': 1 = yes, 0 = no
    'hypertension': 1 = yes, 0 = no
    'heart_disease': 1 = yes, 0 = no
    'occupation': Splits to 5 columns ['Occupation_A',
       'Occupation_B', 'Occupation_C', 'Occupation_D', 'Occupation_E']
    'residence': 1 = Urban, 0 = Rural
    'metric_1': Should be removed, irrelevant
    'metric_2': Should be removed, irrelevant
    'metric_3': Should be removed, irrelevant
    'metric_4': Should be removed, irrelevant
    'metric_5': Should be removed, irrelevant
    'smoking_status': Splits to 4 columns ['Smoking_Status_Unknown',
       'Smoking_Status_formerly smoked', 'Smoking_Status_never smoked',
       'Smoking_Status_smokes']
    'stroke': 1 = yes, 0 = no

- **Data Cleaning**: 
        - Addressing missing values in the dataset.
        - Removed columns ['metric_1', 'metric_2', 'metric_3', 'metric_4', 'metric_5', 'id'], since they're not binary variables and not hugely related to the prediction training and results.
        - Made dummy variables for columns ['gender', 'age', 'married','occupation', 'residence', 'smoking_status']

    - **Feature Engineering**: Extracting relevant features and encoding binary variables.
        - Data Split: Splitting the dataset into training and testing sets (80% for training, 20% for testing).

### Fifth Dataset Overview
- **Source**:
    - test_dataset.csv was created by hand and contains 11 rows of meaningless boolean values with similarly meaningless class labels assigned to each item.
- **Features**: ['f0','f1','f2','f3']
- **Target**: ['0','1','2']

- **Column and Usage**:
    Every feature column contains binary variables.
- **Data Preprocessing**:
    N/A



## Model Evaluation:
- **Testing**: Evaluating the model's performance using the testing dataset.

- **Metrics**: Using appropriate evaluation metrics such as accuracy, precision, recall, and F1-score.

- **Cross-validation**: Ensuring the model's robustness through cross-validation techniques.

## Ethical Considerations:
- **Patient Privacy**: Ensuring that patient privacy and confidentiality are maintained throughout the project.

- **Ethical Use**: Emphasizing the ethical use of the model for supportive purposes and not as a substitute for medical expertise.

- **Informed Consent**: If applicable, ensuring that data used for model development has proper consent and adherence to ethical guidelines.

## Dataset License

Two datasets we will be using for this project, the "Disease_Symptoms.csv",  CDC_Diabetes.csv" and are made available under the [CC0: Public Domain License](https://creativecommons.org/publicdomain/zero/1.0/). This license grants us the freedom to use, modify, and distribute the dataset without any restrictions. It is essential to note that this dataset is in the public domain, ensuring open access and usability for our research.

Note: "Symptom_Checker.csv" is primarily employed for analytical and modeling purposes within the scope of this project. Given the dataset’s public availability on Kaggle and the nature of this project (educational), it is assumed to be appropriate for such use. However, it's noteworthy that the dataset lacks an explicit license, and as such, its use is governed by Kaggle’s terms of service and ethical data usage principles. All efforts have been made to ensure compliance with these guidelines. We acknowledge the dataset provider on Kaggle, [username: Rabi Singh], for compiling and making this valuable resource available. This project does not claim any ownership of the data and utilizes it solely for the purposes mentioned above, under the assumption of permissible use. 

We will adhere to the terms of this license throughout our project, respecting the dataset's open nature and providing proper attribution when necessary.

This proposal outlines the key components and considerations for developing a CART model for disease prediction based on symptoms using the provided dataset. The project will proceed with meticulous attention to data privacy, ethical standards, and medical domain expertise.
