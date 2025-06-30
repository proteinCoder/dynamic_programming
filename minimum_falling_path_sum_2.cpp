#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    // Plain Recursion
    int plainRec(int i, int j, vector<vector<int>>& matrix) {
        int m = matrix[0].size();
        if (j < 0 || j >= m) return 1e9;
        if (i == 0) return matrix[0][j];

        int ans = INT_MAX;
        for (int newj = 0; newj < m; newj++) {
            if (newj == j) continue;
            ans = min(ans, matrix[i][j] + plainRec(i - 1, newj, matrix));
        }
        return ans;
    }

    // Memoization (Top-Down DP)
    int memoRec(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
        int m = matrix[0].size();
        if (j < 0 || j >= m) return 1e9;
        if (i == 0) return matrix[0][j];
        if (dp[i][j] != -1) return dp[i][j];

        int ans = INT_MAX;
        for (int newj = 0; newj < m; newj++) {
            if (newj == j) continue;
            ans = min(ans, matrix[i][j] + memoRec(i - 1, newj, matrix, dp));
        }
        return dp[i][j] = ans;
    }

    // Tabulation (Bottom-Up DP)
    int tabulation(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int j = 0; j < m; j++) dp[0][j] = matrix[0][j];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int minPrev = INT_MAX;
                for (int k = 0; k < m; k++) {
                    if (k == j) continue;
                    minPrev = min(minPrev, dp[i - 1][k]);
                }
                dp[i][j] = matrix[i][j] + minPrev;
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }

    // Space Optimized Bottom-Up DP
    int spaceOptimized(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<int> prev(m, 0), curr(m, 0);
        for (int j = 0; j < m; j++) prev[j] = matrix[0][j];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int minPrev = INT_MAX;
                for (int k = 0; k < m; k++) {
                    if (k == j) continue;
                    minPrev = min(minPrev, prev[k]);
                }
                curr[j] = matrix[i][j] + minPrev;
            }
            prev = curr;
        }

        return *min_element(prev.begin(), prev.end());
    }

    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();

        // Method 1: Plain Recursion
        /*
        int ans = INT_MAX;
        for (int j = 0; j < m; j++)
            ans = min(ans, plainRec(n - 1, j, matrix));
        return ans;
        */

        // Method 2: Memoization
        /*
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int ans = INT_MAX;
        for (int j = 0; j < m; j++)
            ans = min(ans, memoRec(n - 1, j, matrix, dp));
        return ans;
        */

        // Method 3: Tabulation
        // return tabulation(matrix);

        // Method 4: Space Optimized
        return spaceOptimized(matrix);
    }
};

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Solution sol;
    cout << "Minimum Falling Path Sum II: " << sol.minFallingPathSum(matrix) << endl;

    return 0;
}
