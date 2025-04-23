#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Debater {
public:
    string name;
    int rating;
    int wins;
    int losses;

    Debater(string n, int r = 1000) : name(n), rating(r), wins(0), losses(0) {}

    double expectedScore(int opponentRating) const {
        return 1.0 / (1.0 + pow(10.0, (opponentRating - rating) / 400.0));
    }

    void updateScore(int opponentRating, double score, int K) {
        double expected = expectedScore(opponentRating);
        rating += static_cast<int>(K * (score - expected));
    }

    void recordResult(bool win) {
        win ? wins++ : losses++;
    }
};

class Leaderboard {
private:
    unordered_map<string, Debater> debaters;
    vector<string> names;
    const int K = 32;
    const string filename = "newLeaderboard.txt";

    string getCurrentTimestamp() {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now_time));
        return string(buffer);
    }

public:
    void addDebater(const string& name, int rating = 1000) {
        debaters[name] = Debater(name, rating);
        names.push_back(name);
    }

    void loadPreviousStats() {
        ifstream inFile(filename);
        string line, lastSectionMarker = "LEADER BOARD:";
        vector<string> lines;

        if (!inFile.is_open()) {
            cout << "Error opening file for reading previous stats.\n";
            return;
        }

        while (getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();

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

            if (debaters.find(name) != debaters.end()) {
                debaters[name].wins = win;
                debaters[name].losses = loss;
            }
        }
    }

    void simulateMatch() {
        int index1 = rand() % names.size();
        int index2;
        do {
            index2 = rand() % names.size();
        } while (index2 == index1);

        Debater& d1 = debaters[names[index1]];
        Debater& d2 = debaters[names[index2]];

        cout << "\nMatch: " << d1.name << " vs " << d2.name << endl;
        cout << "Pick your winner (0 for " << d1.name << ", 1 for " << d2.name << "): ";
        int choice;
        cin >> choice;

        Debater* winner = (choice == 0) ? &d1 : &d2;
        Debater* loser  = (choice == 0) ? &d2 : &d1;

        winner->recordResult(true);
        loser->recordResult(false);

        winner->updateScore(loser->rating, 1.0, K);
        loser->updateScore(winner->rating, 0.0, K);

        cout << "Winner is: " << winner->name << endl;
        cout << "Updated Rating of " << d1.name << ": " << d1.rating << endl;
        cout << "Updated Rating of " << d2.name << ": " << d2.rating << endl;

        saveLeaderboard();
    }

    void saveLeaderboard() {
        ofstream outFile(filename, ios::out);
        if (!outFile.is_open()) {
            cout << "Error opening the file for writing." << endl;
            return;
        }

        string timestamp = getCurrentTimestamp();
        outFile << "LEADER BOARD: [" << timestamp << "]" << endl;
        for (const string& name : names) {
            Debater& d = debaters[name];
            outFile << "Debater: " << name
                    << " Wins: " << d.wins
                    << " Losses: " << d.losses << endl;
        }
        outFile.close();
    }

    void displayLeaderboard() {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "Error opening the file for reading." << endl;
            return;
        }

        cout << "\nCurrent Leaderboard:\n----------------------\n";
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
};

int main() {
    srand(time(0));

    Leaderboard lb;
    lb.addDebater("Soban", 1000);
    lb.addDebater("Ismail", 1000);
    lb.addDebater("Hasnain", 2000);
    lb.addDebater("Musa", 1500);

    lb.loadPreviousStats();
    lb.displayLeaderboard();
    lb.simulateMatch();

    return 0;
}
