#include<iostream>
using namespace std;

int main(){
    int n;
    int curr = 1;
    int digits = 0;
    while(cin >> n){
        curr = 1;
        if(n == 0){
            cout << 1 << endl;
            continue;
        }

        digits = 1;
        curr = curr % n;
        while(curr){
            //cout << "curr = " << curr << endl;
            curr = (curr * 10 + 1) % n;
            digits++;
        }
        cout << digits << endl;
    }
}
