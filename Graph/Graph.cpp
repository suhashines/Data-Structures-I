#include <bits/stdc++.h>
// #include "MyLinkedList.cpp"
#include "Stack.cpp"
#include "MyQueueCircular.cpp"

#define w -1 // unseeen
#define g 0  // seen but not explored
#define b 1  // seen and explored

#define inf 1000000

using namespace std;

class Graph
{

    int n;
    LinkedList<int> *adj;

    LinkedList<int> vertices;

    LinkedList<pair<int, int>> edges;

    int *color;
    int *dist;

    int *parent;

    int *start;
    int *finish;

    int time;

    void initialize()
    {

        for (int i = 0; i <= n; i++)
        {
            color[i] = w;
            dist[i] = -inf;
            parent[i] = -1;
            start[i] = -inf;
            finish[i] = -inf;
        }
    }

public:
    Graph(int n)
    {
        this->n = n;

        // this->n = n+1 ;

        time = 0;

        adj = new LinkedList<int>[n + 1];
        color = new int[n + 1];
        dist = new int[n + 1];
        parent = new int[n + 1];
        start = new int[n + 1];
        finish = new int[n + 1];
        initialize();
    }

    void addEdge(int u, int v)
    {
        adj[u].pushBack(v); // u = 1 , v = 2
        // u ->  2 , 3 , 4
    }

    void show()
    {

        for (int i = 0; i < n; i++)
        {

            cout << i << " -> ";

            adj[i].print();

            cout << endl;
        }
    }

    void BFS(int src)
    { // O ( V + E )

        color[src] = g;
        dist[src] = 0;
        parent[src] = src;

        QueueC<int> q;

        q.enqueue(src);

        while (q.length() > 0)
        { // O(E)

            int u = q.dequeue();

            vertices.pushBack(u);

            LinkedList<int> neigh = adj[u];

            for (neigh.setToBegin(); neigh.currPos() < neigh.length(); neigh.next())
            { // O(V)

                int v = neigh.getValue();

                if (color[v] == w)
                {

                    color[v] = g;

                    dist[v] = dist[u] + 1;

                    parent[v] = u;

                    q.enqueue(v);

                    edges.pushBack(make_pair(u, v));
                }
            }

            color[u] = b;
        }
    }

    void printShortestPath(int u, int v)
    {

        if (u == v)
        {
            cout << u;
            return;
        }

        printShortestPath(u, parent[v]);

        cout << "->" << v;
    }

    void shortestPath(int u, int v)
    {

        BFS(u);

        int d = dist[v];

        if (d == -inf)
        {
            cout << "Unreachable" << endl;
            return;
        }

        cout << "shortest distance (" << u << "," << v << ") : " << d << endl;
        cout << "\nshortest path :\n";
        printShortestPath(u, v);

        cout << endl;
    }

    void DFS(int src) // O(V+E)
    {

        color[src] = g;

        vertices.pushBack(src);

        LinkedList<int> neigh = adj[src];

        for (neigh.setToBegin(); neigh.currPos() < neigh.length(); neigh.next())
        {

            int u = neigh.getValue();

            if (color[u] == w)
            {

                edges.pushBack(make_pair(src, u));

                DFS(u);
            }
        }

        color[src] = b;
    }

    bool isCyclicUtil(int src)
    {

        color[src] = g;

        LinkedList<int> neigh = adj[src];

        for (neigh.setToBegin(); neigh.currPos() < neigh.length(); neigh.next())
        {

            int u = neigh.getValue();

            if (color[u] == w && isCyclicUtil(u))
            {
                return true;
            }
            else if (color[u] == g)
            {
                return true;
            }
        }

        color[src] = b;

        return false;
    }

    bool isCyclic()
    {

        initialize();

        for (int i = 0; i <= n; i++)
        {

            if (color[i] == w)
            {
                if (isCyclicUtil(i))
                {
                    return true;
                }
            }
        }

        return false;
    }

    void printTree()
    {

        cout << "Set of vertices: ";

        for (vertices.setToBegin(); vertices.currPos() < vertices.length(); vertices.next())
        {
            cout << vertices.getValue() << " ";
        }

        cout << "\n\nSet of edges:" << endl;

        for (edges.setToBegin(); edges.currPos() < edges.length(); edges.next())
        {
            cout << "(" << edges.getValue().first << "," << edges.getValue().second << ")" << endl;
        }

        vertices.clear();
        edges.clear();
        initialize();
    }

    bool isBipartiteUtil(int src)
    {

        color[src] = g; // 0

        QueueC<int> q;

        q.enqueue(src);

        while (q.length() > 0)
        { // O(E)

            int u = q.dequeue();

            LinkedList<int> neigh = adj[u];

            for (neigh.setToBegin(); neigh.currPos() < neigh.length(); neigh.next())
            { // O(V)

                int v = neigh.getValue();

                if (color[v] == w)
                {

                    color[v] = 1 - color[u];

                    q.enqueue(v);
                }
                else if (color[v] == color[u])
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool isBipartite()
    {

        initialize();

        for (int i = 0; i <= n; i++)
        {

            if (color[i] == w)
            {

                if (!isBipartiteUtil(i))
                {
                    return false;
                }
            }
        }

        return true;
    }

    void topoSortUtil(int src, Stack<int> &st)
    {

        color[src] = g;

        LinkedList<int> neigh = adj[src];

        for (neigh.setToBegin(); neigh.currPos() < neigh.length(); neigh.next())
        {

            int u = neigh.getValue();

            if (color[u] == w)
            {
                topoSortUtil(u, st);
            }
        }

        color[src] = b;
        st.push(src);
    }

    void topoSort()
    {

        if (isCyclic())
        {
            cout << "There is a cycle" << endl;
            return;
        }

        initialize(); // color must be initialized

        Stack<int> st;

        for (int i = 0; i < n; i++)
        {

            if (color[i] == w)
            {

                topoSortUtil(i, st);
            }
        }

        int size = st.size();

        for (int i = 0; i < size; i++)
        {
            cout << st.pop() << " ";
        }

        cout << endl;
    }

    void classifyEdgeUtil(int src,
                          LinkedList<pair<int, int>> &tree,
                          LinkedList<pair<int, int>> &back,
                          LinkedList<pair<int, int>> &forward,
                          LinkedList<pair<int, int>> &cross)
    {

        time = time + 1;
        color[src] = g;
        start[src] = time;

        LinkedList<int> neigh = adj[src];

        for (neigh.setToBegin(); neigh.currPos() < neigh.length(); neigh.next())
        {

            int u = neigh.getValue();

            if (color[u] == w)
            {
                tree.pushBack(make_pair(src, u));
                classifyEdgeUtil(u, tree, back, forward, cross);
            }
            else if (color[u] == g)
            {
                back.pushBack(make_pair(src, u));
            }
            else if (color[u] == b && start[u]>start[src])
            {
                forward.pushBack(make_pair(src, u));
            }
            else
            {
                cross.pushBack(make_pair(src, u));
            }
        }

        time = time+1 ;
        finish[src] = time;

        color[src] = b;
    }

    void classifyEdge()
    {

        initialize();

        LinkedList<pair<int, int>> tree;
        LinkedList<pair<int, int>> back;
        LinkedList<pair<int, int>> forward;
        LinkedList<pair<int, int>> cross;

        for (int i = 1; i <= n; i++)
        {

            if (color[i] == w)
            {
                classifyEdgeUtil(i, tree, back, forward, cross);
            }
        }

          cout<<"Time:\n";

        for(int i=1;i<=n;i++){
            cout<<i<<": "<<start[i]<<","<<finish[i]<<endl;
        }

        cout<<"\nTree Edges: "<<endl;

        for(tree.setToBegin();tree.currPos()<tree.length();tree.next()){
            cout<<"("<<tree.getValue().first<<","<<tree.getValue().second<<") ";
        }
        cout<<"\nBack Edges: "<<endl;

        for(back.setToBegin();back.currPos()<back.length();back.next()){
            cout<<"("<<back.getValue().first<<","<<back.getValue().second<<") ";
        }

        cout<<"\nForward Edges: "<<endl;

        for(forward.setToBegin();forward.currPos()<forward.length();forward.next()){
            cout<<"("<<forward.getValue().first<<","<<forward.getValue().second<<") ";
        }
            cout<<"\nCross Edges: "<<endl;

        for(cross.setToBegin();cross.currPos()<cross.length();cross.next()){
            cout<<"("<<cross.getValue().first<<","<<cross.getValue().second<<") ";
        }

      

        
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, u, v, src, dest;
    // cout<<"Enter the number of vertices : ";
    cin >> n;
    Graph G(n);
    // cout<<"Enter the number of edges : ";
    cin >> m;
    // cout<<"Enter the list of directed edges : "<<endl;

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        G.addEdge(u, v);
    }
    // cout<<"Enter the source : ";
    // cin >> src >> dest;

    // G.BFS(src);
    // cout<<"Breadth-First Search:\n"<<endl;
    // G.printTree();

    // G.DFS(src);
    // cout<<"\nDepth-First Search:\n"<<endl;
    // G.printTree();

    // Shortest Path
    // cout<<G.shortestPath(u,v)<<endl;

    // Bipartiteness
    //  cout<<G.isBipartite()<<endl;

    // Cycle Detection

    // cout<<G.isCyclic()<<endl;

    // Topological Sort

    //G.topoSort();

    //Classify Edge

    G.classifyEdge();

    return 0;
}