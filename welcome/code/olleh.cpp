#include <iostream>
#include <string>
#include <bits/stdc++.h> 
using namespace std;

string flip(string input, vector<int> ind) {
    int size = ind.size();
    int length = input.length();
    string result = "";
<<<<<<< HEAD
    if (size == 0) {
        string temp = input;
        reverse(temp.begin(),temp.end());
        return temp;
=======
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
>>>>>>> ec662c93e077efe43645c2c461e452704e2ce100
    }
    else {
        string temp = input.substr(0,ind[0]);
        reverse(temp.begin(),temp.end());
        result += temp + input[ind[0]];
    }

    for (int i = 1; i<size;i++) {
        if(ind[i]-ind[i-1]==1) {
            result += input[ind[i]];
        }
        else {
            string temp = input.substr(ind[i-1]+1,ind[i]-(ind[i-1]+1));
            reverse(temp.begin(),temp.end());
            result += temp + input[ind[i]];
        }
    }
    string temp = input.substr(ind[size-1]+1,length-(ind[size-1]+1));
    reverse(temp.begin(),temp.end());
    result += temp;

    
    return result;
}

vector<int> findSpaceAndPunct(string input) {
    vector<int> ind;
    int size = input.length();
    for(int i = 0;i<size;i++) {
        if (ispunct(input[i])!=0 || input[i] == ' ') { 
            ind.push_back(i);
        }
    }
    return ind;
}

int main() {
    string input;
    getline(cin,input);
    vector<int> ind = findSpaceAndPunct(input);
    
    string result = flip(input,ind);
    
    cout<<result<<endl;
}
