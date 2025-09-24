#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Trie {
public:
    unordered_set<string> words;

    void insert(const string& word) {
        words.insert(word);
    }

    bool search(const string& word) {
        return words.find(word) != words.end();
    }

    vector<string> suggestCorrections(const string& word) {
        vector<string> suggestions;
        for (const string& dictWord : words) {
            if (levenshteinDistance(word, dictWord) == 1) {
                suggestions.push_back(dictWord);
            }
        }
        return suggestions;
    }

    int levenshteinDistance(const string& word1, const string& word2) {
        int m = word1.size();
        int n = word2.size();
        
        if (abs(m - n) > 1) return 2;
        
        int distance = 0;
        for (int i = 0; i < min(m, n); ++i) {
            if (word1[i] != word2[i]) {
                ++distance;
            }
        }
        return distance;
    }
};

class SpellChecker {
public:
    Trie trie;

    SpellChecker(const vector<string>& dictionary) {
        for (const string& word : dictionary) {
            trie.insert(word);
        }
    }

    void checkWord(const string& word) {
        if (trie.search(word)) {
            cout << "'" << word << "' is correct.\n";
        } else {
            cout << "'" << word << "' is incorrect. Suggestions: ";
            vector<string> suggestions = trie.suggestCorrections(word);
            if (suggestions.empty()) {
                cout << "No suggestions found.\n";
            } else {
                for (const string& suggestion : suggestions) {
                    cout << suggestion << " ";
                }
                cout << "\n";
            }
        }
    }
};

int main() {
    vector<string> dictionary = {"apple", "banana", "grape", "orange", "kiwi"};
    SpellChecker spellChecker(dictionary);

    spellChecker.checkWord("apple");
    spellChecker.checkWord("grape");
    spellChecker.checkWord("grapa");
    spellChecker.checkWord("bananna");
    spellChecker.checkWord("oranga");

    return 0;
}
