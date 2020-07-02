#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    string key;
    Node* left;
    Node* right;
    vector<string> list;

    Node(string key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class SplayTree
{
private:
    Node* root = nullptr;
public:
    void insert(string key)
    {
        if (root == nullptr) root = new Node(key);
        root = splay(key);
        if (root->key == key) return;

        Node* temp = new Node(key);
        if (root->key <= key)
        {
            temp->left = root;
            temp->right = root->right;
            root->right = nullptr;
        }
        else
        {
            temp->right = root;
            temp->left = root->left;
            root->left = nullptr;
        }
        this->root = temp;
    }

    Node* search(string key)
    {
        return search(this->root, key);
    }

    Node* search(Node* root, string key)
    {
        if (root == nullptr || root->key == key)
            return root;
        if (root->key < key)
            return search(root->right, key);
        else
            return search(root->left, key);
    }
private:
    Node* zig_rotation(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* zag_rotation(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(string key)
    {
        return splay(root, key);
    }

    Node* splay(Node* root, string key)
    {
        if (root == nullptr || root->key == key) return root;

        if (root->key <= key)
        {
            if (root->right == nullptr) return root;
            if (root->right->key > key)
            {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = zig_rotation(root->right);
            }
            else if (root->right->key < key)
            {
                root->right->right = splay(root->right->right, key);
                root = zag_rotation(root);
            }

            if (root->right != nullptr) return zag_rotation(root);
            else return root;
        }
        else
        {
            if (root->left == nullptr) return root;
            if (root->left->key > key)
            {
                root->left->left = splay(root->left->left, key);
                root = zig_rotation(root);
            }
            else if (root->left->key < key)
            {
                root->left->right = splay(root->left->right, key);

                if (root->left->right != nullptr)
                    root->left = zag_rotation(root->left);
            }

            if (root->left != nullptr) return zig_rotation(root);
            else return root;
        }
    }
};


int main()
{
    ios::sync_with_stdio(false);

    int count;
    cin >> count;
    cin.ignore();

    SplayTree A;
    SplayTree B;

    string nazwa_zespolu, tytul_kasety;
    string action;

    for (int i = 0; i < count; i++)
    {
        getline(cin, action);

        if (action == "d") // dodanie do bazy nowej kasety
        {
            getline(cin, nazwa_zespolu);
            getline(cin, tytul_kasety);

            if (A.search(nazwa_zespolu) == nullptr)
            {
                A.insert(nazwa_zespolu);
            }
            A.search(nazwa_zespolu)->list.push_back(tytul_kasety);

            if (B.search(tytul_kasety) == nullptr)
            {
                B.insert(tytul_kasety);
            }
            B.search(tytul_kasety)->list.push_back(nazwa_zespolu);
        }
        else if (action == "w") // wypisanie w osobnych liniach tytułów kaset podanego zespołu
        {
            getline(cin, nazwa_zespolu);

            Node* result = A.search(nazwa_zespolu);
            if (result != nullptr)
            {
                for (unsigned long long i = 0; i < result->list.size(); i++) {
                    cout << result->list.at(i) << endl;
                }
            }
        }
        else if (action == "z") // wypisanie w osobnych liniach zespołów, które nagrały kasetę o podanym tytule
        {
            getline(cin, tytul_kasety);

            Node* result = B.search(tytul_kasety);
            if (result != nullptr)
            {
                for (unsigned long long i = 0; i < result->list.size(); i++) {
                    cout << result->list.at(i) << endl;
                }
            }
        }
    }

    return 0;
}
