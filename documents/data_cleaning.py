import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from ucimlrepo import fetch_ucirepo

# fetch 1st dataset (Disease_symptom.csv)
df = pd.read_csv("../shoppingCARTs/data/Disease_symptom.csv")

# drop invalid values
df = df.dropna() 

# variable transformation
df['Fever'] = (df['Fever'] == 'Yes').astype(int)
df['Cough'] = (df['Cough'] == 'Yes').astype(int)
df['Fatigue'] = (df['Fatigue'] == 'Yes').astype(int)
df['Difficulty Breathing'] = (df['Difficulty Breathing'] == 'Yes').astype(int)

df['Outcome Variable'] = (df['Outcome Variable'] == 'Positive').astype(int)
df['Gender'] = (df['Gender'] == 'Male').astype(int)

df['Age'] = (df['Age'] > 43).astype(int)

dummies = pd.get_dummies(df['Blood Pressure'], prefix='Blood Pressure')
df = pd.concat([df, dummies], axis=1).drop('Blood Pressure', axis=1)

dummies_2 = pd.get_dummies(df['Cholesterol Level'], prefix='Cholesterol Level')
df = pd.concat([df, dummies_2], axis=1).drop('Cholesterol Level', axis=1)

# create target and features columns
target = ['Disease']
features = [
    'Fever',
    'Cough',
    'Fatigue',
    'Difficulty Breathing',
    'Outcome Variable',
    'Gender',
    'Age',
    'Blood Pressure_Low',
    'Blood Pressure_Normal',
    'Blood Pressure_High',
    'Cholesterol Level_Low',
    'Cholesterol Level_Normal',
    'Cholesterol Level_High'
]

# split into train and test datasets
X = df[features].to_numpy()
y = df[target].to_numpy()

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.20, random_state=42
)

# Convert to DataFrame
X_train = pd.DataFrame(X_train)
y_train = pd.DataFrame(y_train)
X_test = pd.DataFrame(X_test)
y_test = pd.DataFrame(y_test)

# Save to CSV
X_train.to_csv("../shoppingCARTs/data/Disease_symptom_XTrain.csv", index=False)
y_train.to_csv("../shoppingCARTs/data/Disease_symptom_yTrain.csv", index=False)
X_test.to_csv("../shoppingCARTs/data/Disease_symptom_XTest.csv", index=False)
y_test.to_csv("../shoppingCARTs/data/Disease_symptom_yTest.csv", index=False)



# fetch 2nd dataset (CDC_Diabetes.csv)
cdc_diabetes_health_indicators = fetch_ucirepo(id=891) 

# data (as pandas dataframes) 
X_2 = cdc_diabetes_health_indicators.data.features 
y_2 = cdc_diabetes_health_indicators.data.targets 
df_2 = pd.concat([X_2, y_2], ignore_index=True)
df_2 = df_2.dropna() 

# remove unnecessary features
X_2 = X_2.drop(['BMI', 'GenHlth', 'MentHlth', 'PhysHlth', 'Education', 'Income'], axis=1)
X_2['Age'] = (X_2['Age'] > 8).astype(int)

# split train and test dataset
X_train_2, X_test_2, y_train_2, y_test_2 = train_test_split(
    X_2, y_2, test_size=0.20, random_state=42
)

# Convert to DataFrame
X_train_2 = pd.DataFrame(X_train_2)
y_train_2 = pd.DataFrame(y_train_2)
X_test_2 = pd.DataFrame(X_test_2)
y_test_2 = pd.DataFrame(y_test_2)

# Save to CSV
X_train_2.to_csv("../shoppingCARTs/data/CDC_Diabetes_XTrain.csv", index=False)
y_train_2.to_csv("../shoppingCARTs/data/CDC_Diabetes_yTrain.csv", index=False)
X_test_2.to_csv("../shoppingCARTs/data/CDC_Diabetes_XTest.csv", index=False)
y_test_2.to_csv("../shoppingCARTs/data/CDC_Diabetes_yTest.csv", index=False)



# fetch 3rd dataset (Symptom_Checker.csv)
df_3 = pd.read_csv("../shoppingCARTs/data/Symptom_Checker.csv")
df_3 = df_3.dropna()
df_3
# Get the last column name
last_column = 'prognosis'

# Reorder columns: Last column followed by the rest
df_3 = df_3[[last_column] + [col for col in df_3.columns if col != last_column]]
df_3.to_csv("../shoppingCARTs/data/Symptom_Checker.csv", index=False)
df_3 = pd.read_csv("../shoppingCARTs/data/Symptom_Checker.csv")

# create train and test datasets
target_3 = ['prognosis']
features_3 = list(set(df_3.columns) - set(target_3))

X_3 = df_3[features_3].to_numpy()
y_3 = df_3[target_3].to_numpy()

# split train and test dataset
X_train_3, X_test_3, y_train_3, y_test_3 = train_test_split(
    X_3, y_3, test_size=0.20, random_state=42
)

# Convert to DataFrame
X_train_3 = pd.DataFrame(X_train_3)
y_train_3 = pd.DataFrame(y_train_3)
X_test_3 = pd.DataFrame(X_test_3)
y_test_3 = pd.DataFrame(y_test_3)

# Save to CSV
X_train_3.to_csv("../shoppingCARTs/data/Symptom_Checker_XTrain.csv", index=False)
y_train_3.to_csv("../shoppingCARTs/data/Symptom_Checker_yTrain.csv", index=False)
X_test_3.to_csv("../shoppingCARTs/data/Symptom_Checker_XTest.csv", index=False)
y_test_3.to_csv("../shoppingCARTs/data/Symptom_Checker_yTest.csv", index=False)


# fetch 4th dataset (Skin_Disease.csv)
df_4 = pd.read_csv("../shoppingCARTs/data/Stroke_Data.csv", on_bad_lines = 'skip')
df_4 = df_4.dropna()
df_4 = df_4.drop(['metric_1', 'metric_2', 'metric_3', 'metric_4', 'metric_5', 'id'], axis=1)

dummies_3 = pd.get_dummies(df_4['gender'], prefix='Gender')
df_4 = pd.concat([df_4, dummies_3], axis=1).drop('gender', axis=1)

dummies_4 = pd.get_dummies(df_4['age'], prefix='Age')
df_4 = pd.concat([df_4, dummies_4], axis=1).drop('age', axis=1)

df_4['married'] = (df_4['married'] == 'Yes').astype(int)

dummies_5 = pd.get_dummies(df_4['occupation'], prefix='Occupation')
df_4 = pd.concat([df_4, dummies_5], axis=1).drop('occupation', axis=1)

dummies_6 = pd.get_dummies(df_4['residence'], prefix='Residence')
df_4 = pd.concat([df_4, dummies_6], axis=1).drop('residence', axis=1)

dummies_7 = pd.get_dummies(df_4['smoking_status'], prefix='Smoking_Status')
df_4 = pd.concat([df_4, dummies_7], axis=1).drop('smoking_status', axis=1)

# create target and features columns
target_4 = ['stroke']
features_4 = list(set(df_4.columns) - set(target_4))

# split into train and test datasets
X_4 = df_4[features_4].to_numpy()
y_4 = df_4[target_4].to_numpy()

X_train_4, X_test_4, y_train_4, y_test_4 = train_test_split(
    X_4, y_4, test_size=0.20, random_state=42
)

# Convert to DataFrame
X_train_4 = pd.DataFrame(X_train_4)
y_train_4 = pd.DataFrame(y_train_4)
X_test_4 = pd.DataFrame(X_test_4)
y_test_4 = pd.DataFrame(y_test_4)

# Save to CSV
X_train_4.to_csv("../shoppingCARTs/data/Stroke_Data_XTrain.csv", index=False)
y_train_4.to_csv("../shoppingCARTs/data/Stroke_Data_yTrain.csv", index=False)
X_test_4.to_csv("../shoppingCARTs/data/Stroke_Data_XTest.csv", index=False)
y_test_4.to_csv("../shoppingCARTs/data/Stroke_Data_yTest.csv", index=False)



# Dataset Magnitude
test_dataset_X = pd.read_csv("../shoppingCARTs/data/test_dataset_X.csv")
test_dataset_y = pd.read_csv("../shoppingCARTs/data/test_dataset_Y.csv")
print("test_dataset_X shape: ", test_dataset_X.shape) # 1
print("test_dataset_X shape: ", test_dataset_y.shape) # 1

print("Disease_symptom shape: ", df.shape) #2
print("Disease_symptom_XTrain shape: ", X_train.shape) # 2
print("Disease_symptom_yTrain shape: ", y_train.shape) # 2
print("Disease_symptom_XTest shape: ", X_test.shape) # 1
print("Disease_symptom_yTest shape: ", y_test.shape) # 1


print("CDC_Diabetes shape: ", df_2.shape) #5
print("CDC_Diabetes_XTrain shape: ", X_train_2.shape) # 5
print("CDC_Diabetes_yTrain shape: ", y_train_2.shape) # 5
print("CDC_Diabetes_XTest shape: ", X_test_2.shape) # 4
print("CDC_Diabetes_yTest shape: ", y_test_2.shape) # 4

print("Symptom_Checker shape: ", df_3.shape) # 3
print("Symptom_Checker_XTrain shape: ", X_train_3.shape) # 3
print("Symptom_Checker_yTrain shape: ", y_train_3.shape) # 3
print("Symptom_Checker_XTest shape: ", X_test_3.shape) # 2
print("Symptom_Checker_yTest shape: ", y_test_3.shape) # 2

print("Stroke_Data shape: ", df_4.shape) # 4
print("Stroke_Data_XTrain shape: ", X_train_4.shape) # 4
print("Stroke_Data_yTrain shape: ", y_train_4.shape) # 4
print("Stroke_Data_XTest shape: ", X_test_4.shape) # 3
print("Stroke_Data_yTest shape: ", y_test_4.shape) # 3