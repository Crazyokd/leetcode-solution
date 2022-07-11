class Solution {

    private int[] f;
    public int[] findRedundantConnection(int[][] edges) {
        // initialization
        f = new int[edges.length+1];
        for (int i = 1; i <= edges.length; i++) {
            f[i] = i;
        }

        for (int i = 0; i < edges.length; i++) {
            if (find(edges[i][0]) != find(edges[i][1])) {
                union(edges[i][0], edges[i][1]);
            } else {
                return edges[i];
            }
        }
        return edges[0];
    }

    public void union(int node1, int node2) {
        f[f[node1]] = f[node2];
    }

    public int find(int node) {
        if (f[node] != node) {
            f[node] = find(f[node]);
        }
        return f[node];
    }
}