    #include "model.h"
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <vector>
    #include <unordered_map>
    #include <unordered_set>
    #include <algorithm>

    using namespace std;

    // Global variables
    unordered_map<string, vector<string>> emotionMap;
    unordered_set<string> neutralWords;

    // Emotion Opposites Mapping (Basic Examples)
    unordered_map<string, string> oppositeEmotion = {
        {"joy", "sadness"}, {"trust", "disgust"}, {"fear", "confidence"},
        {"surprise", "calm"}, {"sadness", "joy"}, {"anger", "calm"},
        {"disgust", "trust"}, {"confidence", "fear"}
    };

    // Load emotions from CSV file
    void loadEmotions(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open the dataset file!" << endl;
            return;
        }

        string line, word, emotion;
        getline(file, line); // Read header (skip)

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, word, ',');   // First column = word
            getline(ss, emotion, ','); // Second column = emotion

            emotionMap[word].push_back(emotion); // Store multiple emotions per word
        }

        file.close();
    }

    // Get opposite emotions (for negation handling)
    vector<string> getOppositeEmotion(const vector<string>& emotions) {
        vector<string> negatedEmotions;
        for (const string& emotion : emotions) {
            if (oppositeEmotion.find(emotion) != oppositeEmotion.end()) {
                negatedEmotions.push_back(oppositeEmotion[emotion]); // Flip emotion
            }
            else {
                negatedEmotions.push_back("neutral"); // Default if no opposite is defined
            }
        }
        return negatedEmotions;
    }

    // Predict Emotion (by checking words)
    string predictEmotion(const vector<string>& words) {
        unordered_map<string, int> emotionCount;
        bool negationFlag = false;
        bool foundInDataset = false;  // Flag to check if any word matched

        for (size_t i = 0; i < words.size(); i++) {
            string word = words[i];

            // Check for negation words
            if (word == "not" || word == "no" || word == "never" || word == "don't" || word == "doesn't") {
                negationFlag = true;
                continue;
            }

            if (emotionMap.find(word) != emotionMap.end()) {
                foundInDataset = true;  // Word is in dataset
                vector<string> emotions = emotionMap[word];

                for (string emotion : emotions) {
                    if (negationFlag) {
                        if (emotion == "joy") emotion = "sadness";
                        else if (emotion == "positive") emotion = "negative";
                        else if (emotion == "trust") emotion = "fear";
                        else if (emotion == "anticipation") emotion = "not_anticipation";
                    }

                    emotionCount[emotion]++;
                }

                // Reset negation **only if a valid emotion word is processed**
                negationFlag = false;
            }
        }

        if (!foundInDataset) {
            cout << "No emotion detected. The word(s) might not be in my memory (dataset)." << endl;
            return "neutral";
        }

        // Find dominant emotion
        auto dominantEmotion = max_element(emotionCount.begin(), emotionCount.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });

        // Collect all detected emotions
        string detectedEmotions = "";
        for (const auto& entry : emotionCount) {
            if (!detectedEmotions.empty()) {
                detectedEmotions += ", ";
            }
            detectedEmotions += entry.first;
        }

        // Print only once
        cout << "Detected Emotions: " << detectedEmotions << endl;
        cout << "Dominant Emotion: " << dominantEmotion->first << " (Most frequent)" << endl;

        return dominantEmotion->first;
    }








