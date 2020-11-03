//
//  dijkstra.cpp
//  dijkstra
//
//  Created by 杨帆 on 2020/11/3.
//

#include "dijkstra.h"

Graph::Graph(int vertices, int edge){
    verticesNum = vertices;
    edgeNum = edge;
    arc = new int*[this->verticesNum];
    dis = new Distances[this->verticesNum];
    for (int i = 0; i < this->verticesNum; ++i){
        arc[i] = new int[this->verticesNum];
        for (int k = 0; k < this->verticesNum; ++k){
            arc[i][k] = INT_MAX;
        }
    }
}

Graph::~Graph(){
    delete[] dis;
    for (int i = 0; i < this->verticesNum; ++i){
        delete this->arc[i];
    }
    delete arc;
}

bool Graph::check_edge_value(int start, int end, int weight){
    if (start < 1 || end < 1 || start > verticesNum || end > verticesNum || weight < 0){
        return false;
    }
    return true;
}


void Graph::createGraph(){
    cout << "请输入每条边的起点和权重：" << endl;
    int start;
    int end;
    int weight;
    int count = 0;
    
    while (count != this->edgeNum){
        
        cin >> start >> end >> weight;
        
        while (!this->check_edge_value(start, end, weight)){
            cout << "非法输入，请重新输入！" << endl;
            cin >> start >> end >> weight;
        }
        arc[start - 1][end - 1] = weight;
        
        ++count;
        
    }
}

void Graph::printGraph(){
    cout << "图的邻接矩阵是：" << endl;
    int count_row = 0;
    int count_col = 0;
    while (count_row != this->verticesNum){
        count_col = 0;
        while (count_col != this->verticesNum) {
            if (arc[count_row][count_col] == INT_MAX){
                cout << "X" << " ";
            }
            else{
                cout << arc[count_row][count_col] << " ";
            }
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}

void Graph::dijkstra(int begin){
    for (int i = 0; i != this->verticesNum; ++i){
        dis[i].path = "v" + to_string(begin) + "-->" + to_string(i + 1);
        dis[i].value = arc[begin - 1][i];
    }
    
    dis[begin - 1].value = 0;
    dis[begin - 1].visit = true;
    
    int count = 1;
    while (count != this->verticesNum){
        int temp = 0;
        int min = INT_MAX;
        for (int i = 0; i != this->verticesNum; ++i){
            if (!dis[i].visit && dis[i].value < min){
                min = dis[i].value;
                temp = i;
            }
        }
        dis[temp].visit = true;
        ++count;
        
        
        for (int i = 0; i != this->verticesNum; ++i){
            if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value){
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "-->" + to_string(i + 1);
            }
        }
    }
    
}


void Graph::printPath(int begin){
    string str;
    str = "v" + to_string(begin);
    cout << "以" << str << "为起点的最短路径为:" << endl;
    for (int i = 0; i != this->verticesNum; ++i){
        if (dis[i].value != INT_MAX){
            cout << dis[i].path << "=" << dis[i].value << endl;
        }
        else{
            cout << dis[i].path << "是无最短路径的" << endl;
        }
    }
}
