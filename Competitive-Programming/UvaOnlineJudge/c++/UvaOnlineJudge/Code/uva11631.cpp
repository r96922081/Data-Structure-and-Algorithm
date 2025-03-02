#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "stdlib.h"
#include "stdio.h"

using namespace std;

static struct Edge {
    Edge(int n1, int n2, int length) : n1(n1), n2(n2), length(length) {}
    int n1;
    int n2;
    int length;
};

static struct compare
{
    bool operator()(const Edge& l, const Edge& r)
    {
        return l.length > r.length;
    }
};


int main11631()
{
    int node_count, edge_count;

    while (true)
    {
        cin >> node_count >> edge_count;

        if (node_count == 0)
            return 0;

        priority_queue<Edge, vector<Edge>, compare > candidate_edges;
        vector<vector<Edge>> edges;
        vector<bool> selected_nodes;

        for (int i = 0; i < node_count; i++)
        {
            selected_nodes.push_back(false);
            edges.push_back(vector<Edge>());
        }

        int all_edge_length_sum = 0;

        for (int i = 0; i < edge_count; i++)
        {
            int n1, n2, length;
            cin >> n1 >> n2 >> length;
            Edge e(n1, n2, length);
            edges[n1].push_back(e);
            edges[n2].push_back(e);
            all_edge_length_sum += length;
        }

        candidate_edges.push(Edge(0, 0, 0));

        int selected_count = 0;
        int selected_edge_length_sum = 0;
        selected_count = 0;

        do
        {
            auto e = candidate_edges.top();
            candidate_edges.pop();

            int new_selected = -1;
            if (selected_nodes[e.n1] == false)
            {
                new_selected = e.n1;
            }
            else if (selected_nodes[e.n2] == false)
            {
                new_selected = e.n2;
            }

            if (new_selected != -1)
            {
                selected_nodes[new_selected] = true;
                selected_count++;
                selected_edge_length_sum += e.length;

                if (selected_count == node_count)
                    break;

                for (int i = 0; i < edges[new_selected].size(); i++)
                    candidate_edges.push(edges[new_selected][i]);

            }
        } while ((selected_count != node_count));

        cout << all_edge_length_sum - selected_edge_length_sum << endl;
    }

    return 0;
}