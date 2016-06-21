// http://uva.onlinejudge.org/external/100/10032.html
// Runtime: 0.248s
// Tag: Dp
 
/*
 * File:   main.cpp
 * Author: shahab
 * Created on March 6, 2011, 11:24 PM
 */
 
// @BEGIN_OF_SOURCE_CODE
 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#include <numeric>
 
#define INT_MAX 2147483647
#define INT_MIN -2147483647
#define pi acos(-1.0)
#define N 1000000
#define LL long long
 
#define For(i, a, b) for ( int i = (a); i < (b); i++ )
#define Fors(i, sz) for ( size_t i = 0; i < sz.size (); i++ )
#define Set(a, s) memset (a, s, sizeof (a))
 
using namespace std;
 
int weight [100 + 10];
bool minWeight [45000 / 2 + 100];
int minPeople [45000 / 2 + 100];
int maxPeople [45000 / 2 + 100];
 
int main(int argc, char** argv) {
    int testCase;
    scanf ("%d", &testCase);
    bool blank = false;
 
    while ( testCase-- ) {
        int n; scanf ("%d", &n);
        int total = 0;
 
        For (i, 0, n) { scanf ("%d", &weight [i]); total += weight [i]; }
 
        Set (minWeight, false);
        for ( int i = 0; i < 45000 / 2 + 100; i++ ) { minPeople [i] = INT_MAX; maxPeople [i] = 0; }
        minWeight [0] = true;
        minPeople [0] = 0;
 
        For (i, 0, n) {
            for ( int j = total / 2 + 5; j >= 0; j-- ) {
                if ( minWeight [j] ) {
                    minWeight [j + weight [i]] = true;
                    if ( minPeople [j + weight [i]] > minPeople [j] + 1)
                        minPeople [j + weight [i]] = minPeople [j] + 1;
                    if ( maxPeople [j + weight [i]] < maxPeople [j] + 1)
                        maxPeople [j + weight [i]] = maxPeople [j] + 1;
                }
            }
        }
 
        if ( blank ) printf ("\n"); blank = true;
 
        for ( int i = total / 2; i >= 0; i-- ) {
            if ( minWeight [i] && ((minPeople [i] <= n / 2 && maxPeople [i] >= n / 2) || (minPeople [i] <= n / 2 + n % 2 && maxPeople [i] >= n / 2 + n % 2)) ) {
                printf ("%d %d\n", i, total - i); break;
            }
        }
 
    }
 
    return 0;
}
 
// @END_OF_SOURCE_CODE