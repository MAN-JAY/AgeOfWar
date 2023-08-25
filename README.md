
### AgeOfWar
You are a medieval king attacking your opponent at five locations simultaneously Each location has a platoon - which has a number of soldiers of a specific class You know the platoons your opponent has Your job is to figure out which of your platoons should attack which of your opponent's platoons so that you can win majority of the battles.

Advantage Map for platoons-
```json
{
    "Militia": ["Spearmen", "LightCavalry"],
    "Spearmen": ["LightCavalry", "HeavyCavalry"],
    "LightCavalry": ["FootArcher", "CavalryArcher"],
    "HeavyCavalry": ["Militia", "FootArcher", "LightCavalry"],
    "CavalryArcher": ["Spearmen", "HeavyCavalry"],
    "FootArcher": ["Militia", "CavalryArcher"]
}
```
The input to the problem statement is the list of platoons that you have with their classes and number of units in the first line The second line contains the list of platoons of the opponent (PlatoonClasses#NoOfSoldiers)

The output of the program should be to give a sequence in which you should arrange your platoons so that you win atleast 3 of the 5 battles. There could be multiple winning arrangements, it is enough to print one of the possible arrangements If there is no possibility to get atleast 3 out of 5 wins in any arrangement, it should intimate that with an error message that "There is no chance of winning"

Sample Input:
```txt
Spearmen#10; Militia#30; FootArcher#20; LightCavalry#1000; HeavyCavalry#120 
Militia#10; Spearmen#10; FootArcher#1000; LightCavalry#120; CavalryArcher#100
```

Sample Output:
```txt
Militia#30; FootArcher#20; Spearmen#10; LightCavalry#1000; HeavyCavalry#120\
```

---

## Technical stack 
  We have used c++ to implement this problem
  
## To execute the code follow below steps in terminal:
  1. run g++ ageOfWar.cpp
  2. ./a.out

Note : We need g++ compiler to execute this code.
