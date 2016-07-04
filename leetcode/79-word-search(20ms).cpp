class Solution {
public:
    int M, N;
    int total;
    bool exist(vector<vector<char>>& board, string word) {
        //dfs.
        M = board.size();
        if(!M) return false;
        N = board[0].size();
        if(!N) return false;
        
        bool visited[500][500];
        memset(visited, false, sizeof(visited));
        total = M*N;
        
        bool found;
        for(int i=0;i<M;i++)
        for(int j=0;j<N;j++){
            found = dfs(board, word, visited, 0, i, j);
            if(found) return true;
        }
        return false;
    }
    
    bool dfs(vector<vector<char> > &board, string &word, bool visited[][500], int posnInWord, int r, int c){

        if(word.length() == posnInWord) {
            cout << "yay" << endl;
            return true;
        }

        if(r >= M || r < 0 || c >= N || c < 0) return false;
        if(visited[r][c]) return false;
        
        //this could be any one of the directions.
        bool found = false;
        if((board[r][c] == word[posnInWord])){
            visited[r][c] = true;
            //cout << "at position: " << r << "," << c << endl;
            found = dfs(board, word, visited, posnInWord+1, r+1, c);
            if(found) return true;
            found = dfs(board, word, visited, posnInWord+1, r-1, c);
            if(found) {
                //cout << "and thats a wrap" << endl;
                return true;
            }
            found = dfs(board, word, visited, posnInWord+1, r, c+1);
            if(found) return true;
            found = dfs(board, word, visited, posnInWord+1, r, c-1);
            visited[r][c] = false;
        }
        return found;
    }
};