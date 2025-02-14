#include <bits/stdc++.h>
#include "graph.h"

void Graph::addNode(const string &nodeId)
{
    nodes.emplace(nodeId, Node(nodeId));
}

void Graph::addEdge(const string &sourceId, const string &targetId, double weight)
{
    nodes.at(sourceId).neighbors.emplace_back(targetId, weight);
    if (nodes.count(targetId) == 0)
    {
        addNode(targetId);
    }
    nodes.at(targetId).neighbors.emplace_back(sourceId, weight);
}

void Graph::initializeSampleGraph(const string &nodeId)
{
    addNode(nodeId);
}

unsigned long long int Graph::findDegree(const string &nodeId)
{
    return nodes.at(nodeId).neighbors.size();
}

pair<string, unsigned long long int> Graph::getMaxDegree()
{
    unsigned long long int maxDegree = 0;
    string maxDegreeNode;
    for (auto &node : nodes)
    {

        if (findDegree(node.first) > maxDegree && !node.second.addedToCluster)
        {
            maxDegree = findDegree(node.first);
            maxDegreeNode = node.first;
        }
    }
    pair<string, unsigned long long int> maxDegreePair = make_pair(maxDegreeNode, maxDegree);
    return maxDegreePair;
}

vector<string> Graph::findCommonNeighbors(const string &sourceId, const string &targetId)
{
    vector<string> commonNeighbors;
    for (auto &sourceNeighbor : nodes.at(sourceId).neighbors)
    {
        for (auto &targetNeighbor : nodes.at(targetId).neighbors)
        {
            if (sourceNeighbor.first == targetNeighbor.first)
            {
                commonNeighbors.push_back(sourceNeighbor.first);
            }
        }
    }
    return commonNeighbors;
}

void Graph::findCommonNeighborOfEach()
{
    for (auto &node : nodes)
    {
        for (auto &neighbor : node.second.neighbors)
        {
            vector<string> commonNeighbors = findCommonNeighbors(node.first, neighbor.first);
            // make the size of this vector the weight of the edge between the two nodes
            neighbor.second = commonNeighbors.size();

            // for(auto& commonNeighbor: commonNeighbors){
            //     // cout << node.first << " " << neighbor.first << " " << commonNeighbor << endl;
            // }
        }
    }
}

pair<string, long long> Graph::getMaxWeight()
{
    long long maxWeight = 0;
    string maxWeightNode;
    for (auto &node : nodes)
    {
        if (node.second.nodeWeight > maxWeight && !node.second.addedToCluster)
        {
            maxWeight = node.second.nodeWeight;
            maxWeightNode = node.first;
        }
    }
    pair<string, long long> maxWeightPair = make_pair(maxWeightNode, maxWeight);
    return maxWeightPair;
}

void Graph::findNodeWeightOfEach()
{
    int Weight = 0;
    for (auto &node : nodes)
    {
        Weight = 0;
        for (auto &neighbor : node.second.neighbors)
        {
            Weight += neighbor.second;
        }
        // cout<< "\nWeight:  "<<Weight;
        node.second.nodeWeight = Weight;
    }
}
double Graph::NumOfEdgesBtNodeAndCluster(unordered_map<string, Node> currCluster, Node nextNode)
{
    double edge = 0;
    vector<pair<string, long long>> neighbors = nextNode.neighbors;
    for (auto neighbor : neighbors)
    {
        Node currNode = nodes.at(neighbor.first);
        if (isPresent(currCluster, currNode))
        {
            edge++;
        }
    }
    return edge;
}
double Graph::calculate_cp(unordered_map<string, Node> currCluster, Node nextNode)
{
    double Ec = NumOfEdgesBtNodeAndCluster(currCluster, nextNode);
    double Nc = currCluster.size();
    double d = calculateDensity(currCluster);

    return Ec / (Nc * d);
}
bool Graph::isPresent(unordered_map<string, Node> currCluster, Node currNode)
{

    if (currCluster.count(currNode.id) > 0)
    {
        return true;
    }

    return false;
}

double Graph::calculateDensity(unordered_map<string, Node> currCluster)
{

    int N = currCluster.size();
    if (N == 1)
        return 1;
    double numOfEdges = 0;
    for (auto it = currCluster.begin(); it != currCluster.end(); it++)
    {
        vector<pair<string, long long>> neighbors = (*it).second.neighbors;
        for (auto neighbor : neighbors)
        {
            Node currNode = nodes.at(neighbor.first);
            if (isPresent(currCluster, currNode))
            {
                numOfEdges++;
            }
        }
    }
    double density = numOfEdges / ((N) * (N - 1));
    return density;
}
double Graph::calculateDensity(unordered_map<string, Node> currCluster, Node nextNode)
{
    currCluster.emplace(nextNode.id, nextNode);
    int N = currCluster.size();
    if (N == 1)
        return 1;
    double numOfEdges = 0;
    for (auto it = currCluster.begin(); it != currCluster.end(); it++)
    {
        vector<pair<string, long long>> neighbors = (*it).second.neighbors;
        for (auto neighbor : neighbors)
        {
            Node currNode = nodes.at(neighbor.first);
            if (isPresent(currCluster, currNode))
            {
                numOfEdges++;
            }
        }
    }
    double density = numOfEdges / ((N) * (N - 1));
    return density;
}

void Graph::displayNodeWeights()
{
    for (auto &&node : nodes)
    {
        cout << "\nNodeWeight: " << node.second.nodeWeight;
    }
}

// Check that whether all are added or not;
bool Graph::AllAreAdded()
{
    for(const auto& i : nodes)
    {
        if (!i.second.addedToCluster)
        {
            return false;
        }
    }
    return true;
}

void Graph::makeCluster(Node &startingNode, double t_density, double t_cp, unordered_map<std::string, Node> &currCluster) {
    queue<string> q;
    q.push(startingNode.id);
    nodes.at(startingNode.id).addedToCluster = true;
    currCluster.emplace(startingNode.id, startingNode);

    while (!q.empty()) {
        string node = q.front();
        q.pop();
        Node currNode = nodes.at(node);
        for (auto neighbor : currNode.neighbors) {
            if (!nodes.at(neighbor.first).addedToCluster) {
                if (t_density <= calculateDensity(currCluster, nodes.at(neighbor.first)) && t_cp <= calculate_cp(currCluster, nodes.at(neighbor.first))) {
                    q.push(neighbor.first);
                    nodes.at(neighbor.first).addedToCluster = true;
                    currCluster.emplace(neighbor.first, nodes.at(neighbor.first));
                }
            }
        }
    }

}

void Graph::MakeClusters(double t_density, double t_cp) {
    while (!AllAreAdded()) {
        // Find the node with maximum degree
        Node currNode = nodes.at(getMaxDegree().first);

        unordered_map<string, Node> currCluster;
        makeCluster(currNode, t_density, t_cp, currCluster);
        if(currCluster.size() > 3)
        clusters.push_back(currCluster);
    }
}

// Function to display the graph (for testing purposes)
void Graph::displayGraph()
{

    for (auto &node : nodes)
    {
        cout << "Node " << node.first << " -> ";
        for (auto &neighbor : node.second.neighbors)
        {
            cout << neighbor.first << " " << neighbor.second << " | ";
        }
        cout << endl
             << endl
             << endl;
    }
}
void Graph::displayClusters()
{
    for (auto cluster : clusters)
    {
        cout << "Cluster:";
        for (auto elem : cluster)
        {
            cout << elem.first << " ";
        }
        cout << endl;
    }
}
vector<unordered_map<string, Node>> Graph::GetClusters() { return clusters; }


int main()
{
    Graph graph;
    ifstream inputFile("dataSet.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string col1, col2;

        if (iss >> col1)
        {
            graph.initializeSampleGraph(col1);
            if (iss >> col2)
            {
                graph.addEdge(col1, col2, 0);
            }
            else
            {
                cerr << "Error reading line!" << endl;
            }
        }
        else
        {
            cerr << "Error reading line!" << endl;
        }
    }

    graph.findCommonNeighborOfEach();
    graph.findNodeWeightOfEach();
    inputFile.close();
    double t_density,c_p;
    cout<<"\nEnter Thresold Density: ";
    cin>>t_density;
    cout<<"\nEnter CP Density: ";
    cin>>c_p;

    graph.MakeClusters(t_density, c_p);
    // graph.displayClusters();

    ofstream printCluster("clusters.txt");
    vector<unordered_map<string, Node>> clusters = graph.GetClusters();
    for (auto &cluster : clusters)
    {
        printCluster << graph.calculateDensity(cluster) << endl;
        for (const auto &pair : cluster)
        {
            printCluster << pair.first << ",";
        }
        printCluster << endl
                     << endl;
    }
    // cout<<"Density: "<<graph.findDensity(10,8);
    cout << endl
         << "Clusters Formed! See clusters.txt";
    return 0;
}