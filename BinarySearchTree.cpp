#include <iostream>
#include <set>
#include <queue>

using namespace std;

class BST
{
private:
    struct node
    {
        int value;
        node* left;
        node* right;
    };
public:
    node* root;
    set<int> s;
    int sum;

    BST()
    {
        this->root = nullptr;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    node* insert(int x, node* t)
    {
        if (t == nullptr)
        {
            t = new node;
            t->value = x;
            t->left = t->right = nullptr;
        }
        else if (x < t->value)
            t->left = insert(x, t->left);
        else if (x > t->value)
            t->right = insert(x, t->right);
        return t;
    }

    void restrict(int a, int b, node* t)
    {
        if (t == nullptr)
            return;
        restrict(a, b, t->left);
        if (t->value < a || t->value > b)
            remove(t->value, root);
        restrict(a, b, t->right);
    }

    node* findMin(node* t)
    {
        if (t == nullptr) return nullptr;
        else if (t->left == nullptr) return t;
        else return findMin(t->left);
    }

    node* remove(int x, node* t) {
        node* temp;
        if (t == nullptr) return nullptr;
        else if (x > t->value) t->right = remove(x, t->right);
        else if (x < t->value) t->left  = remove(x, t->left);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->right = remove(t->value, t->right);
            t->value = temp->value;
        }
        else
        {
            temp = t;
            if (t->left == nullptr) t = t->right;
            else if (t->right == nullptr) t = t->left;
        }
        return t;
    }

    bool findPair(node* t)
    {
        if (t == nullptr)
            return false;
        if (findPair(t->left) == true)
            return true;
        if (s.find(sum - t->value) != s.end())
        {
            cout << (sum - t->value) << " " << t->value;
            exit(0);
        }
        s.insert(t->value);
        return findPair(t->right);
    }
};

int main()
{
    BST* bst = new BST();

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        bst->insert(value);
    }

    int a, b, k;
    cin >> a >> b >> k;
    bst->sum = k;
    bst->restrict(a, b, bst->root);

    if (bst->findPair(bst->root) == false)
        cout << "NIE ZNALEZIONO";

    return 0;
}
