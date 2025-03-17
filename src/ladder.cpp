#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include "ladder.h"

void error(string word1, string word2, string msg){
    cerr << "Error: " << msg << word1 << " " << word2 << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1 - len2) > d) return false;
    int i = 0;
    int j = 0;
    int changes = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++changes > d) return false;
            if (len1 > len2){
                ++i;
            } else if (len1 < len2){
                ++j;
            } else {
                ++i; 
                ++j; 
            }
        } else {
            ++i;
            ++j;
        }
    }
    return changes + (len1 - i) + (len2 - j) <= d;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words must be different");
        return {};
    }
    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (string word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder); 
            }
        }
    }

    error(begin_word, end_word, "No valid word ladder found");
    return {};
}
void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        cout << "No valid word ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}
void verify_word_ladder();