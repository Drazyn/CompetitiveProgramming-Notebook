//OBI 2014 - Nível 1 - Fase 2
//Problema resolvido por LCA em O(Log N) para cada consulta de LCA e O(N) para a construção da DP.

#include <bits/stdc++.h>

#define MAXN 50005 //Número de vértices
#define LOGN 20 //Limite de saltos binários possíveis + armazenamento de segurança

using namespace std;

vector<int> children[MAXN];

int dp[MAXN][LOGN], grau[MAXN];

void dfs(int vertex, int parent, int height)
{
    dp[vertex][0] = parent;
    grau[vertex] = height;

    for (int i = 1; i < LOGN; i++) //Vamos acessar todos os saltos binários possíveis que 'vertex' consegue fazer
    {
        if (dp[vertex][i] != -1) //Se esse subproblema não foi resolvido, então vamos resolvê-lo.
            dp[vertex][i] = dp[ dp[vertex][i-1] ][i-1];
    }

    for (int i = 0; i < (int)children[vertex].size(); i++) //Vamos percorrer todos seus filhos
    {
        int v = children[vertex][i];
        if (v != parent)
            dfs(v, vertex, height +1);
    }

}

int LCA(int u, int v)
{
    //Precisamos igualar os graus;
    if (grau[u] < grau[v])
        swap(v, u);

    //O grau de u sempre será maior ou igual ao grau de v;

    int U = u, V = v; //Originais
    for (int i = LOGN-1; i >= 0; i--) //Vamos acessar todos os possíveis k-ésimos pais de u, de modo a encontrar um de grau igual a v;
    {
        if (dp[u][i] != 0 && grau[ dp[u][i] ] >= grau[v])
            u = dp[u][i];
    }

    if (u == v) //v é o LCA de u, então, retornamos u
        return grau[U] - grau[V];

    for (int i = LOGN - 1; i >= 0; i--) //Esse algoritmo sobe a árvore logaritimicamente em base 2.
    {
        if (dp[u][i] != dp[v][i]) //Enquanto o ancestral de i-ésima ordem for diferente, vamos atualizar os vértices.
        {
            v = dp[v][i];
            u = dp[u][i];
        }
    }

    //Nesse momento, u e v são exatamente filhos do respectivo LCA

    return grau[U] + grau[V] - 2 * grau[dp[v][0]];
}

int paridade[MAXN][2], usado[MAXN];
int id[MAXN];

int main()
{
    int n; cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> id[i];
        if (paridade[id[i]][0] == 0)
            paridade[id[i]][0] = i;
         else
            paridade[id[i]][1] = i;
    }

    for (int i = 1; i < n; i++)
    {

        int x, y; cin >> x >> y;
        children[x].push_back(y);
        children[y].push_back(x);
    }

    dfs(1, 1, 0);

    int points = 0;

    for (int i = 1; i <= n; i++)
    {
        int par = (paridade[id[i]][0] == i ? paridade[id[i]][1] : paridade[id[i]][0]);
        points += LCA(i, par);
    }

    cout << points/2 << endl;

    return 0;
}
