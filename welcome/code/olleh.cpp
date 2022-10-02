#include <iostream>
#include <string>
#include <bits/stdc++.h> 
using namespace std;

string flip(string input) {
    int currentSp = 0;
    int prevSp = -1;
    string result = "";
    int isSec = 0;
    int size = input.length();
    for(int i = 0;i<size;i++) {
        if (ispunct(input[i])!=0 || input[i] == ' ') { 
            prevSp = currentSp;
            currentSp = i;
            if (isSec==1) {
                prevSp++;
            }
            string str = input.substr(prevSp, currentSp);
            isSec = 1;
            //cout<<str<<endl;
            reverse(str.begin(), str.end());
            result += str + input[i];
            //cout<<result<<endl;
        }
    }
    //cout<<result<<endl;
    prevSp = currentSp;
    currentSp = size-1;
    string str;
    if (currentSp != prevSp) {
        str = input.substr(prevSp, size);
    }
    else {
        str = "";
    }
    reverse(str.begin(), str.end());
    result += str;
    //cout<<result<<endl;
    return result;
}



int main() {
    string input;
    getline(cin,input);
    string result = flip(input);
    cout<<result<<endl;
}
