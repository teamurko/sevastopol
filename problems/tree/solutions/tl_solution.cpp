#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <cmath>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, (v).size())

typedef vector<vector<int> > Graph;
const int UNDEFINED = -1;
const int MOD = 1000000007;
const int P = 127;

void readData(Graph* graph, vector<int>* values, int& root)
{
    int numVertices;
    cin >> numVertices;
    graph->resize(numVertices);
    values->resize(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        int parent, value;
        cin >> parent >> value;
        if (parent != UNDEFINED) {
            assert(parent >= 0);
            graph->at(parent).push_back(i);
        } else {
            root = i;
        }
        values->at(i) = value;
    }
}

vector<int>* merge(vector<int>* first, vector<int>* second, int& ans)
{
    cerr << first->size() << " " << second-> size() << endl;
    if (first->size() > second->size()) {
        swap(first, second);
    }
    forv(i, *first) {
        forv(j, *second) {
            int a = first->at(i);
            int b = second->at(j);
            ans = min(ans, abs(a - b));
        }
    }
    forv(i, *second) {
        first->push_back(second->at(i));
    }
    second->clear();
    return first;
}

void dfs(int vertex, const Graph& graph,
         const vector<int>& values,
         vector<vector<int>*>* table,
         vector<int>* ans)
{
    if (graph.at(vertex).size() == 0) {
        table->at(vertex) = new vector<int>();
        table->at(vertex)->push_back(values[vertex]);
        return;
    }
    int localAns = MOD;
    forv(i, graph[vertex]) {
        int child = graph[vertex].at(i);
        dfs(child, graph, values, table, ans);
        localAns = min(localAns, ans->at(child));
    }
    vector<int>* cur = table->at(graph[vertex].front());
    for (size_t i = 1; i < graph[vertex].size(); ++i) {
        int child = graph[vertex][i];
        cur = merge(cur, table->at(child), localAns);
    }
    forv(i, *cur) {
        localAns = min(localAns, abs(values[vertex] - cur->at(i)));
    }
    cur->push_back(values[vertex]);
    table->at(vertex) = cur;
    ans->at(vertex) = localAns;
}

void solve(const Graph& graph, const vector<int>& values, int root)
{
    vector<vector<int>*> table(graph.size());
    vector<int> ans(graph.size(), MOD);
    dfs(root, graph, values, &table, &ans);
    long long Ans = 0;
    forv(i, graph) {
        Ans = (Ans * P + ans[i]) % MOD;
    }
    cout << Ans << endl;
}

int main (int argc, char * const argv[])
{
    ios_base::sync_with_stdio(false);
    Graph graph;
    vector<int> values;
    int root;
    readData(&graph, &values, root);
    solve(graph, values, root);
    return 0;
}
