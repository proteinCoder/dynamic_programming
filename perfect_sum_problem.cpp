#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Solution {
public:
    // 1. Naive Recursive (from n-1 to 0)
    int countSubsetsRecursive(int i, int currentSum, int target, vector<int> &arr) {
        if (i < 0)
            return (currentSum == target) ? 1 : 0;
        int exclude = countSubsetsRecursive(i - 1, currentSum, target, arr);
        int include = countSubsetsRecursive(i - 1, currentSum + arr[i], target, arr);
        return include + exclude;
    }

    int perfectSumRecursive(vector<int> &arr, int target) {
        return countSubsetsRecursive(arr.size() - 1, 0, target, arr);
    }

    // 2. Recursive with Memoization
    int countSubsetsMemo(int i, int currentSum, int target, vector<int> &arr, vector<vector<int>> &dp) {
        if (i < 0)
            return (currentSum == target) ? 1 : 0;
        if (dp[i][currentSum] != -1)
            return dp[i][currentSum];
        int exclude = countSubsetsMemo(i - 1, currentSum, target, arr, dp);
        int include = 0;
        if (currentSum + arr[i] <= target)
            include = countSubsetsMemo(i - 1, currentSum + arr[i], target, arr, dp);
        return dp[i][currentSum] = include + exclude;
    }

    int perfectSumMemo(vector<int> &arr, int target) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        return countSubsetsMemo(n - 1, 0, target, arr, dp);
    }

    // 3. Bottom-Up Tabulation DP
    int perfectSumTabulation(vector<int> &arr, int target) {
        int n = arr.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int sum = 0; sum <= target; ++sum) {
                dp[i][sum] = dp[i - 1][sum]; // exclude
                if (sum >= arr[i - 1])
                    dp[i][sum] += dp[i - 1][sum - arr[i - 1]]; // include
            }
        }
        return dp[n][target];
    }

    // 4. Space Optimized DP (2D → 1D with reverse traversal)
    int perfectSumSpaceOptimized(vector<int> &arr, int target) {
        int n = arr.size();
        vector<int> dp(target + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < n; ++i) {
            for (int sum = target; sum >= arr[i]; --sum) {
                dp[sum] += dp[sum - arr[i]];
            }
        }
        return dp[target];
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 3};
    int target = 6;

    Solution sol;

    cout << "1. Naive Recursive: "
         << sol.perfectSumRecursive(arr, target) << endl;

    cout << "2. Memoization: "
         << sol.perfectSumMemo(arr, target) << endl;

    cout << "3. Tabulation DP: "
         << sol.perfectSumTabulation(arr, target) << endl;

    cout << "4. Space Optimized DP: "
         << sol.perfectSumSpaceOptimized(arr, target) << endl;

    return 0;
}
