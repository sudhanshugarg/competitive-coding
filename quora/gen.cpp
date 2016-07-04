#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sstream>
using namespace std;

int main(int argc, char* argv[]){
    int len=100000;
    if(argc > 1){
        istringstream iss(argv[1]);
        iss >> len;
    }
    int maxtime = 1000000;
    cout << len << endl;

    srand(time(NULL));
    for(int i=0;i<len-1;i++){
        cout << rand()%maxtime+1 << " ";
    }
    cout << rand()%maxtime+1 << endl;
    for(int i=1;true;i++){
        if(2*i <= len)
        cout << i << " " << 2*i << endl;
        else break;
        if(2*i+1 <= len)
        cout << i << " " << 2*i+1 << endl;
        else break;
    }
}
