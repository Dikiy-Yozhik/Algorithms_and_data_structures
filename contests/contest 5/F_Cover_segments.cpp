#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    long long int left, right;
};

bool compare_segments(const Segment &a, const Segment &b) {
    return a.right < b.right;
}

int main() {
    int n;
    cin >> n;

    vector<Segment> segments (n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].left >> segments[i].right;
    }

    sort(segments.begin(), segments.end(), compare_segments);

    vector<int> points;
    int last = -1;
    for (const auto& seg : segments) {
        if (last < seg.left || last > seg.right) {
            points.push_back(seg.right);
            last = seg.right;
        }
    }

    cout << points.size() << endl;
    for (int i = 0; i < points.size(); i++) {
        if (i != 0) cout << " ";
        cout << points[i];
    }

    return 0;
}