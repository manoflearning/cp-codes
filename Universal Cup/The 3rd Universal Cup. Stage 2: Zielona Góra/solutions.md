# A. Interesting Paths

## Problem

Given a DAG with $n$ nodes and $m$ edges. Find the length of the longest interesting sequence of paths.

Interesting sequence of paths is:
- each path starts at $1$ and ends at $n$.
- each path contains at least one edge that was not presented in any of the previous paths.

## Intuition

- Assume there exists Hamiltonian path in the given DAG.
- Let $c$ be the number of edges that is not presented in the Hamiltonian path.
- Then, the answer is $c + 1$.

## Solution

### Solution 1

First, remove all nodes and edges that cannot reachable from both $1$ and $n$. (use reversed graph for the later case.)

Traverse all the nodes $v$ in topological order and get the value of $dp[v]$.
Let's say we can get from node $v$ to $u_1$, $u_2$, $\cdots$, $u_k$ using one edge (i.e., there exists edges $(v, u_1)$, $(v, u_2)$, $\cdots$, $(v, u_k)$).

For the first node $u_1$, add $dp[v]$ to $dp[u_1]$.
For all the other nodes $u_2$, $\cdots$, $u_k$, add $1$ instead of $dp[v]$.

Answer is $dp[n]$.

### Solution 2

Let $x$ be the number of nodes that can reachable from both $1$ and $n$, and $y$ be the number of edges that can reachable from both $1$ and $n$. (use reversed graph for the later case.)

If $n$ is not reachable from $1$, the answer is $0$. From now, let's assume $n$ is reachable from $1$.

Let $p$ be the the longest interesting sequence, and $e$ be the set of edges in each path that are not presented in the previous paths. Then, the following holds:
- $y = \sum_{p} |e|$
- $x - 2 = \sum_{p} |e| - 1 = y - |p|$

$\therefore |p| = y - x + 2$

# D. Xor Partitions

## Problem

