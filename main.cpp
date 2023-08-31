#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

void addEdge(unordered_map<char, vector<char>>& graph, char from, char to) {
    graph[from].push_back(to);
}

bool topologicalSort(unordered_map<char, vector<char>>& graph, char node, unordered_map<char, bool>& visited, string& result) {
    visited[node] = true;
    
    for (char neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (!topologicalSort(graph, neighbor, visited, result))
                return false;
        }
        else if (visited[neighbor] && result.find(neighbor) == string::npos)
            return false;
    }
    
    result = node + result;
    return true;
}

string findOrder(vector<string>& dict, int N, int K) {
    unordered_map<char, vector<char>> graph;
    
    for (int i = 0; i < N - 1; ++i) {
        string word1 = dict[i];
        string word2 = dict[i + 1];
        
        for (int j = 0; j < min(word1.length(), word2.length()); ++j) {
            if (word1[j] != word2[j]) {
                addEdge(graph, word1[j], word2[j]);
                break;
            }
        }
    }
    
    string result = "";
    unordered_map<char, bool> visited;
    for (char ch = 'a'; ch < 'a' + K; ++ch) {
        visited[ch] = false;
    }
    
    for (char ch = 'a'; ch < 'a' + K; ++ch) {
        if (!visited[ch]) {
            if (!topologicalSort(graph, ch, visited, result))
                return ""; // Invalid order found
        }
    }
    
    return result;
}

int main() {
    int N = 5, K = 4;
    vector<string> dict = {"baa", "abcd", "abca", "cab", "cad"};
    
    string order = findOrder(dict, N, K);
    if (order.length() == 0)
        cout << "0\n"; // Invalid order found
    else
        cout << "1\n" << order << "\n";
    
    return 0;
}
