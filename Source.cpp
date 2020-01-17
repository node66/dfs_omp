#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

void dfs(int node, vector<int> adj[], int dp[], bool vis[])
{
	vis[node] = true;

	for (size_t i = 0; i < adj[node].size(); i++) {

		if (!vis[adj[node][i]])
			dfs(adj[node][i], adj, dp, vis);

		dp[node] = max(dp[node], 1 + dp[adj[node][i]]);
	}
}

int main()
{
	setlocale(0, "");
	const int n(5);
	vector<int> adj[n + 1];

	adj[1].push_back(2);
	adj[1].push_back(3);
	adj[3].push_back(2);
	adj[2].push_back(4);
	adj[3].push_back(4);		

	int dp[n + 1];
	memset(dp, 0, sizeof dp);

	bool vis[n + 1];
	memset(vis, false, sizeof vis);

	int ans(0);
#pragma omp parallel shared(dp,vis,adj,ans)
	{
#pragma omp for
		for (int i = 1; i <= n; i++) {
			if (!vis[i])
				dfs(i, adj, dp, vis);
		}
#pragma omp barrier
#pragma omp for
		for (int i = 1; i <= n; i++) {
			ans = max(ans, dp[i]);
		}
#pragma omp single 
		cout << "Максимальная длинна = " << ans << endl;
	}
	system("pause");
	return 0;
}
