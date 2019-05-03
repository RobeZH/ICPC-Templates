#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
typedef pair<int, int> P;
typedef long long ll;
using namespace __gnu_pbds;

typedef tree<
        pair<int, int>,
        null_type,
        less<>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        my_tree;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cout << tree.find_by_order(2) << endl;
    cout << tree.order_of_key({1, 2}) << endl;
}