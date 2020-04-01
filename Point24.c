#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <algorithm>
#include <sstream>
#include <functional>
#include <bitset>
#include <numeric>
#include <cmath>
#include <regex>

using namespace std;



class Solution
{
public:
    bool judgePoint24(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        do
        {
            if (valid(nums))
                return true;
        } while (next_permutation(nums.begin(), nums.end()));
        return false;
    }

    bool valid(vector<int>& nums)
    {
        double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
        if (valid(a + b, c, d) || valid(a - b, c, d) || valid(a*b, c, d) || b != 0 && valid(a / b, c, d))
            return true;

        if (valid(a, b + c, d) || valid(a, b - c, d) || valid(a, b*c, d) || c != 0 && valid(a, b / c, d))
            return true;

        if (valid(a, b, c + d) || valid(a, b, c - d) || valid(a, b, c*d) || d != 0 && valid(a, b, c / d))
            return true;

        return false;
    }

    bool valid(double a, double b, double c)
    {
        if (valid(a + b, c) || valid(a - b, c) || valid(a*b, c) || b != 0 && valid(a / b, c))
            return true;

        if (valid(a, b + c) || valid(a, b - c) || valid(a, b*c) || c != 0 && valid(a, b / c))
            return true;

        return false;
    }

    bool valid(double a, double b)
    {
        if (abs(a + b - 24.0) < 0.0001 || abs(a - b - 24.0) < 0.0001
            || abs(a*b - 24.0) < 0.0001 || b!= 0 && abs(a / b - 24.0) < 0.0001)
            return true;

        return false;
    }
};
