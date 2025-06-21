#include <iostream>
#include <vector>
using namespace std;

class HouseRobber {
public:
    // 1. Brute Force (Recursive from end to start)
    int robBruteForce(vector<int>& nums, int index) {
        if (index < 0) return 0;

        // Choose to rob this house or skip it
        int rob = nums[index] + robBruteForce(nums, index - 2);
        int skip = robBruteForce(nums, index - 1);
        return max(rob, skip);
    }

    // 2. Memoization (Top-Down DP, Reverse)
    int robMemoized(vector<int>& nums, int index, vector<int>& memo) {
        if (index < 0) return 0;
        if (memo[index] != -1) return memo[index];

        int rob = nums[index] + robMemoized(nums, index - 2, memo);
        int skip = robMemoized(nums, index - 1, memo);
        return memo[index] = max(rob, skip);
    }

    int robMemoization(vector<int>& nums) {
        int n = nums.size();
        vector<int> memo(n, -1);
        return robMemoized(nums, n - 1, memo);
    }

    // 3. Tabulation (Bottom-Up DP)
    int robTabulation(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
        }

        return dp[n - 1];
    }

    // 4. Space Optimized DP
    int robOptimized(vector<int>& nums) {
        int prev2 = 0; // dp[i - 2]
        int prev1 = 0; // dp[i - 1]

        for (int amount : nums) {
            int curr = max(prev1, amount + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    vector<int> houses = {2, 7, 9, 3, 1};
    int n = houses.size();

    HouseRobber solver;

    cout << "House values: ";
    for (int val : houses) cout << val << " ";
    cout << "\n\n";

    cout << "1. Brute Force (Reverse): "
         << solver.robBruteForce(houses, n - 1) << endl;

    cout << "2. Memoization (Reverse): "
         << solver.robMemoization(houses) << endl;

    cout << "3. Tabulation: "
         << solver.robTabulation(houses) << endl;

    cout << "4. Space Optimized DP: "
         << solver.robOptimized(houses) << endl;

    return 0;
}
