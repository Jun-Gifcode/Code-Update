#include <iostream>
#include <string> // For string handling
#include <iomanip> // For formatted output
#include <limits> // For input validation
#include <chrono> // For performance measurement
#include <vector> // For dynamic arrays
#include <queue> // For waiting queue
#include <stack> // For undo operations
#include <list> // For hash table chaining
#include <algorithm> // For sorting
#include <cctype> // For character checks

using namespace std;
using namespace std::chrono;

void clearInput() {// Clear input buffer to avoid infinite loop on invalid input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getIntInput(const string& prompt) {// Get integer input with validation
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) { clearInput(); return value; }
        cout << "  [!] Invalid input. Please enter a number.\n";
        clearInput();
    }
}

string getStringInput(const string& prompt) {// Get string input (including spaces)
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void printLine(char c = '-', int len = 78) {// Print a line of characters for formatting
    cout << string(len, c) << "\n";
}

void printHeader(const string& title) {// Print a formatted header with title
    cout << "\n";
    printLine('=');
    cout << "  " << title << "\n";
    printLine('=');
}

struct Patient {// Structure to hold patient information
    int    id;
    string name;
    int    age;
    string gender;
    string department;
    string condition;
};

class PatientArray {// Class to manage an array of patients
private:
    static const int MAX = 100;
    Patient records[MAX];
    int     count;

    int findIndexById(int id) const { // Find index of patient by ID, return -1 if not found
        for (int i = 0; i < count; ++i)
            if (records[i].id == id) return i;
        return -1;
    }

public:
    PatientArray() : count(0) {}

    // Seed with 10 sample records (assessment requirement)
    void loadSampleData() {
        Patient sample[10] = {
            {1001, "Ahmad Zaki",     34, "Male",   "Cardiology",  "Hypertension"},
            {1002, "Siti Nurhaliza", 28, "Female", "Neurology",   "Migraine"},
            {1003, "Lim Wei Jie",    45, "Male",   "Surgery",     "Appendicitis"},
            {1004, "Priya Raman",    52, "Female", "Radiology",   "Fracture"},
            {1005, "Daniel Tan",     19, "Male",   "Emergency",   "Flu"},
            {1006, "Nur Aisyah",     61, "Female", "Cardiology",  "Arrhythmia"},
            {1007, "Kumar Raj",      38, "Male",   "Pharmacy",    "Diabetes"},
            {1008, "Chong Mei Ling", 47, "Female", "Neurology",   "Epilepsy"},
            {1009, "Hafiz Rahman",   25, "Male",   "Surgery",     "Hernia"},
            {1010, "Tan Li Wen",     55, "Female", "Radiology",   "Tumor Screening"}
        };
        for (int i = 0; i < 10; ++i) records[i] = sample[i];
        count = 10;
    }

    void insertPatient() {// Insert a new patient record with input validation
        if (count >= MAX) { cout << "  [!] Array full.\n"; return; }
        Patient p;
        p.id = getIntInput("  Enter Patient ID   : ");
        if (findIndexById(p.id) != -1) {
            cout << "  [!] Duplicate Patient ID.\n"; return;
        }
        p.name       = getStringInput("  Enter Name         : ");
        p.age        = getIntInput  ("  Enter Age          : ");
        p.gender     = getStringInput("  Enter Gender       : ");
        p.department = getStringInput("  Enter Department   : ");
        p.condition  = getStringInput("  Enter Condition    : ");
        records[count++] = p;
        cout << "  [OK] Patient record inserted.\n";
    }

    void deletePatient() {// Delete a patient record by ID
        int id = getIntInput("  Enter Patient ID to delete: ");
        int idx = findIndexById(id);
        if (idx == -1) { cout << "  [!] Record not found.\n"; return; }
        for (int i = idx; i < count - 1; ++i) records[i] = records[i + 1];
        --count;
        cout << "  [OK] Record deleted.\n";
    }

    void searchPatient() const {// Search for a patient record by ID
        int id = getIntInput("  Enter Patient ID to search: ");
        int idx = findIndexById(id);
        if (idx == -1) { cout << "  [!] Record not found.\n"; return; }
        cout << "  [OK] Record found:\n";
        printOne(idx); // Print the found record
    }

    void updatePatient() {// Update an existing patient record by ID
        int id = getIntInput("  Enter Patient ID to update: ");
        int idx = findIndexById(id);
        if (idx == -1) { cout << "  [!] Record not found.\n"; return; }
        cout << "  (Leave blank to keep current value)\n"; // Using If statements to check if user input is empty
        string s;
        cout << "  New Name [" << records[idx].name << "]: "; getline(cin, s);
        if (!s.empty()) records[idx].name = s;
        cout << "  New Age [" << records[idx].age << "]: "; getline(cin, s);
        if (!s.empty()) records[idx].age = stoi(s);
        cout << "  New Gender [" << records[idx].gender << "]: "; getline(cin, s);
        if (!s.empty()) records[idx].gender = s;
        cout << "  New Department [" << records[idx].department << "]: "; getline(cin, s);
        if (!s.empty()) records[idx].department = s;
        cout << "  New Condition [" << records[idx].condition << "]: "; getline(cin, s);
        if (!s.empty()) records[idx].condition = s;
        cout << "  [OK] Record updated.\n";
    }

    void printOne(int i) const {// print a single patient record in a formatted way
        const Patient& p = records[i];
        cout << "  ID:" << p.id << " | " << p.name << " | Age:" << p.age
             << " | " << p.gender << " | " << p.department
             << " | " << p.condition << "\n";
    }

    void displayAll() const {// Display all patient records in a formatted table
        if (count == 0) { cout << "  [!] No patient records.\n"; return; }
        printLine();
        cout << left << setw(6)  << "ID"
                     << setw(20) << "Name"
                     << setw(5)  << "Age"
                     << setw(9)  << "Gender"
                     << setw(14) << "Department"
                     << "Condition\n";
        printLine();
        for (int i = 0; i < count; ++i) {
            cout << left << setw(6)  << records[i].id
                         << setw(20) << records[i].name
                         << setw(5)  << records[i].age
                         << setw(9)  << records[i].gender
                         << setw(14) << records[i].department
                         << records[i].condition << "\n";
        }
        printLine();
        cout << "  Total records: " << count << "\n";
    }

    // Accessors (used by Task 7, 8, 9)
    int     size() const { return count; } // Return number of records
    Patient get(int i) const { return records[i]; } // Return copy of patient at index i
    Patient* raw() { return records; } // Return raw pointer to array for sorting/searching
};

struct MedicalRecord {
    string date;
    string type;        // Consultation / Diagnosis / Treatment / Prescription
    string description;
    MedicalRecord* next;

    MedicalRecord(string d, string t, string desc)
        : date(d), type(t), description(desc), next(nullptr) {} // Constructor
};

class MedicalHistoryList { // Singly linked list for medical history records
private:
    MedicalRecord* head;

public:
    MedicalHistoryList() : head(nullptr) {}

    ~MedicalHistoryList() {
        while (head) {
            MedicalRecord* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void addRecord() {// Add a new medical record in chronological order
        string date = getStringInput("  Date (YYYY-MM-DD): ");
        string type = getStringInput("  Type (Consultation/Diagnosis/Treatment/Prescription): ");
        string desc = getStringInput("  Description: ");

        MedicalRecord* node = new MedicalRecord(date, type, desc);
        if (!head) { head = node; return; }
        // Insert in chronological order (by date)
        if (date < head->date) { node->next = head; head = node; return; }
        MedicalRecord* cur = head;
        while (cur->next && cur->next->date < date) cur = cur->next;
        node->next = cur->next;
        cur->next = node;
    }

    void deleteRecord() { // Delete a medical record by date
        string date = getStringInput("  Enter date of record to delete: ");
        MedicalRecord* cur = head;
        MedicalRecord* prev = nullptr;
        while (cur) {
            if (cur->date == date) { // Search linked list for the record with the given date
                if (prev) prev->next = cur->next;
                else      head = cur->next;
                delete cur;
                cout << "  [OK] Record deleted.\n";
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "  [!] Record not found.\n";
    }

    void searchRecord() const {
        string date = getStringInput("  Search by date (YYYY-MM-DD): ");
        MedicalRecord* cur = head;
        bool found = false;
        while (cur) {
            if (cur->date == date) {
                cout << "  " << cur->date << " | " << cur->type
                     << " | " << cur->description << "\n";
                found = true;
            }
            cur = cur->next;
        }
        if (!found) cout << "  [!] No record on that date.\n";
    }

    void traverse() const { // Display all medical records the early to the top
        if (!head) { cout << "  [!] Medical history is empty.\n"; return; }
        cout << "  Medical History (chronological order):\n";
        MedicalRecord* cur = head;
        while (cur) {
            cout << "    " << cur->date << " | " << left << setw(14) << cur->type
                 << " | " << cur->description << "\n";
            cur = cur->next;
        }
    }
};

class UndoStack {
private:
    stack<string> history;

public:
    void pushOperation(const string& op) { // Allow user to push a custom operation onto the stack
        history.push(op);
        cout << "  [OK] Operation recorded: " << op << "\n";
    }

    void peek() const { // Peek at the most recent operation without removing it
        if (history.empty()) { cout << "  [!] No recent operation.\n"; return; }
        cout << "  Most recent operation: " << history.top() << "\n";
    }

    void undo() { // Undo the most recent operation by popping it from the stack
        if (history.empty()) {
            cout << "  [!] No operations to undo.\n";
            return;
        }
        cout << "  [UNDO] " << history.top() << " has been undone.\n";
        history.pop();
    }

    void displayAll() const {// Display all operations in the stack (most recent first)
        if (history.empty()) { cout << "  [!] History empty.\n"; return; }
        stack<string> copy = history;
        cout << "  Operation history (most recent first):\n";
        while (!copy.empty()) {
            cout << "    - " << copy.top() << "\n";
            copy.pop();
        }
    }
};

struct QueuePatient { // Structure to hold patient information in the waiting queue
    int    id;
    string name;
    string department;
    string service;
    string priority;
};

class WaitingQueue {
private:
    queue<QueuePatient> q;

public:
    void enqueue() { // Enqueue a new patient into the waiting queue
        QueuePatient p;
        p.id         = getIntInput  ("  Patient ID      : ");
        p.name       = getStringInput("  Patient Name    : ");
        p.department = getStringInput("  Department      : ");
        p.service    = getStringInput("  Service         : ");
        p.priority   = getStringInput("  Priority (High/Medium/Low): ");
        q.push(p);
        cout << "  [OK] Patient enqueued.\n";
    }

    void dequeue() { // Dequeue the patient at the front of the waiting queue
        if (q.empty()) { cout << "  [!] Queue is empty.\n"; return; }
        QueuePatient p = q.front();
        q.pop();
        cout << "  [SERVED] " << p.name << " (ID " << p.id << ") for "
             << p.service << "\n";
    }

    void front() const { // Display the patient at the front of the waiting queue without removing them
        if (q.empty()) { cout << "  [!] Queue is empty.\n"; return; }
        const QueuePatient& p = q.front();
        cout << "  Front: ID " << p.id << " | " << p.name
             << " | " << p.department << " | " << p.service
             << " | Priority: " << p.priority << "\n";
    }

    void display() const { // Display all patients in the waiting queue in FIFO order
        if (q.empty()) { cout << "  [!] Queue is empty.\n"; return; }
        queue<QueuePatient> copy = q;
        printLine();
        cout << left << setw(6)  << "ID"
                     << setw(20) << "Name"
                     << setw(14) << "Department"
                     << setw(16) << "Service"
                     << "Priority\n";
        printLine();
        while (!copy.empty()) {
            const QueuePatient& p = copy.front();
            cout << left << setw(6)  << p.id
                         << setw(20) << p.name
                         << setw(14) << p.department
                         << setw(16) << p.service
                         << p.priority << "\n";
            copy.pop();
        }
        printLine();
        cout << "  Waiting: " << q.size() << " patient(s)  (FIFO order)\n";
    }
};

struct BSTNode { // Structure for a node in the binary search tree (BST) for patients
    Patient  data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const Patient& p) : data(p), left(nullptr), right(nullptr) {}
};

class PatientBST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, const Patient& p) { // Insert a new patient into the BST based on patient ID
        if (!node) return new BSTNode(p);
        if (p.id < node->data.id)      node->left  = insert(node->left,  p);
        else if (p.id > node->data.id) node->right = insert(node->right, p);
        else cout << "  [!] Duplicate ID ignored.\n";
        return node;
    }

    BSTNode* search(BSTNode* node, int id) const { // Search for a patient in the BST by ID
        if (!node || node->data.id == id) return node;
        if (id < node->data.id) return search(node->left,  id);
        return search(node->right, id);
    }

    BSTNode* findMin(BSTNode* node) const { // Find the node with the minimum ID in the BST (leftmost node)
        while (node && node->left) node = node->left;
        return node;
    }

    BSTNode* remove(BSTNode* node, int id) { // Remove a patient from the BST by ID
        if (!node) return nullptr;
        if (id < node->data.id)      node->left  = remove(node->left,  id);
        else if (id > node->data.id) node->right = remove(node->right, id);
        else {
            if (!node->left)  { BSTNode* r = node->right; delete node; return r; }
            if (!node->right) { BSTNode* l = node->left;  delete node; return l; }
            BSTNode* succ = findMin(node->right);
            node->data = succ->data;
            node->right = remove(node->right, succ->data.id);
        }
        return node;
    }

    void inOrder(BSTNode* node) const { // In-order traversal of the BST to display patients in ascending order of ID
        if (!node) return;
        inOrder(node->left);
        cout << "  ID:" << node->data.id << " | " << node->data.name
             << " | Age:" << node->data.age << " | " << node->data.department << "\n";
        inOrder(node->right);
    }

    void destroy(BSTNode* node) { // Recursively delete all nodes in the BST to free memory
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    PatientBST() : root(nullptr) {}
    ~PatientBST() { destroy(root); }

    void insertPatient(const Patient& p) { root = insert(root, p); }

    void insertInteractive() {
        Patient p;
        p.id = getIntInput("  Patient ID : ");
        if (search(root, p.id)) { cout << "  [!] ID already exists.\n"; return; }
        p.name       = getStringInput("  Name       : ");
        p.age        = getIntInput  ("  Age        : ");
        p.gender     = getStringInput("  Gender     : ");
        p.department = getStringInput("  Department : ");
        p.condition  = getStringInput("  Condition  : ");
        insertPatient(p);
        cout << "  [OK] Inserted into BST.\n";
    }

    void searchInteractive() const {
        int id = getIntInput("  Search Patient ID: ");
        BSTNode* n = search(root, id);
        if (!n) { cout << "  [!] Patient not found.\n"; return; }
        cout << "  [OK] Found: ID " << n->data.id << " | " << n->data.name
             << " | Age " << n->data.age << " | " << n->data.department << "\n";
    }

    void deleteInteractive() {
        int id = getIntInput("  Delete Patient ID: ");
        if (!search(root, id)) { cout << "  [!] Patient not found.\n"; return; }
        root = remove(root, id);
        cout << "  [OK] Patient deleted from BST.\n";
    }

    void displayInOrder() const {
        if (!root) { cout << "  [!] BST is empty.\n"; return; }
        cout << "  In-order traversal (ascending Patient ID):\n";
        inOrder(root);
    }
};

class ReferralGraph { // Directed graph to represent department referrals
private:
    static const int V = 6;
    string dept[V] = {"A (Emergency)","B (Cardiology)","C (Radiology)",
                      "D (Surgery)","E (Neurology)","F (Pharmacy)"};
    vector<int> adj[V];

public:
    ReferralGraph() { // Initialize the graph with predefined edges representing referrals between departments
        // A=0, B=1, C=2, D=3, E=4, F=5
        addEdge(0,1); addEdge(0,2);
        addEdge(1,3); addEdge(1,4);
        addEdge(2,3);
        addEdge(3,5);
        addEdge(4,5);
    }

    void addEdge(int u, int v) { adj[u].push_back(v); } //  Add a directed edge from department u to department v

    void displayAdjacency() const { // Display the adjacency list representation of the graph
        cout << "  Referral Adjacency List:\n";
        for (int i = 0; i < V; ++i) {
            cout << "    " << dept[i] << " -> ";
            for (size_t j = 0; j < adj[i].size(); ++j)
                cout << dept[adj[i][j]] << (j + 1 < adj[i].size() ? ", " : "");
            cout << "\n";
        }
    }

    void DFS(int start) const {// Perform Depth-First Search (DFS) starting from a given department index
        vector<bool> visited(V, false);
        cout << "  DFS from " << dept[start] << ": ";
        dfsUtil(start, visited);
        cout << "\n";
    }

    void dfsUtil(int u, vector<bool>& visited) const {// Utility function for DFS traversal
        visited[u] = true;
        cout << dept[u] << " ";
        for (size_t i = 0; i < adj[u].size(); ++i)
            if (!visited[adj[u][i]]) dfsUtil(adj[u][i], visited);
    }

    void BFS(int start) const {// Perform Breadth-First Search (BFS) starting from a given department index
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "  BFS from " << dept[start] << ": ";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << dept[u] << " ";
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i];
                if (!visited[v]) { visited[v] = true; q.push(v); }
            }
        }
        cout << "\n";
    }
};

class SearchCompare {// Class to compare linear search and binary search on patient records
public:
    static int linearSearch(const vector<Patient>& arr, int id) {// Perform linear search on the array of patients for a given ID
        int comparisons = 0;
        for (size_t i = 0; i < arr.size(); ++i) {
            ++comparisons;
            if (arr[i].id == id) { cout << "  Linear comparisons: " << comparisons << "\n"; return (int)i; }
        }
        cout << "  Linear comparisons: " << comparisons << "\n";
        return -1;
    }

    static int binarySearch(const vector<Patient>& arr, int id) {// Perform binary search on the sorted array of patients for a given ID
        int lo = 0, hi = (int)arr.size() - 1, comparisons = 0;
        while (lo <= hi) {
            ++comparisons;
            int mid = lo + (hi - lo) / 2;
            if (arr[mid].id == id) { cout << "  Binary comparisons: " << comparisons << "\n"; return mid; }
            else if (arr[mid].id < id) lo = mid + 1;
            else hi = mid - 1;
        }
        cout << "  Binary comparisons: " << comparisons << "\n";
        return -1;
    }

    static void run(PatientArray& pa) {// Run the search comparison by prompting user for a patient ID and performing both linear and binary searches
        int n = pa.size();
        vector<Patient> arr(pa.raw(), pa.raw() + n);
        int id = getIntInput("  Enter Patient ID to search: ");

        cout << "\n  --- Linear Search ---\n";
        int r1 = linearSearch(arr, id);
        cout << (r1 != -1 ? "  Patient FOUND.\n" : "  Patient NOT found.\n");

        sort(arr.begin(), arr.end(), [](const Patient& a, const Patient& b){
            return a.id < b.id;
        });

        cout << "\n  --- Binary Search (after sorting) ---\n";
        int r2 = binarySearch(arr, id);
        cout << (r2 != -1 ? "  Patient FOUND.\n" : "  Patient NOT found.\n");

        cout << "\n  Efficiency note: Binary search is O(log n) vs O(n) for linear.\n";
    }
};

class SortCompare {// Class to compare merge sort and bubble sort on patient records
public:
    static long long mergeComparisons;
    static long long bubbleComparisons;

    static void mergeSort(vector<Patient>& arr, int l, int r) {// Perform merge sort on the array of patients
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

    static void merge(vector<Patient>& arr, int l, int m, int r) {// Merge two sorted subarrays into one sorted array
        vector<Patient> left(arr.begin() + l, arr.begin() + m + 1);
        vector<Patient> right(arr.begin() + m + 1, arr.begin() + r + 1);
        size_t i = 0, j = 0; int k = l;
        while (i < left.size() && j < right.size()) {
            ++mergeComparisons;
            if (left[i].id <= right[j].id) arr[k++] = left[i++];
            else                            arr[k++] = right[j++];
        }
        while (i < left.size())  arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }

    static void bubbleSort(vector<Patient>& arr) {// Perform bubble sort on the array of patients
        int n = (int)arr.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                ++bubbleComparisons;
                if (arr[j].id > arr[j + 1].id) swap(arr[j], arr[j + 1]);
            }
        }
    }

    static void run(PatientArray& pa) {// Run the sort comparison by sorting the patient records using both merge sort and bubble sort, measuring comparisons and time taken
        int n = pa.size();
        vector<Patient> a(pa.raw(), pa.raw() + n);
        vector<Patient> b = a;

        cout << "\n  Unsorted (first 5):\n";
        for (int i = 0; i < min(5, n); ++i) cout << "    ID " << a[i].id << "\n";

        mergeComparisons = 0;
        auto t1 = high_resolution_clock::now();
        mergeSort(a, 0, n - 1);
        auto t2 = high_resolution_clock::now();
        auto mergeMs = duration_cast<microseconds>(t2 - t1).count();

        bubbleComparisons = 0;
        auto t3 = high_resolution_clock::now();
        bubbleSort(b);
        auto t4 = high_resolution_clock::now();
        auto bubbleMs = duration_cast<microseconds>(t4 - t3).count();

        cout << "\n  Sorted (ascending Patient ID, first 5):\n";
        for (int i = 0; i < min(5, n); ++i) cout << "    ID " << a[i].id << "\n";

        cout << "\n  --- Performance Comparison ---\n";
        cout << "  Merge Sort : " << mergeComparisons << " comparisons | "
             << mergeMs << " us\n";
        cout << "  Bubble Sort: " << bubbleComparisons << " comparisons | "
             << bubbleMs << " us\n";
        cout << "  Merge sort is more efficient: O(n log n) vs O(n^2).\n";
    }
};
long long SortCompare::mergeComparisons  = 0;
long long SortCompare::bubbleComparisons = 0;

class PatientHashTable {// Class to implement a hash table for patient records using separate chaining for collision resolution
private:
    static const int SIZE = 17;    // prime number reduces collisions
    list<pair<int, Patient>> table[SIZE];

    int hashFunc(int id) const { return id % SIZE; }// Hash function to compute the index for a given patient ID

public:
    void insert(const Patient& p) {// Insert a patient into the hash table, updating if ID already exists
        int h = hashFunc(p.id);
        for (auto& kv : table[h])
            if (kv.first == p.id) { kv.second = p; return; }
        table[h].push_back({p.id, p});
    }

    Patient* find(int id) {// Find a patient in the hash table by ID, returning a pointer to the patient if found, or nullptr if not found
        int h = hashFunc(id);
        for (auto& kv : table[h])
            if (kv.first == id) return &kv.second;
        return nullptr;
    }

    void display() const {// Display the contents of the hash table, showing each bucket and the patient IDs stored in it
        cout << "  Hash Table contents:\n";
        for (int i = 0; i < SIZE; ++i) {
            if (table[i].empty()) continue;
            cout << "    Bucket " << setw(2) << i << ": ";
            for (auto& kv : table[i]) cout << kv.first << " ";
            cout << "\n";
        }
    }

    void runInteractive() {// Run an interactive lookup for a patient by ID using the hash table
        cout << "\n  [Hash Table] O(1) average lookup by Patient ID\n";
        int id = getIntInput("  Enter Patient ID: ");
        Patient* p = find(id);
        if (p) cout << "  Found: " << p->name << " | " << p->department << "\n";
        else   cout << "  [!] Not found.\n";
    }
};

class HospitalManagementSystem {//Mainmenu class to manage the hospital management system, integrating all data structures and providing a user interface
private:
    PatientArray patientArray;
    MedicalHistoryList medicalHistory;
    UndoStack undoStack;
    WaitingQueue waitingQueue;
    PatientBST patientBST;
    ReferralGraph referralGraph;
    PatientHashTable patientHashTable;

    void showMainMenu() const {
        printHeader("HOSPITAL MANAGEMENT SYSTEM");
        cout << "  1.  Patient Records (Array)\n";
        cout << "  2.  Medical History (Linked List)\n";
        cout << "  3.  Undo Operations (Stack)\n";
        cout << "  4.  Waiting Queue (Queue)\n";
        cout << "  5.  Patient BST (Tree)\n";
        cout << "  6.  Department Referrals (Graph)\n";
        cout << "  7.  Search Comparison (Linear vs Binary)\n";
        cout << "  8.  Sort Comparison (Merge vs Bubble)\n";
        cout << "  9.  Hash Table Lookup (Extra)\n";
        cout << "  0.  Exit\n";
        printLine();
    }

    void runPatientRecordsMenu() {
        int choice;
        do {
            printHeader("PATIENT RECORDS (ARRAY)");
            cout << "  1. Display all\n  2. Insert\n  3. Delete\n"
                 << "  4. Search by ID\n  5. Update\n  0. Back\n";
            choice = getIntInput("  Choice: ");
            switch (choice) {
            case 1: patientArray.displayAll(); break;
            case 2: patientArray.insertPatient(); undoStack.pushOperation("Insert patient (array)"); break;
            case 3: patientArray.deletePatient(); undoStack.pushOperation("Delete patient (array)"); break;
            case 4: patientArray.searchPatient(); break;
            case 5: patientArray.updatePatient(); undoStack.pushOperation("Update patient (array)"); break;
            }
        } while (choice != 0);
    }

    void runMedicalHistoryMenu() {
        int choice;
        do {
            printHeader("MEDICAL HISTORY (LINKED LIST)");
            cout << "  1. Add record\n  2. Delete record\n"
                 << "  3. Search by date\n  4. Traverse (chronological)\n  0. Back\n";
            choice = getIntInput("  Choice: ");
            switch (choice) {
            case 1: medicalHistory.addRecord(); undoStack.pushOperation("Add medical record"); break;
            case 2: medicalHistory.deleteRecord(); undoStack.pushOperation("Delete medical record"); break;
            case 3: medicalHistory.searchRecord(); break;
            case 4: medicalHistory.traverse(); break;
            }
        } while (choice != 0);
    }

    void runUndoMenu() {
        int choice;
        do {
            printHeader("UNDO OPERATIONS (STACK)");
            cout << "  1. Push custom operation\n  2. Peek most recent\n"
                 << "  3. Undo\n  4. Display all\n  0. Back\n";
            choice = getIntInput("  Choice: ");
            switch (choice) {
            case 1: undoStack.pushOperation(getStringInput("  Operation: ")); break;
            case 2: undoStack.peek(); break;
            case 3: undoStack.undo(); break;
            case 4: undoStack.displayAll(); break;
            }
        } while (choice != 0);
    }

    void runWaitingQueueMenu() {
        int choice;
        do {
            printHeader("WAITING QUEUE (QUEUE)");
            cout << "  1. Enqueue patient\n  2. Dequeue patient\n"
                 << "  3. Show front\n  4. Display all\n  0. Back\n";
            choice = getIntInput("  Choice: ");
            switch (choice) {
            case 1: waitingQueue.enqueue(); undoStack.pushOperation("Enqueue patient"); break;
            case 2: waitingQueue.dequeue(); break;
            case 3: waitingQueue.front(); break;
            case 4: waitingQueue.display(); break;
            }
        } while (choice != 0);
    }

    void runPatientBSTMenu() {
        int choice;
        do {
            printHeader("PATIENT BST");
            cout << "  1. Insert\n  2. Search\n  3. Delete\n"
                 << "  4. In-order traversal\n  0. Back\n";
            choice = getIntInput("  Choice: ");
            switch (choice) {
            case 1: patientBST.insertInteractive(); break;
            case 2: patientBST.searchInteractive(); break;
            case 3: patientBST.deleteInteractive(); break;
            case 4: patientBST.displayInOrder(); break;
            }
        } while (choice != 0);
    }

    void runReferralMenu() const {
        printHeader("DEPARTMENT REFERRALS (GRAPH)");
        referralGraph.displayAdjacency();
        int start = getIntInput("  Enter start vertex (0=A,1=B,2=C,3=D,4=E,5=F): ");
        if (start < 0 || start > 5) {
            cout << "  [!] Invalid vertex.\n";
            return;
        }
        referralGraph.DFS(start);
        referralGraph.BFS(start);
    }

public:
    HospitalManagementSystem() {
        patientArray.loadSampleData();
        for (int i = 0; i < patientArray.size(); ++i) {
            patientBST.insertPatient(patientArray.get(i));
            patientHashTable.insert(patientArray.get(i));
        }
    }

    void run() {
        int choice;
        do {
            showMainMenu();
            choice = getIntInput("  Enter choice: ");
            switch (choice) {
            case 1: runPatientRecordsMenu(); break;
            case 2: runMedicalHistoryMenu(); break;
            case 3: runUndoMenu(); break;
            case 4: runWaitingQueueMenu(); break;
            case 5: runPatientBSTMenu(); break;
            case 6: runReferralMenu(); break;
            case 7: printHeader("SEARCH COMPARISON"); SearchCompare::run(patientArray); break;
            case 8: printHeader("SORT COMPARISON"); SortCompare::run(patientArray); break;
            case 9:
                printHeader("HASH TABLE");
                patientHashTable.display();
                patientHashTable.runInteractive();
                break;
            case 0: cout << "\n  Exiting... Thank you.\n"; break;
            default: cout << "  [!] Invalid choice.\n";
            }
        } while (choice != 0);
    }
};

