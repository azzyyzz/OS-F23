#include<stdio.h>
#include<string.h>
#define ll long long



void convert(ll num, ll b1, ll b2) {
    if (b1 > 10 || b2 > 10 || b1 < 2 || b2 < 2) {
        printf("cannot convert!");
        return;
    }

    ll numdub = num;
    ll to_base_10 = 0, pow = 1;
    
    while(numdub > 0) {
        if (numdub % 10 >= b1) {
            printf("cannot convert!");
            return;
        }
        to_base_10 += (numdub % 10) * pow;
        numdub /= 10;
        pow *= b1;
    }

    ll res = 0;
    pow = 1;
    while (to_base_10 > 0)
    {
        res += (to_base_10 % b2) * pow;
        pow *= 10;
        to_base_10 /= b2;
    }

    printf("%lld\n", res);
    

    
}

int main() {
    ll num, b1, b2;

    scanf("%lld %lld %lld", &num, &b1, &b2);
    convert(num, b1, b2);
}