#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int K = 32;

double expectedscore(int playerrating, int opponentrating){
	double base= 1.0 / (1.0 + pow(10.0, (opponentrating - playerrating) / 400.0));
}
	
	
int updatescore(int currentrating, int opponentrating, double score, int K){
	double expectedScore = expectedscore(currentrating, opponentrating);
    return currentrating + K * (score - expectedScore);
}

int main(){
	//Seeds the random generator with time
	srand(time(0));
	//Creats an unordered map which stores the int ratings against string values
	unordered_map<string, int> debaterRatings;
	string S = "Soban";
	string I = "Ismail";
	string H = "Hasnain";
	string M = "Musa";
	
	debaterRatings[S] = 1000;
	debaterRatings[I] = 1000;
	debaterRatings[H]= 2000;
	debaterRatings[M] = 1500;
	
	//Creating a string vector to store the debaters name
	vector<string> debaters;
	
	//Looping through the unordered map to push back key values to the vector
	for(auto& pair:debaterRatings ){
		debaters.push_back(pair.first);
	}
	
	//looping through the vectors to see the stored values
	for (const auto& pair: debaterRatings){
		cout << pair.first << " " << pair.second<<endl;
	}
	
	//We have the different players stored in the vector to make the matchmaking random 
	//I will use the rand operator to generate random indexes within the size range through the modulo
	int index1 = rand() % debaters.size();
	int index2;
	
	do{
		 index2 = rand() % debaters.size();
		
	}while ( index2 == index1);
	
	//Simulating the match between random debaters
	string debater1 = debaters[index1];
	string debater2 = debaters[index2];
	
	//the random winner
	int winner = rand() % 2;
	
	//Printing the winner 
	cout << "Winner is: " << (winner == 0 ? debaters[index1] : debaters[index2]) <<endl; // 0 so player index 1 wins if 1 then player index 2 wins
		
	double db1 = (winner == 0) ? 1.0 : 0.0; //Assigns score 1.0 to player index1 if winner == 0
	double db2 = (winner == 1) ? 1.0 : 0.0; //Assigns score 1.0 to player index2 if winner == 1
	
	//Fetching the debaters ratings
	int debaterRating1 = debaterRatings[debater1];
	int debaterRating2 = debaterRatings[debater2];
	
	//Storing the updated ratings in different variables
	int newdebaterRating1 = updatescore(debaterRating1, debaterRating2, db1, K);
	int newdebaterRating2 = updatescore(debaterRating2, debaterRating1, db2, K);
	
	//Updating the original ratings
	debaterRatings[debater1] = newdebaterRating1;
	debaterRatings[debater2] = newdebaterRating2;
	
	//Printing the updated ratings
	cout << "Rating of " <<debaters[index1] << " after the match is: " << debaterRatings[debater1]<<endl;
	cout << "Rating of " <<debaters[index2] << " after the match is: " << debaterRatings[debater2]<<endl;
	
	return 0;	
}