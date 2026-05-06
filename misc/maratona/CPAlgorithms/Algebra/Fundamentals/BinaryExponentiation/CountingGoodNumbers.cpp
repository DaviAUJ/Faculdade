// Link: https://leetcode.com/problems/count-good-numbers/submissions/1784734256/
// Current Status: Accepted

constexpr uint64_t MOD = 1000000007;

class Solution {
public:
    int64_t modPow(int64_t b, uint64_t e) {
        b %= MOD;
        int64_t out = 1;

        while(e > 0) {
            if(e & 1) {
                out = (b * out) % MOD;
            }

            b = (b * b) % MOD ;
            e >>= 1;
        }

        return out;
    } 

    int countGoodNumbers(int64_t n) {
        uint64_t odds = n / 2, evens = n - odds;

        return (modPow(5, evens) * modPow(4, odds)) % MOD;
    }
};
