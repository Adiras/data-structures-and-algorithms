#include <iostream>
#include <list>
#include <string>

using namespace std;


struct TableEntry
{
    string key;
    list<string> data;

    TableEntry(string key)
    {
        this->key = key;
    }
};

class HashTable
{
private:
    int capacity;
    list<TableEntry*>* table;
public:
    HashTable(int initialCapacity)
    {
        capacity = initialCapacity;
        table = new list<TableEntry*>[capacity];
    }

    void insert(string key)
    {
        int index = hashCode(key);
        table[index].push_back(new TableEntry(key));
    }

    TableEntry* get(string key)
    {
        int i = hashCode(key);
        for (auto& entry : table[i])
        {
            if (entry->key == key) return entry;
        }
        return nullptr;
    }

    int hashCode(string key)
    {
        int hash = 0;
        for (size_t i = 0; i < key.length(); i++)
            hash += key[i] * (key[i] + 8);
        return hash % capacity;
    }
};

int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    cin.ignore();

    string line;
    string nazwa_zespolu, tytul_kasety;

    HashTable authors(n);
    HashTable titles(n);

    for (int i = 0; i < n; i++)
    {
        getline(cin, line);

        if (line == "d")
        {
            getline(cin, nazwa_zespolu);
            getline(cin, tytul_kasety);


            if (authors.get(nazwa_zespolu) == nullptr) {
                authors.insert(nazwa_zespolu);
            }
            authors.get(nazwa_zespolu)->data.push_back(tytul_kasety);

            if (titles.get(tytul_kasety) == nullptr) {
                titles.insert(tytul_kasety);
            }
            titles.get(tytul_kasety)->data.push_back(nazwa_zespolu);
        }
        if (line == "w")
        {
            getline(cin, nazwa_zespolu);

            TableEntry* result = authors.get(nazwa_zespolu);
            if (result != nullptr)
            {
                for (string entry : result->data)
                {
                    cout << entry << endl;
                }
            }
        }
        if (line == "z")
        {
            getline(cin, tytul_kasety);

            TableEntry* result = titles.get(tytul_kasety);
            if (result != nullptr)
            {
                for (string entry : result->data)
                {
                    cout << entry << endl;
                }
            }
        }
    }

    return 0;
}
