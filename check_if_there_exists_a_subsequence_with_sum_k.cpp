#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // 1️⃣ Plain Recursive
    bool solveRecursive(int i, vector<int>& arr, int target) {
        if (target == 0) return true;
        if (i == 0) return target == arr[0];

        bool skip = solveRecursive(i - 1, arr, target);
        bool take = false;
        if (arr[i] <= target)
            take = solveRecursive(i - 1, arr, target - arr[i]);

        return skip || take;
    }

    // 2️⃣ Recursive with Memoization
    bool solveMemo(int i, vector<int>& arr, int target, vector<vector<int>>& dp) {
        if (target == 0) return true;
        if (i == 0) return target == arr[0];

        if (dp[i][target] != -1) return dp[i][target];

        bool skip = solveMemo(i - 1, arr, target, dp);
        bool take = false;
        if (arr[i] <= target)
            take = solveMemo(i - 1, arr, target - arr[i], dp);

        return dp[i][target] = skip || take;
    }

    // 3️⃣ Tabulation (Bottom-Up DP)
    bool solveTabulation(int n, vector<int>& arr, int k) {
        vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

        // Base cases
        for (int i = 0; i < n; i++) dp[i][0] = true;
        if (arr[0] <= k) dp[0][arr[0]] = true;

        for (int i = 1; i < n; i++) {
            for (int target = 1; target <= k; target++) {
                bool skip = dp[i - 1][target];
                bool take = false;
                if (arr[i] <= target)
                    take = dp[i - 1][target - arr[i]];
                dp[i][target] = skip || take;
            }
        }

        return dp[n - 1][k];
    }

    // 4️⃣ Space Optimized DP
    bool solveSpaceOptimized(int n, vector<int>& arr, int k) {
        vector<bool> prev(k + 1, false), curr(k + 1, false);

        prev[0] = true;
        if (arr[0] <= k) prev[arr[0]] = true;

        for (int i = 1; i < n; i++) {
            curr[0] = true;
            for (int target = 1; target <= k; target++) {
                bool skip = prev[target];
                bool take = false;
                if (arr[i] <= target)
                    take = prev[target - arr[i]];
                curr[target] = skip || take;
            }
            prev = curr;
        }

        return prev[k];
    }

    // Main call wrapper
    bool checkSubsequenceSum(int n, vector<int>& arr, int k, string method = "space_opt") {
        if (method == "plain")
            return solveRecursive(n - 1, arr, k);
        else if (method == "memo") {
            vector<vector<int>> dp(n, vector<int>(k + 1, -1));
            return solveMemo(n - 1, arr, k, dp);
        }
        else if (method == "tab")
            return solveTabulation(n, arr, k);
        else // default to space optimized
            return solveSpaceOptimized(n, arr, k);
    }
};

int main() {
    Solution sol;

    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int k = 9;
    int n = arr.size();

    cout << "Plain Recursion: " << sol.checkSubsequenceSum(n, arr, k, "plain") << "\n";
    cout << "Memoization: "     << sol.checkSubsequenceSum(n, arr, k, "memo") << "\n";
    cout << "Tabulation: "      << sol.checkSubsequenceSum(n, arr, k, "tab") << "\n";
    cout << "Space Optimized: " << sol.checkSubsequenceSum(n, arr, k, "space_opt") << "\n";

    return 0;
}
