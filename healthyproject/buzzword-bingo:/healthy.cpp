//
//  healthy.cpp
//  
//
//  Created by Nicole O'Brien and Rachel Rotteveel on 1/26/15.
//
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

double calculateDailyIntake() {
    double BMR, calorieIntake;
    int servings;
    int height, age, weight;
    string gender, activityLevel;
    cout << "\nWELCOME TO RACHEL AND NICOLE'S CALORIE CALCULATOR!\n";
    cout << "\nPlease enter some personal information so we can accurately calculate your daily calorie intake.\n";
    cout << "\nWhat is your height? (in inches) \n";
    cin >> height;
    cout << "\nWhat is your weight? (in pounds) \n";
    cin >> weight;
    cout << "\nWhat is your age? \n";
    cin >> age;
    cout << "\nWhat is your gender? (M/F) \n";
    cin >> gender;
    transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
    cout << "\nWhat is your activity level? (sedentary, light, moderate, active) \n";
    cin >> activityLevel;
    cout<<endl;
    
    if (gender == "m") {
        BMR = 66 + ( 6.23 * weight ) + ( 12.7 * height ) - ( 6.8 * age );
        if (activityLevel == "sedentary" || activityLevel== "s") {
            calorieIntake = 1.2 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
        if (activityLevel == "light" || activityLevel== "l") {
            calorieIntake = 1.375 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
        if (activityLevel == "moderate"||activityLevel== "m") {
            calorieIntake = 1.55 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
        if (activityLevel == "active"||activityLevel== "a") {
            calorieIntake = 1.725 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
        
    } else if (gender == "f") {
        BMR = 655 + ( 4.35 * weight ) + ( 4.7 * height ) - ( 4.7 * age );
        if (activityLevel == "sedentary"|| activityLevel== "s") {
            calorieIntake = 1.2 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
        if (activityLevel == "light"|| activityLevel== "l") {
            calorieIntake = 1.375 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
        if (activityLevel == "moderate"||activityLevel== "m") {
            calorieIntake = 1.55 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
        if (activityLevel == "active"||activityLevel== "a") {
            calorieIntake = 1.725 * BMR;
            cout << "\nYour daily calorie intake is " << calorieIntake << " calories.\n\n";
            return calorieIntake;
        }
    }
    return calorieIntake;
}


class Serving {
public:
    string description;
    double gram_per_serv;
    
public: Serving(string desc, double w){
        this->description = desc;
        this->gram_per_serv = w;
    }
};

map<int, string> create_descrip() {
    map <int, string> id_desc;
    FILE * foodFile;
    char liney[1000];
    foodFile = fopen("FOOD_DES.txt", "r");
    while (fscanf(foodFile, "~%[-,A-Za-z0-9%^~./()&':;!#@$+=?<>_ ]\n", liney)!= EOF){
        string line(liney);
        char *part;
        part = strtok(liney, "~^");
        int index=0;
        while (part!= NULL){
            int food_id;
            if (index == 0){
             //   cout<<"food id ";
                food_id=atoi(part);
              //  cout<<food_id<<endl;
            }
            
            if (index == 2){
              //  cout<<"description 1";
                id_desc[food_id] = part;
             //  cout<<id_desc[food_id]<<"and"<<food_id<<endl;
            }
            part = strtok(NULL, "^");
            index+=1;
        }
        
    }
    return id_desc;
}

map<int, vector<Serving>> create_serving_size(){
    map<int, vector<Serving>> serving_size;
    FILE * foodFile;
    char liney[1000];
    foodFile = fopen("WEIGHT.txt","r");
    while (fscanf(foodFile,"~%[-,A-Za-z0-9%^~./()&':;!#@$+=?<>_ ]\n", liney)!=EOF){
        string line(liney);
        char *part;
        char *first_part;
        char *second_part;
        int food_id;
        double gram_per_serv;
        part = strtok(liney, "^~");
        int index=0;
        while (part!= NULL){
            if (index==0){
           //        cout<<"food id ";
                food_id=atoi(part);
             //     cout<<food_id<<endl;
            }
            if (index==2){
                first_part = part;
               // cout<<part<<endl;
                
            }
            if (index==3){
                second_part = part;
               // cout<<part<<endl;
            }
            if (index==4){
                gram_per_serv = atof(part);
            }
            part = strtok(NULL, "^");
            index+=1;
        }
        string s = strcat(first_part, second_part);
        replace(s.begin(), s.end(), '~', ' ');
        Serving *this_serving = new Serving(s,gram_per_serv);
        serving_size[food_id].push_back(*this_serving);
    }
    return serving_size;
}

map<int, int> create_cal(){
    map <int, int> id_cal;
    bool found_cal;
    FILE * foodFile;
    char liney[1000];
    foodFile = fopen("NUT_DATA.txt","r");
    while (fscanf(foodFile,"~%[-,A-Za-z0-9%^~./()&':;!#@$+=?<>_ ]\n", liney)!=EOF){
        string line(liney);
        char *part;
        part = strtok(liney, "~^");
        int index=0;
        found_cal=false;
        while (part!= NULL && found_cal==false){
            int food_id;
            if (index==0){
             //     cout<<"food id ";
                food_id=atoi(part);
              //    cout<<food_id<<endl;
            }
            
            if (index==1){
                if (strncmp(part,"~208~",5)==0){
                    found_cal=true;
                    part = strtok(NULL, "^");
                    int new_part = atoi(part);
                    id_cal[food_id]=new_part;
                  //  cout<<food_id<<"is food id"<<new_part<<"is cal"<<endl;
                }
                else{
                    part=NULL;
                }
                //cout<<food_id<<endl;
            }
            
            part = strtok(NULL, "^");
            index+=1;
        }
        
    }
    return id_cal;
}

int get_food_id(map<int, string> food_stuff){
    char user_input[256];
    string description;
    int user_choice;
    vector <int> possible_foods;
    cout<< "\nPlease enter a type of food (be specific):\n";
    vector <string> user_words;
    char *word;
    cin.getline(user_input,256);
    cout<<endl;
    //cout<<"THIS IS USER INPUT"<<user_input<<endl;
    string str(user_input);
    //cout<<"THIS IS STR BEFORE TRANSFORM"<<str<<endl;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    //cout<<"THIS IS STR"<<str<<endl;
    char input_array[256];
    strcpy(input_array, str.c_str());
 //   cout<<"THIS IS INPUT ARRAY"<<input_array;
    word = strtok(input_array,"' ");
    while(word != NULL){
     //   cout<<"THIS IS A WORD"<<word<<endl;
        user_words.push_back(word);
        word = strtok(NULL, "' ");
    }
    for (auto& food: food_stuff){
        int sizey=user_words.size();
        //cout<<sizey<<endl;
        int tries = 0;
        for (auto word: user_words){
            transform(food.second.begin(), food.second.end(), food.second.begin(), ::tolower);
       // cout<<food.second.c_str()<<endl;
            if(strstr(food.second.c_str(), word.c_str())!=NULL){
                tries+=1;
            //cout<<"YES"<<endl;
           // possible_foods.push_back(food.first);
            }
            if(tries>=sizey){
             //   cout<<"HERE WE GO"<<endl;
                 possible_foods.push_back(food.first);
            }
        }
       // else{
          //  cout<<description.c_str()<<endl;;
      ///  }
    }
    int index = 1;
    for (auto food_id: possible_foods){
        cout<<"["<<index<<"]"<<food_stuff[food_id]<<endl;
        index+=1;
    }
    if (possible_foods.size()==0){
        cout<<"Sorry we could not find any food matches!\n"<<endl;
        return 0;
    }
    else {
       // cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    cout<<"\nPlease type the number that corresponds to your food choice:"<<endl;
    cin>>user_choice;
        while (user_choice>possible_foods.size()){
            cout<<"\nPlease type the number that corresponds to your food choice:"<<endl;
            cin>>user_choice;
        }
    int answer = possible_foods[user_choice-1];
    return answer;
    }
}

double get_calories_per_100g(map<int, int> id_cal, int food_id){
    return id_cal[food_id];
}

double get_gram_per_serv(map<int, vector<Serving>> serving_size, int food_id){
    int index = 1;
    for (auto serving :serving_size[food_id]){
        cout<<"\n["<<index<<"] "<<serving.description;
        index+=1;
  //      cout<<serving.gram_per_serv<<endl;
    }
    cout<<"\n\nPlease type the number that corresponds to one serving:"<<endl;
    int user_choice;
    cin>>user_choice;
    while (user_choice>serving_size[food_id].size()){
        cout<<"\nPlease type the number that corresponds to one serving:"<<endl;
        cin>>user_choice;
    }
    double answer = serving_size[food_id][user_choice-1].gram_per_serv;
    return answer;
}

double get_num_serv(){
    double ans;
    cout<<"\nHow many servings did you have?"<<endl;
    cin>> ans;
    return ans;
}

double getCalorieContent(int food_id, map<int, int> id_cal, map<int, vector<Serving>> serving_size){
    double calorieContent;
    double cal_per_100g=get_calories_per_100g(id_cal, food_id);
   // cout<<cal_per_100g<<"is cal per 100 g"<<endl;
    double gram_per_serving = get_gram_per_serv(serving_size, food_id);
  //  cout<<gram_per_serving<< "is gram per serving"<<endl;
    double servings = get_num_serv();
   // cout<<servings<<"is number of servings"<<endl;
    return cal_per_100g*gram_per_serving*servings/100.0;
}

int main(){
    double totalCalories = calculateDailyIntake();
    double currCalTotal = 0.0;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    map<int, string> id_desc;
    map<int, int> id_cal;
    map<int, vector<Serving>> serving_size;
    id_desc = create_descrip();
    id_cal = create_cal();
    serving_size = create_serving_size();

    
    int i;
    for (i = 0; i < 1000; i++) {
        string answer;
        while (answer != "y" && answer!="n"){
        cout << "Would you like to enter a food item? (Y/N)\n";
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        }
        if (answer == "y") {
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            int food_id = get_food_id(id_desc);
            if (food_id!=0){
            double calories = getCalorieContent(food_id, id_cal, serving_size);
            currCalTotal += calories;
            cout << "\nYour total number of consumed calories is: " << currCalTotal << endl;
            totalCalories = totalCalories - calories;
            cout << "\nYou have " << totalCalories << " calories left in your suggested intake for today.\n\n";
            }
        } else if(answer=="n"){
            cout << "\nThank you for using the calorie calculator. Bye!\n";
            break;
        }
    }
    return 0;
}
