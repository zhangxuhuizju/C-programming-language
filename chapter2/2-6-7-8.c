unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return (y & ~(~0 << n)) << (p + 1 - n) | (x & ~(~(~0 << n) << (p + 1 - n)));
}

unsigned invert(unsigned x, int p, int n) {
    return x ^ (~(~0 << n) << (p + 1 - n));
}

unsigned rightrot(unsigned x, int n) {
    int len = sizeof(unsigned) * 8;
    n %= len;
    int rbit;

    while (n--)
    {
        rbit = (x & 1) << (len - 1);
        x >>= 1;
        x |= rbit;
    }
    return x;
}