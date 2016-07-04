// hello world
/*

Find the max lenght of a substring in a string such that substring contains unique characters
   paragraph has graph
   abcdefcbaf  has abcdef, defca,caf
   
   map<char, int> m;
   start from index 0
   
   initially m is empty.
   
   i=0;
   m[a] = 0
   i= 1;
   
   abcdcbe
   1,2,3,4,
   last index of c is 2.
   
   b is at positions 1, and 5

*/

   #include<iostream>
   #include<map>
   #include<vector>
   
   using namespace std;
   
   int main(){
       string s;
       map<char, int> lastSeenIndex;
       int maxSoFar = 0;
       int currentMax = 0;
       
       while(cin >> s){

           int n = s.length();
           if(n == 0) return 0;

           lastSeenIndex.clear();
           lastSeenIndex[s[0]] = 0;
           maxSoFar = 1;
           currentMax = 1;

           for(int i=1;i<n;i++){
               //at the ith position, and determine the longest substring
               // that includes the ith character.
               //s[i] can be 1+s[i-1], this is if s[i] doesn't appear in the
               //longest substring ending in s[i-1]

               //or s[i] can be 1+(i-lastSeenIndex[s[i]]) if s[i] appears in the
               //longest substring ending in s[i-1]

               if((lastSeenIndex.find(s[i]) == lastSeenIndex.end()) ||
                       lastSeenIndex[s[i]] < (i-currentMax)){
                   currentMax = 1+currentMax;
               }
               else{
                   currentMax = i-lastSeenIndex[s[i]];
               }
               if(currentMax > maxSoFar)
                   maxSoFar = currentMax;

               lastSeenIndex[s[i]] = i;
           } //end of for.
           cout << maxSoFar << endl;
       }
       return 0;
   }
