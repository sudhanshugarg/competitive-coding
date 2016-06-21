#include<iostream>
#include<cstring>
using namespace std;

const int LEN = 2;
int main(){
    int arr[LEN][2*LEN];
    for(int i=0;i<LEN;i++)
        arr[i][i] = i;

    memset(arr,0,sizeof(arr));
    for(int i=0;i<LEN;i++){
    for(int j=0;j<2*LEN;j++)
        cout << arr[i][j] << " ";
    cout << endl;
    }
    cout << endl << sizeof(arr) << endl;
    cout << endl;
}
