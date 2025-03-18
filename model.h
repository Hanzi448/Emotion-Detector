#ifndef MODEL_H
#define MODEL_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

// Declare global variables
extern unordered_map<string, vector<string>> emotionMap;
extern unordered_set<string> neutralWords;

// Function declarations
void loadEmotions(const string& filename);
string predictEmotion(const vector<string>& words);
vector<string> getOppositeEmotion(const vector<string>& emotions);

#endif // MODEL_H
