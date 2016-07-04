class Solution {
public:
    map<string, int> numberDecodes;
    int numDecodings(string s) {

        for(int i=1;i<=26;i++){
            ostringstream oss;
            oss << i;
            if(i < 10)
                numberDecodes[oss.str()] = 1;
            else
                numberDecodes[oss.str()] = 2;
        }
        numberDecodes["10"] = 1;
        numberDecodes["20"] = 1;

        return myDecode(s, s.length());
    }
    
    int myDecode(string &s, int endPosn){
        if(endPosn <= 0) return 0;
        string shorter = s.substr(0,endPosn);

        if(numberDecodes.find(shorter) != numberDecodes.end())
            return numberDecodes[shorter];
        
        //the number of ways to decode this string,
        //is the number of ways to decode the string ending at
        //endPosn -1 + endPosn-2;
        
        //there are atleast 2 characters in s.
        int last1 = (s[endPosn-1]-'0');
        int last2 = last1 + (s[endPosn-2]-'0')*10;

        numberDecodes[shorter] = 0;

        //if last1 is a 0, houston, we have...
        if(last1 != 0)
            numberDecodes[shorter] = myDecode(s, endPosn-1);

        if(last2 >= 10 && last2 <= 26)
            numberDecodes[shorter] += myDecode(s,endPosn-2);
        
        return numberDecodes[shorter];
    }
};