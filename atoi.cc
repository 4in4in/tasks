#include <string>
#include <climits>

class Solution
{
public:
    int myAtoi(std::string &s)
    {
        int curr_idx = 0;

        int sign = 1;
        int result = 0;

        // skip leading spaces
        while (s[curr_idx] == ' ')
        {
            ++curr_idx;
        }

        // get possible sign ("+" or "-")
        if (s[curr_idx] == '-' || s[curr_idx] == '+')
        {
            if (s[curr_idx] == '-')
            {
                sign = -1;
            }
            ++curr_idx;
        }

        // skip leading zeroes
        while (s[curr_idx] == '0')
        {
            ++curr_idx;
        }

        // parse value
        while (s[curr_idx] >= '0' && s[curr_idx] <= '9')
        {
            // check for overflow
            // https://stackoverflow.com/a/1514309
            if (result > INT_MAX / 10)
            {
                return INT_MAX;
            }
            if (result < INT_MIN / 10)
            {
                return INT_MIN;
            }
            result *= 10;
            int arg = sign * (s[curr_idx] - '0');

            // check for overflow
            if (arg < 0 && result < INT_MIN - arg)
            {
                return INT_MIN;
            }
            if (arg > 0 && result > INT_MAX - arg)
            {
                return INT_MAX;
            }

            result += arg;
            ++curr_idx;
        }
        return result;
    }
};

int main(void)
{
    auto solution = new Solution;

    std::string tests[] = {
        "     -42a",
        "     42   ",
        "-214748364800",
        "-2147483648",
        "-2147483647",
        "214748364700",
        "-91283472332",
        " 3.14",
        "",
        "  0000000000012345678",
        " ",
        "-6147483648",
        "   -42",
        "2147483647",
    };

    for (auto test : tests)
    {
        printf("->INPUT: %s\n", test.c_str());
        int result = solution->myAtoi(test);
        printf("<-RESULT: %d\n\n", result);
    }

    printf("MAX: %d\nMIN: %d\n", INT_MAX, INT_MIN);

    delete solution;

    return 0;
}