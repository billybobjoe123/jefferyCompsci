#include <iostream>
#include <string>
#include <bits/stdc++.h> 
using namespace std;

string flip(string input) {
    int currentSp = 0;
    int prevSp = 0;
    string result = "";
    for(int i = 0;i<input.size();i++) {
        if (ispunct(input[i])!=0 || input[i] == ' ') { 
            prevSp = currentSp;
            currentSp = i;
            string str = input.substr(prevSp, currentSp);
            
            reverse(str.begin(), str.end());
            result += str;
        }
    }
    prevSp = currentSp;
    currentSp = input.length()-1;
    string str = input.substr(prevSp, currentSp);
    result += str;
    cout<<result<<endl;
    return result;
}



int main() {
    cout<<"input a string"<<endl;
    string input;
    getline(cin,input);
    string result = flip(input);
    cout<<result<<endl;
}