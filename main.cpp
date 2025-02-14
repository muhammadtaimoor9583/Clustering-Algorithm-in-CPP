// #include<bits/stdc++.h>
// #include "graph.h"

// void Graph::addNode(const string& nodeId) {
//     nodes.emplace(nodeId, Node(nodeId));
// }

// void Graph::addEdge(const string& sourceId, string targetId,double weight) {
//     nodes.at(sourceId).neighbors.emplace_back(targetId,weight);
// }

// void Graph::initializeSampleGraph(string vertice){
//     addNode(vertice);
// }

// // Function to display the graph (for testing purposes)
// void Graph::displayGraph() {
//     for (auto& node : nodes) {
//         cout << "Node " << node.first << " -> ";
//         for (auto& neighbor : node.second.neighbors) {
//             cout << neighbor.first << " " << neighbor.second << " | ";
//         }
//         cout << endl;
//     }
// }

// int main() {
//     Graph graph;
//     ifstream inputFile("dataSet.txt"); // Replace "your_file.txt" with your file name
//     if (!inputFile.is_open()) {
//         cerr << "Error opening file!" << endl;
//         return 1;
//     }

//     string line;
//     while (getline(inputFile, line)) {
//         istringstream iss(line);
//         string col1, col2;
//         double col3;

//         if (iss >> col1) {
//             graph.initializeSampleGraph(col1);
//             if (iss >> col2 >> col3) {
//                 // Process the read data (for example, print them)
//                 graph.addEdge(col1,col2,col3);
//             } else {
//                 cerr << "Error reading line!" << endl;
//             }
//         } else {
//             cerr << "Error reading line!" << endl;
//         }
//     }

//     graph.displayGraph();

//     return 0;
// }
