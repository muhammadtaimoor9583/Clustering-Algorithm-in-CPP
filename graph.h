//
// Created by hamza on 23/12/2023.
//

#ifndef SEMESTER_PROJECT_GRAPH_H
#define SEMESTER_PROJECT_GRAPH_H

#include <bits/stdc++.h>

#include <utility>
using namespace std;
// Node class representing individual nodes in the graph
class Node
{
public:
    string id;
    int nodeWeight;
    bool addedToCluster;
    vector<pair<string, long long int>> neighbors;

    explicit Node(string _id, int _nodeWeight = 0, bool _addedToCluster = false) : id(std::move(_id)), nodeWeight(_nodeWeight), addedToCluster(_addedToCluster) {}
};

// Graph class representing the entire graph structure
class Graph
{

public:
    unordered_map<string, Node> nodes;

    // Function to add a node to the graph
    void addNode(const string &nodeId);

    // Function to add an edge between two nodes in the graph
    void addEdge(const string &sourceId, const string &targetId, double weight);

    // Function to initialize a sample graph
    void initializeSampleGraph(const string &);

    // Function for finding degree of a node
    unsigned long long int findDegree(const string &nodeId);

    // Function to find common neighbors between two nodes
    vector<string> findCommonNeighbors(const string &sourceId, const string &targetId);

    // Function to find common neighbors of each node
    void findCommonNeighborOfEach();

    // Function to get max degree of the graph
    pair<string, unsigned long long int> getMaxDegree();

    // Function that will take the density to make the clusters;
    bool AllAreAdded();
    bool isPresent(unordered_map<string, Node> currCluster, Node currNode);
    double calculateDensity(unordered_map<string, Node> currCluster);
    double calculateDensity(unordered_map<string, Node> currCluster, Node nextNode);
    double NumOfEdgesBtNodeAndCluster(unordered_map<string, Node> currCluster, Node nextNode);
    double calculate_cp(unordered_map<string, Node> currCluster, Node nextNode);
    void MakeClusters(double t_density, double t_cp);
    void makeCluster(Node &startingNode, double t_density, double t_cp, unordered_map<string, Node> &currCluster);

    // Function to get max weight of the graph
    pair<string, long long> getMaxWeight();

    // Function to find node weight
    void findNodeWeightOfEach();

    // density
    double findDensity(int numberOfEdges, int numberOfNodes);

    void displayNodeWeights();

    void makeCluster();

    // Function to display the graph
    void displayGraph();
    void displayClusters();
    vector<unordered_map<string, Node>> GetClusters();

private:
    vector<unordered_map<string, Node>> clusters;
};

#endif // SEMESTER_PROJECT_GRAPH_H