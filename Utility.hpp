#ifndef UTILITY_HPP
#define	UTILITY_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * 座標を表す
 */
class Point {
public:
    int x, y;
    void set(int i, int j);//*this=(i,j)
    bool equal(int i, int j)const;//*thisと(i,j)が等しいかどうか
    bool operator==(const Point &point)const;//点同士が等しいかどうか
};

int getRandom(int max);//0からmax-1までのランダムな整数値を返す
void sleep(double t);//指定秒休憩

#endif	/* UTILITY_HPP */

