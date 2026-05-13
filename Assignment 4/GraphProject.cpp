#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

// --- 1: ساختار اصلی گراف ---
// تعریف لبه برای ذخیره مقصد و وزن یال
struct Edge {
    int destination;
    int weight;
};

class Graph {
public:
    // لیست مجاورتی برای نگهداری رئوس و همسایه‌ها
    map<int, list<Edge>> adjList;

    // متد اضافه کردن رأس
    void add_vertex(int v) {
        if (adjList.find(v) == adjList.end()) {
            adjList[v] = list<Edge>();
        }
    }

    // متد اضافه کردن یال وزن‌دار (دو طرفه)
    void add_edge(int v, int w, int weight) {
        add_vertex(v);
        add_vertex(w);
        adjList[v].push_back({w, weight});
        adjList[w].push_back({v, weight}); 
    }

    // چاپ لیست مجاورتی برای تأیید اتصالات
    void print_adj_list() {
        cout << "--- Task 1: Adjacency List (Verification) ---" << endl;
        for (auto const& [vertex, edges] : adjList) {
            cout << vertex << ": ";
            for (auto const& edge : edges) {
                cout << "-> (" << edge.destination << ", w:" << edge.weight << ") ";
            }
            cout << endl;
        }
    }

    // ---  2: الگوریتم‌های پیمایش ---
    // پیمایش اول‌عمق (DFS) به صورت بازگشتی
    void DFS(int startNode) {
        map<int, bool> visited;
        cout << "DFS Traversal Order: ";
        DFS_Helper(startNode, visited);
        cout << endl;
    }

    void DFS_Helper(int v, map<int, bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto const& edge : adjList[v]) {
            if (!visited[edge.destination]) {
                DFS_Helper(edge.destination, visited);
            }
        }
    }

    // پیمایش اول‌سطح (BFS) با استفاده از صف
    void BFS(int startNode) {
        map<int, bool> visited;
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS Traversal Order: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto const& edge : adjList[v]) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    q.push(edge.destination);
                }
            }
        }
        cout << endl;
    }

    // ---  3: کوتاه‌ترین مسیر  ---
    void dijkstra(int S) {
        map<int, int> dist;
        map<int, int> parent;
        // صف اولویت‌دار برای انتخاب گره با کمترین فاصله
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for (auto const& [vertex, edges] : adjList) {
            dist[vertex] = numeric_limits<int>::max(); // تنظیم فواصل روی بی‌نهایت
        }

        dist[S] = 0;
        pq.push({0, S});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto const& edge : adjList[u]) {
                if (dist[u] + edge.weight < dist[edge.destination]) {
                    dist[edge.destination] = dist[u] + edge.weight;
                    parent[edge.destination] = u;
                    pq.push({dist[edge.destination], edge.destination});
                }
            }
        }

        cout << "--- Task 3: Dijkstra Shortest Paths ---" << endl;
        for (auto const& [vertex, d] : dist) {
            cout << "Node " << vertex << " : Distance = " << d << ", Path = ";
            print_path(parent, vertex);
            cout << endl;
        }
    }

    // متد کمکی برای چاپ مسیر پیمایش شده
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
    
    // اضافه کردن داده‌های نمونه برای تست
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 8);
    g.add_edge(1, 2, 2);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 3, 1);

    // اجرای تسک‌ها
    g.print_adj_list(); 
    cout << endl;

    g.DFS(0);           
    g.BFS(0);           
    cout << endl;

    g.dijkstra(0);      

    return 0;
}