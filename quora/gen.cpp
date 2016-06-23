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
    for(int i=1;i<len;i++){
        cout << i+1 << " " << 1 << endl;
    }
}
