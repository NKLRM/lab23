#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string textline;
    int s1,s2,s3,score;
    while(getline(source, textline)){
        char name[100];
        char format[] = "%[^:]: %d %d %d";
        sscanf(textline.c_str(),format,name,&s1,&s2,&s3);
        names.push_back(name);
        score=s1+s2+s3;
        scores.push_back(score);
        grades.push_back(score2grade(score));
    }
}

void getCommand(string &command, string &key){
    string text;
    cout << "Please input your command:\n";
    cin >> command;
    if(toUpperStr(command) == "GRADE"||toUpperStr(command) == "NAME") {
        cin.ignore();
        getline(cin,text);
    }
    else {
        getline(cin,text);
    }
    key = text;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int x=0;
    for(unsigned int i=0;i<names.size();i++){
        if(toUpperStr(names[i])==toUpperStr(key)){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            x = 1;
        }
    }
    if(x==0){
        cout << "---------------------------------\n";
        cout << "Cannot found." << endl;
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int x=0; string g;
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<names.size();i++){
        g = grades[i];
        if(g==toUpperStr(key)){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            x = 1;
        }
    }
    if(x==0){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
