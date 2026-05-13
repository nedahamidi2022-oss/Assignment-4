#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

// --- بخش 1: ساختار اصلی برای ذخیره اطلاعات یال‌ها ---
struct Edge {
    int destination; // شماره گره مقصد
    int weight;      // وزن یا هزینه مسیر
};

class Graph {
public:
    // لیست مجاورتی: شماره هر گره را به لیست همسایه‌هایش وصل می‌کند
    map<int, list<Edge>> adjList;

    // متد برای ساختن یک نقطه (رأس) جدید در گراف
    void add_vertex(int v) {
        if (adjList.find(v) == adjList.end()) {
            adjList[v] = list<Edge>();
        }
    }

    // متد برای کشیدن یک خط (یال) بین دو نقطه با وزن مشخص
    void add_edge(int v, int w, int weight) {
        add_vertex(v);
        add_vertex(w);
        adjList[v].push_back({w, weight}); // از v به w
        adjList[w].push_back({v, weight}); // چون گراف دوطرفه است، از w به v هم می‌کشیم
    }

    // چاپ گراف در کنسول برای چک کردن درستی کد (تسک 1)
    void print_adj_list() {
        cout << "--- Task 1: List Majaverati ---" << endl;
        for (auto const& [node, neighbors] : adjList) {
            cout << "Gereh " << node << ": ";
            for (auto const& edge : neighbors) {
                cout << "-> (Be: " << edge.destination << ", Vazn: " << edge.weight << ") ";
            }
            cout << endl;
        }
    }

    // --- بخش 2: روش‌های گشتن در گراف (تسک 2) ---

    // روش اول‌عمق (DFS): مثل گشتن در هزارتو، تا جایی که راه داشته باشد جلو می‌رود
    void DFS(int startNode) {
        map<int, bool> visited;
        cout << "Tartib DFS: ";
        DFS_Helper(startNode, visited);
        cout << endl;
    }

    void DFS_Helper(int v, map<int, bool>& visited) {
        visited[v] = true; // علامت می‌زنیم که این نقطه را دیده‌ایم
        cout << v << " "; // چاپ شماره گره

        for (auto const& edge : adjList[v]) {
            if (!visited[edge.destination]) {
                DFS_Helper(edge.destination, visited); // رفتن به عمقِ همسایه بعدی
            }
        }
    }

    // روش اول‌سطح (BFS): گره‌ها را لایه به لایه (اول همسایه‌های نزدیک) می‌بیند
    void BFS(int startNode) {
        map<int, bool> visited;
        queue<int> q; // صفی برای مدیریت نوبت بازدید گره‌ها

        visited[startNode] = true;
        q.push(startNode);

        cout << "Tartib BFS: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " "; // چاپ شماره گره

            for (auto const& edge : adjList[v]) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    q.push(edge.destination); // اضافه کردن همسایه‌ها به تهِ صف
                }
            }
        }
        cout << endl;
    }

    // --- بخش 3: کوتاه‌ترین مسیر (تسک 3) ---

    // الگوریتم دایکسترا برای پیدا کردن ارزان‌ترین مسیر در گراف وزن‌دار
    void dijkstra(int S) {
        map<int, int> dist;   // ذخیره کمترین فاصله از شروع تا هر گره
        map<int, int> parent; // ذخیره گره قبلی برای نشان دادن مسیر نهایی
        
        // صف اولویت‌دار برای اینکه همیشه اول سراغ گره با کمترین فاصله برود
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // در ابتدا فاصله همه را "بی‌نهایت" می‌گذاریم
        for (auto const& [v, e] : adjList) dist[v] = numeric_limits<int>::max();

        dist[S] = 0; // فاصله شروع از خودش صفر است
        pq.push({0, S});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto const& edge : adjList[u]) {
                // اگر راه جدیدی پیدا شد که از راه قبلی ارزان‌تر بود:
                if (dist[u] + edge.weight < dist[edge.destination]) {
                    dist[edge.destination] = dist[u] + edge.weight;
                    parent[edge.destination] = u; // ثبت می‌کنیم از کجا به این گره رسیدیم
                    pq.push({dist[edge.destination], edge.destination});
                }
            }
        }

        // چاپ فواصل و مسیرهای پیدا شده
        cout << "--- Task 3: Dijkstra (Shortest Paths) ---" << endl;
        for (auto const& [node, d] : dist) {
            cout << "Node " << node << " : Distance = " << d << ", Path = ";
            print_path(parent, node);
            cout << endl;
        }
    }

    // متد کمکی برای چاپ مرحله به مرحله مسیر (مثلاً 0 -> 1 -> 2)
    void print_path(map<int, int>& parent, int j) {
        if (parent.find(j) == parent.end()) {
            cout << j;
            return;
        }
        print_path(parent, parent[j]);
        cout << " -> " << j;
    }
};

int main() {
    Graph g;
    
    // وارد کردن داده‌ها برای تست برنامه
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 8);
    g.add_edge(1, 2, 2);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 3, 1);

    // اجرای هر سه بخش تکلیف
    g.print_adj_list(); 
    cout << endl;

    g.DFS(0);           
    g.BFS(0);           
    cout << endl;

    g.dijkstra(0);      

    return 0;
}
