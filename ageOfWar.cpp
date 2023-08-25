#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Soldier 
{

    public:

        string name;
        int count;

        Soldier(string platoon) 
        {
            size_t pos = platoon.find("#");
            name = platoon.substr(0, pos);
            count = stoi(platoon.substr(pos + 1));
        }

        string toString() 
        {
            return name + "(" + to_string(count) + ")";
        }

        static bool compareByName(const Soldier& a, const Soldier& b) 
        {
            return a.name < b.name;
        }

};

class BattleSimulation 
{
    private:
        vector<Soldier> ownPlatoons;
        vector<Soldier> opponentPlatoons;
        map<string, vector<string>> advantages;


    public:
        BattleSimulation() 
        {
            advantages = 
            {
                {"Militia", {"Spearmen", "LightCavalry"}},
                {"Spearmen", {"LightCavalry", "HeavyCavalry"}},
                {"LightCavalry", {"FootArcher", "CavalryArcher"}},
                {"HeavyCavalry", {"Militia", "FootArcher", "LightCavalry"}},
                {"CavalryArcher", {"Spearmen", "HeavyCavalry"}},
                {"FootArcher", {"Militia", "CavalryArcher"}}
            };
        }

    vector<string> getAdvantage(string unitClass) 
    {
        return advantages[unitClass];
    }
    void readInput() 
    {
        // Read input and populate ownPlatoons and opponentPlatoons
        string ownInput, opponentInput;
        cout << "Your Platoons: ";
        getline(cin, ownInput);
        cout << "Opponent Platoons: ";
        getline(cin, opponentInput);
        ownPlatoons = readPlatoonsInput(ownInput);
        opponentPlatoons = readPlatoonsInput(opponentInput);                            
        sort(ownPlatoons.begin(), ownPlatoons.end(),Soldier::compareByName);
    }

    vector<Soldier> readPlatoonsInput(const string &input) 
    {
        vector<Soldier> platoons;
        size_t startPos = 0, endPos;

        while ((endPos = input.find(";", startPos)) != string::npos) 
        {
            platoons.push_back(Soldier(input.substr(startPos, endPos - startPos)));
            startPos = endPos + 1;
        }
        platoons.push_back(Soldier(input.substr(startPos)));

        return platoons;
}

    int applyAdvantages(const Soldier &unit,  const Soldier &enemy) 
    {
        int unitCount = unit.count;
        vector<string> unitAdvantageOver = getAdvantage(unit.name);
        string enemyName = enemy.name;
        for (const string &enemyClass : unitAdvantageOver) 
        {
            if (!enemyName.compare(enemyClass)) 
            {
                unitCount *= 2;
            }
        }
        return unitCount;
    }

    pair<int, int> simulateBattle(const Soldier &attacker, const Soldier &defender) 
    {
        int attackerCount = applyAdvantages(attacker, defender);
        int defenderCount = applyAdvantages(defender, attacker);
        return make_pair(attackerCount, defenderCount);
    }

    int getWinsForArrangement(const std::vector<Soldier>& ownPlatoonsArrangement) 
    {
        int wins = 0;
        int length = ownPlatoonsArrangement.size();
        for (size_t i = 0; i < length; ++i) 
        {
            Soldier ownPlatoon = ownPlatoonsArrangement[i];
            Soldier opponentPlatoon = opponentPlatoons[i];
            pair<int, int> result = simulateBattle(ownPlatoon, opponentPlatoon);
            if (result.first > result.second) 
            {
                wins++;
            }
        }
        return wins;
    }

    std::vector<string> getWinningArrangement() 
    {
        int maxWins = 0;
        int majorityWins = (ownPlatoons.size() / 2) + 1;
        vector<string> winningArrangement;

        vector<Soldier> ownPlatoonsArrangement = ownPlatoons;
        do {
                int wins = getWinsForArrangement(ownPlatoonsArrangement);
                if (wins >= majorityWins && wins > maxWins) 
                {
                    maxWins = wins;
                    winningArrangement.clear();
                    for (Soldier &platoon : ownPlatoonsArrangement)
                    {
                        winningArrangement.push_back(platoon.toString());
                    }
                }
            } while (next_permutation(ownPlatoonsArrangement.begin(), ownPlatoonsArrangement.end(),Soldier::compareByName));
        return winningArrangement;
    }

    void runSimulation() 
    {
        readInput();
        vector<string> winningArrangement = getWinningArrangement();

        if (!winningArrangement.empty()) 
        {
            cout << "Winning arrangement:";
            for (const string &platoon : winningArrangement) 
            {
                cout << platoon << ";";
            }
            cout << endl;
        } 
        else 
        {
            cout << "There is no chance of winning" << endl;
        }
    }
};


int main() {
    BattleSimulation battleSimulator;
    battleSimulator.runSimulation();
    return 0;
}