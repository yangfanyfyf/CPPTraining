//
//  main.cpp
//  dijkstra
//
//  Created by 杨帆 on 2020/11/3.
//

#include <iostream>
#include "dijkstra.h"

bool check(int verticesNum, int edgeNum){
    if (verticesNum <= 0 || edgeNum <= 0 || (verticesNum*(verticesNum-1)/2)<edgeNum){
        return false;
    }
    return true;
}


int main(){
    int verticesNum;
    int edgeNum;
    cout << "输入图的顶点个数和边的条数：" << endl;
    cin >> verticesNum >> edgeNum;
    while (!check(verticesNum, edgeNum)){
        cout << "输入不合法，请重新输入" << endl;
        cin >> verticesNum >> edgeNum;
    }
    Graph graph(verticesNum, edgeNum);
    
    graph.createGraph();
    graph.printGraph();
    graph.dijkstra(1);
    graph.printPath(1);
    return 0;
}
