/*
 * ============================================================================
 * GRAPH PROBLEMS - COMPREHENSIVE PROBLEM SET
 * ============================================================================
 * 
 * A comprehensive collection of graph problems covering:
 * - Graph traversal and connectivity
 * - Shortest path problems
 * - Cycle detection and topological sorting
 * - Minimum spanning tree problems
 * - Advanced graph algorithms
 * - Real-world graph applications
 * 
 * Each problem includes:
 * - Problem statement and examples
 * - Multiple solution approaches
 * - Time and space complexity analysis
 * - Edge cases and optimizations
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <string>
#include <set>
#include <map>

using namespace std;

/*
 * ========================================================================
 * PROBLEM 1: NUMBER OF ISLANDS
 * ========================================================================
 * 
 * Given a 2D grid of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and formed by connecting adjacent lands
 * horizontally or vertically.
 * 
 * Example:
 * Input: grid = [
 *   ["1","1","1","1","0"],
 *   ["1","1","0","1","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","0","0","0"]
 * ]
 * Output: 1
 */

class Solution_NumberOfIslands {
public:
    // DFS Solution
    int numIslands_DFS(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int islands = 0;
        int rows = grid.size(), cols = grid[0].size();
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    islands++;
                    dfs(grid, i, j);
                }
            }
        }
        
        return islands;
    }
    
    // BFS Solution
    int numIslands_BFS(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int islands = 0;
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    islands++;
                    
                    // BFS to mark all connected land
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    grid[i][j] = '0';
                    
                    while (!q.empty()) {
                        auto [row, col] = q.front();
                        q.pop();
                        
                        for (auto& dir : directions) {
                            int newRow = row + dir[0];
                            int newCol = col + dir[1];
                            
                            if (newRow >= 0 && newRow < rows && 
                                newCol >= 0 && newCol < cols && 
                                grid[newRow][newCol] == '1') {
                                grid[newRow][newCol] = '0';
                                q.push({newRow, newCol});
                            }
                        }
                    }
                }
            }
        }
        
        return islands;
    }
    
    // Union-Find Solution
    class UnionFind {
    public:
        vector<int> parent, rank;
        int count;
        
        UnionFind(vector<vector<char>>& grid) {
            int rows = grid.size(), cols = grid[0].size();
            count = 0;
            parent.resize(rows * cols);
            rank.resize(rows * cols, 0);
            
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (grid[i][j] == '1') {
                        parent[i * cols + j] = i * cols + j;
                        count++;
                    }
                }
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        void unite(int x, int y) {
            int px = find(x), py = find(y);
            if (px == py) return;
            
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
            count--;
        }
    };
    
    int numIslands_UnionFind(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int rows = grid.size(), cols = grid[0].size();
        UnionFind uf(grid);
        vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    for (auto& dir : directions) {
                        int newRow = i + dir[0];
                        int newCol = j + dir[1];
                        
                        if (newRow >= 0 && newRow < rows && 
                            newCol >= 0 && newCol < cols && 
                            grid[newRow][newCol] == '1') {
                            uf.unite(i * cols + j, newRow * cols + newCol);
                        }
                    }
                }
            }
        }
        
        return uf.count;
    }

private:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || 
            grid[i][j] == '0') {
            return;
        }
        
        grid[i][j] = '0';  // Mark as visited
        
        // Visit all 4 directions
        dfs(grid, i-1, j);
        dfs(grid, i+1, j);
        dfs(grid, i, j-1);
        dfs(grid, i, j+1);
    }
};

/*
 * ========================================================================
 * PROBLEM 2: COURSE SCHEDULE (CYCLE DETECTION)
 * ========================================================================
 * 
 * There are numCourses courses labeled from 0 to numCourses - 1.
 * Given prerequisites array where prerequisites[i] = [ai, bi] indicates
 * that you must take course bi before course ai.
 * Return true if you can finish all courses.
 * 
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true (take course 0, then course 1)
 * 
 * Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 * Output: false (circular dependency)
 */

class Solution_CourseSchedule {
public:
    // DFS Solution (Cycle Detection)
    bool canFinish_DFS(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        
        // Build adjacency list
        for (const auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
        }
        
        vector<int> state(numCourses, 0);  // 0: unvisited, 1: visiting, 2: visited
        
        for (int i = 0; i < numCourses; ++i) {
            if (state[i] == 0 && hasCycle(graph, i, state)) {
                return false;
            }
        }
        
        return true;
    }
    
    // BFS Solution (Topological Sort)
    bool canFinish_BFS(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        // Build graph and calculate indegrees
        for (const auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int processedCourses = 0;
        
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            processedCourses++;
            
            for (int nextCourse : graph[course]) {
                indegree[nextCourse]--;
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        return processedCourses == numCourses;
    }
    
    // Return the course order (Course Schedule II)
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (const auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> order;
        
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            
            for (int nextCourse : graph[course]) {
                indegree[nextCourse]--;
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        return order.size() == numCourses ? order : vector<int>();
    }

private:
    bool hasCycle(const vector<vector<int>>& graph, int node, vector<int>& state) {
        state[node] = 1;  // Mark as visiting
        
        for (int neighbor : graph[node]) {
            if (state[neighbor] == 1) {  // Back edge found
                return true;
            }
            if (state[neighbor] == 0 && hasCycle(graph, neighbor, state)) {
                return true;
            }
        }
        
        state[node] = 2;  // Mark as visited
        return false;
    }
};

/*
 * ========================================================================
 * PROBLEM 3: SHORTEST PATH IN BINARY MATRIX
 * ========================================================================
 * 
 * Given an n x n binary matrix grid, return the length of the shortest 
 * clear path from top-left to bottom-right. If no path exists, return -1.
 * A clear path is from (0, 0) to (n-1, n-1) such that all visited cells
 * are 0 and you can move in 8 directions.
 */

class Solution_ShortestPath {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) {
            return -1;
        }
        
        if (n == 1) return 1;
        
        vector<vector<int>> directions = {
            {-1,-1}, {-1,0}, {-1,1},
            {0,-1},          {0,1},
            {1,-1},  {1,0},  {1,1}
        };
        
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        q.push({0, 0});
        visited[0][0] = true;
        int pathLength = 1;
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; ++i) {
                auto [row, col] = q.front();
                q.pop();
                
                if (row == n-1 && col == n-1) {
                    return pathLength;
                }
                
                for (auto& dir : directions) {
                    int newRow = row + dir[0];
                    int newCol = col + dir[1];
                    
                    if (newRow >= 0 && newRow < n && 
                        newCol >= 0 && newCol < n && 
                        grid[newRow][newCol] == 0 && 
                        !visited[newRow][newCol]) {
                        visited[newRow][newCol] = true;
                        q.push({newRow, newCol});
                    }
                }
            }
            
            pathLength++;
        }
        
        return -1;
    }
    
    // A* Algorithm variant for better performance
    int shortestPathBinaryMatrix_AStar(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) {
            return -1;
        }
        
        if (n == 1) return 1;
        
        auto heuristic = [n](int row, int col) {
            return max(abs(row - (n-1)), abs(col - (n-1)));
        };
        
        vector<vector<int>> directions = {
            {-1,-1}, {-1,0}, {-1,1},
            {0,-1},          {0,1},
            {1,-1},  {1,0},  {1,1}
        };
        
        priority_queue<tuple<int, int, int, int>, 
                      vector<tuple<int, int, int, int>>, 
                      greater<tuple<int, int, int, int>>> pq;
        
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        
        pq.push({1 + heuristic(0, 0), 1, 0, 0});
        dist[0][0] = 1;
        
        while (!pq.empty()) {
            auto [f, g, row, col] = pq.top();
            pq.pop();
            
            if (row == n-1 && col == n-1) {
                return g;
            }
            
            if (g > dist[row][col]) continue;
            
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < n && 
                    newCol >= 0 && newCol < n && 
                    grid[newRow][newCol] == 0) {
                    
                    int newG = g + 1;
                    if (newG < dist[newRow][newCol]) {
                        dist[newRow][newCol] = newG;
                        int newF = newG + heuristic(newRow, newCol);
                        pq.push({newF, newG, newRow, newCol});
                    }
                }
            }
        }
        
        return -1;
    }
};

/*
 * ========================================================================
 * PROBLEM 4: CLONE GRAPH
 * ========================================================================
 * 
 * Given a reference of a node in a connected undirected graph,
 * return a deep copy (clone) of the graph.
 */

class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution_CloneGraph {
public:
    // DFS Solution
    Node* cloneGraph_DFS(Node* node) {
        if (!node) return nullptr;
        
        unordered_map<Node*, Node*> cloned;
        return dfsClone(node, cloned);
    }
    
    // BFS Solution
    Node* cloneGraph_BFS(Node* node) {
        if (!node) return nullptr;
        
        unordered_map<Node*, Node*> cloned;
        queue<Node*> q;
        
        cloned[node] = new Node(node->val);
        q.push(node);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            for (Node* neighbor : current->neighbors) {
                if (cloned.find(neighbor) == cloned.end()) {
                    cloned[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                cloned[current]->neighbors.push_back(cloned[neighbor]);
            }
        }
        
        return cloned[node];
    }

private:
    Node* dfsClone(Node* node, unordered_map<Node*, Node*>& cloned) {
        if (cloned.find(node) != cloned.end()) {
            return cloned[node];
        }
        
        cloned[node] = new Node(node->val);
        
        for (Node* neighbor : node->neighbors) {
            cloned[node]->neighbors.push_back(dfsClone(neighbor, cloned));
        }
        
        return cloned[node];
    }
};

/*
 * ========================================================================
 * PROBLEM 5: NETWORK DELAY TIME (DIJKSTRA'S APPLICATION)
 * ========================================================================
 * 
 * You are given a network of n nodes, labeled from 1 to n.
 * Given times array where times[i] = [ui, vi, wi] represents
 * a directed edge from ui to vi with travel time wi.
 * Find the minimum time for all nodes to receive signal sent from node k.
 * Return -1 if impossible.
 */

class Solution_NetworkDelay {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& time : times) {
            graph[time[0]].emplace_back(time[1], time[2]);
        }
        
        // Dijkstra's algorithm
        vector<int> dist(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[k] = 0;
        pq.push({0, k});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto [v, w] : graph[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        int maxTime = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) {
                return -1;  // Some node unreachable
            }
            maxTime = max(maxTime, dist[i]);
        }
        
        return maxTime;
    }
    
    // Bellman-Ford variant
    int networkDelayTime_BellmanFord(vector<vector<int>>& times, int n, int k) {
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        
        // Relax edges n-1 times
        for (int i = 0; i < n - 1; ++i) {
            bool updated = false;
            for (const auto& time : times) {
                int u = time[0], v = time[1], w = time[2];
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
            if (!updated) break;
        }
        
        int maxTime = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) {
                return -1;
            }
            maxTime = max(maxTime, dist[i]);
        }
        
        return maxTime;
    }
};

/*
 * ========================================================================
 * PROBLEM 6: WORD LADDER
 * ========================================================================
 * 
 * Given two words, beginWord and endWord, and a dictionary wordList,
 * return the length of shortest transformation sequence from beginWord
 * to endWord. Each transformed word must exist in wordList.
 * Only one letter can be changed at a time.
 */

class Solution_WordLadder {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        queue<string> q;
        q.push(beginWord);
        int level = 1;
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; ++i) {
                string current = q.front();
                q.pop();
                
                if (current == endWord) {
                    return level;
                }
                
                // Try changing each character
                for (int j = 0; j < current.length(); ++j) {
                    char original = current[j];
                    
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == original) continue;
                        
                        current[j] = c;
                        
                        if (wordSet.find(current) != wordSet.end()) {
                            q.push(current);
                            wordSet.erase(current);  // Mark as visited
                        }
                    }
                    
                    current[j] = original;  // Restore
                }
            }
            
            level++;
        }
        
        return 0;
    }
    
    // Bidirectional BFS for optimization
    int ladderLength_Bidirectional(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        unordered_set<string> beginSet{beginWord};
        unordered_set<string> endSet{endWord};
        int level = 1;
        
        while (!beginSet.empty() && !endSet.empty()) {
            // Always expand the smaller set
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            
            unordered_set<string> nextSet;
            
            for (const string& word : beginSet) {
                string current = word;
                
                for (int i = 0; i < current.length(); ++i) {
                    char original = current[i];
                    
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == original) continue;
                        
                        current[i] = c;
                        
                        if (endSet.find(current) != endSet.end()) {
                            return level + 1;
                        }
                        
                        if (wordSet.find(current) != wordSet.end()) {
                            nextSet.insert(current);
                            wordSet.erase(current);
                        }
                    }
                    
                    current[i] = original;
                }
            }
            
            beginSet = nextSet;
            level++;
        }
        
        return 0;
    }
    
    // Return all shortest transformation sequences
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> result;
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if (wordSet.find(endWord) == wordSet.end()) {
            return result;
        }
        
        unordered_map<string, vector<string>> neighbors;
        unordered_map<string, int> distance;
        
        // BFS to build graph and find distances
        queue<string> q;
        q.push(beginWord);
        distance[beginWord] = 0;
        
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            
            for (int i = 0; i < current.length(); ++i) {
                string next = current;
                
                for (char c = 'a'; c <= 'z'; ++c) {
                    next[i] = c;
                    
                    if (wordSet.find(next) != wordSet.end()) {
                        if (distance.find(next) == distance.end()) {
                            distance[next] = distance[current] + 1;
                            q.push(next);
                        }
                        
                        if (distance[next] == distance[current] + 1) {
                            neighbors[current].push_back(next);
                        }
                    }
                }
            }
        }
        
        // DFS to build all paths
        vector<string> path{beginWord};
        dfsPath(beginWord, endWord, neighbors, distance, path, result);
        
        return result;
    }

private:
    void dfsPath(const string& current, const string& endWord,
                 const unordered_map<string, vector<string>>& neighbors,
                 const unordered_map<string, int>& distance,
                 vector<string>& path, vector<vector<string>>& result) {
        
        if (current == endWord) {
            result.push_back(path);
            return;
        }
        
        auto it = neighbors.find(current);
        if (it != neighbors.end()) {
            for (const string& neighbor : it->second) {
                path.push_back(neighbor);
                dfsPath(neighbor, endWord, neighbors, distance, path, result);
                path.pop_back();
            }
        }
    }
};

/*
 * ========================================================================
 * PROBLEM 7: ALIEN DICTIONARY (TOPOLOGICAL SORT)
 * ========================================================================
 * 
 * Given a list of words from an alien language sorted lexicographically,
 * derive the order of letters in the alien alphabet.
 * Return empty string if no valid order exists.
 */

class Solution_AlienDictionary {
public:
    string alienOrder(vector<string>& words) {
        // Build graph
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> indegree;
        
        // Initialize all characters
        for (const string& word : words) {
            for (char c : word) {
                if (indegree.find(c) == indegree.end()) {
                    indegree[c] = 0;
                }
            }
        }
        
        // Build edges
        for (int i = 0; i < words.size() - 1; ++i) {
            string word1 = words[i], word2 = words[i + 1];
            
            // Check for invalid case: word1 is prefix of word2 but longer
            if (word1.length() > word2.length() && 
                word1.substr(0, word2.length()) == word2) {
                return "";
            }
            
            for (int j = 0; j < min(word1.length(), word2.length()); ++j) {
                if (word1[j] != word2[j]) {
                    if (graph[word1[j]].find(word2[j]) == graph[word1[j]].end()) {
                        graph[word1[j]].insert(word2[j]);
                        indegree[word2[j]]++;
                    }
                    break;
                }
            }
        }
        
        // Topological sort
        queue<char> q;
        for (auto& [c, degree] : indegree) {
            if (degree == 0) {
                q.push(c);
            }
        }
        
        string result;
        
        while (!q.empty()) {
            char c = q.front();
            q.pop();
            result += c;
            
            for (char neighbor : graph[c]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return result.length() == indegree.size() ? result : "";
    }
};

/*
 * ========================================================================
 * PROBLEM 8: CRITICAL CONNECTIONS (BRIDGES)
 * ========================================================================
 * 
 * Given an undirected connected graph, find all critical connections.
 * A critical connection is an edge whose removal increases the number
 * of connected components.
 */

class Solution_CriticalConnections {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n);
        
        // Build adjacency list
        for (const auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        
        vector<vector<int>> bridges;
        vector<int> disc(n, -1), low(n, -1), parent(n, -1);
        vector<bool> visited(n, false);
        int time = 0;
        
        // Run Tarjan's algorithm from each unvisited node
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                bridgeUtil(i, graph, visited, disc, low, parent, bridges, time);
            }
        }
        
        return bridges;
    }

private:
    void bridgeUtil(int u, const vector<vector<int>>& graph,
                    vector<bool>& visited, vector<int>& disc, vector<int>& low,
                    vector<int>& parent, vector<vector<int>>& bridges, int& time) {
        
        visited[u] = true;
        disc[u] = low[u] = ++time;
        
        for (int v : graph[u]) {
            if (!visited[v]) {
                parent[v] = u;
                bridgeUtil(v, graph, visited, disc, low, parent, bridges, time);
                
                low[u] = min(low[u], low[v]);
                
                // If low[v] > disc[u], then u-v is a bridge
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
};

/*
 * ========================================================================
 * PROBLEM 9: MINIMUM SPANNING TREE VARIATIONS
 * ========================================================================
 */

class Solution_MST {
public:
    // Connect all cities with minimum cost
    int minimumCost(int n, vector<vector<int>>& connections) {
        // Kruskal's algorithm
        sort(connections.begin(), connections.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });
        
        UnionFind uf(n + 1);
        int totalCost = 0;
        int edgesUsed = 0;
        
        for (const auto& conn : connections) {
            if (uf.unite(conn[0], conn[1])) {
                totalCost += conn[2];
                edgesUsed++;
                if (edgesUsed == n - 1) break;
            }
        }
        
        return edgesUsed == n - 1 ? totalCost : -1;
    }
    
    // Find critical and pseudo-critical edges in MST
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // Add original indices
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].push_back(i);
        }
        
        // Sort by weight
        sort(edges.begin(), edges.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });
        
        int mstWeight = findMSTWeight(n, edges, -1, -1);
        
        vector<int> critical, pseudoCritical;
        
        for (int i = 0; i < edges.size(); ++i) {
            // Check if edge is critical
            if (findMSTWeight(n, edges, i, -1) > mstWeight) {
                critical.push_back(edges[i][3]);
            }
            // Check if edge is pseudo-critical
            else if (findMSTWeight(n, edges, -1, i) == mstWeight) {
                pseudoCritical.push_back(edges[i][3]);
            }
        }
        
        return {critical, pseudoCritical};
    }

private:
    class UnionFind {
    public:
        vector<int> parent, rank;
        
        UnionFind(int n) : parent(n), rank(n, 0) {
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        bool unite(int x, int y) {
            int px = find(x), py = find(y);
            if (px == py) return false;
            
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
            return true;
        }
    };
    
    int findMSTWeight(int n, const vector<vector<int>>& edges, int skipEdge, int forceEdge) {
        UnionFind uf(n);
        int weight = 0;
        int edgesUsed = 0;
        
        // Force include edge if specified
        if (forceEdge != -1) {
            if (uf.unite(edges[forceEdge][0], edges[forceEdge][1])) {
                weight += edges[forceEdge][2];
                edgesUsed++;
            }
        }
        
        // Process all other edges
        for (int i = 0; i < edges.size(); ++i) {
            if (i == skipEdge || i == forceEdge) continue;
            
            if (uf.unite(edges[i][0], edges[i][1])) {
                weight += edges[i][2];
                edgesUsed++;
                if (edgesUsed == n - 1) break;
            }
        }
        
        return edgesUsed == n - 1 ? weight : INT_MAX;
    }
};

/*
 * ========================================================================
 * PROBLEM 10: GRAPH BIPARTITION
 * ========================================================================
 * 
 * Given an undirected graph, return true if we can partition its vertices
 * into two independent sets such that every edge connects vertices from
 * different sets.
 */

class Solution_Bipartite {
public:
    // DFS Solution
    bool isBipartite_DFS(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        
        for (int i = 0; i < n; ++i) {
            if (color[i] == -1) {
                if (!dfs(graph, i, 0, color)) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    // BFS Solution
    bool isBipartite_BFS(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        
        for (int i = 0; i < n; ++i) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    for (int neighbor : graph[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
        
        return true;
    }
    
    // Union-Find Solution
    bool isBipartite_UnionFind(vector<vector<int>>& graph) {
        int n = graph.size();
        UnionFind uf(2 * n);
        
        for (int i = 0; i < n; ++i) {
            for (int neighbor : graph[i]) {
                // If i and neighbor are in same set, not bipartite
                if (uf.connected(i, neighbor)) {
                    return false;
                }
                
                // Union i with neighbor's opposite set
                // Union neighbor with i's opposite set
                uf.unite(i, neighbor + n);
                uf.unite(neighbor, i + n);
            }
        }
        
        return true;
    }

private:
    bool dfs(const vector<vector<int>>& graph, int node, int c, vector<int>& color) {
        color[node] = c;
        
        for (int neighbor : graph[node]) {
            if (color[neighbor] == c) {
                return false;
            }
            if (color[neighbor] == -1 && !dfs(graph, neighbor, 1 - c, color)) {
                return false;
            }
        }
        
        return true;
    }
    
    class UnionFind {
    public:
        vector<int> parent;
        
        UnionFind(int n) : parent(n) {
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        void unite(int x, int y) {
            parent[find(x)] = find(y);
        }
        
        bool connected(int x, int y) {
            return find(x) == find(y);
        }
    };
};

/*
 * ========================================================================
 * TESTING AND DEMONSTRATION
 * ========================================================================
 */

void testGraphProblems() {
    cout << "=== TESTING GRAPH PROBLEMS ===" << endl;
    
    // Test Number of Islands
    {
        cout << "\n--- Number of Islands ---" << endl;
        Solution_NumberOfIslands sol;
        vector<vector<char>> grid = {
            {'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','0'}
        };
        
        cout << "DFS: " << sol.numIslands_DFS(grid) << endl;
        
        // Reset grid for BFS test
        grid = {
            {'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','0'}
        };
        cout << "BFS: " << sol.numIslands_BFS(grid) << endl;
    }
    
    // Test Course Schedule
    {
        cout << "\n--- Course Schedule ---" << endl;
        Solution_CourseSchedule sol;
        vector<vector<int>> prerequisites = {{1,0},{0,1}};
        cout << "Can finish (cycle): " << sol.canFinish_DFS(2, prerequisites) << endl;
        
        prerequisites = {{1,0}};
        cout << "Can finish (no cycle): " << sol.canFinish_DFS(2, prerequisites) << endl;
        
        auto order = sol.findOrder(2, prerequisites);
        cout << "Course order: ";
        for (int course : order) cout << course << " ";
        cout << endl;
    }
    
    // Test Network Delay
    {
        cout << "\n--- Network Delay ---" << endl;
        Solution_NetworkDelay sol;
        vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
        cout << "Network delay time: " << sol.networkDelayTime(times, 4, 2) << endl;
    }
    
    // Test Word Ladder
    {
        cout << "\n--- Word Ladder ---" << endl;
        Solution_WordLadder sol;
        vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
        cout << "Ladder length: " << sol.ladderLength("hit", "cog", wordList) << endl;
    }
    
    // Test Bipartite
    {
        cout << "\n--- Graph Bipartition ---" << endl;
        Solution_Bipartite sol;
        vector<vector<int>> graph = {{1,3},{0,2},{1,3},{0,2}};
        cout << "Is bipartite: " << sol.isBipartite_DFS(graph) << endl;
    }
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== GRAPH PROBLEMS COMPREHENSIVE GUIDE ===" << endl;
    
    testGraphProblems();
    
    cout << "\n=== All Graph Problems Tested! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * GRAPH PROBLEMS COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * 1. NUMBER OF ISLANDS:
 *    - DFS/BFS: O(m*n) time, O(m*n) space (worst case for recursion/queue)
 *    - Union-Find: O(m*n*α(m*n)) time, O(m*n) space
 * 
 * 2. COURSE SCHEDULE:
 *    - DFS: O(V + E) time, O(V) space
 *    - BFS (Kahn's): O(V + E) time, O(V) space
 * 
 * 3. SHORTEST PATH IN BINARY MATRIX:
 *    - BFS: O(n²) time, O(n²) space
 *    - A*: Better average case, same worst case
 * 
 * 4. CLONE GRAPH:
 *    - DFS/BFS: O(V + E) time, O(V) space
 * 
 * 5. NETWORK DELAY TIME:
 *    - Dijkstra: O((V + E) log V) time
 *    - Bellman-Ford: O(VE) time
 * 
 * 6. WORD LADDER:
 *    - BFS: O(M²*N) time where M = word length, N = word count
 *    - Bidirectional BFS: Better average case
 * 
 * 7. ALIEN DICTIONARY:
 *    - Topological Sort: O(C) time where C = total characters
 * 
 * 8. CRITICAL CONNECTIONS:
 *    - Tarjan's Algorithm: O(V + E) time, O(V) space
 * 
 * 9. MST PROBLEMS:
 *    - Kruskal: O(E log E) time
 *    - Prim: O((V + E) log V) time
 * 
 * 10. GRAPH BIPARTITION:
 *     - DFS/BFS: O(V + E) time, O(V) space
 *     - Union-Find: O(V + E*α(V)) time
 * 
 * PROBLEM SOLVING PATTERNS:
 * - Grid problems: DFS/BFS traversal
 * - Cycle detection: DFS with coloring or topological sort
 * - Shortest path: BFS (unweighted) or Dijkstra (weighted)
 * - Connectivity: Union-Find or DFS/BFS
 * - Ordering: Topological sort
 * - Optimization: MST algorithms
 * 
 * ============================================================================
 */
