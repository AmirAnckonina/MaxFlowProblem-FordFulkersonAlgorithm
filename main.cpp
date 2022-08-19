#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include <list>
#include<string>
#include<stdio.h>
#include "verticesNodes.h"
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
    string a;
    std::list<vertices> edges;
    vertices tmp;
    for (int i = 0; i < m; i++) { // NOTICE - The edges are as STRING because of the spaces
        scanf("%d", &tmp.curr_ver);
        scanf("%d", &tmp.adj);
        scanf("%d", &tmp.flow);
        edges.push_back(tmp);
    }
    edges.push_back(tmp);
// Now need to implement - Graph graph(n,m,s,t,edges), bty i think the input check should be inside the c'tor while we transform the string into int.
}