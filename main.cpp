#include <iostream>
#include <vector>
#include "preprocess.h"
#include "model.h"

using namespace std;

int main() {
    // Load emotion dataset
    loadEmotions("emotions.csv");

    cout << "----- Emotion Detector -----" << endl;

    while (true) {
        string inputText;
        cout << "\nEnter text for Detection or '0' to Quit: ";
        getline(cin, inputText);

        if (inputText == "0") {
            cout << "Thank you for using Emotion Detector!" << endl;
            break;
        }

        // Handle empty input
        if (inputText.empty()) {
            cout << "Please enter some text!" << endl;
            continue;
        }

        // Preprocessing
        inputText = toLowerCase(inputText);
        inputText = removePunctuation(inputText);
        vector<string> words = tokenize(inputText);
        words = removeStopwords(words);

        // Emotion Prediction
        predictEmotion(words); // No need to print here, function handles it
    }

    return 0;
}
