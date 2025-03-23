#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>

using namespace std;

unordered_map<int, int> origVertexMap;

string dataFile = "Wikipedia Vote Network.txt";

int maxCliqueSize = 0;
int totalCliqueCount = 0;
int numVertices;  

vector<int> vecA, vecB, currentClique; 
vector<unordered_set<int>> neighborList;  
unordered_map<int, int> cliqueSizeDist;

// Add these global variables for safety
const int MAX_RECURSION_DEPTH = 1000000; // Adjust based on your system
int recursionDepth = 0;
bool overflowDetected = false;

void exploreClique(int currIndex) {
    // Add recursion depth check
    recursionDepth++;
    if (recursionDepth > MAX_RECURSION_DEPTH) {
        if (!overflowDetected) {
            cout << "Warning: Maximum recursion depth reached. Results may be incomplete." << endl;
            overflowDetected = true;
        }
        recursionDepth--;
        return;
    }
    
    if (currIndex == numVertices) {  
        totalCliqueCount++;
        if (totalCliqueCount % 1000 == 0) { // Reduce output frequency
            cout << "Found " << totalCliqueCount << " cliques so far" << endl;
        }
        int cliqueSize = count(currentClique.begin(), currentClique.end(), 1);
        maxCliqueSize = max(maxCliqueSize, cliqueSize);
        if(cliqueSizeDist.find(cliqueSize) == cliqueSizeDist.end()){
            cliqueSizeDist[cliqueSize] = 1;
        }
        else{
            cliqueSizeDist[cliqueSize]++;
        }
        recursionDepth--; // Decrement before returning
        return;
    }
    
    vector<int> nonAdjInClique, adjInClique;
    for (int j = 0; j < numVertices; j++) {
        if (currentClique[j] == 1 && neighborList[currIndex].find(j) == neighborList[currIndex].end()) {
            nonAdjInClique.push_back(j);
        }
    }
    for (int j : neighborList[currIndex]) {
        if (currentClique[j] == 1) {
            adjInClique.push_back(j);
        }
    }
    
    if (!nonAdjInClique.empty()) {
        exploreClique(currIndex + 1);
    }
    
    
    for (int x : adjInClique) {
        for (int y : neighborList[x]) {
            if (currentClique[y] == 0 && y != currIndex) {
                vecB[y]++;
            }
        }
    }


    for (int x : nonAdjInClique) {
        for (int y : neighborList[x]) {
            if (currentClique[y] == 0) {
                vecA[y]++;
            }
        }
    }
    

    int validFlag = 1;
    

    for (int y : neighborList[currIndex]) {
        if (currentClique[y] == 0 && y < currIndex && vecB[y] == adjInClique.size()) {
            validFlag = 0;
            break;
        }
    }
    

    long long nonAdjCount = nonAdjInClique.size();
    sort(nonAdjInClique.begin(), nonAdjInClique.end());
    

    for (int k = 0; k < nonAdjCount; k++) {
        for (int y : neighborList[nonAdjInClique[k]]) {
            if (currentClique[y] == 0 && y < currIndex && vecB[y] == adjInClique.size()) {
                if (y >= nonAdjInClique[k]) {
                    vecA[y]--;
                } else {
                    if (k == 0 || y >= nonAdjInClique[k - 1]) {
                        if (vecA[y] + k == nonAdjCount) {
                            if (k > 0 && y >= nonAdjInClique[k - 1]) {
                                validFlag = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    

    if (!adjInClique.empty() && nonAdjCount != 0) {
        for (int y = 0; y < numVertices; y++) {
            if (currentClique[y] == 0 && y < currIndex && vecB[y] == adjInClique.size() && vecA[y] == 0) {
                if (nonAdjInClique[nonAdjCount - 1] < y) {
                    validFlag = 0;
                    break;
                }
            }
        }
    } else if (nonAdjCount != 0 && nonAdjInClique[nonAdjCount - 1] < currIndex - 1) {
        validFlag = 0;
    }
    

    for (int x : adjInClique) {
        for (int y : neighborList[x]) {
            if (currentClique[y] == 0 && y != currIndex) {
                vecB[y] = 0;
            }
        }
    }

    for (int x : nonAdjInClique) {
        for (int y : neighborList[x]) {
            if (currentClique[y] == 0) {
                vecA[y] = 0;
            }
        }
    }
    

    if (validFlag) {
        for (int x : adjInClique) {
            currentClique[x] = 2;
        }
        currentClique[currIndex] = 2;
        for (int j = 0; j < numVertices; j++) {
            if (currentClique[j] == 1) currentClique[j] = 0;
            if (currentClique[j] == 2) currentClique[j] = 1;
        }
        exploreClique(currIndex + 1);
        currentClique[currIndex] = 0;
        for (int x : nonAdjInClique) {
            currentClique[x] = 1;
        }
    }
    // Make sure to decrement recursion depth before returning
    recursionDepth--;
}

int main() {
    clock_t startTime = clock();
    
    ifstream inFile(dataFile);
    if (!inFile) {
        cout << "Error: Could not open file " << dataFile << endl;
        return 1;
    }
    
    inFile >> numVertices;
    int numEdges;
    inFile >> numEdges;
    
    cout << "Graph has " << numVertices << " vertices and " << numEdges << " edges" << endl;
    
    // Check if graph is too large
    if (numVertices > 100000) {
        cout << "Warning: Very large graph detected. This implementation may not handle it efficiently." << endl;
    }
    

    unordered_map<int, unordered_set<int>> tempNeighbors;
    for (int i = 0; i < numEdges; i++) {
        int a, b;
        inFile >> a >> b;
        tempNeighbors[a].insert(b);
        tempNeighbors[b].insert(a);
    }
    inFile.close();
    
    // Sort vertices by degree
    vector<pair<int, unordered_set<int>>> vertexVec(tempNeighbors.begin(), tempNeighbors.end());
    sort(vertexVec.begin(), vertexVec.end(), [](const auto& p1, const auto& p2) {
        return p1.second.size() < p2.second.size();
    });
    
    tempNeighbors.clear();
    numVertices = vertexVec.size();  
    
    unordered_map<int, int> newIndex;
    long long counter = 0;
    for (int i = 0; i < vertexVec.size(); i++) {
        newIndex[vertexVec[i].first] = counter++;
    }
    
    for (auto pair : newIndex) {
        origVertexMap[pair.second] = pair.first;
    }
    
    // Create the adjacency list using the new vertex numbering
    neighborList.assign(numVertices, unordered_set<int>());
    for (int i = 0; i < vertexVec.size(); i++) {
        for (int neighbor : vertexVec[i].second) {
            neighborList[newIndex[vertexVec[i].first]].insert(newIndex[neighbor]);
        }
    }
    
    vertexVec.clear();
    
    // Initialize helper vectors with safe size check
    try {
        vecA.assign(numVertices, 0);
        vecB.assign(numVertices, 0);
        currentClique.assign(numVertices, 0);
        currentClique[0] = 1;
    } catch (const std::bad_alloc& e) {
        cout << "Memory allocation failed. Graph may be too large." << endl;
        return 1;
    }
    
    printf("Initialization complete, starting clique exploration\n");
    recursionDepth = 0; // Reset recursion depth counter
    exploreClique(1);
    
    if (overflowDetected) {
        cout << "Note: Recursion limit was reached. Results may be incomplete." << endl;
    }
    
    clock_t endTime = clock();
    double elapsedTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    
    // Print summary table
    cout << "+--------------------------+---------------------------+" << endl;
    cout << "|         Metric           |          Value            |" << endl;
    cout << "+--------------------------+---------------------------+" << endl;
    cout << "| Maximum clique size      | " << setw(25) << maxCliqueSize << " |" << endl;
    cout << "| Total maximal cliques    | " << setw(25) << totalCliqueCount << " |" << endl;
    cout << "| Execution Time (seconds) | " << setw(25) << elapsedTime << " |" << endl;
    cout << "+--------------------------+---------------------------+" << endl << endl;

    // Print clique size distribution table
    cout << "+---------------+---------+" << endl;
    cout << "| Clique Size   | Count   |" << endl;
    cout << "+---------------+---------+" << endl;
    for (auto entry : cliqueSizeDist) {
        cout << "| " << setw(13) << entry.first << " | " << setw(7) << entry.second << " |" << endl;
    }
    cout << "+---------------+---------+" << endl;

    return 0;
}