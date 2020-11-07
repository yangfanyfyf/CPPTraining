//
//  Astar.hpp
//  Astar
//
//  Created by 杨帆 on 2020/11/6.
//

#pragma once

#include <vector>
#include <list>
using namespace std;

const int kCost1 = 10;
const int kCost2 = 14;

struct Point{
    int x;
    int y;
    int F, G, H;
    Point *parent;
    Point(int _x, int _y):x(_x), y(_y), F(0), G(0), H(0), parent(NULL){}
    
};

class Astar{
public:
    void initAstar(vector<vector<int> > &_maze);
    list<Point *> getPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    
public: // 是什么类型的？？？？？？
    Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
    bool canReach(const Point *point, const Point *target, bool isIgnoreCorner) const;
    Point *isInlist(const list<Point *> &list, const Point *point) const;
    Point *getLeastFPoint();
    
    int calcG(Point *tempStart, Point *point);
    int calcH(Point *point, Point *end);
    int calcF(Point *point);
private:
    vector<vector<int> > maze;
    list<Point *> openList;
    list<Point *> closeList;
    
};
