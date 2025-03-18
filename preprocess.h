#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <string>
#include <vector>

using namespace std;

string toLowerCase(const string& text);
string removePunctuation(const string& text);
vector<string> tokenize(const string& text);
vector<string> removeStopwords(const vector<string>& words);

#endif // PREPROCESS_H
