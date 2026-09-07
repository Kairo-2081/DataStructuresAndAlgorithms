#define BINOMIAL_HEAP_H

#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
    int key;
    int degree;
    Node *parent;
    Node *child;
    Node *sibling;
    
    Node()
    {
        this->key=0;
        this->degree=0;
        this->parent=nullptr;
        this->child=nullptr;
        this->sibling=nullptr;
    }

    Node(int k)
    {
        this->key=k;
        this->degree=0;
        this->parent=nullptr;
        this->child=nullptr;
        this->sibling=nullptr;
    }

};

extern unordered_map<int,Node*>nodes;

class BinomialHeap
{
    private:
    Node *head;
    int size;

    void linkTrees(Node *parent,Node *child)
    {
        child->parent=parent;
        child->sibling=parent->child;
        parent->child=child;
        parent->degree++;
    }

    Node *mergeRoots(Node *root1,Node *root2)
    {
        if(root1==nullptr)
        {
            return root2;
        }
        if(root2==nullptr)
        {
            return root1;
        }
        Node *newHead=nullptr;
        Node *tail=nullptr;
        if(root1->degree<=root2->degree)
        {
            newHead=root1;
            root1=root1->sibling;
        }
        else
        {
            newHead=root2;
            root2=root2->sibling;
        }
        tail=newHead;
        while(root1!=nullptr && root2!=nullptr)
        {
            if(root1->degree<=root2->degree)
            {
                tail->sibling=root1;
                root1=root1->sibling;
            }
            else
            {
                tail->sibling=root2;
                root2=root2->sibling;
            }
            tail=tail->sibling;
        }
        if(root1!=nullptr)
        {
            tail->sibling=root1;
        }
        else
        {
            tail->sibling=root2;
        }
        return newHead;
    }
    
    Node* unionHelper(Node *a1, Node *a2, bool verbose = false)
    {
        if(a1==nullptr)
        {
            return a2;
        }
        if(a2==nullptr)
        {
            return a1;
        }
        Node *newHead=mergeRoots(a1,a2);
        if(newHead==nullptr)
        {
            return nullptr;
        }
        Node *previous=nullptr;
        Node *current=newHead;
        Node *next=current->sibling;

        while(next!=nullptr)
        {
            if((current->degree != next->degree) || (next->sibling!=nullptr && next->sibling->degree==current->degree))
            {
                previous=current;
                current=next;
            }
            else if(current->key<=next->key)
            {
                current->sibling=next->sibling;
                if (verbose) {
                    cout << "Linking B" << current->degree << " (parent " << current->key 
                         << ") -> B" << (current->degree + 1) << " (child " << next->key << ")\n";
                }
                linkTrees(current,next);
            }
            else 
            {
                if(previous==nullptr)
                {
                    newHead=next;
                }
                else
                {
                    previous->sibling=next;
                }
                if (verbose) {
                    cout << "Linking B" << next->degree << " (parent " << next->key 
                         << ") -> B" << (next->degree + 1) << " (child " << current->key << ")\n";
                }
                linkTrees(next,current);
                current=next;
            }
            next=current->sibling;
        }
        return newHead;
    }

    void visualizeTree(Node* node, string prefix, bool isLast, bool isRoot = false) 
    {
        if (!node) return;
        cout << prefix;
        if (!isRoot) 
        {
            cout << (isLast ? "\\-- " : "+-- ");
        }
        
        cout << node->key << (isRoot ? " [root, deg " : " [deg ") << node->degree << "]\n";
        
        Node* child = node->child;
        while (child) 
        {
            visualizeTree(child, prefix + (isRoot ? "" : (isLast ? "    " : "│   ")), child->sibling == nullptr, false);
            child = child->sibling;
        }
    }

    bool isHeapOrderValid(Node* root) 
    {
        if (!root) return true;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) 
        {
            Node* curr = q.front(); 
            q.pop();
            Node* child = curr->child;
            while (child) 
            {
                if (child->key < curr->key) return false;
                q.push(child);
                child = child->sibling;
            }
        }
        return true;
    }

    bool validateEntireHeap() 
    {
        Node* curr = this->head;
        while (curr) 
        {
            if (!isHeapOrderValid(curr)) return false;
            curr = curr->sibling;
        }
        return true;
    }

    string getLevelOrderString(Node* root) 
    {
        if (!root) return "";
        string res = "    Level-order (sorted per level): ";
        vector<vector<int>> levels;
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        while (!q.empty()) 
        {
            auto nodeset = q.front(); 
            q.pop();
            Node* node = nodeset.first;
            int depth = nodeset.second;
            if (depth >= levels.size()) levels.push_back(vector<int>());
            levels[depth].push_back(node->key);
            
            Node* child = node->child;
            while (child) 
            {
                q.push({child, depth + 1});
                child = child->sibling;
            }
        }
        for (size_t i = 0; i < levels.size(); i++) 
        {
            sort(levels[i].begin(), levels[i].end());
            res += "L" + to_string(i) + ":{";
            for (size_t j = 0; j < levels[i].size(); j++) 
            {
                res += to_string(levels[i][j]) + (j + 1 < levels[i].size() ? "," : "");
            }
            res += "} ";
        }
        return res;
    }

    string getBinaryRepresentation(int n)
    {
        if (n == 0) return "0";
        string bin = "";
        while (n > 0)
        {
            bin = to_string(n % 2) + bin;
            n /= 2;
        }
        return bin;
    }

    public:
    BinomialHeap()
    {
        this->head=nullptr;
        this->size=0;
    }
    BinomialHeap(Node *head)
    {
        this->head=head;
        this->size=1;
    }
    void insert(int k)
    {
        Node *newNode=new Node(k);
        nodes[k]=newNode;
        this->head=unionHelper(this->head,newNode);
        this->size++;
    }
    void findMin()
    {
        if(this->head==nullptr)
        {
            cout<<"Minimum key not found"<<endl;
            return;
        }
        else
        {
            Node *current=this->head;
            int minimum=current->key;
            while(current!=nullptr)
            {
                if(current->key<minimum)
                {
                    minimum=current->key;
                }
                current=current->sibling;
            }
            cout<<"Find Min returned: "<<minimum<<endl;
        }
    }

    int extractMin()
    {
        if(head==nullptr)
        {
            return -1;
        }
        else
        {
            Node *minimumNode=this->head;
            Node *minimumPrevious=nullptr;
            Node *current=this->head->sibling;
            Node *previous=this->head;
            while(current!=nullptr)
            {
                if(current->key<minimumNode->key)
                {
                    minimumNode=current;
                    minimumPrevious=previous;
                }
                previous=current;
                current=current->sibling;
            }
            int minimumKey=minimumNode->key;
            if(minimumPrevious!=nullptr)
            {
                minimumPrevious->sibling=minimumNode->sibling;
            }
            else
            {
                head=minimumNode->sibling;
            }
            Node *child=minimumNode->child;
            Node *reverseChild=nullptr;
            while(child!=nullptr)
            {
                Node *nextChild=child->sibling;
                child->sibling=reverseChild;
                child->parent=nullptr;
                reverseChild=child;
                child=nextChild;
            }
            this->head=this->unionHelper(this->head,reverseChild);
            this->size--;
            nodes.erase(minimumKey);
            delete minimumNode;
            return minimumKey;
        }
    }

    void decreaseKey(int oldKey, int newKey)
    {
        if(nodes.find(oldKey)==nodes.end())
        {
            return;
        }
        else
        {
            Node *node=nodes[oldKey];
            nodes.erase(oldKey);
            node->key=newKey;
            nodes[newKey]=node;

            while(node->parent!=nullptr && node->key<node->parent->key)
            {
                int temp=node->key;
                node->key=node->parent->key;
                node->parent->key=temp;
                nodes[node->key]=node;
                nodes[node->parent->key]=node->parent;
                node=node->parent;
            }
        }
    }

    void removeKey(int key)
    {
        static int smallest=-2e9;
        decreaseKey(key,smallest);
        extractMin();
        smallest--;
    }

    void unionFunction(BinomialHeap &other, bool verbose = false)
    {
        this->head=this->unionHelper(this->head, other.head, verbose);
        this->size=this->size+other.size;
        other.head=nullptr;
        other.size=0;
    }

    void printer(int id)
    {
        cout<<"Printing Binomial Heap H"<<id<<endl;
        cout<<"Heap size: "<<this->size<<endl;
        if(this->size==0)
        {
            cout<<"Heap H"<<id<<" is empty"<<endl;
            return;
        }
        else
        {
            Node *current=this->head;
            while(current!=nullptr)
            {
                cout<<"Binomial Tree, B"<<current->degree<<endl;
                vector<vector<int>>level;
                queue<pair<Node*,int>>q;
                q.push({current,0});
                while(q.empty()!=true)
                {
                    auto nodeset=q.front();
                    q.pop();
                    Node *node=nodeset.first;
                    int depth=nodeset.second;
                    if(depth>=level.size())
                    {
                        level.push_back(vector<int>());
                    }
                    level[depth].push_back(node->key);
                    Node *child=node->child;
                    while(child!=nullptr)
                    {
                        q.push({child,depth+1});
                        child=child->sibling;
                    }
                }
                for(int i=0;i<level.size();i++)
                {
                    sort(level[i].begin(),level[i].end());
                    cout<<"Level "<<i<<":";
                    for(int k:level[i])
                    {
                        cout<<" "<<k;      
                    }
                    cout<<endl;
                }
                current=current->sibling;
            }
        }
    }

    void visualizeHeap(int h, string label = "") 
    {
        cout << ">>> Visualizing Heap H" << h << " " << label << "(Heap size: " << this->size << ")\n";
        if (this->size == 0 || this->head == nullptr) 
        {
            cout << "    (empty heap)\n    Binary size: 0 -> no trees\n";
            return;
        }

        string binRep = getBinaryRepresentation(this->size);
        cout << "    Binary: " << binRep << "  => trees: ";
        
        int minKey = this->head->key;
        int minDegree = this->head->degree;
        int maxDegree = 0;
        int treeCount = 0;
        
        Node* curr = this->head;
        while (curr) 
        {
            cout << "B" << curr->degree << "  ";
            if (curr->key < minKey) 
            {
                minKey = curr->key;
                minDegree = curr->degree;
            }
            if (curr->degree > maxDegree) maxDegree = curr->degree;
            treeCount++;
            curr = curr->sibling;
        }
        cout << "\n    Minimum key: " << minKey << " (in B" << minDegree << ")\n";
        cout << "    Number of trees: " << treeCount << ", max degree: " << maxDegree << "\n";
        cout << "    Heap-order valid: " << (validateEntireHeap() ? "YES" : "NO") << "\n\n";

        curr = this->head;
        while (curr) 
        {
            int treeSize = 1 << curr->degree; // 2^degree
            cout << "    --- Binomial Tree B" << curr->degree << " (root " << curr->key << ", size " << treeSize << ") ---\n";
            cout << "    ";
            visualizeTree(curr, "    ", true, true);
            cout << getLevelOrderString(curr) << "\n\n";
            curr = curr->sibling;
        }
    }

    void printRootDegrees(Node* head, string label)
    {
        cout << "  Initial root degrees " << label << ": ";
        Node* curr = head;
        if (!curr) cout << "empty ";
        while(curr)
        {
            cout << "B" << curr->degree << "(root " << curr->key << ") ";
            curr = curr->sibling;
        }
        cout << "\n";
    }

    void visualizeUnion(int dest_id, int src_id, BinomialHeap &other)
    {
        cout << "UNION OPERATION: H" << dest_id << " <- Union(H" << dest_id << ", H" << src_id << ")\n";
        this->visualizeHeap(dest_id, "(before union) ");
        other.visualizeHeap(src_id, "(before union) ");
        
        if (other.size == 0) {
            cout << "H" << src_id << " empty => result is H" << dest_id << " (moving).\n\n";
        } else if (this->size == 0) {
            cout << "H" << dest_id << " empty => result is H" << src_id << " (moving).\n\n";
        } else {
            printRootDegrees(this->head, "dest");
            printRootDegrees(other.head, "src");
            cout << "Merging root lists in increasing degree order:\n";
        }

        // To achieve step-by-step verbose output, unionHelper[cite: 1] must be slightly modified.
        // If 'verbose' is true inside unionHelper, print: 
        // "  Degree X: link BX(key1) + BX(key2) => BX+1 root min_key (carry)"
        // immediately prior to calling linkTrees().
        this->unionFunction(other, true); 
        
        cout << "Union complete. Final heap:\n";
        this->visualizeHeap(dest_id, "(after union) ");
        cout << "UNION VISUALIZATION END\n\n";
    }


    void printStatistics(int h) 
    {
        cout << "=== Structural Statistics for Heap H" << h << " ===\n";
        cout << "Total Nodes (Size): " << this->size << "\n";
        
        if (!this->head) 
        {
            cout << "Forest composition: Empty\n";
            cout << "Max Tree Depth: 0\n";
            cout << "=======================================\n";
            return;
        }

        vector<int> orders;
        int maxDepth = 0;
        Node* curr = this->head;
        
        while (curr) 
        {
            orders.push_back(curr->degree);
            if (curr->degree > maxDepth) 
            {
                maxDepth = curr->degree;
            }
            curr = curr->sibling;
        }

        cout << "Binomial Trees Present (Orders): ";
        for (size_t i = 0; i < orders.size(); i++) 
        {
            cout << "B" << orders[i] << (i + 1 < orders.size() ? ", " : "");
        }
        cout << "\n";
        cout << "Max Tree Order / Depth: B" << maxDepth << " (Height: " << maxDepth << ")\n";
        cout << "=======================================\n";
    }
};


