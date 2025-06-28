#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // 1. Pure Recursion (Exponential Time)
    int minPathSum_Recursion(vector<vector<int>>& grid) {
        return recur(grid.size() - 1, grid[0].size() - 1, grid);
    }

    int recur(int i, int j, vector<vector<int>>& grid) {
        if(i < 0 || j < 0) return INT_MAX;
        if(i == 0 && j == 0) return grid[0][0];
        int up = recur(i-1, j, grid);
        int left = recur(i, j-1, grid);
        int minPrev = min(up, left);
        return grid[i][j] + (minPrev == INT_MAX ? 0 : minPrev);
    }

    // 2. Recursion + Memoization
    int minPathSum_Memo(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return memo(n-1, m-1, grid, dp);
    }

    int memo(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
        if(i < 0 || j < 0) return INT_MAX;
        if(i == 0 && j == 0) return grid[0][0];
        if(dp[i][j] != -1) return dp[i][j];
        int up = memo(i-1, j, grid, dp);
        int left = memo(i, j-1, grid, dp);
        int minPrev = min(up, left);
        return dp[i][j] = grid[i][j] + (minPrev == INT_MAX ? 0 : minPrev);
    }

    // 3. Tabulation (Bottom-Up DP)
    int minPathSum_Tabulation(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(i == 0 && j == 0) dp[i][j] = grid[i][j];
                else {
                    int up = (i > 0) ? dp[i-1][j] : INT_MAX;
                    int left = (j > 0) ? dp[i][j-1] : INT_MAX;
                    dp[i][j] = grid[i][j] + min(up, left);
                }
            }
        }
        return dp[n-1][m-1];
    }

    // 4. Space Optimized DP
    int minPathSum_SpaceOptimized(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> prev(m, 0);
        for(int i = 0; i < n; i++) {
            vector<int> curr(m, 0);
            for(int j = 0; j < m; j++) {
                if(i == 0 && j == 0) curr[j] = grid[i][j];
                else {
                    int up = (i > 0) ? prev[j] : INT_MAX;
                    int left = (j > 0) ? curr[j-1] : INT_MAX;
                    curr[j] = grid[i][j] + min(up, left);
                }
            }
            prev = curr;
        }
        return prev[m-1];
    }

    // 5. In-Place Grid Update
    int minPathSum_InPlace(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(i == 0 && j == 0) continue;
                else if(i == 0) grid[i][j] += grid[i][j-1];
                else if(j == 0) grid[i][j] += grid[i-1][j];
                else grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
            }
        }
        return grid[n-1][m-1];
    }
};

// Example usage
int main() {
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    Solution sol;

    cout << "1. Recursion: " << sol.minPathSum_Recursion(grid) << endl;
    cout << "2. Memoization: " << sol.minPathSum_Memo(grid) << endl;
    cout << "3. Tabulation: " << sol.minPathSum_Tabulation(grid) << endl;
    cout << "4. Space Optimized: " << sol.minPathSum_SpaceOptimized(grid) << endl;
    cout << "5. In-Place: " << sol.minPathSum_InPlace(grid) << endl;

    return 0;
}
