#include <bits/stdc++.h>
using namespace std;

int main() {
    int l, m;
    cin >> l >> m;
    vector<pair<int, int>> regions(m);
    for (int i = 0; i < m; i++) { 
        cin >> regions[i].first >> regions[i].second;
    }

    vector<bool> trees(l + 1, false); 
    for (const auto& region : regions) {
        int u = region.first;
        int v = region.second;
        for (int i = u; i <= v; i++) {
            if (i >= 0 && i <= l) {
                trees[i] = true; 
            }
        }
    }
    int remaining_trees = count(trees.begin(), trees.end(), false);
    cout << remaining_trees << endl;

    return 0;
}
