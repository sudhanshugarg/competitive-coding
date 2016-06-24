#include<iostream>
#include<vector>
#include<map>
#include<stack>
#include<sstream>

using namespace std;


typedef struct Trie{
    map<char, Trie*> next;
    int numQ;
    Trie() : numQ(0){}

}Trie;

typedef struct Tree{
    vector<Tree*> children;
    Tree* parent;
    Trie* dict;
    string name;
}Tree;

map<string, Tree*> directAccessToTreeNode;

//TODO figure out why I cant use const for Trie* T.
int findQuery(Trie* T, const string& prefix, int posn){
    if(T == NULL || T->numQ == 0) return 0;

    if(posn >= prefix.length())
        return T->numQ;

    //find the next character, if it doesn't exist, return 0.
    if(T->next.find(prefix[posn]) == T->next.end()) return 0;
    return findQuery(T->next[prefix[posn]], prefix, posn+1);

}

void pushQuestion(const string &s, int posn, Trie* tr){

    if(posn >= s.length()) return;
    if(tr->next.find(s[posn]) == tr->next.end())
        tr->next[s[posn]] = new Trie();

    tr->next[s[posn]]->numQ++;
    pushQuestion(s, posn+1, tr->next[s[posn]]);
}

string mytrim(const string& s){
    int i,j;
    i = 0;
    j = s.length()-1;
    while(s[i] == ' ' || s[i] == '\t' || s[i] == '\n') i++;
    while(s[j] == ' ' || s[j] == '\t' || s[j] == '\n') j--;
    //return the substring from i to j, inclusive.
    return s.substr(i, j-i+1);
}

void insertTrie(Tree* T, const string &q){
    if(T->dict == NULL)
        T->dict = new Trie();

    pushQuestion(q, 0, T->dict);
    (T->dict)->numQ++;
}

void insertQuestion(const string &name, const string &q){
    //assume that name is always a node in the tree.
    Tree* node = directAccessToTreeNode[name];
    //if this is the root
    while(node != NULL){
        insertTrie(node, q);
        node = node->parent;
    }
    return;
}


int main(){
    int N, M, K;
    cin >> N;
    //there are N topics.
    //
    string line;
    std::getline(cin, line);
    istringstream iss;
    string s;
    int level = 0;
    //there is a guarantee for a single root topic
    iss >> s;
    Tree* root = new Tree();
    root->parent = NULL;
    root->dict = NULL;
    root->name = s;
    directAccessToTreeNode[root->name] = root;

    stack<Tree*> st;
    Tree* currentTop = root;

    while(iss >> s){
        if(s == "("){
            st.push(currentTop);
            //currentTop stays unchanged.
        }
        else if (s == ")"){
            st.pop();
            if(!st.empty()) currentTop = st.top();
            else currentTop = NULL;
        }
        else{
            Tree* next = new Tree();
            next->name = s;
            next->parent = currentTop;
            next->dict = NULL;
            currentTop->children.push_back(next);
            directAccessToTreeNode[s] = next;
        }
    }
    //this has created the tree. Now comes the time to populate it.
    //based on the question, it seems like the topic names have to be
    //unique. This is simply because the queries are made against
    //the topic name, and thus have to be unique.

    cin >> M;
    for(int i=0;i<M;i++){
        std::getline(cin,line);
        istringstream iss2(line);
        string q;
        std::getline(iss2, s, ':');
        std::getline(iss2, q, ':');
        //
        //first token is name of tree node
        //second token is question
        q = mytrim(q);
        insertQuestion(s, q);
    }

    //now that we have inserted all possible questions, now its 
    //time to find the queries.
    cin >> K;
    for(int i=0;i<K;i++){
        std::getline(cin, line);
        istringstream iss2(line);
        string topic, prefix;
        iss2 >> topic;
        getline(iss2, prefix);
        prefix = mytrim(prefix);

        //assuming prefix exists.
        //TODO put in a check incase it doesn't exist.
        cout << findQuery(directAccessToTreeNode[topic]->dict, prefix, 0) << endl;
    }
}
