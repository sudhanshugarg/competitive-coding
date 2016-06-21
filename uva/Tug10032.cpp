#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;

int main(){
    int T;
    cin >> T;
    string s;
    getline(cin,s);

    int a,i,j,k,n;
    vector<int> wt(100);
    //bool reach[460][110];
    bool reach[45100];
//    int maxppl[45100];
//    int minppl[45100];
//    int oldmaxppl[45100];
//    int oldminppl[45100];
    bool b[45100][100];

    for(a=0;a<T;a++){
        cin >> n;
        for(j=0;j<n;j++)
            cin >> wt[j];

        //dont really need to sort them.
        sort(wt.begin(), wt.begin()+n);
        memset(reach, 0, sizeof(reach));
        memset(b, 0, sizeof(b));


        int total = 0;
        for(i=0;i<n;i++) total += wt[i];
        int currMax;

        /*
        memset(maxppl, 0, sizeof(maxppl));
        memset(minppl, 1, sizeof(minppl));
        memset(oldmaxppl, 0, sizeof(oldmaxppl));
        memset(oldminppl, 1, sizeof(oldminppl));
        */
        //can reach 0 weight, using 0 people.
        reach[0] = true;
        /*
        oldminppl[0] = minppl[0] = 0;
        oldmaxppl[0] = maxppl[0] = 0;
        */
        currMax = 0;
        b[0][0] = true;

        //cout << total << endl;
        int mid = total/2;
        int num = n/2;
        if(n%2) num++;

        for(i=0;i<n;i++){
            //using the ith person, the weights you can reach are:
            //can you reach wt
            //cout << "for i = " << i 
            //    << ", currMax = " << currMax << endl;
            for(j=currMax;j>=0;j--){
                if(reach[j]){
                    reach[j+wt[i]] = true;
                    //keep a count of the minimum and maximum number of people
                    //you can reach using this.
                    
                    //new stuff
                    //for all the numbers that j can be reached
                    //with, j+wt[1] can be reached with by j+1 bits.
                    for(k=i;k>=0;k--){
                        if(b[j][k]){
                            /*
                            if(j+wt[i] == 6){
                                cout << j << "#" << endl;
                                cout << wt[i] << "@" << endl;
                                cout << i << "$" << endl;
                                cout << k+1 << endl;
                            }
                            */
                            b[j+wt[i]][k+1] = true;
                        }
                    }
                    /*
                    if(minppl[j+wt[i]] > (oldminppl[j]+1))
                        minppl[j+wt[i]] = oldminppl[j]+1;
                    if(maxppl[j+wt[i]] < (oldmaxppl[j]+1))
                        maxppl[j+wt[i]] = oldmaxppl[j]+1;
                        */

                }
            }
            currMax = currMax+wt[i];
            /*
            for(j = 0;j<=currMax;j++){
                oldminppl[j] = minppl[j];
                oldmaxppl[j] = maxppl[j];
            }
            */
        }
        /*
        for(i=0;i<=total;i++){
            if(reach[i]){
                cout << i << " can be reached using: ";
                for(j=0;j<n;j++){
                    if(b[i][j])
                        cout << j << ",";
                }
                cout << endl;
            }
        }
        */


        //now find out which of these
        //weights are reachable by using
        //some subset of the people.
        //starting from total/2, move lower.
        //if a number can be reached, such that
        //it can be made by atleast
        //cout << "num = " << num << endl;
        //cout << "mid = " << mid << endl;
        for(i=mid;i>=0;i--){
            //cout << i << "," << reach[i] << "," << b[i][num] << endl;
            if(reach[i] && b[i][num]){
                //cout << "reached here" << endl;
                break;
            }
        }
        if(i == -1){
            //has to be odd.
            num--;
            for(i=mid;i>=0;i--){
                if(reach[i] && b[i][num]){
                    break;
                }
            }
        }
        cout << i << " " << total-i << endl;
        if(a != T-1)
            cout << endl;
    }
}
