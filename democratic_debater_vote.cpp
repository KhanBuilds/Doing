#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>

using namespace std;

int K = 32;

double expectedscore(int playerrating, int opponentrating){
	double base= 1.0 / (1.0 + pow(10.0, (opponentrating - playerrating) / 400.0));
	return base;
}
	
	
int updatescore(int currentrating, int opponentrating, double score, int K){
	double expectedScore = expectedscore(currentrating, opponentrating);
    return currentrating + K * (score - expectedScore);
}

string getCurrentTimestamp() {
    // Get current time
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // Convert to readable format
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now_time));
    
    return string(buffer);
}

// Load wins/losses from the latest leaderboard in the file
//This essentially overwrites specific lines to keep the leaderboard updated
// Used string stream to break lines into tokens and extract the data I needed since I knew the  file structure
void loadPreviousStats(unordered_map<string, int>& wins, unordered_map<string, int>& losses) {
    ifstream inFile("newLeaderboard.txt");
    string line;
    string lastSectionMarker = "LEADER BOARD:";
    vector<string> lines;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();
    } else {
        cout << "Error opening file for reading previous stats.\n";
        return;
    }

    int lastIndex = -1;
    for (int i = lines.size() - 1; i >= 0; i--) {
        if (lines[i].find(lastSectionMarker) != string::npos) {
            lastIndex = i;
            break;
        }
    }

    if (lastIndex == -1) return;

    for (int i = lastIndex + 1; i < lines.size(); i++) {
        if (lines[i].empty()) continue;
        stringstream ss(lines[i]);
        string dummy, name;
        int win, loss;

        ss >> dummy >> name >> dummy >> win >> dummy >> loss;

        if (!name.empty() && name.back() == ':') name.pop_back();

        wins[name] = win;
        losses[name] = loss;
    }
}
//You're lowkey dumb if you dont know what this function does (Jk we've all been there) this functio simulates the match
void simulateMatch(vector<string>& debaters, unordered_map<string, int>& debaterRatings, unordered_map<string, int>& wins, unordered_map<string, int>& losses, int K){
    int choice;
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

	cout << "Match: " << debater1 << " vs " << debater2 << endl;
	
	//the voted winner
	cout << "Pick your winner (0 for first debater 1 for second debater): ";
	cin >> choice;
	cout <<endl;
	//Updating the wins and losses
	string winner = (choice == 0) ? debater1 : debater2;
	string loser  = (choice == 1) ? debater1 : debater2;
	wins[winner]++;
	losses[loser]++;

	
	//Printing the winner 
	cout << "Winner is: " << (choice == 0 ? debaters[index1] : debaters[index2]) <<endl; // 0 so player index 1 wins if 1 then player index 2 wins
		
	double db1 = (choice == 0) ? 1.0 : 0.0; //Assigns score 1.0 to player index1 if choice == 0
	double db2 = (choice == 1) ? 1.0 : 0.0; //Assigns score 1.0 to player index2 if choice == 1
	
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
	cout << "Updated Rating of " << debater1 << ": " << newRating1 << endl;
	cout << "Updated Rating of " << debater2 << ": " << newRating2 << endl;

	
    
    //Added filehandling
    //This opens/creates the file if it doesnt exist
    ofstream outFile("newLeaderboard.txt", ios::out);
    
    //This checks if the file is open 
    if (outFile.is_open()){
    //Adding a timestamp to clarify which leaderboard is the latest 
    string timestamp = getCurrentTimestamp();

    	
    //This then writes a Leaderboard with the updated scores and stuff
	outFile<< "LEADER BOARD: " <<"[" << timestamp << "]"<<endl;
	for (int i = 0; i < debaters.size(); i++){
		string name = debaters[i];
		outFile<< "Debater: "<<name<< " Wins: "<<wins[name]<< " "<<"Losses: "<<losses[name]<<endl;
	
}
   //This closes the file after writing
   outFile.close();
} else{
	cout << "Error opening the file for writing"<<endl;
}
}

//This function reads the file
void readfile(){
    ifstream inFile("newLeaderboard.txt");
    string line;
    if (inFile.is_open()) {
        cout << "\nCurrent Leaderboard:\n----------------------\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error opening the file for reading" << endl;
    }
}

int main(){
	int choice;
	//Seeds the random generator with time
	srand(time(0));
	//Creats an unordered map which stores the int ratings against string values
	unordered_map<string, int> debaterRatings;
	unordered_map<string, int> wins; //stores the wins against the string 
	unordered_map<string, int> losses; //stores losses againt the string
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
	//calling the function
	simulateMatch(debaters, debaterRatings, wins, losses, K);
	

	return 0;	
}
