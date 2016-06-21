#include<iostream>
#include<sstream>

using namespace std;

int main(){
	string s;
	int cases = -1;
	cin >> cases;
	std::getline(cin,s);
	while(std::getline(cin,s))
		cout << "#" << s << "@" << endl;
}
