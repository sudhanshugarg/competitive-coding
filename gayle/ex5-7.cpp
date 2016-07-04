#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

void myPrint(vector<int> &a){
    for(int i=0;i<a.size();i++)
        cout << a[i] << " ";
    cout << endl;
}

int bin2Int(vector<bool> &b){
    int val = 0;
    for(int i=0;i<b.size();i++){
        val = val*2;
        if(b[i]) val++;
    }
    return val;
}

class BinArr{
    private:
        vector<int> arr;
    public:
        BinArr(int n){
            arr.resize(n+1);
            for(int i=0;i<=n;i++){
                arr[i] = i;
            }
            srand(time(NULL));
            int del = rand()%(n+1);
            arr.erase(arr.begin()+del);
            //randomize the array.
            int id1, id2;
            for(int i=0;i<n;i++){
                srand(i);
                id1 = rand()%n;
                srand(i+3);
                id2 = rand()%n;
                int tmp = arr[id1];
                arr[id1] = arr[id2];
                arr[id2] = tmp;
            }
            //having randomized the array.
            //now, give a function to get bits.
            //better yet, create a class for this.
        }

        bool getBit(int elem, int bit){
            //bits start from 0 all the way upto floor(log2(n))
            return ((arr[elem] & (1<<bit)) != 0);
        }

        int getMissing(void){
            int total = 0;
            for(int i=0;i<arr.size();i++) total += arr[i];
            return arr.size()*(arr.size()+1)/2-total;
        }

        void printArr(void){
            for(int i=0;i<arr.size();i++)
                cout << arr[i] << " ";
            cout << endl;
        }
};

int main(){
    //first figure a method, such that given an 
    //input n, randomly populate an array of size
    //n, and leave out one of the elements from 0 to n.
    int n;
    cin >> n;
    BinArr obj(n);

    //now we have one number missing.
    //the only method we can call is getBit.
    //
    vector<int> currIndices;
    vector<bool> ret;
    for(int i=0;i<n;i++)
        currIndices.push_back(i);

    vector<int> next1Indices;
    vector<int> next0Indices;
    int currBit;
    currBit = 0;
    while(currIndices.size()){
        //myPrint(currIndices);
        next1Indices.clear();
        next0Indices.clear();
        for(int i=0;i<currIndices.size();i++){
            if(obj.getBit(currIndices[i], currBit)){
                next1Indices.push_back(currIndices[i]);
            }
            else {
                next0Indices.push_back(currIndices[i]);
            }
        }


        if((currIndices.size()+1) & 1) {   //odd
            //number of 0s is 1 more than number of 1s.
            if(next0Indices.size() == next1Indices.size()){
                //0 is missing.
                currIndices = next0Indices;
                ret.push_back(false);
            }
            else{
                currIndices = next1Indices;
                ret.push_back(true);
            }
        }
        else {              //even
            //number of 0s is equal to number of 1s
            if(next0Indices.size() < next1Indices.size()){
                currIndices = next0Indices;
                ret.push_back(false);
            }
            else{
                currIndices = next1Indices;
                ret.push_back(true);
            }
        }
        currBit++;
    }
    reverse(ret.begin(), ret.end());
    for(int i=0;i<ret.size();i++)
        if(ret[i]) cout << 1;
        else cout << 0;
    cout << " , " << bin2Int(ret) << endl;
    cout << "Ans: " << obj.getMissing() << endl;
    //obj.printArr();
}

