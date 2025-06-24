#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 1. Plain Recursive
    long long recursive(int idx, const vector<int>& nums, bool isEven) {
        if (idx >= nums.size()) return 0;

        long long skip = recursive(idx + 1, nums, isEven);
        long long val = isEven ? nums[idx] : -nums[idx];
        long long take = val + recursive(idx + 1, nums, !isEven);

        return max(skip, take);
    }

    // 2. Recursive + Memoization (Top-down DP)
    long long memo(int idx, const vector<int>& nums, bool isEven, vector<vector<long long>>& dp) {
        if (idx >= nums.size()) return 0;

        if (dp[idx][isEven] != -1) return dp[idx][isEven];

        long long skip = memo(idx + 1, nums, isEven, dp);
        long long val = isEven ? nums[idx] : -nums[idx];
        long long take = val + memo(idx + 1, nums, !isEven, dp);

        return dp[idx][isEven] = max(skip, take);
    }

    // 3. Tabulation (Bottom-up DP)
    long long tabulation(const vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));

        for (int idx = n - 1; idx >= 0; --idx) {
            for (int isEven = 0; isEven <= 1; ++isEven) {
                long long skip = dp[idx + 1][isEven];
                long long val = isEven ? nums[idx] : -nums[idx];
                long long take = val + dp[idx + 1][!isEven];

                dp[idx][isEven] = max(skip, take);
            }
        }
        return dp[0][1]; // Start from index 0, isEven = true
    }

    // 4. Space Optimized
    long long spaceOptimized(const vector<int>& nums) {
        long long nextEven = 0, nextOdd = 0;

        for (int i = nums.size() - 1; i >= 0; --i) {
            long long currEven = max(nextEven, nums[i] + nextOdd);
            long long currOdd = max(nextOdd, -nums[i] + nextEven);
            nextEven = currEven;
            nextOdd = currOdd;
        }
        return nextEven;
    }

    // Wrapper functions
    long long maxAlternatingSum_recursive(vector<int>& nums) {
        return recursive(0, nums, true);
    }

    long long maxAlternatingSum_memo(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(2, -1));
        return memo(0, nums, true, dp);
    }

    long long maxAlternatingSum_tabulation(vector<int>& nums) {
        return tabulation(nums);
    }

    long long maxAlternatingSum_spaceOptimized(vector<int>& nums) {
        return spaceOptimized(nums);
    }
};

// 🔽 Driver Code (for demonstration)
int main() {
    vector<int> nums = {4, 2, 5, 3};
    Solution sol;

    cout << "Recursive: " << sol.maxAlternatingSum_recursive(nums) << endl;
    cout << "Memoized : " << sol.maxAlternatingSum_memo(nums) << endl;
    cout << "Tabulated: " << sol.maxAlternatingSum_tabulation(nums) << endl;
    cout << "Optimized: " << sol.maxAlternatingSum_spaceOptimized(nums) << endl;

    return 0;
}
