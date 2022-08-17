#include <iostream>
#include <iterator>
#include <list>
#include<string>
using namespace std;

int main() {
    int n,m, s, t;
    string edge;
    cout << "Please enter number of vertices: \n";
    cin >> n;
    cout << "Please enter number of edges:\n";
    cin >> m;
    cout << " Please choose a starting edge: \n";
    cin >> s;
    cout << " Please choose an ending edge: \n";
    cin >> t;
    list<string> edges;
    string a;
    for (int i = 0; i <= m; i++) { // NOTICE - The edges are as STRING because of the spaces
        
        getline(cin, a);
        edges.push_back(a);
    }
// Now need to implement - Graph graph(n,m,s,t,edges), bty i think the input check should be inside the c'tor while we transform the string into int.
}