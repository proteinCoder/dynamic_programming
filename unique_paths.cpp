#include <bits/stdc++.h>
using namespace std;

int n = 3, m = 3; // Grid size, can be customized

// 1. Pure Recursion (Exponential Time)
int countPathsRecursive(int i, int j) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;

    int up = countPathsRecursive(i - 1, j);
    int left = countPathsRecursive(i, j - 1);
    return up + left;
}

// 2. Memoization (Top-Down DP)
int countPathsMemo(int i, int j, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    int up = countPathsMemo(i - 1, j, dp);
    int left = countPathsMemo(i, j - 1, dp);
    return dp[i][j] = up + left;
}

// 3. Tabulation (Bottom-Up DP)
int countPathsTabulation(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 && j == 0) continue;
            int up = (i > 0) ? dp[i - 1][j] : 0;
            int left = (j > 0) ? dp[i][j - 1] : 0;
            dp[i][j] = up + left;
        }
    }
    return dp[n - 1][m - 1];
}

// 4. Space Optimized DP (Using 1D Array)
int countPathsSpaceOptimized(int n, int m) {
    vector<int> prev(m, 0);
    for (int i = 0; i < n; ++i) {
        vector<int> curr(m, 0);
        for (int j = 0; j < m; ++j) {
            if (i == 0 && j == 0) curr[j] = 1;
            else {
                int up = (i > 0) ? prev[j] : 0;
                int left = (j > 0) ? curr[j - 1] : 0;
                curr[j] = up + left;
            }
        }
        prev = curr;
    }
    return prev[m - 1];
}

int main() {
    cout << "Grid size: " << n << " x " << m << "\n";

    // 1. Recursive
    cout << "1. Pure Recursion: " << countPathsRecursive(n - 1, m - 1) << "\n";

    // 2. Memoization
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << "2. Memoization: " << countPathsMemo(n - 1, m - 1, dp) << "\n";

    // 3. Tabulation
    cout << "3. Tabulation: " << countPathsTabulation(n, m) << "\n";

    // 4. Space Optimized
    cout << "4. Space Optimized: " << countPathsSpaceOptimized(n, m) << "\n";

    return 0;
}
