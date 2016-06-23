#include<iostream>
#include<vector>
#include<map>
#include<cstring>
using namespace std;

const int MAXSIZE = 100100;
const int MAXTIME = 1000010;
int readingTime[MAXSIZE];
map<pair<int,int>, double> edges;
vector< vector<int> > edgeStore;
vector<double> expectedValue; 

void dfs(const pair<int,int> &p){
    if(edges[p] != 0) return;

    int u = p.first;
    int v = p.second;

    int deg = edgeStore[v].size();
    edges[p] = readingTime[v];
    if(deg == 1) return;

    //first find out if the expectedValue for v
    //has already been calculated. If so, then
    //you can easily compute the value for 
    //edges[p];
    //
    //if u hasn't been calculated, then the array
    //won't be that long.

    //already know that degree of v is atleast 2.
    if(expectedValue.size() > v) {
        //already calculated the value of v.
        pair<int,int> revp;
        revp.first = v;
        revp.second = u;
        edges[p] = ((expectedValue[v] - readingTime[v])* edgeStore[v].size()
                    - edges[revp]) 
                    /(edgeStore[v].size()-1) + readingTime[v];
        return;
    }
    //now, calculate the value for a dfs, starting
    //from node u as root, and travelling towards
    //node v.

    //v is connected to atleast 1 node, including u
    //from where it arrived.
    //perform dfs on each node
    //except u
    pair<int,int> next;
    next.first = v;
    for(int i=0;i<deg;i++){
        if(edgeStore[v][i] == u) continue;
        //say the next edge is v,w.
        next.second = edgeStore[v][i];
        dfs(next);
        edges[p] += edges[next]/(double)(deg-1);
    }
}

int main(){
    int N;
    pair<int,int> p;

    cin >> N;
    memset(readingTime, 0, sizeof(readingTime));
    for(int i=0;i<N;i++)
        cin >> readingTime[i];

    edgeStore.resize(N,vector<int>());
    //read in edges
    for(int i=0;i<N-1;i++){
        cin >> p.first >> p.second;
        //0-indexed
        p.first--;
        p.second--;
        edges[p] = 0.0;

        //undirected graph.
        //store both directions in map
        int tmp = p.first;
        p.first = p.second;
        p.second = tmp;
        edges[p] = 0.0;

        //create "linked list" for edge storage.
        edgeStore[p.first].push_back(p.second);
        edgeStore[p.second].push_back(p.first);

    }

    //algorithm: find the expected value of each edge e(i,j).
    //note that the expected value of e(i,j) is not the same
    //as the E[e(j,i)].
    //base case, when i is a leaf, then E[(v,i)] = readingTime[i];
//    map<pair<int,int>, double>::iterator it;
//    for(it = edges.begin(); it != edges.end(); it++){
//        dfs(it->first);
//    }

    //now, for all edges e(u,v), we have the expected
    //reading time taken if a person starts reading at node v, coming
    //from node u. Note that the time taken at node u is not
    //incorporated in this, but the reading time taken at node v
    //is infact incorporated in this.
    double minVal = (double)MAXSIZE * (double)MAXTIME;
    int minVertex;
    double currVal;
    double deg;
    for(int i=0;i<N;i++){
        //compute the edges value.
        deg = (double)edgeStore[i].size();
        currVal = readingTime[i];
        p.first = i;
        for(int j=0;j<deg;j++){
            p.second = edgeStore[i][j];
            dfs(p);
            currVal += edges[p]/deg;
        }
        expectedValue.push_back(currVal);
        if(currVal < minVal){
            minVal = currVal;
            minVertex = i+1;
        }
    }
//    for(int i=0;i<N;i++)
//        cout << expectedValue[i] << "#" << endl;
    cout << minVertex << endl;
}
