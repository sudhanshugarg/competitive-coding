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

int indexRemove(int index, int start, int end, int *arr){
    //find first index in between start and end, inclusive,
    //that is greater than the value index.
    int low = start;
    int high = end;
    int mid;
    int lastSeen = -1;
    while(low <= high){
        mid = (low+high)/2;
        if(arr[mid] > index)
            high = mid-1;
        else if(arr[mid] < index)
            low = mid+1;
        else{
            //equal, keep moving to the right
            low = mid+1;
            lastSeen = mid;
        }
    }
    if(lastSeen != -1) return lastSeen+1;
    return low;
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
            incr[i] = incr[i-1];
            decr[i] = i;
            int prev = incr[i]<(i-K+1)?(i-K+1):incr[i];
            runningIncrTotal += i-prev;
            //incrUpdate(i,K,incr,upvotes);
        }
        else if(upvotes[i] < upvotes[i-1]){
            decr[i] = decr[i-1];
            incr[i] = i;
            int prev = decr[i]<(i-K+1)?(i-K+1):decr[i];
            runningDecrTotal += i-prev;
            //decrUpdate(i,K,decr,upvotes);
        }
        else{
            incr[i] = incr[i-1];
            decr[i] = decr[i-1];
            int prev = incr[i]<(i-K+1)?(i-K+1):incr[i];
            runningIncrTotal += i-prev;
            prev = decr[i]<(i-K+1)?(i-K+1):decr[i];
            runningDecrTotal += i-prev;
            //incrUpdate(i,K,incr,upvotes);
            //decrUpdate(i,K,decr,upvotes);
        }

        int index;
        if(i>K-2){
            if(i>=K){
                index = indexRemove(i-K, i-K+1, i-1, incr);
                runningIncrTotal -= index-(i-K)-1;
                index = indexRemove(i-K, i-K+1, i-1, decr);
                runningDecrTotal -= index-(i-K)-1;
            }
            cout << runningIncrTotal - runningDecrTotal << endl;

        }
    }
}
