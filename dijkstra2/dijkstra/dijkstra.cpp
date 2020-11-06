//
//  dijkstra.cpp
//  dijkstra
//
//  Created by 杨帆 on 2020/11/3.
//

#include "dijkstra.h"

Graph::Graph(int vertices, int edge){ // 初始化地图
    verticesNum = vertices;
    edgeNum = edge;
    //arc = new int*[this->verticesNum];
    
    
    dis = new Distances[this->verticesNum];
    for (int i = 0; i < this->verticesNum; ++i){
        //arc[i] = new int[this->verticesNum];
        vector<int> mArc;
        
        for (int k = 0; k < this->verticesNum; ++k){
            //arc[i][k] = INT_MAX;
            mArc.push_back(INT_MAX);
        }
        arc.push_back(mArc);
    }
    
    //或者
//    vector<int> mArc(verticesNum, INT_MAX);
//    for (int i = 0; i != verticesNum; ++i){
//        arc.push_back(mArc);
//    }
}

Graph::~Graph(){
    delete[] dis;
//    for (int i = 0; i < this->verticesNum; ++i){
//        delete this->arc[i];
//    }
//    delete arc;
}

bool Graph::check_edge_value(int start, int end, int weight){ // 保证输入合理
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
        
        arc[start - 1][end - 1] = weight; // 修改地图
        
        ++count;
        
    }
}

void Graph::printGraph(){
    cout << "图的邻接矩阵是：" << endl;
    int count_row = 0;
    int count_col = 0;
    while (count_row != this->verticesNum){ // 打印完一行后换行
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
    //初始化
    for (int i = 0; i != this->verticesNum; ++i){
        dis[i].path = "v" + to_string(begin) + "-->" + to_string(i + 1);
        dis[i].value = arc[begin - 1][i];
    }
    dis[begin - 1].value = 0;// 存储到每个点的最短距离
    dis[begin - 1].visit = true;
    
    // 选出离起点最短的点
    int count = 1;
    while (count != this->verticesNum){ // 遍历所有的点
        int temp = 0;
        int min = INT_MAX;
        for (int i = 0; i != this->verticesNum; ++i){
            // 未访问过，离begin最近的点
            if (!dis[i].visit && dis[i].value < min){
                min = dis[i].value;
                temp = i;
            }
        }
        dis[temp].visit = true; // 下一次就会从第二小的开始
        ++count;
        
        // 以这个点为中继更新所有的点
        for (int i = 0; i != this->verticesNum; ++i){
            if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value){
                dis[i].value = dis[temp].value + arc[temp][i];//新的距离
                dis[i].path = dis[temp].path + "-->" + to_string(i + 1); //到达temp的新路径
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
