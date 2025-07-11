/*
 * ============================================================================
 * GRAPH ALGORITHMS IMPLEMENTATION - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * A complete implementation of graph data structures and algorithms including:
 * - Graph representations (adjacency list, adjacency matrix)
 * - Graph traversal algorithms (DFS, BFS)
 * - Shortest path algorithms (Dijkstra, Bellman-Ford, Floyd-Warshall)
 * - Minimum spanning tree algorithms (Kruskal, Prim)
 * - Topological sorting and cycle detection
 * - Connected components and strongly connected components
 * - Advanced graph algorithms and applications
 * 
 * GRAPH FUNDAMENTALS:
 * - Vertices (nodes) and Edges (connections)
 * - Directed vs Undirected graphs
 * - Weighted vs Unweighted graphs
 * - Dense vs Sparse graphs
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

/*
 * ========================================================================
 * GRAPH UTILITY STRUCTURES
 * ========================================================================
 */

// Edge structure for weighted graphs
struct Edge {
    int from, to, weight;
    
    Edge(int f, int t, int w = 1) : from(f), to(t), weight(w) {}
    
    // For priority queue (min-heap)
    bool operator<(const Edge& other) const {
        return weight > other.weight;  // Reverse for min-heap
    }
    
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

// For Union-Find (Disjoint Set)
class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        // Union by rank
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
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

/*
 * ========================================================================
 * GRAPH CLASS
 * ========================================================================
 */

class Graph {
private:
    int num_vertices;
    bool is_directed;
    bool is_weighted;
    
    // Adjacency list representation
    vector<vector<pair<int, int>>> adj_list;  // {neighbor, weight}
    
    // Adjacency matrix representation (for dense graphs)
    vector<vector<int>> adj_matrix;
    bool use_matrix;

public:
    /*
     * Constructors
     */
    Graph(int vertices, bool directed = false, bool weighted = false, bool use_adj_matrix = false) 
        : num_vertices(vertices), is_directed(directed), is_weighted(weighted), use_matrix(use_adj_matrix) {
        
        // Initialize adjacency list
        adj_list.resize(vertices);
        
        // Initialize adjacency matrix if needed
        if (use_matrix) {
            adj_matrix.assign(vertices, vector<int>(vertices, 
                weighted ? INT_MAX : 0));
            
            // Set diagonal to 0 for weighted graphs
            if (weighted) {
                for (int i = 0; i < vertices; ++i) {
                    adj_matrix[i][i] = 0;
                }
            }
        }
    }
    
    /*
     * Basic Graph Operations
     */
    
    // Add edge to graph
    void add_edge(int from, int to, int weight = 1) {
        if (from < 0 || from >= num_vertices || to < 0 || to >= num_vertices) {
            throw invalid_argument("Invalid vertex index");
        }
        
        // Add to adjacency list
        adj_list[from].emplace_back(to, weight);
        if (!is_directed) {
            adj_list[to].emplace_back(from, weight);
        }
        
        // Add to adjacency matrix
        if (use_matrix) {
            adj_matrix[from][to] = weight;
            if (!is_directed) {
                adj_matrix[to][from] = weight;
            }
        }
    }
    
    // Remove edge from graph
    void remove_edge(int from, int to) {
        // Remove from adjacency list
        adj_list[from].erase(
            remove_if(adj_list[from].begin(), adj_list[from].end(),
                     [to](const pair<int, int>& p) { return p.first == to; }),
            adj_list[from].end());
        
        if (!is_directed) {
            adj_list[to].erase(
                remove_if(adj_list[to].begin(), adj_list[to].end(),
                         [from](const pair<int, int>& p) { return p.first == from; }),
                adj_list[to].end());
        }
        
        // Remove from adjacency matrix
        if (use_matrix) {
            adj_matrix[from][to] = is_weighted ? INT_MAX : 0;
            if (!is_directed) {
                adj_matrix[to][from] = is_weighted ? INT_MAX : 0;
            }
        }
    }
    
    // Check if edge exists
    bool has_edge(int from, int to) const {
        for (const auto& edge : adj_list[from]) {
            if (edge.first == to) return true;
        }
        return false;
    }
    
    // Get edge weight
    int get_edge_weight(int from, int to) const {
        for (const auto& edge : adj_list[from]) {
            if (edge.first == to) return edge.second;
        }
        return is_weighted ? INT_MAX : 0;
    }
    
    // Get neighbors of a vertex
    vector<int> get_neighbors(int vertex) const {
        vector<int> neighbors;
        for (const auto& edge : adj_list[vertex]) {
            neighbors.push_back(edge.first);
        }
        return neighbors;
    }
    
    // Get degree of vertex
    int get_degree(int vertex) const {
        if (is_directed) {
            throw logic_error("Use get_in_degree() and get_out_degree() for directed graphs");
        }
        return static_cast<int>(adj_list[vertex].size());
    }
    
    // Get in-degree (for directed graphs)
    int get_in_degree(int vertex) const {
        if (!is_directed) return get_degree(vertex);
        
        int in_degree = 0;
        for (int i = 0; i < num_vertices; ++i) {
            if (has_edge(i, vertex)) in_degree++;
        }
        return in_degree;
    }
    
    // Get out-degree (for directed graphs)
    int get_out_degree(int vertex) const {
        return static_cast<int>(adj_list[vertex].size());
    }
    
    /*
     * Graph Properties
     */
    
    int get_num_vertices() const { return num_vertices; }
    bool is_directed_graph() const { return is_directed; }
    bool is_weighted_graph() const { return is_weighted; }
    
    // Count total edges
    int get_num_edges() const {
        int edges = 0;
        for (int i = 0; i < num_vertices; ++i) {
            edges += adj_list[i].size();
        }
        return is_directed ? edges : edges / 2;
    }
    
    // Check if graph is complete
    bool is_complete() const {
        int expected_edges = is_directed ? 
            num_vertices * (num_vertices - 1) :
            num_vertices * (num_vertices - 1) / 2;
        return get_num_edges() == expected_edges;
    }
    
    /*
     * Graph Traversal Algorithms
     */
    
    // Depth-First Search
    vector<int> dfs(int start_vertex) const {
        vector<int> result;
        vector<bool> visited(num_vertices, false);
        dfs_recursive(start_vertex, visited, result);
        return result;
    }
    
    // DFS iterative version
    vector<int> dfs_iterative(int start_vertex) const {
        vector<int> result;
        vector<bool> visited(num_vertices, false);
        stack<int> st;
        
        st.push(start_vertex);
        
        while (!st.empty()) {
            int vertex = st.top();
            st.pop();
            
            if (!visited[vertex]) {
                visited[vertex] = true;
                result.push_back(vertex);
                
                // Add neighbors in reverse order for correct traversal
                for (int i = adj_list[vertex].size() - 1; i >= 0; --i) {
                    int neighbor = adj_list[vertex][i].first;
                    if (!visited[neighbor]) {
                        st.push(neighbor);
                    }
                }
            }
        }
        
        return result;
    }
    
    // Breadth-First Search
    vector<int> bfs(int start_vertex) const {
        vector<int> result;
        vector<bool> visited(num_vertices, false);
        queue<int> q;
        
        visited[start_vertex] = true;
        q.push(start_vertex);
        
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            result.push_back(vertex);
            
            for (const auto& edge : adj_list[vertex]) {
                int neighbor = edge.first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        return result;
    }
    
    // BFS with levels (returns vector of levels)
    vector<vector<int>> bfs_levels(int start_vertex) const {
        vector<vector<int>> levels;
        vector<bool> visited(num_vertices, false);
        queue<int> q;
        
        visited[start_vertex] = true;
        q.push(start_vertex);
        
        while (!q.empty()) {
            int level_size = q.size();
            vector<int> current_level;
            
            for (int i = 0; i < level_size; ++i) {
                int vertex = q.front();
                q.pop();
                current_level.push_back(vertex);
                
                for (const auto& edge : adj_list[vertex]) {
                    int neighbor = edge.first;
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            
            levels.push_back(current_level);
        }
        
        return levels;
    }
    
    /*
     * Shortest Path Algorithms
     */
    
    // Dijkstra's Algorithm (single-source shortest path)
    vector<int> dijkstra(int source) const {
        if (!is_weighted) {
            throw logic_error("Dijkstra's algorithm requires weighted graph");
        }
        
        vector<int> dist(num_vertices, INT_MAX);
        vector<bool> visited(num_vertices, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            for (const auto& edge : adj_list[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // Dijkstra with path reconstruction
    pair<vector<int>, vector<int>> dijkstra_with_path(int source) const {
        vector<int> dist(num_vertices, INT_MAX);
        vector<int> parent(num_vertices, -1);
        vector<bool> visited(num_vertices, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            for (const auto& edge : adj_list[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return {dist, parent};
    }
    
    // Get shortest path between two vertices
    vector<int> get_shortest_path(int source, int target) const {
        auto [dist, parent] = dijkstra_with_path(source);
        
        if (dist[target] == INT_MAX) {
            return {};  // No path exists
        }
        
        vector<int> path;
        int current = target;
        
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
    
    // Bellman-Ford Algorithm (handles negative weights)
    pair<vector<int>, bool> bellman_ford(int source) const {
        vector<int> dist(num_vertices, INT_MAX);
        dist[source] = 0;
        
        // Relax edges num_vertices - 1 times
        for (int i = 0; i < num_vertices - 1; ++i) {
            for (int u = 0; u < num_vertices; ++u) {
                if (dist[u] == INT_MAX) continue;
                
                for (const auto& edge : adj_list[u]) {
                    int v = edge.first;
                    int weight = edge.second;
                    
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
        
        // Check for negative cycles
        bool has_negative_cycle = false;
        for (int u = 0; u < num_vertices; ++u) {
            if (dist[u] == INT_MAX) continue;
            
            for (const auto& edge : adj_list[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] + weight < dist[v]) {
                    has_negative_cycle = true;
                    break;
                }
            }
            if (has_negative_cycle) break;
        }
        
        return {dist, has_negative_cycle};
    }
    
    // Floyd-Warshall Algorithm (all-pairs shortest path)
    vector<vector<int>> floyd_warshall() const {
        vector<vector<int>> dist(num_vertices, vector<int>(num_vertices, INT_MAX));
        
        // Initialize distances
        for (int i = 0; i < num_vertices; ++i) {
            dist[i][i] = 0;
            for (const auto& edge : adj_list[i]) {
                dist[i][edge.first] = edge.second;
            }
        }
        
        // Floyd-Warshall algorithm
        for (int k = 0; k < num_vertices; ++k) {
            for (int i = 0; i < num_vertices; ++i) {
                for (int j = 0; j < num_vertices; ++j) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        
        return dist;
    }
    
    /*
     * Minimum Spanning Tree Algorithms
     */
    
    // Kruskal's Algorithm
    vector<Edge> kruskal_mst() const {
        if (is_directed) {
            throw logic_error("MST algorithms work only on undirected graphs");
        }
        
        vector<Edge> edges;
        vector<Edge> mst;
        
        // Collect all edges
        for (int u = 0; u < num_vertices; ++u) {
            for (const auto& edge : adj_list[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (u < v) {  // Avoid duplicate edges in undirected graph
                    edges.emplace_back(u, v, weight);
                }
            }
        }
        
        // Sort edges by weight
        sort(edges.begin(), edges.end(), 
             [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
        
        UnionFind uf(num_vertices);
        
        for (const Edge& edge : edges) {
            if (uf.unite(edge.from, edge.to)) {
                mst.push_back(edge);
                if (mst.size() == num_vertices - 1) break;
            }
        }
        
        return mst;
    }
    
    // Prim's Algorithm
    vector<Edge> prim_mst(int start_vertex = 0) const {
        if (is_directed) {
            throw logic_error("MST algorithms work only on undirected graphs");
        }
        
        vector<Edge> mst;
        vector<bool> in_mst(num_vertices, false);
        priority_queue<Edge> pq;
        
        // Start with start_vertex
        in_mst[start_vertex] = true;
        
        // Add all edges from start_vertex to priority queue
        for (const auto& edge : adj_list[start_vertex]) {
            pq.emplace(start_vertex, edge.first, edge.second);
        }
        
        while (!pq.empty() && mst.size() < num_vertices - 1) {
            Edge min_edge = pq.top();
            pq.pop();
            
            if (in_mst[min_edge.to]) continue;
            
            // Add edge to MST
            mst.push_back(min_edge);
            in_mst[min_edge.to] = true;
            
            // Add new edges to priority queue
            for (const auto& edge : adj_list[min_edge.to]) {
                if (!in_mst[edge.first]) {
                    pq.emplace(min_edge.to, edge.first, edge.second);
                }
            }
        }
        
        return mst;
    }
    
    /*
     * Cycle Detection
     */
    
    // Detect cycle in undirected graph
    bool has_cycle_undirected() const {
        if (is_directed) {
            throw logic_error("Use has_cycle_directed() for directed graphs");
        }
        
        vector<bool> visited(num_vertices, false);
        
        for (int i = 0; i < num_vertices; ++i) {
            if (!visited[i] && has_cycle_undirected_util(i, -1, visited)) {
                return true;
            }
        }
        
        return false;
    }
    
    // Detect cycle in directed graph
    bool has_cycle_directed() const {
        if (!is_directed) {
            throw logic_error("Use has_cycle_undirected() for undirected graphs");
        }
        
        vector<int> color(num_vertices, 0);  // 0: white, 1: gray, 2: black
        
        for (int i = 0; i < num_vertices; ++i) {
            if (color[i] == 0 && has_cycle_directed_util(i, color)) {
                return true;
            }
        }
        
        return false;
    }
    
    /*
     * Topological Sorting (for DAGs)
     */
    
    // Topological sort using DFS
    vector<int> topological_sort_dfs() const {
        if (!is_directed) {
            throw logic_error("Topological sort is only for directed graphs");
        }
        
        if (has_cycle_directed()) {
            throw logic_error("Graph has cycle, topological sort not possible");
        }
        
        vector<bool> visited(num_vertices, false);
        stack<int> st;
        
        for (int i = 0; i < num_vertices; ++i) {
            if (!visited[i]) {
                topological_sort_dfs_util(i, visited, st);
            }
        }
        
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
        
        return result;
    }
    
    // Topological sort using Kahn's algorithm (BFS)
    vector<int> topological_sort_kahn() const {
        if (!is_directed) {
            throw logic_error("Topological sort is only for directed graphs");
        }
        
        vector<int> in_degree(num_vertices, 0);
        
        // Calculate in-degrees
        for (int u = 0; u < num_vertices; ++u) {
            for (const auto& edge : adj_list[u]) {
                in_degree[edge.first]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < num_vertices; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> result;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);
            
            for (const auto& edge : adj_list[u]) {
                int v = edge.first;
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        if (result.size() != num_vertices) {
            throw logic_error("Graph has cycle, topological sort not possible");
        }
        
        return result;
    }
    
    /*
     * Connected Components
     */
    
    // Find connected components in undirected graph
    vector<vector<int>> find_connected_components() const {
        if (is_directed) {
            throw logic_error("Use find_strongly_connected_components() for directed graphs");
        }
        
        vector<bool> visited(num_vertices, false);
        vector<vector<int>> components;
        
        for (int i = 0; i < num_vertices; ++i) {
            if (!visited[i]) {
                vector<int> component;
                dfs_component(i, visited, component);
                components.push_back(component);
            }
        }
        
        return components;
    }
    
    // Find strongly connected components (Kosaraju's algorithm)
    vector<vector<int>> find_strongly_connected_components() const {
        if (!is_directed) {
            throw logic_error("Use find_connected_components() for undirected graphs");
        }
        
        // Step 1: Fill vertices in stack according to finishing times
        vector<bool> visited(num_vertices, false);
        stack<int> st;
        
        for (int i = 0; i < num_vertices; ++i) {
            if (!visited[i]) {
                fill_order(i, visited, st);
            }
        }
        
        // Step 2: Create transpose graph
        Graph transpose = get_transpose();
        
        // Step 3: Process all vertices in order defined by stack
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            
            if (!visited[v]) {
                vector<int> scc;
                transpose.dfs_component(v, visited, scc);
                sccs.push_back(scc);
            }
        }
        
        return sccs;
    }
    
    /*
     * Utility and Display Functions
     */
    
    // Print graph
    void print_graph() const {
        cout << "Graph (" << (is_directed ? "Directed" : "Undirected") 
             << ", " << (is_weighted ? "Weighted" : "Unweighted") << "):" << endl;
        
        for (int i = 0; i < num_vertices; ++i) {
            cout << "Vertex " << i << ": ";
            for (const auto& edge : adj_list[i]) {
                if (is_weighted) {
                    cout << edge.first << "(" << edge.second << ") ";
                } else {
                    cout << edge.first << " ";
                }
            }
            cout << endl;
        }
    }
    
    // Print adjacency matrix
    void print_matrix() const {
        if (!use_matrix) {
            cout << "Adjacency matrix not initialized" << endl;
            return;
        }
        
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                if (adj_matrix[i][j] == INT_MAX) {
                    cout << "∞ ";
                } else {
                    cout << adj_matrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

private:
    /*
     * Helper Functions
     */
    
    // DFS recursive helper
    void dfs_recursive(int vertex, vector<bool>& visited, vector<int>& result) const {
        visited[vertex] = true;
        result.push_back(vertex);
        
        for (const auto& edge : adj_list[vertex]) {
            if (!visited[edge.first]) {
                dfs_recursive(edge.first, visited, result);
            }
        }
    }
    
    // Cycle detection in undirected graph
    bool has_cycle_undirected_util(int v, int parent, vector<bool>& visited) const {
        visited[v] = true;
        
        for (const auto& edge : adj_list[v]) {
            int neighbor = edge.first;
            if (!visited[neighbor]) {
                if (has_cycle_undirected_util(neighbor, v, visited)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true;
            }
        }
        
        return false;
    }
    
    // Cycle detection in directed graph
    bool has_cycle_directed_util(int v, vector<int>& color) const {
        color[v] = 1;  // Gray
        
        for (const auto& edge : adj_list[v]) {
            int neighbor = edge.first;
            if (color[neighbor] == 1) {  // Back edge found
                return true;
            }
            if (color[neighbor] == 0 && has_cycle_directed_util(neighbor, color)) {
                return true;
            }
        }
        
        color[v] = 2;  // Black
        return false;
    }
    
    // Topological sort DFS utility
    void topological_sort_dfs_util(int v, vector<bool>& visited, stack<int>& st) const {
        visited[v] = true;
        
        for (const auto& edge : adj_list[v]) {
            if (!visited[edge.first]) {
                topological_sort_dfs_util(edge.first, visited, st);
            }
        }
        
        st.push(v);
    }
    
    // Connected component DFS
    void dfs_component(int v, vector<bool>& visited, vector<int>& component) const {
        visited[v] = true;
        component.push_back(v);
        
        for (const auto& edge : adj_list[v]) {
            if (!visited[edge.first]) {
                dfs_component(edge.first, visited, component);
            }
        }
    }
    
    // Fill order for SCC
    void fill_order(int v, vector<bool>& visited, stack<int>& st) const {
        visited[v] = true;
        
        for (const auto& edge : adj_list[v]) {
            if (!visited[edge.first]) {
                fill_order(edge.first, visited, st);
            }
        }
        
        st.push(v);
    }
    
    // Get transpose graph
    Graph get_transpose() const {
        Graph transpose(num_vertices, true, is_weighted);
        
        for (int v = 0; v < num_vertices; ++v) {
            for (const auto& edge : adj_list[v]) {
                transpose.add_edge(edge.first, v, edge.second);
            }
        }
        
        return transpose;
    }
};

/*
 * ========================================================================
 * TESTING AND DEMONSTRATION
 * ========================================================================
 */

void demonstrate_graph_traversal() {
    cout << "=== GRAPH TRAVERSAL DEMONSTRATION ===" << endl;
    
    // Create undirected graph
    Graph g(6, false, false);
    
    // Add edges
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 5);
    g.add_edge(3, 4);
    
    g.print_graph();
    cout << endl;
    
    // DFS traversal
    auto dfs_result = g.dfs(0);
    cout << "DFS from vertex 0: ";
    for (int v : dfs_result) cout << v << " ";
    cout << endl;
    
    // BFS traversal
    auto bfs_result = g.bfs(0);
    cout << "BFS from vertex 0: ";
    for (int v : bfs_result) cout << v << " ";
    cout << endl;
    
    // BFS with levels
    auto bfs_levels = g.bfs_levels(0);
    cout << "BFS levels from vertex 0:" << endl;
    for (int i = 0; i < bfs_levels.size(); ++i) {
        cout << "Level " << i << ": ";
        for (int v : bfs_levels[i]) cout << v << " ";
        cout << endl;
    }
    cout << endl;
}

void demonstrate_shortest_path() {
    cout << "=== SHORTEST PATH DEMONSTRATION ===" << endl;
    
    // Create weighted directed graph
    Graph g(5, true, true);
    
    g.add_edge(0, 1, 10);
    g.add_edge(0, 4, 5);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 4, 2);
    g.add_edge(2, 3, 4);
    g.add_edge(3, 0, 7);
    g.add_edge(3, 2, 6);
    g.add_edge(4, 1, 3);
    g.add_edge(4, 2, 9);
    g.add_edge(4, 3, 2);
    
    g.print_graph();
    cout << endl;
    
    // Dijkstra's algorithm
    auto distances = g.dijkstra(0);
    cout << "Shortest distances from vertex 0 (Dijkstra):" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "To vertex " << i << ": " << distances[i] << endl;
    }
    cout << endl;
    
    // Shortest path
    auto path = g.get_shortest_path(0, 3);
    cout << "Shortest path from 0 to 3: ";
    for (int v : path) cout << v << " ";
    cout << endl << endl;
    
    // Floyd-Warshall algorithm
    auto all_distances = g.floyd_warshall();
    cout << "All-pairs shortest distances (Floyd-Warshall):" << endl;
    for (int i = 0; i < all_distances.size(); ++i) {
        for (int j = 0; j < all_distances[i].size(); ++j) {
            if (all_distances[i][j] == INT_MAX) {
                cout << "∞ ";
            } else {
                cout << all_distances[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void demonstrate_mst() {
    cout << "=== MINIMUM SPANNING TREE DEMONSTRATION ===" << endl;
    
    // Create weighted undirected graph
    Graph g(4, false, true);
    
    g.add_edge(0, 1, 10);
    g.add_edge(0, 2, 6);
    g.add_edge(0, 3, 5);
    g.add_edge(1, 3, 15);
    g.add_edge(2, 3, 4);
    
    g.print_graph();
    cout << endl;
    
    // Kruskal's MST
    auto kruskal_mst = g.kruskal_mst();
    cout << "Minimum Spanning Tree (Kruskal):" << endl;
    int total_weight = 0;
    for (const auto& edge : kruskal_mst) {
        cout << edge.from << " - " << edge.to << " : " << edge.weight << endl;
        total_weight += edge.weight;
    }
    cout << "Total weight: " << total_weight << endl << endl;
    
    // Prim's MST
    auto prim_mst = g.prim_mst();
    cout << "Minimum Spanning Tree (Prim):" << endl;
    total_weight = 0;
    for (const auto& edge : prim_mst) {
        cout << edge.from << " - " << edge.to << " : " << edge.weight << endl;
        total_weight += edge.weight;
    }
    cout << "Total weight: " << total_weight << endl << endl;
}

void demonstrate_topological_sort() {
    cout << "=== TOPOLOGICAL SORTING DEMONSTRATION ===" << endl;
    
    // Create directed acyclic graph (DAG)
    Graph dag(6, true, false);
    
    dag.add_edge(5, 2);
    dag.add_edge(5, 0);
    dag.add_edge(4, 0);
    dag.add_edge(4, 1);
    dag.add_edge(2, 3);
    dag.add_edge(3, 1);
    
    dag.print_graph();
    cout << endl;
    
    // Check if it's a DAG
    cout << "Has cycle: " << (dag.has_cycle_directed() ? "Yes" : "No") << endl;
    
    // Topological sort using DFS
    auto topo_dfs = dag.topological_sort_dfs();
    cout << "Topological sort (DFS): ";
    for (int v : topo_dfs) cout << v << " ";
    cout << endl;
    
    // Topological sort using Kahn's algorithm
    auto topo_kahn = dag.topological_sort_kahn();
    cout << "Topological sort (Kahn): ";
    for (int v : topo_kahn) cout << v << " ";
    cout << endl << endl;
}

void demonstrate_connected_components() {
    cout << "=== CONNECTED COMPONENTS DEMONSTRATION ===" << endl;
    
    // Create undirected graph with multiple components
    Graph g(7, false, false);
    
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(3, 4);
    // Vertices 5 and 6 are isolated
    
    g.print_graph();
    cout << endl;
    
    auto components = g.find_connected_components();
    cout << "Connected components:" << endl;
    for (int i = 0; i < components.size(); ++i) {
        cout << "Component " << i + 1 << ": ";
        for (int v : components[i]) cout << v << " ";
        cout << endl;
    }
    cout << endl;
    
    // Create directed graph for SCC
    cout << "Strongly Connected Components:" << endl;
    Graph directed_g(5, true, false);
    
    directed_g.add_edge(1, 0);
    directed_g.add_edge(0, 2);
    directed_g.add_edge(2, 1);
    directed_g.add_edge(0, 3);
    directed_g.add_edge(3, 4);
    
    directed_g.print_graph();
    cout << endl;
    
    auto sccs = directed_g.find_strongly_connected_components();
    cout << "Strongly connected components:" << endl;
    for (int i = 0; i < sccs.size(); ++i) {
        cout << "SCC " << i + 1 << ": ";
        for (int v : sccs[i]) cout << v << " ";
        cout << endl;
    }
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== GRAPH ALGORITHMS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrate_graph_traversal();
    demonstrate_shortest_path();
    demonstrate_mst();
    demonstrate_topological_sort();
    demonstrate_connected_components();
    
    cout << "=== Graph Algorithms Demo Completed! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * GRAPH ALGORITHMS COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * GRAPH REPRESENTATIONS:
 * Adjacency List:
 * - Space: O(V + E)
 * - Add edge: O(1)
 * - Check edge: O(degree(v)) = O(V) worst case
 * - Get neighbors: O(degree(v))
 * 
 * Adjacency Matrix:
 * - Space: O(V²)
 * - Add edge: O(1)
 * - Check edge: O(1)
 * - Get neighbors: O(V)
 * 
 * TRAVERSAL ALGORITHMS:
 * - DFS: O(V + E) time, O(V) space (recursion stack)
 * - BFS: O(V + E) time, O(V) space (queue)
 * 
 * SHORTEST PATH ALGORITHMS:
 * - Dijkstra: O((V + E) log V) with binary heap
 * - Bellman-Ford: O(VE) time, detects negative cycles
 * - Floyd-Warshall: O(V³) time, O(V²) space
 * 
 * MINIMUM SPANNING TREE:
 * - Kruskal: O(E log E) time (sorting edges)
 * - Prim: O((V + E) log V) with binary heap
 * 
 * TOPOLOGICAL SORTING:
 * - DFS-based: O(V + E) time
 * - Kahn's algorithm: O(V + E) time
 * 
 * CONNECTED COMPONENTS:
 * - Undirected: O(V + E) using DFS/BFS
 * - Strongly connected (Kosaraju): O(V + E)
 * 
 * WHEN TO USE DIFFERENT REPRESENTATIONS:
 * - Adjacency List: Sparse graphs, memory efficient
 * - Adjacency Matrix: Dense graphs, frequent edge queries
 * 
 * GRAPH APPLICATIONS:
 * - Social networks (friendship graphs)
 * - Transportation networks (shortest paths)
 * - Dependency resolution (topological sort)
 * - Network flow problems
 * - Recommendation systems
 * 
 * ============================================================================
 */
