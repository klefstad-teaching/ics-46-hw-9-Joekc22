#include "ladder.h"
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <cassert>

void error(string word1, string word2, string msg) {
    cout << "Error: " << word1 <<  ","  << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1 - len2) > d) {
        return false;
    }
    int diff_counter = 0; 
    int i = 0;
    int j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff_counter++;
            if (diff_counter > d) 
            return false;
            if (len1 > len2) {
                i++;
            } else if (len1 < len2) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladderqueue;
    ladderqueue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladderqueue.empty()) {
        vector<string> ladder = ladderqueue.front();
        ladderqueue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.count(word) == 0) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladderqueue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream infile(file_name);
    string word;
    while (infile >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    infile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() == 0){
        cout << "No word ladder found.\n";
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i){
        cout << ladder[i] << ' ';
    }
    cout << endl;
}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    // vector<string> result = generate_word_ladder("car", "cheat", word_list);
    // print_word_ladder(result);


    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
