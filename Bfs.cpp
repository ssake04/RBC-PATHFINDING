#include <iostream>
#include <algorithm> // For sorting the packages
#include <cmath>
#include <chrono> // For timing the algorithm
#include <queue> // For BFS

using namespace std;

const int GRID_SIZE = 50;
char START = 'S';
char END = 'E';
char OBSTACLE = 'X'; 
char OPEN = '.';

struct packages 
{
    const char *id;
    int urgency;
    int weight;
    const char *description;
};

bool comparePackages(const packages &a, const packages &b) 
{
    if (a.urgency == b.urgency) 
        return a.weight > b.weight;
    return a.urgency < b.urgency;
}

struct Node
{
    int x, y;
    Node *parent;
    
    Node() : x(0), y(0), parent(nullptr) {}

    Node(int x, int y, Node *parent = nullptr) 
        : x(x), y(y), parent(parent) {}
};

void displayGridWithPath(char grid[50][50], pair<int, int> path[], int pathLength) 
{
    for (int i = 0; i < pathLength; ++i) 
    {
        int x = path[i].first;
        int y = path[i].second;
        if (grid[x][y] != 'S' && grid[x][y] != 'E') 
        {
            grid[x][y] = '*';
        }
    }
    cout << "\nRoutes\n";
    for (int i = 0; i < 50; ++i) 
    {
        for (int j = 0; j < 50; ++j) 
        {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

int findPath(char grid[50][50], int startX, int startY, int endX, int endY, pair<int, int> path[], int &pathLength) 
{
    const int MAX_NODES = 2500;
    bool visited[50][50] = {false};

    queue<Node> openList; // Use queue for BFS

    openList.push(Node(startX, startY));

    while (!openList.empty()) 
    {
        Node current = openList.front();
        openList.pop();

        if (visited[current.x][current.y]) 
            continue; 

        visited[current.x][current.y] = true;

        if (current.x == endX && current.y == endY) 
        {
            Node *node = &current;
            pathLength = 0;

            while (node) 
            {
                path[pathLength++] = {node->x, node->y};
                node = node->parent;
            }
            reverse(path, path + pathLength);
            return 1;
        }

        int directions[4][2] = 
        {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}, // Up Down Left Right directions
        };

        for (int i = 0; i < 4; ++i) 
        {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && !visited[nx][ny] && grid[nx][ny] != OBSTACLE) 
            {
                openList.push(Node(nx, ny, new Node(current))); 
            }
        }
    }
    return 0;
}

void findStartAndEnd(char grid[50][50], int &startX, int &startY, int &endX, int &endY) 
{
    for (int i = 0; i < GRID_SIZE; ++i) 
    {
        for (int j = 0; j < GRID_SIZE; ++j) 
        {
            if (grid[i][j] == START) 
            {
                startX = i;
                startY = j;
            } 
            else if (grid[i][j] == END) 
            {
                endX = i;
                endY = j;
            }
        }
    }
}


int main() 
{
    packages packages[] = {
        {"PKG1", 3, 1, "Chinese Propaganda Books"}, 
        {"PKG2", 4, 14, "An Elephant"}, 
        {"PKG3", 3, 3, "The President"}, 
        {"PKG4", 4, 1, "A Dead Body"}, 
        {"PKG5", 4, 3, "The President"}, 
        {"PKG6", 4, 12, "A Feather"}, 
        {"PKG7", 3, 14, "Drinking Water"}, 
        {"PKG8", 3, 6, "Chinese Propaganda Books"}, 
        {"PKG9", 3, 6, "Chinese Propaganda Books"}, 
        {"PKG10", 4, 3, "Drinking Water"} 
    };


    const int packageCount = sizeof(packages) / sizeof(packages[0]);

    sort(packages, packages + packageCount, comparePackages);

    cout << "Sorted Packages by ascending order : \n";
    for (int i = 0; i < packageCount; ++i) 
    {
        cout << packages[i].id << " - (Urgency: " << packages[i].urgency << ", Weight: " << packages[i].weight << ")\n";
    }


    int startX ;
    int startY ; 
    int endX ; 
    int endY ;
    
// char grid[50][50] = 
//     {
//         {'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X', '.', '.', '.'},
//         {'.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.'},
//         {'.', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', 'X', '.', '.'},
//         {'.', '.', '.', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', 'X', 'X', '.', '.', '.', 'X', 'X', '.', 'X', '.', '.', 'X', '.', 'X'},
//         {'.', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', 'X', 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X', 'E', 'X', 'X', '.', '.', '.', '.', 'X'},
//         {'.', '.', '.', '.', '.', '.', 'S', '.', '.', 'X', '.', 'X', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.'},
//         {'.', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', 'X', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
//         {'.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X'},
//         {'.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.'},
//         {'.', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.'},
//         {'.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.'},
//         {'.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', 'X', '.', '.'},
//         {'.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', 'X'},
//         {'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.'},
//         {'.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', 'X'},
//         {'.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X'},
//         {'.', 'X', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.'},
//         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X'},
//         {'X', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', 'X', '.', 'X'},
//         {'.', '.', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', '.'},
//         {'.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X'},
//         {'.', '.', '.', '.', 'X', 'X', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.'},
//         {'.', '.', 'X', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.'},
//         {'X', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X', '.', '.', '.'},
//         {'X', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X'},
//         {'.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.'},
//         {'.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
//         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', 'X'},
//         {'X', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', 'X', 'X', 'X', '.', '.', '.', '.', 'X'},
//         {'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X'}
//     };

    char grid[50][50] = 
    {
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', 'X', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', 'X', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'E', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.'},
        {'.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', 'X'},
        {'.', 'X', 'X', 'X', 'X', 'X', '.', 'X', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.'},
        {'.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X', '.'},
        {'X', 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', 'X', '.', 'X', 'X', '.', 'X', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.'},
        {'.', 'X', 'X', 'X', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', 'X', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', 'X', 'X', 'X', '.', 'X', '.', 'X'},
        {'.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.'},
        {'.', '.', '.', 'X', 'X', '.', 'X', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', '.'},
        {'.', 'X', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', 'X'},
        {'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.'},
        {'.', '.', '.', '.', '.', 'X', 'X', '.', 'X', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.'},
        {'.', 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'S', '.', 'X', 'X', 'X'},
        {'.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.', 'X', 'X', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.'},
        {'.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X', 'X'},
        {'.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.'},
        {'.', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.'},
        {'.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', 'X', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.'},
        {'.', '.', '.', '.', '.', 'X', 'X', '.', 'X', '.', 'X', 'X', '.', 'X', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', 'X', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.'},
        {'.', 'X', '.', 'X', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.'},
        {'.', 'X', '.', '.', 'X', 'X', '.', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', 'X', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', '.'},
        {'X', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', 'X', 'X'},
        {'.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X', 'X', '.', 'X', '.', '.', '.', 'X', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', 'X', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', 'X', 'X', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', 'X'},
        {'.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X', 'X', '.'},
        {'.', '.', 'X', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.'},
        {'X', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', '.', 'X'},
        {'X', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', 'X', '.', '.', 'X', '.', 'X', '.', 'X', 'X', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.', 'X', 'X'},
        {'.', 'X', '.', '.', '.', 'X', '.', '.', 'X', 'X', 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X', '.', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', 'X', '.'},
        {'X', 'X', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', 'X', 'X', '.', 'X', '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.'} 
    };

    findStartAndEnd(grid, startX, startY, endX, endY);

    pair<int, int> path[2500];
    int pathLength = 0;

    auto start = chrono::high_resolution_clock::now();
    bool pathFound = findPath(grid, startX, startY, endX, endY, path, pathLength);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "\nTime taken to find the path: " << duration << " microseconds\n";

    if (findPath(grid, startX, startY, endX, endY, path, pathLength)) 
    {
        cout << "\nPath from Start to End:\n";
        for (int i = 0; i < pathLength; ++i) 
        {
            cout << "(" << path[i].second << ", " << path[i].first << ") -> ";
        }
        cout << "End\n";
        displayGridWithPath(grid, path, pathLength);
    } 
    else 
    {
        cout << "No path found!\n";
    }

    return 0;
}
