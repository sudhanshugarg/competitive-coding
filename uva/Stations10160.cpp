#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

typedef class Node{
    public:
        int degree;
        int vertex;
        Node(int d, int v){
            degree = d;
            vertex = v;
        }
        bool operator < (const Node &n) const{
            if(degree < n.degree)
                return true;
            return false;
        }
}Node;

const int MAXNUM = 35;
int *inSet;
int minSize;
int n,m;
int arr[35][35];
int depth;
bool debug = false;
bool debug2 = false;
vector<int> currComponent;
int currN;

void backtrack(int stationsLeft, int setSize);
void dfs(int a, vector<int> &v);

int main(){
    inSet = new int[MAXNUM];
//    debug = true;
//    debug2 = true;

    int v1, v2;
    while(1){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        for(int i=0;i<n;i++){
            inSet[i] = 0;
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


        //backtracking with pruning.
        //TODO divide into connected components.
        vector<vector<int> > scc;
        for(int i=0;i<n;i++){
            if(inSet[i] == 0){
                vector<int> nextSet;
                nextSet.push_back(i);
                inSet[i] = 1;
                dfs(i,nextSet);
                scc.push_back(nextSet);
            }
        }

        //backtrack from service station 1, and see where to go next.
        depth = 0;
        int total = 0;
        if(debug)
            cout << "scc size = " << scc.size() << endl;
        for(int i=0;i<scc.size();i++){
            //reset all inSet.
            for(int j=0;j<n;j++)
                inSet[j] = 0;
            
            currComponent = scc[i];
            minSize = scc[i].size();
            currN = minSize;
            backtrack(currN,0);
            total += minSize;
        }

        /*
        for(int i=0;i<35;i++)
            currComponent.push_back(i);
        minSize = 35;
        currN = 35;
        backtrack(35,0);
        int total = minSize;
        */

        cout << total << endl;
        //TODO need to delete all dynamically
        //allocated variables.
        //for(int i=0;i<MAXNUM;i++)
        //    delete arr[i];
    }
    delete inSet;
}

void dfs(int a, vector<int> &v){
    for(int i=0;i<n;i++)
        if(arr[a][i] && !inSet[i]) {
            v.push_back(i);
            inSet[i] = 1;
            dfs(i,v);
        }
    return;
}

void backtrack(int stationsLeft, int setSize){
    //check if this is a solution.
    //if all stations are covered
    int count = 0;
    int i,j;
    if(stationsLeft <= 1){
        for(i=0;i<currN;i++)
            if(inSet[currComponent[i]]) count++;
        if(debug)
        cout << "Covered all nodes" 
            << ", Current minsize = "
            << minSize
            << endl;

        if(stationsLeft == 1) count++;
        if(minSize > count){
            minSize = count;
            if(debug)
            cout << "New minSize = "
                << minSize
                << endl;
        }
        return;
    }

    if(setSize >= minSize) return;

    //now that atleast 1 station is left, choose
    //the candidates to traverse through in the optimal
    //order. here the order is greedy.
    vector<Node> nodeList;
    bool alreadySet;
    //find the degree of each station.
    for(i=0;i<currN;i++){
        count = 0;
        if(inSet[currComponent[i]]) continue;
        //cout << "reached at i=" << i+1 <<endl;
        for(j=0;j<currN;j++){
            if(arr[currComponent[i]][currComponent[j]]){
                alreadySet = false;
                //check if it hasn't already been covered by
                //someone else.
                for(int k=0;k<currN;k++){
                    if(debug2)
                    cout << "checking if node " << k
                        << " is already set: " << inSet[currComponent[k]]
                        << " and the value of arr[j][k] = " 
                        << arr[currComponent[j]][currComponent[k]]
                        << endl;
                    if(inSet[currComponent[k]] && arr[currComponent[j]][currComponent[k]]) {
                        alreadySet = true;
                        break;
                    }
                }
                if(!alreadySet) count++;
            }
        }
        if(count != 0){
            Node next(count, currComponent[i]);
            nodeList.push_back(next);
        }
    }
    sort(nodeList.begin(), nodeList.end());
    int len = nodeList.size();
    if(debug)
    cout << "node num for stationsLeft = "
        << stationsLeft 
        << ", is "
        << len
        << endl;

    //choose candidate order
    //order candidates by decreasing order of degree of
    //uncovered vertices, and choose them in that order.
    for(i=len-1; i>=0; i--){
        //set candidate
        inSet[nodeList[i].vertex] = true;
        if(debug)
        cout << "Chosen node: "
            << nodeList[i].vertex +1 
            << ", with uncovered degree: "
            << nodeList[i].degree
            << endl;

        setSize++;
        count = 0;

        //backtrack
        if(debug)
        cout << "Starting Depth = " << depth << endl;
        depth++;
        backtrack(stationsLeft-nodeList[i].degree, setSize);
        depth--;
        if(debug)
        cout << "Returning Depth = " << depth << endl;

        //unset candidate
        inSet[nodeList[i].vertex] = false;
        setSize--;
    }
}
