#include <iostream>
#include <vector>
using namespace std;

// ---------- 1. Recursive (Brute Force) ----------
int uniquePathsRecursive(int m, int n) {
    if (m == 1 || n == 1)
        return 1;
    return uniquePathsRecursive(m - 1, n) + uniquePathsRecursive(m, n - 1);
}

// ---------- 2. Memoization (Top-Down DP) ----------
int dfs(int m, int n, vector<vector<int>>& memo) {
    if (m == 1 || n == 1)
        return 1;
    if (memo[m][n] != -1)
        return memo[m][n];
    return memo[m][n] = dfs(m - 1, n, memo) + dfs(m, n - 1, memo);
}

int uniquePathsMemo(int m, int n) {
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    return dfs(m, n, memo);
}

// ---------- 3. DP Tabulation (Bottom-Up) ----------
int uniquePathsDP(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));
    
    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    
    return dp[m - 1][n - 1];
}

// ---------- 4. Space Optimized DP ----------
int uniquePathsDPOptimized(int m, int n) {
    vector<int> dp(n, 1);
    
    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp[j] += dp[j - 1];
    
    return dp[n - 1];
}

// ---------- 5. Combinatorics ----------
int uniquePathsCombinatorics(int m, int n) {
    long long res = 1;
    for (int i = 1; i <= m - 1; ++i) {
        res = res * (n - 1 + i) / i;
    }
    return (int)res;
}

// ---------- Main Program ----------
int main() {
    int m, n;
    cout << "Enter grid size (m rows, n columns): ";
    cin >> m >> n;

    cout << "\n--- Unique Paths for " << m << "x" << n << " Grid ---\n";
    cout << "1. Recursive (Brute Force): ";
    if (m <= 10 && n <= 10) // limit size for recursion
        cout << uniquePathsRecursive(m, n) << endl;
    else
        cout << "Skipped (too large for recursion)\n";

    cout << "2. Memoization (Top-Down DP): " << uniquePathsMemo(m, n) << endl;
    cout << "3. DP Tabulation (Bottom-Up): " << uniquePathsDP(m, n) << endl;
    cout << "4. Space Optimized DP: " << uniquePathsDPOptimized(m, n) << endl;
    cout << "5. Combinatorics: " << uniquePathsCombinatorics(m, n) << endl;

    return 0;
}
