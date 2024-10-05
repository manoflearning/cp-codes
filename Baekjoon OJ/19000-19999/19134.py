def f(n: int):
    if n <= 3: return n
    
    m = n // 2 - 1
    l, r = 0, m
    while l < r:
        mid = (l + r + 1) // 2
        if 2 * mid + 2 > m: r = mid - 1
        else: l = mid
    return n - m + f(l)
    
n = int(input())
print(f(n))
