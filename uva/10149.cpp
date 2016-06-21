#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>
using namespace std;

const int DIE=5;

bool matches(int roll[][5], int which, int cat){
	//find out which category the dice fall in.
	vector<int> r;
	int exists[6];
	for(int i=0;i<6;i++)
		exists[i] = 0;

	for(int i=0;i<DIE;i++){
		r.push_back(roll[which][i]);
		exists[roll[which][i]-1]++;
	}
	
	sort(r.begin(), r.end());
	switch(cat){
		case 9:
			//five of a kind
			if(r[0] == r[1] && r[1] == r[2] && r[2] == r[3] && r[3] == r[4])
				return 1;
			break;
		case 8:
			//four of a kind
			if(r[0] == r[1] && r[1] == r[2] && r[2] == r[3])
				return 1;
			if(r[4] == r[1] && r[1] == r[2] && r[2] == r[3])
				return 1;
			break;
		case 7:
			//three of a kind
			if(r[0] == r[1] && r[1] == r[2])
				return 1;
			if(r[1] == r[2] && r[2] == r[3])
				return 1;
			if(r[2] == r[3] && r[3] == r[4])
				return 1;
			break;
		case 11:
			//long straight
			if(exists[0] && exists[1] && exists[2] && exists[3] && exists[4])
				return 1;
			if(exists[5] && exists[1] && exists[2] && exists[3] && exists[4])
				return 1;
			break;
		case 10:
			//short straight
			if(exists[0] && exists[1] && exists[2] && exists[3])
				return 1;
			if(exists[4] && exists[1] && exists[2] && exists[3])
				return 1;
			if(exists[4] && exists[5] && exists[2] && exists[3])
				return 1;
			break;
		case 12:
			//full house
			if(r[0] == r[1] && r[2] == r[3] && r[3] == r[4])
				return 1;
			if(r[0] == r[1] && r[1] == r[2] && r[3] == r[4])
				return 1;
			break;
	}
	return 0;
}

int score(int roll[][5], int which, int cat){
	int count = 0;
	switch(cat){
		case 0:
			//sum of 1's
			for(int i=0;i<DIE;i++) if(roll[which][i] == 1) count++;
			return count;
			break;
		case 1:
			for(int i=0;i<DIE;i++) if(roll[which][i] == 2) count++;
			return count*2;
			break;
		case 2:
			for(int i=0;i<DIE;i++) if(roll[which][i] == 3) count++;
			return count*3;
			break;
		case 3:
			for(int i=0;i<DIE;i++) if(roll[which][i] == 4) count++;
			return count*4;
			break;
		case 4:
			for(int i=0;i<DIE;i++) if(roll[which][i] == 5) count++;
			return count*5;
			break;
		case 5:
			for(int i=0;i<DIE;i++) if(roll[which][i] == 6) count++;
			return count*6;
			break;
		case 6:
			//chance
			for(int i=0;i<DIE;i++) count+=roll[which][i];
			return count;
			break;
		case 7:
			//3 of a kind
			if(!matches(roll, which, 7)) return 0;
			for(int i=0;i<DIE;i++) count+=roll[which][i];
			return count;
			break;
		case 8:
			//4 of a kind
			if(!matches(roll, which, 8)) return 0;
			for(int i=0;i<DIE;i++) count+=roll[which][i];
			return count;
			break;
		case 9:
			//5 of a kind
			if(!matches(roll, which, 9)) return 0;
			return 50;
			break;
		case 10:
			if(!matches(roll, which, 10)) return 0;
			return 25;
			break;
		case 11:
			if(!matches(roll, which, 11)) return 0;
			return 35;
			break;
		case 12:
			if(!matches(roll, which, 12)) return 0;
			return 40;
			break;
		default:
			return 0;
	}
}

int main(){
	//13 die rolls are stored in
	string s;
	while(std::getline(cin, s)){
	int roll[13][5];
	for(int i=0;i<13;i++)
		for(int j=0;j<DIE;j++)
			roll[i][j] = 0;

	istringstream iss(s);
	for(int i=0;i<DIE;i++)
		iss >> roll[0][i];

	//take in all 13 die rolls.
	for(int i=1;i<13;i++){
		std::getline(cin, s);
		istringstream iss2(s);
		for(int j=0;j<DIE;j++){
			iss2 >> roll[i][j];
		}
	}
	//see how it works.
	//
	/*
	for(int i=0;i<13;i++){
		if(i == 0)
			cout << roll[i][0] << "," << roll[i][1] << "," << roll[i][2] << "," << roll[i][3] << "," << roll[i][4] << endl;
		for(int j=0;j<13;j++){
			cout << "roll" << i+1
				<< ",cat:" << j+1
				<< "=" << score(roll, i, j)
				<< endl;
		}
	}*/

	int n = (int)pow(2,13);
	int maxscore[13][n];
	int location[13][n];

	for(int j=n-1;j>=0;j--){
		//take roll 0
		maxscore[0][j] = -1;
		location[0][j] = -1;
		for(int k=0;k<13;k++){
			//if j says bit k is not free, continue;
			if(j & (int)pow(2,k)) continue;
			int val = score(roll,0,k);
			if(maxscore[0][j] < val){
				maxscore[0][j] = val;
				location[0][j] = k;
			}
		}
	}

	for(int i=1;i<13;i++)
		for(int j=n-1;j>=0;j--){
			maxscore[i][j] = -1;
			location[i][j] = -1;
			for(int k=0;k<13;k++){
				//if j says bit k is not free, continue;
				if(j & (int)pow(2,k)) continue;
				int val = score(roll,i,k);
				bool flag = 0;
				if(k < 6) {
					//check if first 6 categories are complete, if so,
					//and their sum is >= 63, update the maxscore
					//by 35 more.
					//also, update iff this k is a category, < 6.
					//find out all the categories already set.
					int used = j;
					int total = val;
					int cat = k;
					int num = 1;
					for(int l=i-1;l>=0;l--){
						//which category is the l+1th roll
						used = used|(int)pow(2,cat);
						cat = location[l][used];
						//if(cat == -1) break;
						if(cat < 6) {
							total += maxscore[l][used];
							num++;
						}
						if(num == 6){
							if(total >= 63)
								flag = 1;
							break;
						}
					}
				}
				if (flag) val += 35;
				if(maxscore[i][j] < (val + maxscore[i-1][j|(int)pow(2,k)])){
					maxscore[i][j] = val + maxscore[i-1][j|(int)pow(2,k)];
					location[i][j] = k;

				}
			}
		}

	int used = 0;
	int final[13];
	int rollnum[13];
	for(int l=0;l<13;l++){
		final[l] = 0;
		rollnum[l] = 0;
	}
	int cat = -1;
	for(int l=12;l>=0;l--){
		//which category is the l+1th roll
		cat = location[l][used];
		//if(cat == -1) continue;
		final[cat] = score(roll, l, cat);
		rollnum[cat] = l+1;
		used = used|(int)pow(2,cat);
	}

	int total = 0;
	int bonus = 0;

	for(int l=0;l<6;l++){
		bonus += final[l];
		cout << final[l] 
//			<< ":" << rollnum[l]
			<< " ";
	}
	total += bonus;
	for(int l=6;l<13;l++){
		total += final[l];
		cout << final[l] 
//			<< ":" << rollnum[l]
			<< " ";
	}
	if(bonus >= 63){
		total += 35;
		cout << "35 ";
	}
	else cout << "0 ";
	cout << total << endl;
	
	}
	
}
