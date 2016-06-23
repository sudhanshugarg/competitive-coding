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

int calc(int *incr, int *decr, int posn, const int &K){

    //there are i-incr[i]+1 numbers in the increment, including
    //this element.
    int incrCount = 0;
    int decrCount = 0;
    int total;
    int i;

    //this takes care of increments.
    i = posn;
    while(i > posn-K+1){
        if(incr[i] >= posn-K+1)
            total = i-incr[i]+1;
        else
            total = i-(posn-K+1)+1;
        incrCount += total*(total-1)/2;
        i = incr[i]-1;
    }

    i = posn;
    while(i > posn-K+1){
        if(decr[i] >= posn-K+1)
            total = i-decr[i]+1;
        else
            total = i-(posn-K+1)+1;
        decrCount += total*(total-1)/2;
        i = decr[i]-1;
    }

    return incrCount - decrCount;
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
    incr[0] = 0;
    decr[0] = 0;

    for(int i=1;i<N;i++){
        cin >> upvotes[i];
        if(upvotes[i] > upvotes[i-1]){
            incr[i] = incr[i-1];
            decr[i] = i;
        }
        else if(upvotes[i] < upvotes[i-1]){
            decr[i] = decr[i-1];
            incr[i] = i;
        }
        else{
            incr[i] = incr[i-1];
            decr[i] = decr[i-1];
        }

        if(i>K-2){
            //it means you have to calculate number of incr
            //sums and number of decr sums.
            cout << calc(incr, decr, i, K) << endl;
        }
    }
}
