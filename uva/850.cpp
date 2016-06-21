#include<iostream>
#include<vector>
#include<sstream>
#include<map>


using namespace std;

const int MAXLEN = 85;

void findfreq(map<int, vector<int> > &freq, const string &s){
	for(int i=0;i<s.length();i++){
		//find char encoder[i] all over the string;
		for(int j=0;j<s.length();j++)
			if(s[i] == s[j]){
				//if(freq.find(i) == freq.end())
					//freq[i] = vector<int> ();
				freq[i].push_back(j);
			}
	}
}

int main(){
	int cases = 0;
	cin >> cases;
	//cout << cases << endl;
	string s;
	std::getline(cin, s);
	std::getline(cin, s);
	//cout << s << "@" << endl;
	vector<string> all;

	//store the encoder;
	string encoder = "the quick brown fox jumps over the lazy dog";
	string copy = encoder;
	map<int, vector<int> > freq;
	//int freq[MAXLEN];
	int i,j;
	for(i=0;i<MAXLEN;i++)
		freq[i] = vector<int>();

	findfreq(freq, encoder);
	//for(i=0;i<MAXLEN;i++)
	//	cout << freq[i] << " ";
	//cout << endl;

	while(cases--){
		all.clear();
		while(std::getline(cin,s)){
			//cout << s << "#" << endl;
			if(s.length() == 0) break;
			all.push_back(s);
		}

		//identify the decoder.
		//int wfreq[MAXLEN];

		for(i=0;i<all.size();i++){
			//find which string matches the encoder
			map<int, vector<int> >wfreq;
			for(j=0;j<MAXLEN;j++)
				wfreq[j] = vector<int>();
			findfreq(wfreq, all[i]);
			for(j=0;j<MAXLEN;j++)
				if(freq[j] != wfreq[j]) break;
			if(j == MAXLEN) break;
		}
		if(i == all.size()){
			cout << "No solution" << endl;
			if(cases > 0) cout << endl;
			continue;
		}

		//now that we have found it, decode it.
		map<char,char> decode;
		int pos = i;
		for(i=0;i<encoder.length();i++)
			decode[all[pos][i]] = encoder[i];

		for(i=0;i<all.size();i++){
			for(j=0;j<all[i].length();j++){
				all[i][j] = decode[all[i][j]];
			}
			cout << all[i] << endl;
		}
		if(cases > 0) cout << endl;
	}
}
