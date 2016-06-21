#include<iostream>
#include<vector>
using namespace std;

int MAX = 1004;
class Queueing{
	public:
    double probFirst(int len1, int len2, int p1, int p2){
    	double result = 0;
        double PC1[MAX][MAX];
        double PC2[MAX][MAX];
        
        for(int i=0;i<MAX;i++)
        for(int j=0;j<MAX;j++)
        	PC1[i][j] = PC2[i][j] = 0.0;
            
        double f1 = 1.0/(double)p1;
        double f2 = 1.0/(double)p2;
        
        PC1[0][0] = PC2[0][0] = 1.0;
        double L1exactly1[MAX];
        double L2exactly1[MAX];
        //cout << "F1=" << f1;
        L1exactly1[0] = L2exactly1[0] = 1.0;
        PC1[1][1] = L1exactly1[1] = f1;
        PC2[1][1] = L2exactly1[1] = f2;

        for(int i=1;i<MAX;i++){
            //PC1[0][i] = PC2[0][i] = 0.0;
            //PC1[1][i] = (1-f1)*PC1[1][i-1];
            //PC2[1][i] = (1-f2)*PC2[1][i-1];
            PC1[i][i] = PC1[i-1][i-1]*f1;
            PC2[i][i] = PC2[i-1][i-1]*f2;
            L1exactly1[i] = (1.0-f1)*L1exactly1[i-1];
            L2exactly1[i] = (1.0-f2)*L2exactly1[i-1];
            //if(i<10)
            //cout << i << "," << L1exactly1[i] << "hello";
        }
        
        //compute PC1,2[i][j], for i < j (i.e. probability that a line
        //of length i finished in exactly j seconds.
        for(int i=1;i<MAX;i++){
            for(int j=i+1; j<MAX; j++){
                PC1[i][j] = PC1[i][j-1];
                PC2[i][j] = PC2[i][j-1];
                for(int k=j-1;k>=i-1;k--){
                	PC1[i][j] += PC1[i-1][k] * L1exactly1[j-k];
                	PC2[i][j] += PC2[i-1][k] * L2exactly1[j-k];
                }
            }
        }

        for(int i=1;i<MAX;i++){
            if(i<10)
            cout << PC1[len1][i] << "," << PC2[len2][i] << "hi" << endl;
            result += PC1[len1][i]*(1-PC2[len2][i]);
            
        }
        return result;
    }
};