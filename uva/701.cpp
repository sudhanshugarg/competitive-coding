#include<iostream>
#include<cmath>

using namespace std;

int main(){
    int n;
    long double l10 = log2(10.0);
    
    while(cin >> n){
        int d = 0;
        int tmp = n;
        while(tmp){
            tmp /= 10;
            d++;
        }
//        cout << "number = " << n << endl;
//        cout << "digits = " << d << endl;
        double k = d+1;
        //need something with atleast k more digits.
        
        long double next;
        long double l1, l2;
        l1 = log2(n);
        l2 = log2(n+1);
        while(1){
            next = k*l10;
            if(floor(next+l1) != floor(next+l2))
              break;
            k++;
        }
        cout << (long long)floor(next+l2) << endl;
    }
}
