//
//  main.cpp
//  Astar
//
//  Created by 杨帆 on 2020/11/6.
//

#include <iostream>
#include "Astar.h"
using namespace std;

int main(){
    vector<vector<int>> maze = {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
            { 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
        };
        Astar astar;
        astar.initAstar(maze);
     
        //设置起始和结束点
        Point start(1, 1);
        Point end(6, 10);
        //A*算法找寻路径
        list<Point *> path = astar.getPath(start, end, false);
        
        for (auto &p : path)
            cout << '(' << p->x << ',' << p->y << ')' << endl;

}
