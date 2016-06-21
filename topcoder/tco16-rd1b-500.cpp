#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class ReplacingDigit{
    public:
    int getMaximumStockWorth (vector<int> A, vector<int> D){
        int n = A.size();
        
        int msd[7][10];
        for(int i=0;i<7;i++)
            for(int j=0;j<9;j++)
            msd[i][j] = 0;
        //divide into most significant digits.
        for(int i=0;i<n;i++){
            int num = A[i];
            int sig = 0;
            while(num > 0){
            	msd[sig][num%10]++;
                num /= 10;
                sig++;
            }//while
        }//for
        long long myresult=0;
        for(int sig=6;sig>=0;sig--){
        	for(int digit=1;digit<=9;digit++){
                myresult += pow(10.0,sig) * msd[sig][digit];
            }//for digit
        }//for sig
        cout << myresult << endl;

        
        //greedy algo.
        //sig represents significant bit.
        for(int sig=6;sig>=0;sig--){
            //for 6th digit, cycle through
            for(int digit=1;digit<9;digit++){
                if(msd[sig][digit]){
                    //try to give the best stickers to these.
                    for(int stickers=9;stickers>digit;stickers--){
                        if(D[stickers-1]){
                        	int given = std::min(msd[sig][digit], D[stickers-1]);
                            D[stickers-1] -= given;
                            msd[sig][digit] -= given;
                            msd[sig][stickers] += given;
                        } // if
                        if(msd[sig][digit] == 0) break;
                    } // for
                } // msd if
            } // digit for
        } // sig for
        
        long long result=0;
        for(int sig=6;sig>=0;sig--){
        	for(int digit=1;digit<=9;digit++){
                result += pow(10.0,sig) * msd[sig][digit];
            }//for digit
        }//for sig
        return result;
    }//funcn
};