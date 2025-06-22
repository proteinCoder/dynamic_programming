#include <bits/stdc++.h>
using namespace std;

// 🧠 MEMOIZATION (TOP-DOWN)
class SolutionMemo {
public:
    int f(int i, vector<int>& height, vector<int>& dp) {
        if (i == 0) return 0;
        if (dp[i] != -1) return dp[i];

        int left = f(i - 1, height, dp) + abs(height[i] - height[i - 1]);
        int right = (i > 1) ? f(i - 2, height, dp) + abs(height[i] - height[i - 2]) : INT_MAX;

        return dp[i] = min(left, right);
    }

    int minCost(vector<int>& height) {
        int n = height.size();
        vector<int> dp(n, -1);
        return f(n - 1, height, dp);
    }
};

// 📊 TABULATION (BOTTOM-UP)
class SolutionTabulation {
public:
    int minCost(vector<int>& height) {
        int n = height.size();
        vector<int> dp(n, 0);
        dp[0] = 0;

        for (int i = 1; i < n; ++i) {
            int left = dp[i - 1] + abs(height[i] - height[i - 1]);
            int right = (i > 1) ? dp[i - 2] + abs(height[i] - height[i - 2]) : INT_MAX;
            dp[i] = min(left, right);
        }
        return dp[n - 1];
    }
};

// ♻️ SPACE OPTIMIZED
class SolutionSpaceOptimized {
public:
    int minCost(vector<int>& height) {
        int n = height.size();
        int prev1 = 0;       // dp[i-1]
        int prev2 = 0;       // dp[i-2]

        for (int i = 1; i < n; ++i) {
            int left = prev1 + abs(height[i] - height[i - 1]);
            int right = (i > 1) ? prev2 + abs(height[i] - height[i - 2]) : INT_MAX;
            int curr = min(left, right);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

// 🧪 DRIVER
int main() {
    vector<int> height = {30, 10, 60, 10, 60, 50};

    SolutionMemo solMemo;
    SolutionTabulation solTab;
    SolutionSpaceOptimized solOpt;

    cout << "Memoization: " << solMemo.minCost(height) << endl;
    cout << "Tabulation: " << solTab.minCost(height) << endl;
    cout << "Space Optimized: " << solOpt.minCost(height) << endl;

    return 0;
}
