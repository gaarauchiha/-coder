#include <iostream>
#include <vector>
using namespace std; //This is Q9

int main() {
    int t;
    cin >> t; // Number of test cases

    while (t--) {
        int n;
        long long f, a, b;
        cin >> n >> f >> a >> b; // Input for n, f, a, b

        vector<long long> m(n + 1); // Moments array with an extra 0 at the start
        m[0] = 0; // First moment is 0

        for (int i = 1; i <= n; i++) {
            cin >> m[i]; // Input moments
        }

        // Process each moment
        for (int i = 1; i <= n; i++) {
            f -= min(a * (m[i] - m[i - 1]), b); // Reduce charge
        }

        // Check if phone still has enough charge
        if (f > 0) {
            cout << "YES" << endl; // Can send all messages
        } else {
            cout << "NO" << endl; // Cannot send all messages
        }
    }

    return 0;
}