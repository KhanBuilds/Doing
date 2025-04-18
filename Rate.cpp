#include <iostream>
#include <cmath>
#include <unordered_map>
#include <string>
using namespace std;
int K = 30;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


double expectedscore(int ratingplayer, int ratingopponent){
	return 1.0 / (1.0 + pow(10.0, (ratingopponent - ratingplayer) / 400.0));
	
}

int updatescore(int currentrating, int opponentrating, double score, int K){
	double expectedScore = expectedscore(currentrating, opponentrating);
    return currentrating + K * (score - expectedScore);
}



int main(int argc, char** argv) {
	unordered_map<string, int> playerRatings;
	string S = "Soban";
	string I = "Ismail";
	string H = "Hasnain";
	string M = "Musa";
	
	playerRatings[S] = 1500;
	playerRatings[I] = 1200;
	playerRatings[H]= 1300;
	playerRatings[M] = 1000;
	
	
	//simulated match between Soban and Ismail in which Ismail wins
	//Soban's rating after the match
	double pSs = 0;
	double pIs = 1;
	
	playerRatings[S]= updatescore(playerRatings[S],playerRatings[I], pSs, K );
	
	cout << "Soban's rating after the match: " << playerRatings[S] <<endl;
	
	//Ismail's rating after the match
	playerRatings[I]= updatescore(playerRatings[I],playerRatings[S], pIs, K );
	
	cout << "Ismail's rating after the match: " <<playerRatings[I]<<endl;
	
	
	
	
}
