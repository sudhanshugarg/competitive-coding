#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int MAXSIZE=100100;
int runningIncrTotal = 0;
int runningDecrTotal = 0;

void incrUpdate(int posn, const int &K, int* incr, int* num){
    for(int i=posn-1; i>=0 && i>=(posn-K+1); i--){
        if(num[i] > num[i+1]) break;

        incr[i]++;
        runningIncrTotal++;
    }
}

void decrUpdate(int posn, const int &K, int* decr, int* num){
    for(int i=posn-1; i>=0 && i>=(posn-K+1); i--){
        if(num[i] < num[i+1]) break;

        decr[i]++;
        runningDecrTotal++;
    }
}

int main(){
    int upvotes[MAXSIZE];
    int incr[MAXSIZE];
    int decr[MAXSIZE];
    int N, K;
    memset(upvotes, 0, sizeof(upvotes));
    memset(incr, 0, sizeof(incr));
    memset(decr, 0, sizeof(decr));
    runningIncrTotal = 0;
    runningDecrTotal = 0;

    cin >> N >> K;
    //edge case.
    if(K == 1) {
        cout << 0 << endl;
    }

    cin >> upvotes[0];
    for(int i=1;i<N;i++){
        cin >> upvotes[i];
        if(upvotes[i] > upvotes[i-1]){
            incrUpdate(i,K,incr,upvotes);
        }
        else if(upvotes[i] < upvotes[i-1]){
            decrUpdate(i,K,decr,upvotes);
        }
        else{
            incrUpdate(i,K,incr,upvotes);
            decrUpdate(i,K,decr,upvotes);
        }

        if(i>K-2){
            if(i>=K){
                runningIncrTotal -= incr[i-K];
                runningDecrTotal -= decr[i-K];
            }
            cout << runningIncrTotal - runningDecrTotal << endl;

            /*
            if(i != N-1) cout << " ";
            else cout << endl;
            */
        }
    }
}
