#include<iostream>
#include<set>
#include<map>

using namespace std;

const int MAXNUM = 35;
int *inSet;
int *covered;
int minSize;
int n,m;
//int** arr;
int arr[35][35];

void backtrack(int startStation, int stationsLeft, int setSize);

int main(){
    //int** arr = new int* [MAXNUM];
    inSet = new int[MAXNUM];
    covered = new int[MAXNUM];

    /*
    for(int i=0;i<MAXNUM;i++){
        arr[i] = new int [MAXNUM];
    }
    */

    int v1, v2;
    while(1){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        for(int i=0;i<n;i++){
            inSet[i] = false;
            covered[i] = 0;
            for(int j=0;j<n;j++)
                arr[i][j] = 0;
            arr[i][i] = 1;
        }


        //build adjacency matrix.
        for(int i=0;i<m;i++){
            cin >> v1 >> v2;
            arr[v1-1][v2-1] = 1;
            arr[v2-1][v1-1] = 1;
        }

        /*
           for(int i=0;i<n;i++){
           for(int j=0;j<n;j++)
           cout << arr[i][j] << " ";
           cout << endl;
           }
           */

        minSize = n;

        //backtracking with pruning.
        //TODO divide into connected components.
        /*
           for(int i=0;i<n;i++){
           if(inSet[i] == 0){
           dfs(i,i+1);
           }
           }
           */

        //backtrack from service station 1, and see where to go next.
        for(int i=0;i<n;i++)
            backtrack(i,n,0);

        cout << minSize << endl;
        //TODO need to delete all dynamically
        //allocated variables.
        //for(int i=0;i<MAXNUM;i++)
        //    delete arr[i];
    }
    delete inSet;
    delete covered;
}

void dfs(int a, int b){
    return;
}

void backtrack(int startStation, int stationsLeft, int setSize){
    //check if this is a solution.
    //if all stations are covered
    if(stationsLeft == 0){
        int count = 0;
        for(int i=0;i<n;i++)
            if(inSet[i]) count++;
        if(minSize > count)
            minSize = count;
        return;
    }

    if(setSize >= minSize) return;

    //now that atleast 1 station is left, choose
    //the candidates to traverse through in the optimal
    //order. here the order is greedy.
    /*
    int deg[MAXSUM];
    int maxIndex = -1;
    //find the number of degree of each station.
    for(int i=0;i<n;i++){
        count = 0;
        if(!inSet[i]){
            for(int j=0;j<n;j++){
                if(!covered[j]) count++;
            }
            deg[i] = count;
            if((maxIndex == -1) || (deg[maxIndex] < deg[i]))
                maxIndex = i;
        }
    }
    //choose the maxIndex.
    */

    int s;
    //choose candidate order
    for(int i=startStation; i<n+startStation;i++){
        s = i%n;
        //cout << "marker 1" << endl;
        if(inSet[s]) continue;
        //else, add s to the set.
        //set candidate
        //cout << "marker 2" << endl;
        inSet[s] = true;
        setSize++;
        int count = 0;

        if(!covered[s]){
            covered[s] = s+1;
            count++;
        }
        //cout << "marker 3" << endl;
        //cover all the stations that are adjacent
        //to s.
        //cout << "n = " << n << endl;
        for(int j=0;j<n;j++){
        //    cout << "s = " << s << endl;
        //    cout << "j = " << j << endl;
        //    cout << "covered[j] = " << covered[j] << endl;
        //    cout << "arr[s][j] = " << arr[s][j] << endl;
            if(!covered[j] && arr[s][j]){
                covered[j] = s+1;
                count++;
            }
        }

        //cout << "marker 4" << endl;
        backtrack((s+1)%n, stationsLeft-count, setSize);
        //backtrack
        //
       // cout << "marker 5" << endl;

        //unset candidate
        inSet[s] = false;
        setSize--;
        for(int j=0;j<n;j++)
            if(covered[j] == s+1){
                covered[j] = 0;
            }
        //cout << "marker 6" << endl;
    }
}
