#include<iostream>
#include<vector>
#include<string>
using namespace std;

class ParenthesesDiv2Medium {
public:

vector<int> correct (string s){
    int n = s.length();
    int open,close;
    open = close= 0;
    vector<int> ret;
    for(int i=0;i<n;i++){
        if(s[i] == '(' ) open++;
        else close++;
        if(open < close){
            ret.push_back(i);
            if(s[i] == '(') {
                s[i] = ')';
                open--; close++;
            }
            else {
                s[i] = '(';
                open++; close--;
            }
        }
    }
    
    if(open == close) return ret;
    open = close = 0;
    for(int i=n-1;i>=0;i--){
        if(s[i] == '(' ) open++;
        else close++;
        if(close < open){
            ret.push_back(i);
            if(s[i] == '(') {
                s[i] = ')';
                open--; close++;
            }
            else {
                s[i] = '(';
                open++; close--;
            }
        }
    }
    return ret;
}

};