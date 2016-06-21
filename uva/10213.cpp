#include<iostream>
#include<cmath>
using namespace std;

int main(){
    int n;
    cin >> n;
    int count;
    long long res;
    for(int i=0;i<n;i++){
        cin >> count;
        if(count == 0) count = 1;
        if(count < 4){
            cout << (int)pow(2,count-1) << endl;
            continue;
        }
        res = count*(count-1)*(count-2)*(count-3)/24 + (count-3)*(count+2)/2 + 4;
        cout << res << endl;
    }
    return 0;
}
