//
//  dijkstra.h
//  dijkstra
//
//  Created by 杨帆 on 2020/11/3.
//

#pragma once

#include <iostream>
#include <string>
using namespace std;

struct Distances{
    string path;
    int value;
    bool visit;
    Distances(){
        visit = false;
        value = 0;
        path = "";
    }
};

class Graph{
private:
    int verticesNum;
    int edgeNum;
    int **arc;
    Distances *dis;
public:
    Graph(int verticesNum, int edgeNum);
    ~Graph();
    bool check_edge_value(int start, int end, int weight);
    void createGraph();
    void printGraph();
    void dijkstra(int begin);
    void printPath(int begin);
};
