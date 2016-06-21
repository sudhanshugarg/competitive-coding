#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<map>

using namespace std;
map<int, int> startPosError;
string file;
const int MAXLEN = 72;

int main(){
    file = "";
    char c;
    while(cin.get(c)){
        file += c;
    }
    //cout << file ;

    //to return startPosError[0].
    //given a string file, what is the minimum distance from 72.
    //take the first word,
    return findMin(0);
}

int findMin(int pos){
    if(startPosError.find(pos) != startPosError.end())
        return startPosError[pos];
        
    startPosError[pos] = MAXLEN;

    bool empty = true;
    bool wordFound = false;
    int currLen = 0;
    int wordLen = 0;
    for(int i=pos;file[i] != '\n';i++){
        if(file[i] == ' '){
            if(wordFound){
                wordFound = false;
                wordLen = 0;
                int lineLen = currLen;
                while(file[i] == ' ') {
                    i++;
                    currLen++;
                }
                if(file[i] != '\n'){
                    nextmin = findMin(i);
                    if(MAXLEN-lineLen + nextmin < startPosError[pos])
                        startPosError[pos] = MAXLEN-lineLen + nextmin;
                }
                
            }
        }
        else {
            empty = false;
            wordFound = true;
            wordLen++;
        }
        currLen++;
    }
}
