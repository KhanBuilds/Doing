#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
using namespace std;

int K = 32;

double expectedscore(int playerrating, int opponentrating){
	double base= 1.0 / (1.0 + pow(10.0, (opponentrating - playerrating) / 400.0));
	
	//Adding slight randomness approx -0.10 to 0.10
	
	double noise = ((rand() % 21) - 10) / 100; // will result in slight randomness from -0.10 to 0.10
	double result = base + noise;
	
	//This limits the result to within the range of 0 to 1 
	if (result < 0.0) result = 0.0;
	else if (result > 1) result = 1;
	
	return result;
	
	
}

int updatescore(int currentrating, int opponentrating, double score, int K){
	double expectedScore = expectedscore(currentrating, opponentrating);
    return currentrating + K * (score - expectedScore);
}

int main(){
	//Seeds the random generator with time 
	srand(time(0));
	//Uses unordered maps to store int values against strings
	unordered_map<string, int> playerRatings;
	string S = "Soban";
	string I = "Ismail";
	string H = "Hasnain";
	string M = "Musa";
	
	playerRatings[S] = 1000;
	playerRatings[I] = 1000;
	playerRatings[H]= 1000;
	playerRatings[M] = 1000;

int ismailorg =	playerRatings[I];
int musaorg = playerRatings[M];
// Simulated match between Ismail and Musa
int winner = rand() % 2 ; // 0 for Ismail and 1 for Musa

//Printing the Winner
cout << "Winner is: " << (winner == 0 ? I : M) << endl;

double pIs = (winner==0) ? 1.0 : 0.0; //Ismail Wins
double pMs = (winner==1) ? 1.0 : 0.0; //Musa Wins
int ismailOriginal = playerRatings[I];
int musaOriginal = playerRatings[M];

double epIs = expectedscore(ismailOriginal, musaOriginal); // Expected score for Ismail
double epMs = expectedscore(musaOriginal, ismailOriginal); // Expected score for Musa

// Use the original ratings here
playerRatings[I] = updatescore(ismailOriginal, musaOriginal, pIs, K);
playerRatings[M] = updatescore(musaOriginal, ismailOriginal, pMs, K);

//Printing Updated ratings
cout << "Ismail's Rating after the match: " << playerRatings[I]<<endl;
cout << "Musa's Rating after the match: " << playerRatings[M]<<endl;
}













