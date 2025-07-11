/*
 * ============================================================================
 * TREE PROBLEMS - COMPREHENSIVE PROBLEM SET
 * ============================================================================
 * 
 * A comprehensive collection of tree problems covering:
 * - Binary tree traversals and properties
 * - Binary search tree operations
 * - Tree construction and modification
 * - Path and distance problems
 * - Tree dynamic programming
 * - Advanced tree algorithms
 * 
 * Each problem includes:
 * - Problem statement and examples
 * - Multiple solution approaches
 * - Time and space complexity analysis
 * - Test cases and explanations
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

using namespace std;

/*
 * ========================================================================
 * TREE NODE DEFINITIONS
 * ========================================================================
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

struct TreeNodeWithParent {
    int val;
    TreeNodeWithParent* left;
    TreeNodeWithParent* right;
    TreeNodeWithParent* parent;
    
    TreeNodeWithParent() : val(0), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNodeWithParent(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

/*
 * ========================================================================
 * PROBLEM 1: TREE TRAVERSALS
 * ========================================================================
 * Problem: Implement all tree traversals (preorder, inorder, postorder)
 * both recursively and iteratively.
 */

class TreeTraversals {
public:
    // Recursive traversals
    vector<int> preorderRecursive(TreeNode* root) {
        vector<int> result;
        preorderHelper(root, result);
        return result;
    }
    
    vector<int> inorderRecursive(TreeNode* root) {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }
    
    vector<int> postorderRecursive(TreeNode* root) {
        vector<int> result;
        postorderHelper(root, result);
        return result;
    }
    
    // Iterative traversals
    vector<int> preorderIterative(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        
        stack<TreeNode*> st;
        st.push(root);
        
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);
            
            // Push right first, then left (stack is LIFO)
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
        
        return result;
    }
    
    vector<int> inorderIterative(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* current = root;
        
        while (current || !st.empty()) {
            // Go to leftmost node
            while (current) {
                st.push(current);
                current = current->left;
            }
            
            // Process node
            current = st.top();
            st.pop();
            result.push_back(current->val);
            
            // Move to right subtree
            current = current->right;
        }
        
        return result;
    }
    
    vector<int> postorderIterative(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        
        stack<TreeNode*> st1, st2;
        st1.push(root);
        
        while (!st1.empty()) {
            TreeNode* node = st1.top();
            st1.pop();
            st2.push(node);
            
            if (node->left) st1.push(node->left);
            if (node->right) st1.push(node->right);
        }
        
        while (!st2.empty()) {
            result.push_back(st2.top()->val);
            st2.pop();
        }
        
        return result;
    }

private:
    void preorderHelper(TreeNode* root, vector<int>& result) {
        if (!root) return;
        result.push_back(root->val);
        preorderHelper(root->left, result);
        preorderHelper(root->right, result);
    }
    
    void inorderHelper(TreeNode* root, vector<int>& result) {
        if (!root) return;
        inorderHelper(root->left, result);
        result.push_back(root->val);
        inorderHelper(root->right, result);
    }
    
    void postorderHelper(TreeNode* root, vector<int>& result) {
        if (!root) return;
        postorderHelper(root->left, result);
        postorderHelper(root->right, result);
        result.push_back(root->val);
    }
};

/*
 * ========================================================================
 * PROBLEM 2: MAXIMUM DEPTH OF BINARY TREE
 * ========================================================================
 * Problem: Find the maximum depth (height) of a binary tree.
 * Example: [3,9,20,null,null,15,7] → 3
 */

class MaxDepthSolution {
public:
    // Recursive approach
    int maxDepthRecursive(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepthRecursive(root->left), maxDepthRecursive(root->right));
    }
    
    // BFS approach
    int maxDepthBFS(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        
        while (!q.empty()) {
            int size = q.size();
            depth++;
            
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return depth;
    }
    
    // DFS iterative approach
    int maxDepthDFS(TreeNode* root) {
        if (!root) return 0;
        
        stack<pair<TreeNode*, int>> st;
        st.push({root, 1});
        int maxDepth = 0;
        
        while (!st.empty()) {
            auto [node, depth] = st.top();
            st.pop();
            
            maxDepth = max(maxDepth, depth);
            
            if (node->left) st.push({node->left, depth + 1});
            if (node->right) st.push({node->right, depth + 1});
        }
        
        return maxDepth;
    }
};

/*
 * ========================================================================
 * PROBLEM 3: SYMMETRIC TREE
 * ========================================================================
 * Problem: Check if a binary tree is symmetric around its center.
 * Example: [1,2,2,3,4,4,3] → true
 */

class SymmetricTreeSolution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isSymmetricHelper(root->left, root->right);
    }
    
    // Iterative approach
    bool isSymmetricIterative(TreeNode* root) {
        if (!root) return true;
        
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);
        
        while (!q.empty()) {
            TreeNode* left = q.front(); q.pop();
            TreeNode* right = q.front(); q.pop();
            
            if (!left && !right) continue;
            if (!left || !right || left->val != right->val) return false;
            
            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);
        }
        
        return true;
    }

private:
    bool isSymmetricHelper(TreeNode* left, TreeNode* right) {
        if (!left && !right) return true;
        if (!left || !right) return false;
        if (left->val != right->val) return false;
        
        return isSymmetricHelper(left->left, right->right) && 
               isSymmetricHelper(left->right, right->left);
    }
};

/*
 * ========================================================================
 * PROBLEM 4: PATH SUM
 * ========================================================================
 * Problem: Check if tree has a root-to-leaf path with given sum.
 * Example: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22 → true
 */

class PathSumSolution {
public:
    // Path Sum I: Check if any root-to-leaf path sum equals target
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        
        // If leaf node, check if remaining sum equals node value
        if (!root->left && !root->right) {
            return targetSum == root->val;
        }
        
        int remainingSum = targetSum - root->val;
        return hasPathSum(root->left, remainingSum) || 
               hasPathSum(root->right, remainingSum);
    }
    
    // Path Sum II: Find all root-to-leaf paths with given sum
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        vector<int> currentPath;
        pathSumHelper(root, targetSum, currentPath, result);
        return result;
    }
    
    // Path Sum III: Number of paths (not necessarily root-to-leaf) with given sum
    int pathSumIII(TreeNode* root, int targetSum) {
        if (!root) return 0;
        
        return countPaths(root, targetSum) + 
               pathSumIII(root->left, targetSum) + 
               pathSumIII(root->right, targetSum);
    }

private:
    void pathSumHelper(TreeNode* root, int targetSum, 
                      vector<int>& currentPath, vector<vector<int>>& result) {
        if (!root) return;
        
        currentPath.push_back(root->val);
        
        if (!root->left && !root->right && targetSum == root->val) {
            result.push_back(currentPath);
        }
        
        pathSumHelper(root->left, targetSum - root->val, currentPath, result);
        pathSumHelper(root->right, targetSum - root->val, currentPath, result);
        
        currentPath.pop_back();  // Backtrack
    }
    
    int countPaths(TreeNode* root, long targetSum) {
        if (!root) return 0;
        
        int count = 0;
        if (root->val == targetSum) count++;
        
        count += countPaths(root->left, targetSum - root->val);
        count += countPaths(root->right, targetSum - root->val);
        
        return count;
    }
};

/*
 * ========================================================================
 * PROBLEM 5: BINARY TREE LEVEL ORDER TRAVERSAL
 * ========================================================================
 * Problem: Return level order traversal as vector of vectors.
 * Example: [3,9,20,null,null,15,7] → [[3],[9,20],[15,7]]
 */

class LevelOrderSolution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(level);
        }
        
        return result;
    }
    
    // Zigzag level order
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);
            
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                int index = leftToRight ? i : size - 1 - i;
                level[index] = node->val;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            leftToRight = !leftToRight;
            result.push_back(level);
        }
        
        return result;
    }
    
    // Bottom-up level order
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result = levelOrder(root);
        reverse(result.begin(), result.end());
        return result;
    }
};

/*
 * ========================================================================
 * PROBLEM 6: CONSTRUCT BINARY TREE FROM TRAVERSALS
 * ========================================================================
 * Problem: Build tree from preorder and inorder traversals.
 */

class ConstructTreeSolution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); ++i) {
            inorderMap[inorder[i]] = i;
        }
        
        int preorderIndex = 0;
        return buildTreeHelper(preorder, preorderIndex, 0, inorder.size() - 1, inorderMap);
    }
    
    // Build from inorder and postorder
    TreeNode* buildTreeFromInPost(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); ++i) {
            inorderMap[inorder[i]] = i;
        }
        
        int postorderIndex = postorder.size() - 1;
        return buildTreeFromInPostHelper(postorder, postorderIndex, 0, inorder.size() - 1, inorderMap);
    }

private:
    TreeNode* buildTreeHelper(vector<int>& preorder, int& preorderIndex, 
                             int left, int right, unordered_map<int, int>& inorderMap) {
        if (left > right) return nullptr;
        
        int rootVal = preorder[preorderIndex++];
        TreeNode* root = new TreeNode(rootVal);
        
        int inorderIndex = inorderMap[rootVal];
        
        root->left = buildTreeHelper(preorder, preorderIndex, left, inorderIndex - 1, inorderMap);
        root->right = buildTreeHelper(preorder, preorderIndex, inorderIndex + 1, right, inorderMap);
        
        return root;
    }
    
    TreeNode* buildTreeFromInPostHelper(vector<int>& postorder, int& postorderIndex,
                                       int left, int right, unordered_map<int, int>& inorderMap) {
        if (left > right) return nullptr;
        
        int rootVal = postorder[postorderIndex--];
        TreeNode* root = new TreeNode(rootVal);
        
        int inorderIndex = inorderMap[rootVal];
        
        // Build right first for postorder
        root->right = buildTreeFromInPostHelper(postorder, postorderIndex, inorderIndex + 1, right, inorderMap);
        root->left = buildTreeFromInPostHelper(postorder, postorderIndex, left, inorderIndex - 1, inorderMap);
        
        return root;
    }
};

/*
 * ========================================================================
 * PROBLEM 7: VALIDATE BINARY SEARCH TREE
 * ========================================================================
 * Problem: Check if a binary tree is a valid BST.
 */

class ValidateBSTSolution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
    }
    
    // Using inorder traversal (should be sorted)
    bool isValidBSTInorder(TreeNode* root) {
        vector<int> inorder;
        inorderTraversal(root, inorder);
        
        for (int i = 1; i < inorder.size(); ++i) {
            if (inorder[i] <= inorder[i-1]) return false;
        }
        return true;
    }

private:
    bool isValidBSTHelper(TreeNode* root, long long minVal, long long maxVal) {
        if (!root) return true;
        
        if (root->val <= minVal || root->val >= maxVal) return false;
        
        return isValidBSTHelper(root->left, minVal, root->val) &&
               isValidBSTHelper(root->right, root->val, maxVal);
    }
    
    void inorderTraversal(TreeNode* root, vector<int>& result) {
        if (!root) return;
        inorderTraversal(root->left, result);
        result.push_back(root->val);
        inorderTraversal(root->right, result);
    }
};

/*
 * ========================================================================
 * PROBLEM 8: LOWEST COMMON ANCESTOR
 * ========================================================================
 * Problem: Find LCA of two nodes in binary tree and BST.
 */

class LCASolution {
public:
    // LCA in binary tree
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if (left && right) return root;
        return left ? left : right;
    }
    
    // LCA in BST (more efficient)
    TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestorBST(root->left, p, q);
        }
        if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestorBST(root->right, p, q);
        }
        
        return root;
    }
    
    // LCA with path storage
    vector<TreeNode*> findPath(TreeNode* root, TreeNode* target) {
        vector<TreeNode*> path;
        findPathHelper(root, target, path);
        return path;
    }

private:
    bool findPathHelper(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
        if (!root) return false;
        
        path.push_back(root);
        
        if (root == target) return true;
        
        if (findPathHelper(root->left, target, path) || 
            findPathHelper(root->right, target, path)) {
            return true;
        }
        
        path.pop_back();
        return false;
    }
};

/*
 * ========================================================================
 * PROBLEM 9: BINARY TREE DIAMETER
 * ========================================================================
 * Problem: Find diameter (longest path between any two nodes).
 */

class DiameterSolution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        maxDepth(root, diameter);
        return diameter;
    }

private:
    int maxDepth(TreeNode* root, int& diameter) {
        if (!root) return 0;
        
        int leftDepth = maxDepth(root->left, diameter);
        int rightDepth = maxDepth(root->right, diameter);
        
        // Update diameter (path through current node)
        diameter = max(diameter, leftDepth + rightDepth);
        
        return 1 + max(leftDepth, rightDepth);
    }
};

/*
 * ========================================================================
 * PROBLEM 10: BINARY TREE MAXIMUM PATH SUM
 * ========================================================================
 * Problem: Find maximum sum path between any two nodes.
 */

class MaxPathSumSolution {
public:
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        maxPathSumHelper(root, maxSum);
        return maxSum;
    }

private:
    int maxPathSumHelper(TreeNode* root, int& maxSum) {
        if (!root) return 0;
        
        // Get max sum from left and right subtrees (ignore negative)
        int leftSum = max(0, maxPathSumHelper(root->left, maxSum));
        int rightSum = max(0, maxPathSumHelper(root->right, maxSum));
        
        // Update global maximum (path through current node)
        maxSum = max(maxSum, root->val + leftSum + rightSum);
        
        // Return max sum including current node (for parent)
        return root->val + max(leftSum, rightSum);
    }
};

/*
 * ========================================================================
 * PROBLEM 11: SERIALIZE AND DESERIALIZE BINARY TREE
 * ========================================================================
 * Problem: Design algorithm to serialize/deserialize binary tree.
 */

class SerializeDeserializeSolution {
public:
    // Serialize using preorder traversal
    string serialize(TreeNode* root) {
        string result;
        serializeHelper(root, result);
        return result;
    }
    
    TreeNode* deserialize(string data) {
        int index = 0;
        return deserializeHelper(data, index);
    }

private:
    void serializeHelper(TreeNode* root, string& result) {
        if (!root) {
            result += "null,";
            return;
        }
        
        result += to_string(root->val) + ",";
        serializeHelper(root->left, result);
        serializeHelper(root->right, result);
    }
    
    TreeNode* deserializeHelper(const string& data, int& index) {
        if (index >= data.length()) return nullptr;
        
        // Find next comma
        int commaPos = data.find(',', index);
        string nodeVal = data.substr(index, commaPos - index);
        index = commaPos + 1;
        
        if (nodeVal == "null") return nullptr;
        
        TreeNode* root = new TreeNode(stoi(nodeVal));
        root->left = deserializeHelper(data, index);
        root->right = deserializeHelper(data, index);
        
        return root;
    }
};

/*
 * ========================================================================
 * PROBLEM 12: BINARY TREE VERTICAL ORDER TRAVERSAL
 * ========================================================================
 * Problem: Return vertical order traversal of binary tree.
 */

class VerticalOrderSolution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) return {};
        
        map<int, vector<int>> columnMap;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        while (!q.empty()) {
            auto [node, col] = q.front();
            q.pop();
            
            columnMap[col].push_back(node->val);
            
            if (node->left) q.push({node->left, col - 1});
            if (node->right) q.push({node->right, col + 1});
        }
        
        vector<vector<int>> result;
        for (auto& [col, nodes] : columnMap) {
            result.push_back(nodes);
        }
        
        return result;
    }
};

/*
 * ========================================================================
 * PROBLEM 13: BINARY TREE RIGHT SIDE VIEW
 * ========================================================================
 * Problem: Return values of nodes seen from right side.
 */

class RightSideViewSolution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        rightSideViewHelper(root, 0, result);
        return result;
    }
    
    // BFS approach
    vector<int> rightSideViewBFS(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                // Last node in level is rightmost
                if (i == size - 1) {
                    result.push_back(node->val);
                }
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return result;
    }

private:
    void rightSideViewHelper(TreeNode* root, int level, vector<int>& result) {
        if (!root) return;
        
        // If this is first node of current level from right
        if (level == result.size()) {
            result.push_back(root->val);
        }
        
        // Traverse right first, then left
        rightSideViewHelper(root->right, level + 1, result);
        rightSideViewHelper(root->left, level + 1, result);
    }
};

/*
 * ========================================================================
 * PROBLEM 14: FLATTEN BINARY TREE TO LINKED LIST
 * ========================================================================
 * Problem: Flatten binary tree to linked list in-place (preorder).
 */

class FlattenTreeSolution {
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        
        TreeNode* current = root;
        
        while (current) {
            if (current->left) {
                // Find rightmost node in left subtree
                TreeNode* rightmost = current->left;
                while (rightmost->right) {
                    rightmost = rightmost->right;
                }
                
                // Connect rightmost to current's right
                rightmost->right = current->right;
                current->right = current->left;
                current->left = nullptr;
            }
            
            current = current->right;
        }
    }
    
    // Recursive approach
    void flattenRecursive(TreeNode* root) {
        flattenHelper(root);
    }

private:
    TreeNode* flattenHelper(TreeNode* root) {
        if (!root) return nullptr;
        
        TreeNode* leftTail = flattenHelper(root->left);
        TreeNode* rightTail = flattenHelper(root->right);
        
        if (leftTail) {
            leftTail->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        
        return rightTail ? rightTail : (leftTail ? leftTail : root);
    }
};

/*
 * ========================================================================
 * PROBLEM 15: BINARY TREE CAMERAS
 * ========================================================================
 * Problem: Minimum number of cameras to monitor all nodes.
 */

class CameraSolution {
public:
    int minCameraCover(TreeNode* root) {
        int cameras = 0;
        int state = dfs(root, cameras);
        return cameras + (state == 0 ? 1 : 0);  // Add camera if root needs one
    }

private:
    // States: 0 = needs camera, 1 = has camera, 2 = covered
    int dfs(TreeNode* root, int& cameras) {
        if (!root) return 2;  // null nodes are considered covered
        
        int left = dfs(root->left, cameras);
        int right = dfs(root->right, cameras);
        
        // If any child needs camera, place camera here
        if (left == 0 || right == 0) {
            cameras++;
            return 1;
        }
        
        // If any child has camera, this node is covered
        if (left == 1 || right == 1) {
            return 2;
        }
        
        // Both children are covered but no camera, this node needs camera
        return 0;
    }
};

/*
 * ========================================================================
 * UTILITY FUNCTIONS AND TESTING
 * ========================================================================
 */

class TreeUtilities {
public:
    // Create tree from level order array
    TreeNode* createTree(vector<int>& vals) {
        if (vals.empty()) return nullptr;
        
        TreeNode* root = new TreeNode(vals[0]);
        queue<TreeNode*> q;
        q.push(root);
        int i = 1;
        
        while (!q.empty() && i < vals.size()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (i < vals.size() && vals[i] != INT_MIN) {
                node->left = new TreeNode(vals[i]);
                q.push(node->left);
            }
            i++;
            
            if (i < vals.size() && vals[i] != INT_MIN) {
                node->right = new TreeNode(vals[i]);
                q.push(node->right);
            }
            i++;
        }
        
        return root;
    }
    
    // Print tree (level order)
    void printTree(TreeNode* root) {
        if (!root) {
            cout << "Empty tree" << endl;
            return;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node) {
                    cout << node->val << " ";
                    q.push(node->left);
                    q.push(node->right);
                } else {
                    cout << "null ";
                }
            }
            cout << endl;
        }
    }
    
    // Delete tree
    void deleteTree(TreeNode* root) {
        if (!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
};

/*
 * ========================================================================
 * TESTING FUNCTIONS
 * ========================================================================
 */

void testTreeProblems() {
    cout << "=== TESTING TREE PROBLEMS ===" << endl;
    
    TreeUtilities utils;
    
    // Test tree: [3,9,20,null,null,15,7]
    vector<int> treeVals = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};
    TreeNode* root = utils.createTree(treeVals);
    
    cout << "Test tree:" << endl;
    utils.printTree(root);
    
    // Test traversals
    TreeTraversals traversals;
    auto preorder = traversals.preorderRecursive(root);
    auto inorder = traversals.inorderRecursive(root);
    auto postorder = traversals.postorderRecursive(root);
    
    cout << "Preorder: ";
    for (int val : preorder) cout << val << " ";
    cout << endl;
    
    cout << "Inorder: ";
    for (int val : inorder) cout << val << " ";
    cout << endl;
    
    cout << "Postorder: ";
    for (int val : postorder) cout << val << " ";
    cout << endl;
    
    // Test max depth
    MaxDepthSolution depthSol;
    cout << "Max depth: " << depthSol.maxDepthRecursive(root) << endl;
    
    // Test level order
    LevelOrderSolution levelSol;
    auto levels = levelSol.levelOrder(root);
    cout << "Level order:" << endl;
    for (const auto& level : levels) {
        for (int val : level) cout << val << " ";
        cout << endl;
    }
    
    utils.deleteTree(root);
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== BINARY TREE PROBLEMS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    testTreeProblems();
    
    cout << "=== Tree Problems Demo Completed! ===" << endl;
    cout << "This collection covers fundamental to advanced tree problems." << endl;
    cout << "Practice these problems to master tree algorithms!" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * TREE PROBLEMS COMPLEXITY SUMMARY:
 * ============================================================================
 * 
 * TRAVERSALS:
 * - All traversals: O(n) time, O(h) space (recursion stack)
 * - Iterative versions: O(n) time, O(h) space (explicit stack)
 * 
 * DEPTH/HEIGHT PROBLEMS:
 * - Max depth: O(n) time, O(h) space
 * - Diameter: O(n) time, O(h) space
 * 
 * PATH PROBLEMS:
 * - Path sum: O(n) time, O(h) space
 * - Max path sum: O(n) time, O(h) space
 * 
 * CONSTRUCTION:
 * - From traversals: O(n) time, O(n) space
 * - Requires hashmap for efficient lookups
 * 
 * BST VALIDATION:
 * - O(n) time, O(h) space
 * - Use bounds or inorder traversal
 * 
 * LCA PROBLEMS:
 * - Binary tree: O(n) time, O(h) space
 * - BST: O(h) time, O(h) space
 * 
 * SERIALIZATION:
 * - O(n) time and space
 * - Preorder with null markers works well
 * 
 * VIEW PROBLEMS:
 * - Right/left side view: O(n) time, O(h) space
 * - Level order approaches often simpler
 * 
 * ADVANCED PROBLEMS:
 * - Vertical order: O(n log n) time, O(n) space
 * - Flatten: O(n) time, O(1) space (Morris-like)
 * - Cameras: O(n) time, O(h) space (greedy with states)
 * 
 * ============================================================================
 */
