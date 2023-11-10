#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 30

int pre[MAX_NODES];

// Function to take absolute value of an integer
int abs_val(int value) {
    return value < 0 ? -value : value;
}

// Function to judge if the subtree is a red-black tree
int judge(int l, int r) {
    // Root is red
    if (l == 0 && pre[l] < 0) return 0;
    // Leaf
    if (l == r) {
        if (pre[l] > 0) return 1;
        else return 0;
    }
    if (l > r) return 0;
    int i = l + 1;
    while (i <= r && abs_val(pre[i]) < abs_val(pre[l])) i++;
    // Node is red and its children not all black
    if ((pre[l] < 0) && (pre[l + 1] < 0 || pre[i] < 0)) return 0;
    int lnum = judge(l + 1, i - 1);
    int rnum = judge(i, r);
    if (lnum == rnum) return lnum + (pre[l] > 0 ? 1 : 0);
    else return 0;
}

int main() {
    int k, n;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &n);
        for (int j = 0; j < n; j++) scanf("%d", &pre[j]);
        if (judge(0, n - 1))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
