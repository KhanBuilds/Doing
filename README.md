# Doing

A small C++ practice repository focused on Elo-style rating simulations for debaters.  
Each source file explores the same idea with a different level of complexity, from basic
rating updates to modular match simulation and a persistent leaderboard.

## What’s in this repo

- `/home/runner/work/Doing/Doing/Rate.cpp`  
  Basic Elo rating update between two hardcoded players.
- `/home/runner/work/Doing/Doing/debater_rate.cpp`  
  Randomized one-match simulation between two named debaters with rating updates.
- `/home/runner/work/Doing/Doing/Random_rate.cpp`  
  Random matchmaking across multiple debaters.
- `/home/runner/work/Doing/Doing/Modular_Debater_rate.cpp`  
  Refactored version with a reusable `simulatematch` function.
- `/home/runner/work/Doing/Doing/democratic_debater_vote.cpp`  
  Class-based leaderboard system with manual winner selection and file persistence.

## Requirements

- A C++ compiler that supports C++11 or later (e.g., `g++`)

## Build and run

Compile and run any file independently:

```bash
g++ -std=c++11 -O2 -Wall -Wextra -pedantic /home/runner/work/Doing/Doing/Rate.cpp -o rate
./rate
```

Replace `Rate.cpp` and output name as needed for the other programs.

## Notes

- Programs are independent experiments, not one integrated app.
- Randomized simulations use `rand()` seeded with current time.
- `democratic_debater_vote.cpp` writes leaderboard data to `newLeaderboard.txt`.
