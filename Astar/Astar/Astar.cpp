//
//  Astar.cpp
//  Astar
//
//  Created by 杨帆 on 2020/11/6.
//

#include "Astar.h"
#include <math.h>

void Astar::initAstar(vector<vector<int> > &_maze){
    maze = _maze;
}

int Astar::calcG(Point *tempStart, Point *point){
    int extraG = (abs(point->x - tempStart->x) + abs(point->y - tempStart->y)) == 1 ? kCost1 : kCost2; // 横向纵向移动cost1,否则cost2
    int parentG = point->parent == NULL ? 0 : point->parent->G; // 距离初始点的距离
    return parentG + extraG;
}

int Astar::calcH(Point *point, Point *end){
    return sqrt(pow((double)(end->x - point->x), 2) + pow((double)(end->y - point->y), 2));
}

int Astar::calcF(Point *point){
    return point->G + point->H;
}

Point *Astar::getLeastFPoint(){
    if (!openList.empty()){
        Point *resPoint = openList.front();
        for (auto &point : openList){
            if (point->F < resPoint->F){
                resPoint = point;
            }
        }
        return resPoint;
    }
    return NULL;
}

vector<Point *> Astar::getSurroundPoints(const Point *point, bool isIgnoreCorner) const{
    vector<Point *> surroundPoints;
    for (int x = point->x - 1; x != point->x + 2; ++x){
        for (int y = point->y - 1; y != point->y + 2; ++y){
            if (canReach(point, new Point(x, y), isIgnoreCorner)){
                surroundPoints.push_back(new Point(x, y));
            }
        }
    }
    return surroundPoints;
}

bool Astar::canReach(const Point *point, const Point *target, bool isIgnoreCorner) const{
    if (target->x < 0 || target->x > maze.size() - 1 || target->y < 0 || target->y > maze[0].size() - 1 || maze[target->x][target->y] == 1 || (target->x == point->x && target-> y == point->y) ||
        isInlist(closeList, target))
        return false;
    else{
        if (abs(point->x - target->x) + abs(point->y - target ->y) == 1)
            return true;
        else
            return isIgnoreCorner;
    }
}

Point *Astar::isInlist(const list<Point *> &list, const Point *point) const{
    for(auto &p : list){
        if (p->x == point->x && p->y == point->y){
            return p;
        }
    }
    return NULL;
}


Point *Astar::findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner){
    openList.push_back(new Point(startPoint.x, startPoint.y));
    
    while (!openList.empty()){
        auto curPoint = getLeastFPoint();
        openList.remove(curPoint);
        closeList.push_back(curPoint);
        
        auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
        
        for (auto &target : surroundPoints){
            if (!isInlist(openList, target)){
                target->parent =curPoint;
                target->G = calcG(curPoint, target);
                target->H = calcH(target, &endPoint);
                target->F = calcF(target);
                openList.push_back(target);
            }
            else{
                int tempG = calcG(curPoint, target);
                if (tempG < target->G){
                    target->parent = curPoint;
                    target->G = tempG;
                    target->F = calcF(target);
                }
            }
            Point *resPoint = isInlist(openList, &endPoint);
            if (resPoint){
                return resPoint;  // 深拷贝？？？
            }
        }
    }
    return NULL;
}


list<Point *> Astar::getPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner){
    Point *result = findPath(startPoint, endPoint, isIgnoreCorner);
    list<Point *> path;
    while(result){
        path.push_front(result);
        result = result->parent;
    }
    openList.clear();
    closeList.clear();
    
    return path;
}
