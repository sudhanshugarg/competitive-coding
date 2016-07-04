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
        //cout << "inserting $" << q << "$" 
        //    << " in %" << node->name << "%"
        //    << endl;
        insertTrie(node, q);
        node = node->parent;
    }
    return;
}

string findLongestSubstr(const string &question, int posn, Trie *queryTrie){
    if(posn >= question.length()) return question;

    if(queryTrie->next.find(question[posn]) == queryTrie->next.end())
        return question.substr(0,posn);
    return findLongestSubstr(question, posn+1, queryTrie->next[question[posn]]);
}


int main(){
    int N, M, K;
    cin >> N;
    //cout << N << endl;
    //there are N topics.
    //
    string line;
    std::getline(cin, line);
    std::getline(cin, line);
    //cout << "line = " << line << endl;
    string s;
    istringstream iss(line);


    //there is a guarantee for a single root topic

    stack<Tree*> st;
    Tree* currentNode = NULL;
    map<string, vector<string> > listOfQs;

    //cout << "reahced here" << endl;

    while(iss >> s){
        //cout << "next string: #" << s << "#" << endl;
        if(s == "("){
            st.push(currentNode);
            //currentTop stays unchanged.
        }
        else if (s == ")"){
            st.pop();
        }
        else{
            Tree* next = new Tree();
            next->name = s;
            //if(st.empty()) cout << "Parent is currently NULL" << endl;
            //else cout << "The parent of #" << s << " is #" << st.top()->name << "#" << endl;
            if(!st.empty())
                next->parent = st.top();
            else next->parent = NULL;
            next->dict = NULL;
            directAccessToTreeNode[s] = next;
            //TODO confirm that children of a node aren't needed.
            currentNode = next;
            listOfQs[s] = vector<string>();
        }
    }
    //this has created the tree. Now comes the time to populate it.
    //based on the question, it seems like the topic names have to be
    //unique. This is simply because the queries are made against
    //the topic name, and thus have to be unique.

    cin >> M;
    std::getline(cin, line);
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
        //cout << "topic = #" << s << "#" << endl;
        //cout << "question = #" << q << "#" << endl;
        //insertQuestion(s, q);
        listOfQs[s].push_back(q);
    }

    //now that we have inserted all possible questions, now its 
    //time to find the queries.


    Trie* queryTrie = new Trie();
    cin >> K;
    std::getline(cin, line);
    vector<string> topics;
    vector<string> queries;
    for(int i=0;i<K;i++){
        std::getline(cin, line);
        istringstream iss2(line);
        string topic, prefix;
        iss2 >> topic;
        getline(iss2, prefix);
        prefix = mytrim(prefix);

        //cout << "finding: #" << prefix << "#" 
        //    << ", in topic: #" << topic << "#"
        //    << endl;

        //insert this prefix into a queryTrie.
        pushQuestion(prefix, 0, queryTrie);
        topics.push_back(topic);
        queries.push_back(prefix);
        //assuming prefix exists.
        //TODO put in a check incase it doesn't exist.
        //cout << findQuery(directAccessToTreeNode[topic]->dict, prefix, 0) << endl;
    }

    map<string, vector<string> >::iterator it;
    for(it = listOfQs.begin(); it!=listOfQs.end(); it++){
        for(int i=0;i<it->second.size();i++){
            //find the longest substring that exists in queryTrie.
            string sub = findLongestSubstr(it->second[i], 0, queryTrie);
            insertQuestion(it->first, sub);
        }
        it->second.clear();
    }
    listOfQs.clear();
    delete queryTrie;

    for(int i=0;i<K;i++){
        cout << findQuery(directAccessToTreeNode[topics[i]]->dict, queries[i], 0) << endl;
    }

    //now iterate through all the queries, and find out the number
    return 0;
}
