#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int mod = 1e9 + 7;

    // 1. Plain Recursive (No memoization)
    int countSubsetsRecursive(int i, int currentSum, int arr[], int target) {
        if (i < 0)
            return (currentSum == target) ? 1 : 0;

        // Don't pick the current element
        int exclude = countSubsetsRecursive(i - 1, currentSum, arr, target);

        // Pick the current element
        int include = countSubsetsRecursive(i - 1, currentSum + arr[i], arr, target);

        return (include + exclude);
    }

    int perfectSumRecursive(int arr[], int n, int target) {
        return countSubsetsRecursive(n - 1, 0, arr, target);
    }

    // 2. Recursive with Memoization
    int f(int ind, int arr[], int n, int target, vector<vector<int>> &dp) {
        if (ind == 0) {
            if (target == 0 && arr[0] == 0) return 2;
            if (target == 0 || target == arr[0]) return 1;
            return 0;
        }

        if (dp[ind][target] != -1) return dp[ind][target];

        int notPick = f(ind - 1, arr, n, target, dp) % mod;
        int pick = 0;
        if (arr[ind] <= target)
            pick = f(ind - 1, arr, n, target - arr[ind], dp) % mod;

        return dp[ind][target] = (pick + notPick) % mod;
    }

    int perfectSumMemo(int arr[], int n, int sum) {
        vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
        return f(n - 1, arr, n, sum, dp);
    }

    // 3. Bottom-Up Tabulation DP
    int perfectSumTabulation(int arr[], int n, int sum) {
        vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

        // Base Case
        if (arr[0] == 0)
            dp[0][0] = 2; // pick and not pick
        else
            dp[0][0] = 1; // only not pick

        if (arr[0] != 0 && arr[0] <= sum)
            dp[0][arr[0]] = 1;

        for (int ind = 1; ind < n; ind++) {
            for (int target = 0; target <= sum; target++) {
                int notPick = dp[ind - 1][target] % mod;
                int pick = 0;
                if (arr[ind] <= target)
                    pick = dp[ind - 1][target - arr[ind]] % mod;
                dp[ind][target] = (pick + notPick) % mod;
            }
        }

        return dp[n - 1][sum];
    }

    // 4. Space Optimized DP (2 rows: prev & curr)
    int perfectSumSpaceOptimized(int arr[], int n, int sum) {
        vector<int> prev(sum + 1, 0);

        if (arr[0] == 0)
            prev[0] = 2;
        else
            prev[0] = 1;

        if (arr[0] != 0 && arr[0] <= sum)
            prev[arr[0]] = 1;

        for (int ind = 1; ind < n; ind++) {
            vector<int> curr(sum + 1, 0);
            for (int target = 0; target <= sum; target++) {
                int notPick = prev[target] % mod;
                int pick = 0;
                if (arr[ind] <= target)
                    pick = prev[target - arr[ind]] % mod;
                curr[target] = (pick + notPick) % mod;
            }
            prev = curr;
        }

        return prev[sum];
    }

    // 5. Fully Space Optimized DP (Single 1D array)
    int perfectSumFullyOptimized(int arr[], int n, int sum) {
        vector<int> dp(sum + 1, 0);

        if (arr[0] == 0)
            dp[0] = 2;
        else
            dp[0] = 1;

        if (arr[0] != 0 && arr[0] <= sum)
            dp[arr[0]] = 1;

        for (int ind = 1; ind < n; ind++) {
            for (int target = sum; target >= 0; target--) {
                int pick = 0;
                if (arr[ind] <= target)
                    pick = dp[target - arr[ind]];
                dp[target] = (dp[target] + pick) % mod;
            }
        }

        return dp[sum];
    }
};

int main() {
    Solution sol;

    int arr[] = {0, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 1;

    cout << "1. Plain Recursive: "
         << sol.perfectSumRecursive(arr, n, sum) << endl;

    cout << "2. Recursive + Memoization: "
         << sol.perfectSumMemo(arr, n, sum) << endl;

    cout << "3. Tabulation DP: "
         << sol.perfectSumTabulation(arr, n, sum) << endl;

    cout << "4. Space Optimized DP (2 arrays): "
         << sol.perfectSumSpaceOptimized(arr, n, sum) << endl;

    cout << "5. Fully Space Optimized DP (1 array): "
         << sol.perfectSumFullyOptimized(arr, n, sum) << endl;

    return 0;
}
