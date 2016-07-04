class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string>> ret;
        int s = beginWord.length();
        if(s != endWord.length()) return ret;

        map<string, vector<string> > prev;
        //now the other cases.
        queue<string> nextWord;
        nextWord.push(beginWord);
        
        string next="",morphed;
        map<string, int> visited;
        map<string, int>::iterator vit;
        
        visited[beginWord] = 1;
        int minDist = -1;
        next = beginWord;
        
        while(!nextWord.empty() && (minDist == -1 || minDist > visited[next])){
            next = nextWord.front();
            if(next == endWord) break;
            nextWord.pop();

            for(int i=0;i<s;i++){
                morphed = next;
                for(int j=0;j<26;j++){
                    morphed[i] = 'a'+j;
                    //we have already seen this word.
                    vit = visited.find(morphed);
                    if(vit != visited.end()){
                        //make sure that the distance to this word
                        //is the same as earlier.
                        if(vit->second == visited[next] + 1){
                            //then we add this word to the prev.
                            prev[morphed].push_back(next);
                        }
                        else continue;
                    }
                    else if(wordList.find(morphed) != wordList.end()){
                        //first time visiting this morphed word.
                        //and it is in the dictionary.
                        prev[morphed] = vector<string>{next};
                        visited[morphed] = visited[next]+1;
                        nextWord.push(morphed);
                        if((minDist == -1) && (morphed == endWord)){
                            minDist = visited[endWord];
                        }
                    }
                }
            }
        }// endwhile
        
        //if next isn't endWord, didn't find
        if(next != endWord) return ret;
        vector<string> &path{endWord};
        createSequences(prev, ret, beginWord, endWord, path);
        return ret;
    }
    
    void createSequences(map<string, vector<string> > &prev, vector<vector<string> > &ret,
                            string &beginWord, string &lastWord, vector<string> &path){

        if(lastWord == beginWord){
            reverse(path.begin(), path.end());
            ret.push_back(path);
            reverse(path.begin(), path.end());
            return;
        }
        for(int i=0;i<prev[lastWord].size();i++){
            path.push_back(prev[lastWord][i]);
            createSequences(prev, ret, beginWord, prev[lastWord][i], path);
            path.pop_back();
        }
        ret.push_back(path);
    }
};