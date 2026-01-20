#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <stack>
#include <type_traits>
#include <vector>

enum class Order { Pre, In, Post };

template <typename T> struct Node {
    T data;
    Node *left = nullptr;
    Node *right = nullptr;

    explicit Node(const T &value) : data(value) {}

    ~Node() = default;
};

template <typename T, typename Compare = std::less<T>> class BinaryTree {
  public:
    using NodeT = Node<T>;

    BinaryTree() = default;
    explicit BinaryTree(NodeT *root) : root_(root) {}

    ~BinaryTree() {
        deinit();
    }

    void deinit() {
        destroy(root_);
        root_ = nullptr;
    }

    void insert(const T &);
    void preOrderIter(void (*visit)(const T &)) const;
    template <typename Visit> void preOrderRecursive(Visit visit) const;
    template <typename Visit> void inOrderIter(Visit visit) const;
    template <typename Visit> void inOrderRecursive(Visit visit) const;
    template <typename Visit> void postOrderIter(Visit visit) const;
    template <typename Visit> void postOrderRecursive(Visit visit) const;
    template <typename Visit> void traversalAll(Visit visit) const;
    template <typename Visit> void levelOrder(Visit visit) const;

    size_t height() const {
        return heightNode(root_);
    }

    bool isBalanced() const {
        return isBalancedOpt(root_).balanced;
    }

    size_t maxDiameter() const {
        size_t diameter = 0;
        maxDiameterNode(root_, diameter);
        return diameter;
    }

    static_assert(std::is_arithmetic_v<T>, "T must be numeric");
    T maxSumPath() const {
        T max_sum = std::numeric_limits<T>::lowest();
        maxSumPathNode(root_, max_sum);
        return max_sum;
    }

  private:
    NodeT *root_ = nullptr;

    void destroy(NodeT *node) {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    template <typename Visit> static void preorderNode(NodeT *node, Visit visit) {
        if (!node)
            return;
        visit(node->data);
        preorderNode(node->left, visit);
        preorderNode(node->right, visit);
    }

    template <typename Visit> static void inorderNode(NodeT *node, Visit visit) {
        if (!node)
            return;
        inorderNode(node->left, visit);
        visit(node->data);
        inorderNode(node->right, visit);
    }

    template <typename Visit> static void postorderNode(NodeT *node, Visit visit) {
        if (!node)
            return;
        postorderNode(node->left, visit);
        postorderNode(node->right, visit);
        visit(node->data);
    }

    static size_t heightNode(NodeT *node) {
        if (!node)
            return 0;
        return 1 + std::max(heightNode(node->left), heightNode(node->right));
    }

    struct BalanceInfo {
        size_t height;
        bool balanced;
    };

    static BalanceInfo isBalancedOpt(NodeT *node) {
        if (!node)
            return {0, true};

        auto l = isBalancedOpt(node->left);
        if (!l.balanced)
            return {0, false};

        auto r = isBalancedOpt(node->right);
        if (!r.balanced)
            return {0, false};

        if (std::abs((int)l.height - (int)r.height) > 1)
            return {0, false};

        return {1 + std::max(l.height, r.height), true};
    }

    static size_t maxDiameterNode(NodeT *node, size_t &diameter) {
        if (!node)
            return 0;

        size_t lh = maxDiameterNode(node->left, diameter);
        size_t rh = maxDiameterNode(node->right, diameter);

        diameter = std::max(diameter, lh + rh);
        return 1 + std::max(lh, rh);
    }

    static T maxSumPathNode(NodeT *node, T &max_sum) {
        if (!node)
            return T{0};

        T l = std::max(T{0}, maxSumPathNode(node->left, max_sum));
        T r = std::max(T{0}, maxSumPathNode(node->right, max_sum));

        max_sum = std::max(max_sum, l + r + node->data);
        return std::max(l, r) + node->data;
    }
};

// ---------------- insert (level-order) ----------------
template <typename T, typename Compare> void BinaryTree<T, Compare>::insert(const T &data) {
    NodeT *new_node = new NodeT(data);

    if (!root_) {
        root_ = new_node;
        return;
    }

    std::queue<NodeT *> q;
    q.push(root_);

    while (!q.empty()) {
        NodeT *current = q.front();
        q.pop();

        if (current->left) {
            q.push(current->left);
        } else {
            current->left = new_node;
            return;
        }

        if (current->right) {
            q.push(current->right);
        } else {
            current->right = new_node;
            return;
        }
    }
}
// --------------- Traversals ---------------
// --------------- Preorder (Iterative) ---------------
template <typename T, typename Compare>
void BinaryTree<T, Compare>::preOrderIter(void (*visit)(const T &)) const {
    if (!root_)
        return;

    std::stack<NodeT *> st;
    st.push(root_);

    while (!st.empty()) {
        NodeT *node = st.top();
        st.pop();

        visit(node->data);

        if (node->right)
            st.push(node->right);
        if (node->left)
            st.push(node->left);
    }
}

// --------------- Preorder (recursive) ---------------
template <typename T, typename Compare>
template <typename Visit>
void BinaryTree<T, Compare>::preOrderRecursive(Visit visit) const {
    preorderNode(root_, visit);
}

// --------------- Inorder (Iterative) ---------------

template <typename T, typename Compare>
template <typename Visit>
void BinaryTree<T, Compare>::inOrderIter(Visit visit) const {
    std::stack<NodeT *> st;
    NodeT *current = root_;

    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        visit(current->data);
        current = current->right;
    }
}

// --------------- Inorder (Recursize) ---------------

template <typename T, typename Compare>
template <typename Visit>
void BinaryTree<T, Compare>::inOrderRecursive(Visit visit) const {
    inorderNode(root_, visit);
}

// --------------- Postorder (Iterative – two stacks) ---------------

template <typename T, typename Compare>
template <typename Visit>
void BinaryTree<T, Compare>::postOrderIter(Visit visit) const {
    if (!root_)
        return;

    std::stack<NodeT *> s1, s2;
    s1.push(root_);

    while (!s1.empty()) {
        NodeT *n = s1.top();
        s1.pop();
        s2.push(n);

        if (n->left)
            s1.push(n->left);
        if (n->right)
            s1.push(n->right);
    }

    while (!s2.empty()) {
        visit(s2.top()->data);
        s2.pop();
    }
}

// --------------- Postorder (Recursive) ---------------

template <typename T, typename Compare>
template <typename Visit>
void BinaryTree<T, Compare>::postOrderRecursive(Visit visit) const {
    postorderNode(root_, visit);
}

// --------------- Unified Traversal (Pre / In / Post) ---------------

template <typename T, typename Compare>
template <typename Visit>
void BinaryTree<T, Compare>::traversalAll(Visit visit) const {
    if (!root_)
        return;

    struct Frame {
        NodeT *node;
        Order state;
    };

    std::vector<Frame> stack;
    stack.push_back({root_, Order::Pre});

    while (!stack.empty()) {
        auto &top = stack.back();

        switch (top.state) {
        case Order::Pre:
            visit(top.node->data, Order::Pre);
            top.state = Order::In;
            if (top.node->left)
                stack.push_back({top.node->left, Order::Pre});
            break;

        case Order::In:
            visit(top.node->data, Order::In);
            top.state = Order::Post;
            if (top.node->right)
                stack.push_back({top.node->right, Order::Pre});
            break;

        case Order::Post:
            visit(top.node->data, Order::Post);
            stack.pop_back();
            break;
        }
    }
}

// --------------- Level Order ---------------

template <typename T, typename Compare>
template <typename Visit>
void BinaryTree<T, Compare>::levelOrder(Visit visit) const {
    if (!root_)
        return;

    std::queue<NodeT *> q;
    q.push(root_);

    while (!q.empty()) {
        NodeT *cur = q.front();
        q.pop();

        visit(cur->data);

        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
    }
}
