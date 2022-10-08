#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

ofstream outf;

constexpr int lprimes[] = {
    7,
    17,19,23,29,47,59,61,97,
    109,113,131,149,167,179,181,193,223,229,233,257,263,269,313,337,367,379,383,389,419,433,461,487,491,499,
    503,509,541,571,577,593,619,647,659,701,709,727,743,811,821,823,857,863,887,937,941,953,971,977,983,
    1019,1021,1033,1051,1063,1069,1087,1091,1097,1103,1109,1153,1171,1181,1193,1217,1223,1229,1259,1291,1297,
    1301,1303,1327,1367,1381,1429,1433,1447,1487,1531,1543,1549,1553,1567,1571,1579,1583,1607,1619,1621,1663,
    1697,1709,1741,1777,1783,1789,1811,1823,1847,1861,1873,1913,1949,1979,2017,2029,2063,2069,2099,2113,2137,
    2141,2143,2153,2179,2207,2221,2251,2269,2273,2297,2309,2339,2341,2371,2383,2389,2411,2417,2423,2447,2459,
    2473,2539,2543,2549,2579,2593,2617,2621,2633,2657,2663,2687,2699,2713,2731,2741,2753,2767,2777,2789,2819,
    2833,2851,2861,2887,2897,2903,2909,2927,2939,2971,3011,3019,3023,3137,3167,3221,3251,3257,3259,3299,3301,
    3313,3331,3343,3371,3389,3407,3433,3461,3463,3469,3527,3539,3571,3581,3593,3607,3617,3623,3659,3673,3701,
    3709,3727,3767,3779,3821,3833,3847,3863,3943,3967,3989,4007,4019,4051,4057,4073,4091,4099,4127,4139,4153,
    4177,4211,4217,4219,4229,4259,4261,4327,4337,4339,4349,4421,4423,4447,4451,4457,4463,4567,4583,4651,4673,
    4691,4703,4783,4793,4817,4931,4937,4943,4967,5021,5059,5087,5099,5153,5167,5179,5189,5233,5273,5297,5303,
    5309,5381,5393,5417,5419,5501,5503,5527,5531,5581,5623,5651,5657,5659,5669,5701,5737,5741,5743,5749,5779,
    5783,5807,5821,5857,5861,5869,5897,5903,5927,5939,5981,6011,6029,6047,6073,6113,6131,6143,6211,6217,6221,
    6247,6257,6263,6269,6287,6301,6337,6343,6353,6367,6389,6473,6553,6571,6619,6659,6661,6673,6691,6701,6703,
    6709,6737,6779,6793,6823,6829,6833,6857,6863,6869,6899,6949,6967,6971,6977,6983,7019,7057,7069,7103,7109,
    7177,7193,7207,7219,7229,7247,7309,7349,7393,7411,7433,7451,7457,7459,7487,7499,7541,7577,7583,7607,7673,
    7687,7691,7699,7703,7727,7753,7793,7817,7823,7829,7873,7901,7927,7937,7949,8017,8059,8069,8087,8171,8179,
    8219,8233,8263,8269,8273,8287,8291,8297,8353,8377,8389,8423,8429,8447,8501,8513,8537,8543,8623,8647,8663,
    8669,8699,8713,8731,8741,8753,8783,8807,8819,8821,8861,8863,8887,8971,9011,9029,9059,9103,9109,9137,9221,
    9257,9341,9343,9371,9377,9421,9461,9473,9491,9497,9539,9623,9629,9697,9739,9743,9749,9767,9781,9811,9817,
    9829,9833,9851,9857,9887,9931,9949,9967,10007 };

constexpr int nlprimes = 468;

int solve(int n) {

    if (n <= 3) {
        return 0;
    }
    if (n <= 7) {
        return 3;
    }

    int il = 0;
    int ir = nlprimes;
    int i = (il + ir) / 2;

    while (true)
    {
        int lpi = lprimes[i];
        int lpiNext = lprimes[i + 1];
        if (n > lpi) {
            if (n <= lpiNext) {
                break;
            }
            il = i;
        }
        else {
            ir = i;
        }
        i = (il + ir) / 2;
    }

    return lprimes[i];
}

int main() {

    outf.open("euler26.txt");

    for (int n = 10000; n <= 10000; n++) {
        cout << n << " " << solve(n) << endl;
        outf << n << " " << solve(n) << endl;
    }

    outf.close();

    return 0;
}