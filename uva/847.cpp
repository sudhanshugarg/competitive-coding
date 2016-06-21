#include<iostream>
#include<cmath>

using namespace std;

int main(){
    int n;
    while(cin >> n){
        double curr = n;
        bool stanWinning = false;
        if(curr == 1) {
            cout << "Stan wins." << endl;
            continue;
        }
        while(curr > 1){
            stanWinning = !stanWinning;

            if(stanWinning)
                curr = ceil(curr/9.0);
            else
                curr = ceil(curr/2.0);

        }
        if(stanWinning) cout << "Stan wins."<< endl;
        else cout << "Ollie wins."<< endl;
    }
}
