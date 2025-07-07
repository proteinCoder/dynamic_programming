#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int md = 1e9 + 7;
    typedef long long ll;
    typedef pair<ll, ll> pll;

    // -------------------- 1. PURE RECURSION --------------------
    pll dfsRec(int i, int j, vector<vector<int>>& grid) {
        if (i == 0 && j == 0) {
            ll val = grid[0][0];
            return {val, val};
        }

        ll maxi = LLONG_MIN, mini = LLONG_MAX;

        if (j > 0) {
            auto [leftMax, leftMin] = dfsRec(i, j - 1, grid);
            maxi = max({maxi, grid[i][j] * leftMax, grid[i][j] * leftMin});
            mini = min({mini, grid[i][j] * leftMax, grid[i][j] * leftMin});
        }

        if (i > 0) {
            auto [upMax, upMin] = dfsRec(i - 1, j, grid);
            maxi = max({maxi, grid[i][j] * upMax, grid[i][j] * upMin});
            mini = min({mini, grid[i][j] * upMax, grid[i][j] * upMin});
        }

        return {maxi, mini};
    }

    // -------------------- 2. MEMOIZATION --------------------
    pll dfsMemo(int i, int j, vector<vector<int>>& grid, vector<vector<pll>>& dp) {
        if (i == 0 && j == 0) {
            ll val = grid[0][0];
            return {val, val};
        }

        if (dp[i][j] != make_pair(LLONG_MIN, LLONG_MAX))
            return dp[i][j];

        ll maxi = LLONG_MIN, mini = LLONG_MAX;

        if (j > 0) {
            auto [leftMax, leftMin] = dfsMemo(i, j - 1, grid, dp);
            maxi = max({maxi, grid[i][j] * leftMax, grid[i][j] * leftMin});
            mini = min({mini, grid[i][j] * leftMax, grid[i][j] * leftMin});
        }

        if (i > 0) {
            auto [upMax, upMin] = dfsMemo(i - 1, j, grid, dp);
            maxi = max({maxi, grid[i][j] * upMax, grid[i][j] * upMin});
            mini = min({mini, grid[i][j] * upMax, grid[i][j] * upMin});
        }

        return dp[i][j] = {maxi, mini};
    }

    // -------------------- 3. TABULATION --------------------
    int maxProductTabulation(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<pll>> dp(n, vector<pll>(m));

        dp[0][0] = {grid[0][0], grid[0][0]};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 && j == 0) continue;

                ll maxi = LLONG_MIN, mini = LLONG_MAX;

                if (j > 0) {
                    auto [leftMax, leftMin] = dp[i][j - 1];
                    maxi = max({maxi, grid[i][j] * leftMax, grid[i][j] * leftMin});
                    mini = min({mini, grid[i][j] * leftMax, grid[i][j] * leftMin});
                }

                if (i > 0) {
                    auto [upMax, upMin] = dp[i - 1][j];
                    maxi = max({maxi, grid[i][j] * upMax, grid[i][j] * upMin});
                    mini = min({mini, grid[i][j] * upMax, grid[i][j] * upMin});
                }

                dp[i][j] = {maxi, mini};
            }
        }

        ll res = dp[n - 1][m - 1].first;
        return res < 0 ? -1 : res % md;
    }

    // -------------------- 4. SPACE OPTIMIZED --------------------
    int maxProductSpaceOptimized(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<pll> prev(m), curr(m);

        prev[0] = {grid[0][0], grid[0][0]};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 && j == 0 && i == 0) continue;

                ll maxi = LLONG_MIN, mini = LLONG_MAX;

                if (j > 0) {
                    auto [leftMax, leftMin] = curr[j - 1];
                    maxi = max({maxi, grid[i][j] * leftMax, grid[i][j] * leftMin});
                    mini = min({mini, grid[i][j] * leftMax, grid[i][j] * leftMin});
                }

                if (i > 0) {
                    auto [upMax, upMin] = prev[j];
                    maxi = max({maxi, grid[i][j] * upMax, grid[i][j] * upMin});
                    mini = min({mini, grid[i][j] * upMax, grid[i][j] * upMin});
                }

                curr[j] = {maxi, mini};
            }
            prev = curr;
        }

        ll res = prev[m - 1].first;
        return res < 0 ? -1 : res % md;
    }

    // -------------------- MASTER CALL FUNCTION --------------------
    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        // Uncomment one of the below approaches to test

        // 1. Pure Recursion (not recommended for large inputs)
        // auto [maxP, minP] = dfsRec(n - 1, m - 1, grid);
        // return maxP < 0 ? -1 : maxP % md;

        // 2. Memoization
        vector<vector<pll>> dp(n, vector<pll>(m, {LLONG_MIN, LLONG_MAX}));
        auto [maxP, minP] = dfsMemo(n - 1, m - 1, grid, dp);
        return maxP < 0 ? -1 : maxP % md;

        // 3. Tabulation
        // return maxProductTabulation(grid);

        // 4. Space Optimized Tabulation
        // return maxProductSpaceOptimized(grid);
    }
};

// -------------------- Example Usage --------------------
int main() {
    Solution sol;
    vector<vector<int>> grid = {
        {1, -2, 1},
        {1, -2, 1},
        {3, -4, 1}
    };

    cout << "Max Product Path: " << sol.maxProductPath(grid) << endl;
    return 0;
}
