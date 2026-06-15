#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

// ================= LICENSE =================

struct License
{
    int id;
    string artist;
    string owner;
};

// ================= MEDIA =================

struct Media
{
    string name;
    int transactions;
};

// ================= GLOBAL STRUCTURES =================

// Hash Table for fast license verification
unordered_map<int, License> ledger;

// Stack for revocation history
stack<string> revocationLog;

// Queue for transfer requests
queue<int> transferQueue;

// Dynamic media list
vector<Media> mediaList;
// ================= B-TREE =================

const int T = 3;

class BTreeNode
{
public:
    int keys[2 * T - 1];
    BTreeNode* children[2 * T];
    int n;
    bool leaf;

    BTreeNode(bool leaf)
    {
        this->leaf = leaf;
        n = 0;

        for(int i = 0; i < 2 * T; i++)
            children[i] = NULL;
    }

    void traverse()
    {
        int i;

        for(i = 0; i < n; i++)
        {
            if(!leaf)
                children[i]->traverse();

            cout << keys[i] << " ";
        }

        if(!leaf)
            children[i]->traverse();
    }

    BTreeNode* search(int k)
    {
        int i = 0;

        while(i < n && k > keys[i])
            i++;

        if(i < n && keys[i] == k)
            return this;

        if(leaf)
            return NULL;

        return children[i]->search(k);
    }

    void splitChild(int i, BTreeNode* y)
    {
        BTreeNode* z = new BTreeNode(y->leaf);

        z->n = T - 1;

        for(int j = 0; j < T - 1; j++)
            z->keys[j] = y->keys[j + T];

        if(!y->leaf)
        {
            for(int j = 0; j < T; j++)
                z->children[j] = y->children[j + T];
        }

        y->n = T - 1;

        for(int j = n; j >= i + 1; j--)
            children[j + 1] = children[j];

        children[i + 1] = z;

        for(int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        keys[i] = y->keys[T - 1];

        n++;
    }

    void insertNonFull(int k)
    {
        int i = n - 1;

        if(leaf)
        {
            while(i >= 0 && keys[i] > k)
            {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
            n++;
        }
        else
        {
            while(i >= 0 && keys[i] > k)
                i--;

            if(children[i + 1]->n == 2 * T - 1)
            {
                splitChild(i + 1, children[i + 1]);

                if(keys[i + 1] < k)
                    i++;
            }

            children[i + 1]->insertNonFull(k);
        }
    }
};

class BTree
{
public:
    BTreeNode* root;

    BTree()
    {
        root = NULL;
    }

    void traverse()
    {
        if(root != NULL)
            root->traverse();
    }

    BTreeNode* search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k)
    {
        if(root == NULL)
        {
            root = new BTreeNode(true);

            root->keys[0] = k;
            root->n = 1;
        }
        else
        {
            if(root->n == 2 * T - 1)
            {
                BTreeNode* s = new BTreeNode(false);

                s->children[0] = root;

                s->splitChild(0, root);

                int i = 0;

                if(s->keys[0] < k)
                    i++;

                s->children[i]->insertNonFull(k);

                root = s;
            }
            else
            {
                root->insertNonFull(k);
            }
        }
    }
};

BTree licenseRegistry;
void merge(vector<Media>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Media> L(n1);
    vector<Media> R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while(i < n1 && j < n2)
    {
        if(L[i].transactions > R[j].transactions)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<Media>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
// ================= GRAPH =================

const int V = 10;

vector<pair<int,int>> graph[V];

void addEdge(int u, int v, int cost)
{
    graph[u].push_back({v, cost});
}

void dijkstra(int source)
{
    vector<int> dist(V, INT_MAX);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for(auto edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if(dist[u] != INT_MAX &&
               dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nMinimum Royalty Route Costs:\n";

    for(int i = 0; i < V; i++)
    {
        if(dist[i] != INT_MAX)
        {
            cout << "Node "
                 << i
                 << " -> "
                 << dist[i]
                 << endl;
        }
    }
}
// ================= STORAGE DIVIDER =================

string compressDescription(string text)
{
    if(text.empty())
        return "";

    string compressed = "";

    int count = 1;

    for(int i = 0; i < text.length(); i++)
    {
        while(i < text.length() - 1 &&
              text[i] == text[i + 1])
        {
            count++;
            i++;
        }

        compressed += to_string(count);
        compressed += text[i];

        count = 1;
    }

    return compressed;
}
// ================= HELPER FUNCTIONS =================

void displayTransferQueue()
{
    queue<int> temp = transferQueue;

    if(temp.empty())
    {
        cout << "No Pending Requests\n";
        return;
    }

    cout << "\nPending Transfer Requests:\n";

    while(!temp.empty())
    {
        cout << temp.front() << endl;
        temp.pop();
    }
}

void displayRevocationHistory()
{
    stack<string> temp = revocationLog;

    if(temp.empty())
    {
        cout << "No Approval History\n";
        return;
    }

    cout << "\nApproval History:\n";

    while(!temp.empty())
    {
        cout << temp.top() << endl;
        temp.pop();
    }
}

void displayMedia()
{
    if(mediaList.empty())
    {
        cout << "No Media Records Found\n";
        return;
    }

    mergeSort(mediaList, 0, mediaList.size() - 1);

    cout << "\nMedia Ranked By Transaction Volume\n";

    for(auto m : mediaList)
    {
        cout << m.name
             << " -> "
             << m.transactions
             << endl;
    }
}
int main()
{
    int choice;

    do
    {
        cout << "\n\n===== ROYALCHAIN COPYRIGHT MANAGEMENT SYSTEM =====\n";

        cout << "1. Add License\n";
        cout << "2. Search License\n";
        cout << "3. Display Registry\n";

        cout << "4. Add Approval\n";
        cout << "5. Revoke Approval\n";
        cout << "6. Display Approval History\n";

        cout << "7. Add Transfer Request\n";
        cout << "8. Display Transfer Requests\n";
        cout << "9. Process Transfer Request\n";

        cout << "10. Add Royalty Connection\n";
        cout << "11. Find Cheapest Royalty Route\n";

        cout << "12. Verify License\n";

        cout << "13. Add Media\n";
        cout << "14. Display Ranked Media\n";

        cout << "15. Compress Asset Description\n";

        cout << "0. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
                        case 1:
            {
                License l;

                cout << "Enter License ID: ";
                cin >> l.id;

                cout << "Enter Artist Name: ";
                cin >> l.artist;

                cout << "Enter Owner Name: ";
                cin >> l.owner;

                ledger[l.id] = l;
                licenseRegistry.insert(l.id);

                cout << "License Added Successfully\n";
                break;
            }

            case 2:
            {
                int id;

                cout << "Enter License ID: ";
                cin >> id;

                if(licenseRegistry.search(id))
                {
                    cout << "\nLicense Found\n";
                    cout << "Artist : "
                         << ledger[id].artist
                         << endl;

                    cout << "Owner  : "
                         << ledger[id].owner
                         << endl;
                }
                else
                {
                    cout << "License Not Found\n";
                }

                break;
            }

            case 3:
            {
                cout << "\nLicense Registry (B-Tree):\n";
                licenseRegistry.traverse();
                cout << endl;

                break;
            }

            case 4:
            {
                string approval;

                cout << "Enter Approval Name: ";
                cin >> approval;

                revocationLog.push(approval);

                cout << "Approval Added\n";

                break;
            }

            case 5:
            {
                if(!revocationLog.empty())
                {
                    cout << "Revoked Approval: "
                         << revocationLog.top()
                         << endl;

                    revocationLog.pop();
                }
                else
                {
                    cout << "No Approvals Available\n";
                }

                break;
            }

            case 6:
            {
                displayRevocationHistory();
                break;
            }

            case 7:
            {
                int id;

                cout << "Enter License ID: ";
                cin >> id;

                transferQueue.push(id);

                cout << "Transfer Request Added\n";

                break;
            }

            case 8:
            {
                displayTransferQueue();
                break;
            }

            case 9:
            {
                if(!transferQueue.empty())
                {
                    cout << "Processed License ID: "
                         << transferQueue.front()
                         << endl;

                    transferQueue.pop();
                }
                else
                {
                    cout << "No Pending Requests\n";
                }

                break;
            }

            case 10:
            {
                int u, v, w;

                cout << "Enter Source Node: ";
                cin >> u;

                cout << "Enter Destination Node: ";
                cin >> v;

                cout << "Enter Cost: ";
                cin >> w;

                addEdge(u, v, w);

                cout << "Royalty Connection Added\n";

                break;
            }

            case 11:
            {
                int source;

                cout << "Enter Source Node: ";
                cin >> source;

                dijkstra(source);

                break;
            }

            case 12:
            {
                int id;

                cout << "Enter License ID: ";
                cin >> id;

                if(ledger.find(id) != ledger.end())
                {
                    cout << "\nLicense Verified\n";

                    cout << "Artist : "
                         << ledger[id].artist
                         << endl;

                    cout << "Owner  : "
                         << ledger[id].owner
                         << endl;
                }
                else
                {
                    cout << "License Not Found\n";
                }

                break;
            }

            case 13:
            {
                Media m;

                cout << "Enter Media Name: ";
                cin >> m.name;

                cout << "Enter Transaction Volume: ";
                cin >> m.transactions;

                mediaList.push_back(m);

                cout << "Media Added Successfully\n";

                break;
            }

            case 14:
            {
                displayMedia();
                break;
            }

            case 15:
            {
                string description;

                cout << "Enter Description: ";
                cin >> description;

                cout << "\nOriginal   : "
                     << description
                     << endl;

                cout << "Compressed : "
                     << compressDescription(description)
                     << endl;

                break;
            }

            case 0:
            {
                cout << "Exiting Program...\n";
                break;
            }

            default:
            {
                cout << "Invalid Choice\n";
            }
        }

    } while(choice != 0);

    return 0;
}