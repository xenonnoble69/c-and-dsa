/*
 * ============================================================================
 * BINARY TREE IMPLEMENTATION - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * This file provides a complete implementation of binary trees with:
 * - Basic binary tree operations
 * - Binary search tree (BST) functionality  
 * - Tree traversal algorithms (DFS and BFS)
 * - Advanced tree algorithms and problems
 * - Balanced tree concepts and rotations
 * - Tree construction and manipulation
 * 
 * LEARNING OBJECTIVES:
 * - Understand tree terminology and properties
 * - Master recursive and iterative tree algorithms
 * - Implement efficient search, insert, delete operations
 * - Learn tree traversal techniques
 * - Solve complex tree problems
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
 * ========================================================================
 * BINARY TREE NODE DEFINITION
 * ========================================================================
 */

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    
    // Constructors
    TreeNode() : data(T{}), left(nullptr), right(nullptr) {}
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
    TreeNode(const T& value, TreeNode* l, TreeNode* r) : data(value), left(l), right(r) {}
};

/*
 * ========================================================================
 * BASIC BINARY TREE CLASS
 * ========================================================================
 */

template<typename T>
class BinaryTree {
protected:
    TreeNode<T>* root;
    
    // Helper function to delete all nodes
    void clear_recursive(TreeNode<T>* node) {
        if (node) {
            clear_recursive(node->left);
            clear_recursive(node->right);
            delete node;
        }
    }
    
    // Helper function to copy tree
    TreeNode<T>* copy_recursive(TreeNode<T>* node) {
        if (!node) return nullptr;
        
        TreeNode<T>* new_node = new TreeNode<T>(node->data);
        new_node->left = copy_recursive(node->left);
        new_node->right = copy_recursive(node->right);
        return new_node;
    }

public:
    /*
     * Constructors and Destructor
     */
    BinaryTree() : root(nullptr) {}
    
    BinaryTree(const T& root_value) : root(new TreeNode<T>(root_value)) {}
    
    // Copy constructor
    BinaryTree(const BinaryTree& other) : root(copy_recursive(other.root)) {}
    
    // Assignment operator
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear();
            root = copy_recursive(other.root);
        }
        return *this;
    }
    
    // Destructor
    virtual ~BinaryTree() {
        clear();
    }
    
    /*
     * Basic Tree Properties
     */
    
    // Check if tree is empty
    bool is_empty() const {
        return root == nullptr;
    }
    
    // Get root node
    TreeNode<T>* get_root() const {
        return root;
    }
    
    // Set root node
    void set_root(TreeNode<T>* new_root) {
        clear();
        root = new_root;
    }
    
    // Clear all nodes
    void clear() {
        clear_recursive(root);
        root = nullptr;
    }
    
    /*
     * Tree Metrics
     */
    
    // Calculate height of tree
    int height() const {
        return height_recursive(root);
    }
    
    // Calculate size (number of nodes)
    int size() const {
        return size_recursive(root);
    }
    
    // Count leaf nodes
    int leaf_count() const {
        return leaf_count_recursive(root);
    }
    
    // Check if tree is complete
    bool is_complete() const {
        return is_complete_recursive(root, 0, size());
    }
    
    // Check if tree is full (every node has 0 or 2 children)
    bool is_full() const {
        return is_full_recursive(root);
    }
    
    // Check if tree is perfect (complete and full)
    bool is_perfect() const {
        int h = height();
        return is_perfect_recursive(root, h, 0);
    }
    
    /*
     * Tree Traversal Methods
     */
    
    // Depth-First Search Traversals
    vector<T> preorder_traversal() const {
        vector<T> result;
        preorder_recursive(root, result);
        return result;
    }
    
    vector<T> inorder_traversal() const {
        vector<T> result;
        inorder_recursive(root, result);
        return result;
    }
    
    vector<T> postorder_traversal() const {
        vector<T> result;
        postorder_recursive(root, result);
        return result;
    }
    
    // Breadth-First Search Traversal
    vector<T> level_order_traversal() const {
        vector<T> result;
        if (!root) return result;
        
        queue<TreeNode<T>*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode<T>* current = q.front();
            q.pop();
            
            result.push_back(current->data);
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        
        return result;
    }
    
    // Level order traversal with level separation
    vector<vector<T>> level_order_levels() const {
        vector<vector<T>> result;
        if (!root) return result;
        
        queue<TreeNode<T>*> q;
        q.push(root);
        
        while (!q.empty()) {
            int level_size = q.size();
            vector<T> current_level;
            
            for (int i = 0; i < level_size; ++i) {
                TreeNode<T>* current = q.front();
                q.pop();
                
                current_level.push_back(current->data);
                
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            
            result.push_back(current_level);
        }
        
        return result;
    }
    
    /*
     * Iterative Traversal Methods
     */
    
    // Iterative preorder traversal
    vector<T> preorder_iterative() const {
        vector<T> result;
        if (!root) return result;
        
        stack<TreeNode<T>*> st;
        st.push(root);
        
        while (!st.empty()) {
            TreeNode<T>* current = st.top();
            st.pop();
            
            result.push_back(current->data);
            
            // Push right first, then left (stack is LIFO)
            if (current->right) st.push(current->right);
            if (current->left) st.push(current->left);
        }
        
        return result;
    }
    
    // Iterative inorder traversal
    vector<T> inorder_iterative() const {
        vector<T> result;
        if (!root) return result;
        
        stack<TreeNode<T>*> st;
        TreeNode<T>* current = root;
        
        while (current || !st.empty()) {
            // Go to leftmost node
            while (current) {
                st.push(current);
                current = current->left;
            }
            
            // Process current node
            current = st.top();
            st.pop();
            result.push_back(current->data);
            
            // Move to right subtree
            current = current->right;
        }
        
        return result;
    }
    
    // Iterative postorder traversal
    vector<T> postorder_iterative() const {
        vector<T> result;
        if (!root) return result;
        
        stack<TreeNode<T>*> st1, st2;
        st1.push(root);
        
        // Use two stacks to reverse the traversal
        while (!st1.empty()) {
            TreeNode<T>* current = st1.top();
            st1.pop();
            st2.push(current);
            
            if (current->left) st1.push(current->left);
            if (current->right) st1.push(current->right);
        }
        
        while (!st2.empty()) {
            result.push_back(st2.top()->data);
            st2.pop();
        }
        
        return result;
    }
    
    /*
     * Search and Path Operations
     */
    
    // Find node with given value
    TreeNode<T>* find(const T& value) const {
        return find_recursive(root, value);
    }
    
    // Check if value exists in tree
    bool contains(const T& value) const {
        return find(value) != nullptr;
    }
    
    // Find path from root to target value
    vector<T> find_path(const T& target) const {
        vector<T> path;
        find_path_recursive(root, target, path);
        return path;
    }
    
    // Find lowest common ancestor of two values
    TreeNode<T>* lowest_common_ancestor(const T& val1, const T& val2) const {
        return lca_recursive(root, val1, val2);
    }
    
    // Calculate distance between two nodes
    int distance_between_nodes(const T& val1, const T& val2) const {
        TreeNode<T>* lca = lowest_common_ancestor(val1, val2);
        if (!lca) return -1;
        
        int dist1 = distance_from_node(lca, val1);
        int dist2 = distance_from_node(lca, val2);
        
        if (dist1 == -1 || dist2 == -1) return -1;
        return dist1 + dist2;
    }
    
    /*
     * Tree Construction
     */
    
    // Build tree from preorder and inorder traversals
    static TreeNode<T>* build_from_preorder_inorder(
        const vector<T>& preorder, const vector<T>& inorder) {
        unordered_map<T, int> inorder_map;
        for (int i = 0; i < inorder.size(); ++i) {
            inorder_map[inorder[i]] = i;
        }
        
        int preorder_idx = 0;
        return build_tree_helper(preorder, inorder_map, preorder_idx, 
                                0, static_cast<int>(inorder.size()) - 1);
    }
    
    // Build tree from postorder and inorder traversals
    static TreeNode<T>* build_from_postorder_inorder(
        const vector<T>& postorder, const vector<T>& inorder) {
        unordered_map<T, int> inorder_map;
        for (int i = 0; i < inorder.size(); ++i) {
            inorder_map[inorder[i]] = i;
        }
        
        int postorder_idx = static_cast<int>(postorder.size()) - 1;
        return build_tree_postorder_helper(postorder, inorder_map, postorder_idx,
                                         0, static_cast<int>(inorder.size()) - 1);
    }
    
    /*
     * Tree Serialization
     */
    
    // Serialize tree to string (preorder with null markers)
    string serialize() const {
        string result;
        serialize_recursive(root, result);
        return result;
    }
    
    // Deserialize string to tree
    void deserialize(const string& data) {
        clear();
        vector<string> tokens = split_string(data, ',');
        int index = 0;
        root = deserialize_recursive(tokens, index);
    }
    
    /*
     * Tree Transformation
     */
    
    // Mirror the tree (swap left and right subtrees)
    void mirror() {
        mirror_recursive(root);
    }
    
    // Check if two trees are mirror images
    bool is_mirror_of(const BinaryTree& other) const {
        return is_mirror_recursive(root, other.root);
    }
    
    // Check if tree is symmetric (mirror of itself)
    bool is_symmetric() const {
        return is_symmetric_recursive(root, root);
    }
    
    /*
     * Advanced Tree Algorithms
     */
    
    // Get all root-to-leaf paths
    vector<vector<T>> get_all_paths() const {
        vector<vector<T>> paths;
        vector<T> current_path;
        get_paths_recursive(root, current_path, paths);
        return paths;
    }
    
    // Find maximum path sum (any path in tree)
    int max_path_sum() const {
        int max_sum = INT_MIN;
        max_path_sum_recursive(root, max_sum);
        return max_sum;
    }
    
    // Get tree diameter (longest path between any two nodes)
    int diameter() const {
        int max_diameter = 0;
        diameter_recursive(root, max_diameter);
        return max_diameter;
    }
    
    // Convert tree to its sum tree (each node = sum of subtree)
    void convert_to_sum_tree() {
        sum_tree_recursive(root);
    }
    
    // Check if tree is sum tree
    bool is_sum_tree() const {
        return is_sum_tree_recursive(root);
    }
    
    /*
     * Display Functions
     */
    
    // Print tree structure
    void print_tree() const {
        cout << "Tree Structure:" << endl;
        print_tree_recursive(root, "", true);
    }
    
    // Print tree in 2D format
    void print_2d() const {
        cout << "Tree 2D Representation:" << endl;
        print_2d_recursive(root, 0, 10);
    }

protected:
    /*
     * Helper Functions
     */
    
    // Recursive height calculation
    int height_recursive(TreeNode<T>* node) const {
        if (!node) return -1;  // Height of empty tree is -1
        return 1 + max(height_recursive(node->left), height_recursive(node->right));
    }
    
    // Recursive size calculation
    int size_recursive(TreeNode<T>* node) const {
        if (!node) return 0;
        return 1 + size_recursive(node->left) + size_recursive(node->right);
    }
    
    // Recursive leaf count
    int leaf_count_recursive(TreeNode<T>* node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return leaf_count_recursive(node->left) + leaf_count_recursive(node->right);
    }
    
    // Check if tree is complete
    bool is_complete_recursive(TreeNode<T>* node, int index, int total_nodes) const {
        if (!node) return true;
        if (index >= total_nodes) return false;
        
        return is_complete_recursive(node->left, 2 * index + 1, total_nodes) &&
               is_complete_recursive(node->right, 2 * index + 2, total_nodes);
    }
    
    // Check if tree is full
    bool is_full_recursive(TreeNode<T>* node) const {
        if (!node) return true;
        if (!node->left && !node->right) return true;
        if (node->left && node->right) {
            return is_full_recursive(node->left) && is_full_recursive(node->right);
        }
        return false;
    }
    
    // Check if tree is perfect
    bool is_perfect_recursive(TreeNode<T>* node, int depth, int level) const {
        if (!node) return true;
        if (!node->left && !node->right) return depth == level;
        if (!node->left || !node->right) return false;
        
        return is_perfect_recursive(node->left, depth, level + 1) &&
               is_perfect_recursive(node->right, depth, level + 1);
    }
    
    // DFS Traversal helpers
    void preorder_recursive(TreeNode<T>* node, vector<T>& result) const {
        if (node) {
            result.push_back(node->data);
            preorder_recursive(node->left, result);
            preorder_recursive(node->right, result);
        }
    }
    
    void inorder_recursive(TreeNode<T>* node, vector<T>& result) const {
        if (node) {
            inorder_recursive(node->left, result);
            result.push_back(node->data);
            inorder_recursive(node->right, result);
        }
    }
    
    void postorder_recursive(TreeNode<T>* node, vector<T>& result) const {
        if (node) {
            postorder_recursive(node->left, result);
            postorder_recursive(node->right, result);
            result.push_back(node->data);
        }
    }
    
    // Search helpers
    TreeNode<T>* find_recursive(TreeNode<T>* node, const T& value) const {
        if (!node || node->data == value) return node;
        
        TreeNode<T>* left_result = find_recursive(node->left, value);
        if (left_result) return left_result;
        
        return find_recursive(node->right, value);
    }
    
    bool find_path_recursive(TreeNode<T>* node, const T& target, vector<T>& path) const {
        if (!node) return false;
        
        path.push_back(node->data);
        
        if (node->data == target) return true;
        
        if (find_path_recursive(node->left, target, path) ||
            find_path_recursive(node->right, target, path)) {
            return true;
        }
        
        path.pop_back();
        return false;
    }
    
    TreeNode<T>* lca_recursive(TreeNode<T>* node, const T& val1, const T& val2) const {
        if (!node) return nullptr;
        if (node->data == val1 || node->data == val2) return node;
        
        TreeNode<T>* left_lca = lca_recursive(node->left, val1, val2);
        TreeNode<T>* right_lca = lca_recursive(node->right, val1, val2);
        
        if (left_lca && right_lca) return node;
        return left_lca ? left_lca : right_lca;
    }
    
    int distance_from_node(TreeNode<T>* node, const T& target) const {
        if (!node) return -1;
        if (node->data == target) return 0;
        
        int left_dist = distance_from_node(node->left, target);
        int right_dist = distance_from_node(node->right, target);
        
        if (left_dist != -1) return left_dist + 1;
        if (right_dist != -1) return right_dist + 1;
        return -1;
    }
    
    // Tree construction helpers
    static TreeNode<T>* build_tree_helper(const vector<T>& preorder,
                                         const unordered_map<T, int>& inorder_map,
                                         int& preorder_idx, int start, int end) {
        if (start > end) return nullptr;
        
        T root_val = preorder[preorder_idx++];
        TreeNode<T>* root = new TreeNode<T>(root_val);
        
        int root_pos = inorder_map.at(root_val);
        
        root->left = build_tree_helper(preorder, inorder_map, preorder_idx, start, root_pos - 1);
        root->right = build_tree_helper(preorder, inorder_map, preorder_idx, root_pos + 1, end);
        
        return root;
    }
    
    static TreeNode<T>* build_tree_postorder_helper(const vector<T>& postorder,
                                                   const unordered_map<T, int>& inorder_map,
                                                   int& postorder_idx, int start, int end) {
        if (start > end) return nullptr;
        
        T root_val = postorder[postorder_idx--];
        TreeNode<T>* root = new TreeNode<T>(root_val);
        
        int root_pos = inorder_map.at(root_val);
        
        root->right = build_tree_postorder_helper(postorder, inorder_map, postorder_idx, root_pos + 1, end);
        root->left = build_tree_postorder_helper(postorder, inorder_map, postorder_idx, start, root_pos - 1);
        
        return root;
    }
    
    // Serialization helpers
    void serialize_recursive(TreeNode<T>* node, string& result) const {
        if (!node) {
            result += "null,";
            return;
        }
        
        result += to_string(node->data) + ",";
        serialize_recursive(node->left, result);
        serialize_recursive(node->right, result);
    }
    
    TreeNode<T>* deserialize_recursive(const vector<string>& tokens, int& index) {
        if (index >= tokens.size() || tokens[index] == "null") {
            index++;
            return nullptr;
        }
        
        TreeNode<T>* node = new TreeNode<T>(stoi(tokens[index++]));
        node->left = deserialize_recursive(tokens, index);
        node->right = deserialize_recursive(tokens, index);
        
        return node;
    }
    
    vector<string> split_string(const string& str, char delimiter) const {
        vector<string> tokens;
        string token;
        
        for (char c : str) {
            if (c == delimiter) {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        
        if (!token.empty()) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    // Transformation helpers
    void mirror_recursive(TreeNode<T>* node) {
        if (!node) return;
        
        swap(node->left, node->right);
        mirror_recursive(node->left);
        mirror_recursive(node->right);
    }
    
    bool is_mirror_recursive(TreeNode<T>* node1, TreeNode<T>* node2) const {
        if (!node1 && !node2) return true;
        if (!node1 || !node2) return false;
        
        return (node1->data == node2->data) &&
               is_mirror_recursive(node1->left, node2->right) &&
               is_mirror_recursive(node1->right, node2->left);
    }
    
    bool is_symmetric_recursive(TreeNode<T>* left, TreeNode<T>* right) const {
        if (!left && !right) return true;
        if (!left || !right) return false;
        
        return (left->data == right->data) &&
               is_symmetric_recursive(left->left, right->right) &&
               is_symmetric_recursive(left->right, right->left);
    }
    
    // Advanced algorithm helpers
    void get_paths_recursive(TreeNode<T>* node, vector<T>& current_path, 
                           vector<vector<T>>& all_paths) const {
        if (!node) return;
        
        current_path.push_back(node->data);
        
        if (!node->left && !node->right) {
            all_paths.push_back(current_path);
        } else {
            get_paths_recursive(node->left, current_path, all_paths);
            get_paths_recursive(node->right, current_path, all_paths);
        }
        
        current_path.pop_back();
    }
    
    int max_path_sum_recursive(TreeNode<T>* node, int& max_sum) const {
        if (!node) return 0;
        
        int left_sum = max(0, max_path_sum_recursive(node->left, max_sum));
        int right_sum = max(0, max_path_sum_recursive(node->right, max_sum));
        
        int current_max = node->data + left_sum + right_sum;
        max_sum = max(max_sum, current_max);
        
        return node->data + max(left_sum, right_sum);
    }
    
    int diameter_recursive(TreeNode<T>* node, int& max_diameter) const {
        if (!node) return 0;
        
        int left_height = diameter_recursive(node->left, max_diameter);
        int right_height = diameter_recursive(node->right, max_diameter);
        
        int current_diameter = left_height + right_height;
        max_diameter = max(max_diameter, current_diameter);
        
        return 1 + max(left_height, right_height);
    }
    
    int sum_tree_recursive(TreeNode<T>* node) {
        if (!node) return 0;
        
        int old_val = node->data;
        node->data = sum_tree_recursive(node->left) + sum_tree_recursive(node->right);
        
        return node->data + old_val;
    }
    
    bool is_sum_tree_recursive(TreeNode<T>* node) const {
        if (!node || (!node->left && !node->right)) return true;
        
        int left_sum = sum_of_tree(node->left);
        int right_sum = sum_of_tree(node->right);
        
        return (node->data == left_sum + right_sum) &&
               is_sum_tree_recursive(node->left) &&
               is_sum_tree_recursive(node->right);
    }
    
    int sum_of_tree(TreeNode<T>* node) const {
        if (!node) return 0;
        return node->data + sum_of_tree(node->left) + sum_of_tree(node->right);
    }
    
    // Display helpers
    void print_tree_recursive(TreeNode<T>* node, const string& prefix, bool is_tail) const {
        if (!node) return;
        
        cout << prefix << (is_tail ? "└── " : "├── ") << node->data << endl;
        
        if (node->left || node->right) {
            if (node->left) {
                print_tree_recursive(node->left, prefix + (is_tail ? "    " : "│   "), 
                                   !node->right);
            }
            if (node->right) {
                print_tree_recursive(node->right, prefix + (is_tail ? "    " : "│   "), true);
            }
        }
    }
    
    void print_2d_recursive(TreeNode<T>* node, int space, int gap) const {
        if (!node) return;
        
        space += gap;
        print_2d_recursive(node->right, space, gap);
        
        cout << endl;
        for (int i = gap; i < space; ++i) {
            cout << " ";
        }
        cout << node->data << endl;
        
        print_2d_recursive(node->left, space, gap);
    }
};

/*
 * ========================================================================
 * TESTING AND DEMONSTRATION
 * ========================================================================
 */

void demonstrate_binary_tree() {
    cout << "=== BINARY TREE DEMONSTRATION ===" << endl;
    
    // Create a sample tree
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    BinaryTree<int> tree;
    
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(6);
    
    tree.set_root(root);
    
    // Display tree structure
    tree.print_tree();
    cout << endl;
    
    // Tree properties
    cout << "Tree Properties:" << endl;
    cout << "Height: " << tree.height() << endl;
    cout << "Size: " << tree.size() << endl;
    cout << "Leaf count: " << tree.leaf_count() << endl;
    cout << "Is complete: " << (tree.is_complete() ? "Yes" : "No") << endl;
    cout << "Is full: " << (tree.is_full() ? "Yes" : "No") << endl;
    cout << "Is perfect: " << (tree.is_perfect() ? "Yes" : "No") << endl;
    cout << "Is symmetric: " << (tree.is_symmetric() ? "Yes" : "No") << endl;
    cout << endl;
    
    // Traversals
    cout << "Tree Traversals:" << endl;
    
    auto preorder = tree.preorder_traversal();
    cout << "Preorder: ";
    for (int val : preorder) cout << val << " ";
    cout << endl;
    
    auto inorder = tree.inorder_traversal();
    cout << "Inorder: ";
    for (int val : inorder) cout << val << " ";
    cout << endl;
    
    auto postorder = tree.postorder_traversal();
    cout << "Postorder: ";
    for (int val : postorder) cout << val << " ";
    cout << endl;
    
    auto level_order = tree.level_order_traversal();
    cout << "Level order: ";
    for (int val : level_order) cout << val << " ";
    cout << endl;
    
    // Level order with levels
    auto levels = tree.level_order_levels();
    cout << "Level order by levels:" << endl;
    for (int i = 0; i < levels.size(); ++i) {
        cout << "Level " << i << ": ";
        for (int val : levels[i]) cout << val << " ";
        cout << endl;
    }
    cout << endl;
    
    // Search operations
    cout << "Search Operations:" << endl;
    cout << "Contains 4: " << (tree.contains(4) ? "Yes" : "No") << endl;
    cout << "Contains 7: " << (tree.contains(7) ? "Yes" : "No") << endl;
    
    auto path_to_5 = tree.find_path(5);
    cout << "Path to 5: ";
    for (int val : path_to_5) cout << val << " ";
    cout << endl;
    
    cout << "Distance between 4 and 6: " << tree.distance_between_nodes(4, 6) << endl;
    cout << endl;
    
    // Advanced algorithms
    cout << "Advanced Algorithms:" << endl;
    
    auto paths = tree.get_all_paths();
    cout << "All root-to-leaf paths:" << endl;
    for (const auto& path : paths) {
        for (int val : path) cout << val << " ";
        cout << endl;
    }
    
    cout << "Tree diameter: " << tree.diameter() << endl;
    cout << "Maximum path sum: " << tree.max_path_sum() << endl;
    cout << endl;
    
    // Serialization
    cout << "Serialization:" << endl;
    string serialized = tree.serialize();
    cout << "Serialized: " << serialized << endl;
    
    BinaryTree<int> deserialized_tree;
    deserialized_tree.deserialize(serialized);
    cout << "Deserialized tree traversal: ";
    auto deserialized_preorder = deserialized_tree.preorder_traversal();
    for (int val : deserialized_preorder) cout << val << " ";
    cout << endl;
    cout << endl;
}

void demonstrate_tree_construction() {
    cout << "=== TREE CONSTRUCTION DEMONSTRATION ===" << endl;
    
    // Build tree from traversals
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    cout << "Building tree from preorder and inorder:" << endl;
    cout << "Preorder: ";
    for (int val : preorder) cout << val << " ";
    cout << endl;
    cout << "Inorder: ";
    for (int val : inorder) cout << val << " ";
    cout << endl;
    
    TreeNode<int>* root = BinaryTree<int>::build_from_preorder_inorder(preorder, inorder);
    BinaryTree<int> constructed_tree;
    constructed_tree.set_root(root);
    
    cout << "Constructed tree:" << endl;
    constructed_tree.print_tree();
    
    // Verify with level order traversal
    auto level_order = constructed_tree.level_order_traversal();
    cout << "Level order: ";
    for (int val : level_order) cout << val << " ";
    cout << endl;
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== BINARY TREE COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrate_binary_tree();
    demonstrate_tree_construction();
    
    cout << "=== Binary Tree Demo Completed! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * BINARY TREE COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * OPERATION COMPLEXITIES:
 * - Height calculation: O(n) time, O(h) space (recursion)
 * - Size calculation: O(n) time, O(h) space
 * - Traversals: O(n) time, O(h) space (recursive), O(n) space (iterative)
 * - Search: O(n) time, O(h) space
 * - Path finding: O(n) time, O(h) space
 * - LCA: O(n) time, O(h) space
 * - Construction: O(n) time, O(n) space
 * - Serialization: O(n) time, O(n) space
 * 
 * Where n = number of nodes, h = height of tree
 * 
 * SPACE CONSIDERATIONS:
 * - Best case height (balanced): O(log n)
 * - Worst case height (skewed): O(n)
 * - Level order traversal: O(w) where w is maximum width
 * 
 * KEY CONCEPTS:
 * - Binary tree: Each node has at most 2 children
 * - Complete tree: All levels filled except possibly last, filled left to right
 * - Full tree: Every node has 0 or 2 children
 * - Perfect tree: Complete and full
 * - Balanced tree: Height difference between subtrees ≤ 1
 * 
 * TRAVERSAL PATTERNS:
 * - Preorder: Root → Left → Right (good for copying tree)
 * - Inorder: Left → Root → Right (gives sorted order in BST)
 * - Postorder: Left → Right → Root (good for deletion)
 * - Level order: BFS approach (good for level-wise processing)
 * 
 * ============================================================================
 */
