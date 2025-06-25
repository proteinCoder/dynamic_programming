#include <iostream>
#include <vector>
using namespace std;

// ---------- 1. Recursive (Bottom-Right to Top-Left) ----------
int uniquePathsRecursive(int n, int m) {
    if (n == 1 || m == 1)
        return 1;
    return uniquePathsRecursive(n - 1, m) + uniquePathsRecursive(n, m - 1);
}

// ---------- 2. Memoization (Top-Down DP) ----------
int dfs(int n, int m, vector<vector<int>>& memo) {
    if (n == 1 || m == 1)
        return 1;
    if (memo[n][m] != -1)
        return memo[n][m];
    return memo[n][m] = dfs(n - 1, m, memo) + dfs(n, m - 1, memo);
}

int uniquePathsMemo(int n, int m) {
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
    return dfs(n, m, memo);
}

// ---------- 3. DP Tabulation (Bottom-Up) ----------
int uniquePathsDP(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, 1));

    for (int i = n - 2; i >= 0; --i)
        for (int j = m - 2; j >= 0; --j)
            dp[i][j] = dp[i + 1][j] + dp[i][j + 1];

    return dp[0][0];
}

// ---------- 4. Space Optimized DP ----------
int uniquePathsDPOptimized(int n, int m) {
    vector<int> dp(m, 1);

    for (int i = n - 2; i >= 0; --i)
        for (int j = m - 2; j >= 0; --j)
            dp[j] += dp[j + 1];

    return dp[0];
}

// ---------- 5. Combinatorics ----------
int uniquePathsCombinatorics(int n, int m) {
    long long res = 1;
    for (int i = 1; i <= n - 1; ++i)
        res = res * (m - 1 + i) / i;
    return (int)res;
}

// ---------- Main Program ----------
int main() {
    int n, m;
    cout << "Enter number of rows (n): ";
    cin >> n;
    cout << "Enter number of columns (m): ";
    cin >> m;

    cout << "\n--- Unique Paths from bottom-right to top-left for " << n << "x" << m << " grid ---\n";
    cout << "1. Recursive (Brute Force): ";
    if (n <= 10 && m <= 10)
        cout << uniquePathsRecursive(n, m) << endl;
    else
        cout << "Skipped (too large for recursion)\n";

    cout << "2. Memoization (Top-Down DP): " << uniquePathsMemo(n, m) << endl;
    cout << "3. DP Tabulation (Bottom-Up): " << uniquePathsDP(n, m) << endl;
    cout << "4. Space Optimized DP: " << uniquePathsDPOptimized(n, m) << endl;
    cout << "5. Combinatorics: " << uniquePathsCombinatorics(n, m) << endl;

    return 0;
}
