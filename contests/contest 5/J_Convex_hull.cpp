#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

int cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> Andrew_hull(vector<Point>& points){
    sort(points.begin(), points.end());

    int n = points.size();
    vector<Point> res;
    res.reserve(2*n);

    for (int i = 0; i < n; i++) {
        while (res.size() >= 2 && cross(res[res.size()-2], res.back(), points[i]) <= 0) {
            res.pop_back();
        }
        res.push_back(points[i]);
    }

    int lower = res.size();
    for (int i = n - 2; i >= 0; i--) {
        while (res.size() > lower && cross(res[res.size()-2], res.back(), points[i]) <= 0) {
            res.pop_back();
        }
        res.push_back(points[i]);
    }

    res.pop_back();
    sort(res.begin(), res.end());
    
    return res;
}

int main() {
    vector<Point> points;
    int x, y;
    while (cin >> x >> y) {
        points.push_back({x, y});
    }

    vector<Point> hull = Andrew_hull(points);

    cout << "Convex Hull is:" << endl;
    for (Point& p : hull) cout << p.x << " " << p.y << endl;

    return 0;
}