#include "preprocess.h"
#include <algorithm>
#include <sstream>
#include <unordered_set>

using namespace std;

// Convert text to lowercase
string toLowerCase(const string& text) {
    string result = text;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Remove punctuation
string removePunctuation(const string& text) {
    string result;
    for (char ch : text) {
        if (isalnum(ch) || isspace(ch)) {
            result += ch;
        }
    }
    return result;
}

// Tokenization
vector<string> tokenize(const string& text) {
    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

// Remove stopwords
vector<string> removeStopwords(const vector<string>& words) {
    unordered_set<string> stopwords = { "is", "a", "the", "and", "of", "to", "in", "it", "that", "this", "on" };
    vector<string> filteredWords;
    for (const string& word : words) {
        if (stopwords.find(word) == stopwords.end()) {
            filteredWords.push_back(word);
        }
    }
    return filteredWords;
}
