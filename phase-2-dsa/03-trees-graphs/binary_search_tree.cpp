/*
 * ============================================================================
 * BINARY SEARCH TREE IMPLEMENTATION - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * A complete implementation of Binary Search Tree (BST) with:
 * - Standard BST operations (insert, delete, search)
 * - Advanced BST algorithms and properties
 * - Tree balancing concepts and rotations
 * - Iterator implementation for in-order traversal
 * - Range queries and kth element finding
 * - BST validation and optimization
 * 
 * BST PROPERTY: For any node X
 * - All values in left subtree < X.data
 * - All values in right subtree > X.data
 * - Both subtrees are also BSTs
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

/*
 * ========================================================================
 * BINARY SEARCH TREE CLASS
 * ========================================================================
 */

template<typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    int tree_size;
    
    // Helper functions
    void clear_recursive(Node* node) {
        if (node) {
            clear_recursive(node->left);
            clear_recursive(node->right);
            delete node;
        }
    }
    
    Node* copy_recursive(Node* node) {
        if (!node) return nullptr;
        
        Node* new_node = new Node(node->data);
        new_node->left = copy_recursive(node->left);
        new_node->right = copy_recursive(node->right);
        return new_node;
    }

public:
    /*
     * Constructor and Destructor
     */
    BinarySearchTree() : root(nullptr), tree_size(0) {}
    
    // Constructor with initial value
    BinarySearchTree(const T& value) : root(new Node(value)), tree_size(1) {}
    
    // Copy constructor
    BinarySearchTree(const BinarySearchTree& other) 
        : root(copy_recursive(other.root)), tree_size(other.tree_size) {}
    
    // Assignment operator
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            clear();
            root = copy_recursive(other.root);
            tree_size = other.tree_size;
        }
        return *this;
    }
    
    // Destructor
    ~BinarySearchTree() {
        clear();
    }
    
    /*
     * Basic Properties
     */
    bool is_empty() const { return root == nullptr; }
    int size() const { return tree_size; }
    int height() const { return height_recursive(root); }
    
    /*
     * Core BST Operations
     */
    
    // Insert value into BST
    void insert(const T& value) {
        root = insert_recursive(root, value);
    }
    
    // Remove value from BST
    void remove(const T& value) {
        root = remove_recursive(root, value);
    }
    
    // Search for value in BST
    bool contains(const T& value) const {
        return search_recursive(root, value) != nullptr;
    }
    
    // Find minimum value
    T find_min() const {
        if (is_empty()) throw runtime_error("Tree is empty");
        return find_min_recursive(root)->data;
    }
    
    // Find maximum value
    T find_max() const {
        if (is_empty()) throw runtime_error("Tree is empty");
        return find_max_recursive(root)->data;
    }
    
    /*
     * Advanced Search Operations
     */
    
    // Find predecessor of a value
    T find_predecessor(const T& value) const {
        Node* node = search_recursive(root, value);
        if (!node) throw runtime_error("Value not found");
        
        Node* pred = find_predecessor_recursive(root, node);
        if (!pred) throw runtime_error("No predecessor found");
        return pred->data;
    }
    
    // Find successor of a value
    T find_successor(const T& value) const {
        Node* node = search_recursive(root, value);
        if (!node) throw runtime_error("Value not found");
        
        Node* succ = find_successor_recursive(root, node);
        if (!succ) throw runtime_error("No successor found");
        return succ->data;
    }
    
    // Find kth smallest element (1-indexed)
    T kth_smallest(int k) const {
        if (k <= 0 || k > tree_size) throw runtime_error("Invalid k");
        
        int count = 0;
        Node* result = kth_smallest_recursive(root, k, count);
        return result->data;
    }
    
    // Find kth largest element (1-indexed)
    T kth_largest(int k) const {
        return kth_smallest(tree_size - k + 1);
    }
    
    // Count nodes in range [low, high]
    int count_in_range(const T& low, const T& high) const {
        return count_in_range_recursive(root, low, high);
    }
    
    // Get all values in range [low, high]
    vector<T> range_query(const T& low, const T& high) const {
        vector<T> result;
        range_query_recursive(root, low, high, result);
        return result;
    }
    
    /*
     * Traversal Methods
     */
    vector<T> inorder_traversal() const {
        vector<T> result;
        inorder_recursive(root, result);
        return result;
    }
    
    vector<T> preorder_traversal() const {
        vector<T> result;
        preorder_recursive(root, result);
        return result;
    }
    
    vector<T> postorder_traversal() const {
        vector<T> result;
        postorder_recursive(root, result);
        return result;
    }
    
    vector<T> level_order_traversal() const {
        vector<T> result;
        if (!root) return result;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            result.push_back(current->data);
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        
        return result;
    }
    
    /*
     * Tree Validation and Properties
     */
    
    // Check if tree is valid BST
    bool is_valid_bst() const {
        return is_valid_bst_recursive(root, nullptr, nullptr);
    }
    
    // Check if tree is balanced (height difference ≤ 1)
    bool is_balanced() const {
        return is_balanced_recursive(root).first;
    }
    
    // Get tree statistics
    struct TreeStats {
        int height;
        int size;
        int leaf_count;
        int internal_count;
        bool is_balanced;
        bool is_complete;
        bool is_full;
    };
    
    TreeStats get_stats() const {
        TreeStats stats;
        stats.height = height();
        stats.size = size();
        stats.leaf_count = count_leaves(root);
        stats.internal_count = stats.size - stats.leaf_count;
        stats.is_balanced = is_balanced();
        stats.is_complete = is_complete();
        stats.is_full = is_full();
        return stats;
    }
    
    /*
     * Tree Transformation
     */
    
    // Convert BST to sorted array
    vector<T> to_sorted_array() const {
        return inorder_traversal();
    }
    
    // Build balanced BST from sorted array
    void build_from_sorted_array(const vector<T>& sorted_array) {
        clear();
        root = build_balanced_recursive(sorted_array, 0, 
                                       static_cast<int>(sorted_array.size()) - 1);
        tree_size = static_cast<int>(sorted_array.size());
    }
    
    // Balance current BST
    void balance() {
        vector<T> sorted_values = to_sorted_array();
        build_from_sorted_array(sorted_values);
    }
    
    /*
     * Advanced BST Algorithms
     */
    
    // Find lowest common ancestor
    T lowest_common_ancestor(const T& val1, const T& val2) const {
        Node* lca = lca_recursive(root, val1, val2);
        if (!lca) throw runtime_error("LCA not found");
        return lca->data;
    }
    
    // Find distance between two nodes
    int distance_between_nodes(const T& val1, const T& val2) const {
        Node* lca = lca_recursive(root, val1, val2);
        if (!lca) return -1;
        
        int dist1 = distance_from_node(lca, val1);
        int dist2 = distance_from_node(lca, val2);
        
        if (dist1 == -1 || dist2 == -1) return -1;
        return dist1 + dist2;
    }
    
    // Get all paths from root to leaves
    vector<vector<T>> get_all_paths() const {
        vector<vector<T>> paths;
        vector<T> current_path;
        get_paths_recursive(root, current_path, paths);
        return paths;
    }
    
    // Find path with given sum
    vector<T> find_path_with_sum(int target_sum) const {
        vector<T> path;
        if (find_path_sum_recursive(root, target_sum, path)) {
            return path;
        }
        return {};  // Empty vector if no path found
    }
    
    /*
     * Utility Functions
     */
    
    // Clear all nodes
    void clear() {
        clear_recursive(root);
        root = nullptr;
        tree_size = 0;
    }
    
    // Print tree structure
    void print_tree() const {
        cout << "BST Structure:" << endl;
        if (root) {
            print_tree_recursive(root, "", true);
        } else {
            cout << "Empty tree" << endl;
        }
    }
    
    // Print tree statistics
    void print_stats() const {
        TreeStats stats = get_stats();
        cout << "BST Statistics:" << endl;
        cout << "Size: " << stats.size << endl;
        cout << "Height: " << stats.height << endl;
        cout << "Leaf nodes: " << stats.leaf_count << endl;
        cout << "Internal nodes: " << stats.internal_count << endl;
        cout << "Is balanced: " << (stats.is_balanced ? "Yes" : "No") << endl;
        cout << "Is complete: " << (stats.is_complete ? "Yes" : "No") << endl;
        cout << "Is full: " << (stats.is_full ? "Yes" : "No") << endl;
    }
    
    /*
     * Iterator Class for In-order Traversal
     */
    class Iterator {
    private:
        stack<Node*> st;
        
        void push_left(Node* node) {
            while (node) {
                st.push(node);
                node = node->left;
            }
        }
        
    public:
        Iterator(Node* root) {
            push_left(root);
        }
        
        bool has_next() const {
            return !st.empty();
        }
        
        T next() {
            if (!has_next()) throw runtime_error("No more elements");
            
            Node* current = st.top();
            st.pop();
            
            T value = current->data;
            
            if (current->right) {
                push_left(current->right);
            }
            
            return value;
        }
    };
    
    Iterator begin() const {
        return Iterator(root);
    }

private:
    /*
     * Helper Functions
     */
    
    // Recursive insertion
    Node* insert_recursive(Node* node, const T& value) {
        if (!node) {
            tree_size++;
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insert_recursive(node->left, value);
        } else if (value > node->data) {
            node->right = insert_recursive(node->right, value);
        }
        // Equal values are ignored (no duplicates)
        
        return node;
    }
    
    // Recursive deletion
    Node* remove_recursive(Node* node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = remove_recursive(node->left, value);
        } else if (value > node->data) {
            node->right = remove_recursive(node->right, value);
        } else {
            // Node to be deleted found
            tree_size--;
            
            // Case 1: No children
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            
            // Case 2: One child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 3: Two children
            Node* successor = find_min_recursive(node->right);
            node->data = successor->data;
            node->right = remove_recursive(node->right, successor->data);
            tree_size++; // Compensate for decrement in recursive call
        }
        
        return node;
    }
    
    // Recursive search
    Node* search_recursive(Node* node, const T& value) const {
        if (!node || node->data == value) return node;
        
        if (value < node->data) {
            return search_recursive(node->left, value);
        } else {
            return search_recursive(node->right, value);
        }
    }
    
    // Find minimum node
    Node* find_min_recursive(Node* node) const {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }
    
    // Find maximum node
    Node* find_max_recursive(Node* node) const {
        if (!node) return nullptr;
        while (node->right) node = node->right;
        return node;
    }
    
    // Height calculation
    int height_recursive(Node* node) const {
        if (!node) return -1;
        return 1 + max(height_recursive(node->left), height_recursive(node->right));
    }
    
    // Predecessor finding
    Node* find_predecessor_recursive(Node* root, Node* target) const {
        if (!root) return nullptr;
        
        if (target->left) {
            return find_max_recursive(target->left);
        }
        
        Node* predecessor = nullptr;
        Node* current = root;
        
        while (current) {
            if (current->data < target->data) {
                predecessor = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }
        
        return predecessor;
    }
    
    // Successor finding
    Node* find_successor_recursive(Node* root, Node* target) const {
        if (!root) return nullptr;
        
        if (target->right) {
            return find_min_recursive(target->right);
        }
        
        Node* successor = nullptr;
        Node* current = root;
        
        while (current) {
            if (current->data > target->data) {
                successor = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        return successor;
    }
    
    // Kth smallest element
    Node* kth_smallest_recursive(Node* node, int k, int& count) const {
        if (!node) return nullptr;
        
        Node* left_result = kth_smallest_recursive(node->left, k, count);
        if (left_result) return left_result;
        
        count++;
        if (count == k) return node;
        
        return kth_smallest_recursive(node->right, k, count);
    }
    
    // Count nodes in range
    int count_in_range_recursive(Node* node, const T& low, const T& high) const {
        if (!node) return 0;
        
        if (node->data < low) {
            return count_in_range_recursive(node->right, low, high);
        } else if (node->data > high) {
            return count_in_range_recursive(node->left, low, high);
        } else {
            return 1 + count_in_range_recursive(node->left, low, high) +
                       count_in_range_recursive(node->right, low, high);
        }
    }
    
    // Range query
    void range_query_recursive(Node* node, const T& low, const T& high, 
                              vector<T>& result) const {
        if (!node) return;
        
        if (node->data >= low) {
            range_query_recursive(node->left, low, high, result);
        }
        
        if (node->data >= low && node->data <= high) {
            result.push_back(node->data);
        }
        
        if (node->data <= high) {
            range_query_recursive(node->right, low, high, result);
        }
    }
    
    // Traversal helpers
    void inorder_recursive(Node* node, vector<T>& result) const {
        if (node) {
            inorder_recursive(node->left, result);
            result.push_back(node->data);
            inorder_recursive(node->right, result);
        }
    }
    
    void preorder_recursive(Node* node, vector<T>& result) const {
        if (node) {
            result.push_back(node->data);
            preorder_recursive(node->left, result);
            preorder_recursive(node->right, result);
        }
    }
    
    void postorder_recursive(Node* node, vector<T>& result) const {
        if (node) {
            postorder_recursive(node->left, result);
            postorder_recursive(node->right, result);
            result.push_back(node->data);
        }
    }
    
    // BST validation
    bool is_valid_bst_recursive(Node* node, const T* min_val, const T* max_val) const {
        if (!node) return true;
        
        if ((min_val && node->data <= *min_val) || 
            (max_val && node->data >= *max_val)) {
            return false;
        }
        
        return is_valid_bst_recursive(node->left, min_val, &node->data) &&
               is_valid_bst_recursive(node->right, &node->data, max_val);
    }
    
    // Balance checking
    pair<bool, int> is_balanced_recursive(Node* node) const {
        if (!node) return {true, 0};
        
        auto left = is_balanced_recursive(node->left);
        auto right = is_balanced_recursive(node->right);
        
        bool balanced = left.first && right.first && 
                       abs(left.second - right.second) <= 1;
        int height = 1 + max(left.second, right.second);
        
        return {balanced, height};
    }
    
    // Tree property checks
    int count_leaves(Node* node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return count_leaves(node->left) + count_leaves(node->right);
    }
    
    bool is_complete() const {
        return is_complete_recursive(root, 0, tree_size);
    }
    
    bool is_complete_recursive(Node* node, int index, int total_nodes) const {
        if (!node) return true;
        if (index >= total_nodes) return false;
        
        return is_complete_recursive(node->left, 2 * index + 1, total_nodes) &&
               is_complete_recursive(node->right, 2 * index + 2, total_nodes);
    }
    
    bool is_full() const {
        return is_full_recursive(root);
    }
    
    bool is_full_recursive(Node* node) const {
        if (!node) return true;
        if (!node->left && !node->right) return true;
        if (node->left && node->right) {
            return is_full_recursive(node->left) && is_full_recursive(node->right);
        }
        return false;
    }
    
    // Build balanced BST
    Node* build_balanced_recursive(const vector<T>& arr, int start, int end) {
        if (start > end) return nullptr;
        
        int mid = start + (end - start) / 2;
        Node* node = new Node(arr[mid]);
        
        node->left = build_balanced_recursive(arr, start, mid - 1);
        node->right = build_balanced_recursive(arr, mid + 1, end);
        
        return node;
    }
    
    // LCA finding
    Node* lca_recursive(Node* node, const T& val1, const T& val2) const {
        if (!node) return nullptr;
        
        if (val1 < node->data && val2 < node->data) {
            return lca_recursive(node->left, val1, val2);
        } else if (val1 > node->data && val2 > node->data) {
            return lca_recursive(node->right, val1, val2);
        } else {
            return node;
        }
    }
    
    // Distance calculation
    int distance_from_node(Node* node, const T& target) const {
        if (!node) return -1;
        if (node->data == target) return 0;
        
        if (target < node->data) {
            int left_dist = distance_from_node(node->left, target);
            return (left_dist == -1) ? -1 : left_dist + 1;
        } else {
            int right_dist = distance_from_node(node->right, target);
            return (right_dist == -1) ? -1 : right_dist + 1;
        }
    }
    
    // Path finding
    void get_paths_recursive(Node* node, vector<T>& current_path, 
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
    
    // Path sum finding
    bool find_path_sum_recursive(Node* node, int target_sum, vector<T>& path) const {
        if (!node) return false;
        
        path.push_back(node->data);
        
        if (!node->left && !node->right) {
            int sum = 0;
            for (const T& val : path) sum += val;
            if (sum == target_sum) return true;
        } else {
            if (find_path_sum_recursive(node->left, target_sum, path) ||
                find_path_sum_recursive(node->right, target_sum, path)) {
                return true;
            }
        }
        
        path.pop_back();
        return false;
    }
    
    // Tree printing
    void print_tree_recursive(Node* node, const string& prefix, bool is_tail) const {
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
};

/*
 * ========================================================================
 * BST TESTING AND DEMONSTRATION
 * ========================================================================
 */

void demonstrate_bst_operations() {
    cout << "=== BST OPERATIONS DEMONSTRATION ===" << endl;
    
    BinarySearchTree<int> bst;
    
    // Insert elements
    vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    cout << "Inserting values: ";
    for (int val : values) {
        cout << val << " ";
        bst.insert(val);
    }
    cout << endl << endl;
    
    // Display tree structure
    bst.print_tree();
    cout << endl;
    
    // Basic operations
    cout << "Basic Operations:" << endl;
    cout << "Contains 40: " << (bst.contains(40) ? "Yes" : "No") << endl;
    cout << "Contains 55: " << (bst.contains(55) ? "Yes" : "No") << endl;
    cout << "Minimum: " << bst.find_min() << endl;
    cout << "Maximum: " << bst.find_max() << endl;
    cout << "Size: " << bst.size() << endl;
    cout << "Height: " << bst.height() << endl;
    cout << endl;
    
    // Advanced search operations
    cout << "Advanced Search:" << endl;
    cout << "3rd smallest: " << bst.kth_smallest(3) << endl;
    cout << "3rd largest: " << bst.kth_largest(3) << endl;
    cout << "Predecessor of 40: " << bst.find_predecessor(40) << endl;
    cout << "Successor of 40: " << bst.find_successor(40) << endl;
    cout << "Count in range [25, 55]: " << bst.count_in_range(25, 55) << endl;
    
    auto range_result = bst.range_query(25, 55);
    cout << "Values in range [25, 55]: ";
    for (int val : range_result) cout << val << " ";
    cout << endl << endl;
    
    // Traversals
    cout << "Traversals:" << endl;
    
    auto inorder = bst.inorder_traversal();
    cout << "Inorder: ";
    for (int val : inorder) cout << val << " ";
    cout << endl;
    
    auto preorder = bst.preorder_traversal();
    cout << "Preorder: ";
    for (int val : preorder) cout << val << " ";
    cout << endl;
    
    auto level_order = bst.level_order_traversal();
    cout << "Level order: ";
    for (int val : level_order) cout << val << " ";
    cout << endl << endl;
    
    // Tree statistics
    bst.print_stats();
    cout << endl;
    
    // LCA and distance
    cout << "Tree Relationships:" << endl;
    cout << "LCA of 25 and 45: " << bst.lowest_common_ancestor(25, 45) << endl;
    cout << "Distance between 25 and 45: " << bst.distance_between_nodes(25, 45) << endl;
    cout << endl;
    
    // Iterator demonstration
    cout << "Iterator traversal: ";
    auto it = bst.begin();
    while (it.has_next()) {
        cout << it.next() << " ";
    }
    cout << endl << endl;
    
    // Deletion
    cout << "Deleting 30..." << endl;
    bst.remove(30);
    bst.print_tree();
    cout << endl;
}

void demonstrate_bst_balancing() {
    cout << "=== BST BALANCING DEMONSTRATION ===" << endl;
    
    BinarySearchTree<int> bst;
    
    // Create unbalanced tree
    vector<int> ascending = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Inserting in ascending order: ";
    for (int val : ascending) {
        cout << val << " ";
        bst.insert(val);
    }
    cout << endl << endl;
    
    cout << "Unbalanced tree:" << endl;
    bst.print_tree();
    bst.print_stats();
    cout << endl;
    
    // Balance the tree
    cout << "Balancing tree..." << endl;
    bst.balance();
    
    cout << "Balanced tree:" << endl;
    bst.print_tree();
    bst.print_stats();
    cout << endl;
    
    // Demonstrate building balanced BST from sorted array
    cout << "Building balanced BST from sorted array:" << endl;
    vector<int> sorted_array = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    
    BinarySearchTree<int> balanced_bst;
    balanced_bst.build_from_sorted_array(sorted_array);
    
    balanced_bst.print_tree();
    balanced_bst.print_stats();
}

void demonstrate_advanced_bst_algorithms() {
    cout << "=== ADVANCED BST ALGORITHMS ===" << endl;
    
    BinarySearchTree<int> bst;
    
    // Build sample tree
    vector<int> values = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int val : values) {
        bst.insert(val);
    }
    
    cout << "Sample BST:" << endl;
    bst.print_tree();
    cout << endl;
    
    // Get all paths
    auto paths = bst.get_all_paths();
    cout << "All root-to-leaf paths:" << endl;
    for (const auto& path : paths) {
        for (int val : path) cout << val << " ";
        cout << endl;
    }
    cout << endl;
    
    // Find path with sum
    int target_sum = 22;  // Path: 8 -> 3 -> 1 -> 10 (hypothetical)
    auto path_with_sum = bst.find_path_with_sum(target_sum);
    cout << "Path with sum " << target_sum << ": ";
    if (path_with_sum.empty()) {
        cout << "Not found" << endl;
    } else {
        for (int val : path_with_sum) cout << val << " ";
        cout << endl;
    }
    cout << endl;
    
    // BST validation
    cout << "Is valid BST: " << (bst.is_valid_bst() ? "Yes" : "No") << endl;
    cout << "Is balanced: " << (bst.is_balanced() ? "Yes" : "No") << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== BINARY SEARCH TREE COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrate_bst_operations();
    demonstrate_bst_balancing();
    demonstrate_advanced_bst_algorithms();
    
    cout << "=== BST Demo Completed! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * BINARY SEARCH TREE COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * AVERAGE CASE (Balanced BST):
 * - Search: O(log n)
 * - Insert: O(log n)
 * - Delete: O(log n)
 * - Find min/max: O(log n)
 * - Predecessor/Successor: O(log n)
 * - Range query: O(log n + k) where k is result size
 * 
 * WORST CASE (Skewed BST):
 * - Search: O(n)
 * - Insert: O(n)
 * - Delete: O(n)
 * - Find min/max: O(n)
 * - Predecessor/Successor: O(n)
 * - Range query: O(n)
 * 
 * SPACE COMPLEXITY:
 * - Tree storage: O(n)
 * - Recursion depth: O(h) where h is height
 * - Best case height: O(log n)
 * - Worst case height: O(n)
 * 
 * BST ADVANTAGES:
 * - Efficient searching (better than unsorted array)
 * - Inorder traversal gives sorted sequence
 * - Dynamic size (can grow/shrink)
 * - No need for pre-allocation
 * 
 * BST DISADVANTAGES:
 * - Can become unbalanced
 * - No random access
 * - Pointer overhead
 * - Cache performance may be poor
 * 
 * WHEN TO USE BST:
 * - Need sorted data with frequent insertions/deletions
 * - Range queries are common
 * - Need to find kth smallest/largest elements
 * - Dynamic dataset with search requirements
 * 
 * BALANCING TECHNIQUES:
 * - AVL Trees: Height-balanced BST
 * - Red-Black Trees: Color-based balancing
 * - Splay Trees: Self-adjusting BST
 * - Treap: Randomized BST
 * 
 * ============================================================================
 */
