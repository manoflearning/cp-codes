n, k = input().split()
n, k = int(n), int(k)

dp = [0] * (1 << (2 * k + 1))

# base case
dp[0] = 1

# inductive step
for i in range(1, n + 1):
    tmp = [0] * (1 << (2 * k + 1))

    lb = max(k - i + 1, 0)
    ub = min(n - i + k, 2 * k)

    for bit in range(1 << (2 * k + 1)):
        if dp[bit] == 0:
            continue

        nbit = bit >> 1
        for j in range(lb, ub + 1):
            if nbit & (1 << j):
                continue
            tmp[nbit | (1 << j)] += dp[bit]

    dp = tmp

print(sum(dp))
