#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MEM(_array,val) memset(_array,val,sizeof(_array))
#define MEM0(_array) MEM(_array,0)
#define MEMZ(_array) MEM(_array,0)
#define FORUP(_v,_b,_n) for(int _v=(_b);_v<=(_n);++_v)
#define FORDOWN(_v,_b,_n) for(int _v=(_b);_v>=(_n);--_v)
#define NXTINT(_v) scanf("%d",&(_v))
#define NXTLL(_v) scanf("%lld",&(_v))
#define TCASES() int _T;NXTINT(_T);while (_T--)

const int INF=0x7FFFFFFF;
const int MAXN=110;
const int MAXM=MAXN*MAXN*2;
struct EDG
{
    int u,v,cap,flow;
} es[MAXM];
int fst[MAXN],nxt[MAXM];
int coe;

/// @init coe=1; MEM0(fst)
inline void mkedg(int u,int v,int cap)
{
    es[++coe]=EDG{u,v,cap,0};
    nxt[coe]=fst[u];
    fst[u]=coe;
    es[++coe]=EDG{v,u,0,0};
    nxt[coe]=fst[v];
    fst[v]=coe;
}

int S,T;
bool vis[MAXN];
int d[MAXN];
int cur[MAXN];
bool dnbfs()
{
    MEM0(vis);
    queue<int> Q;
    Q.push(S);
    d[S]=0;
    vis[S]=1;
    while (!Q.empty()) {
        int u=Q.front(); Q.pop();
        for (int k=fst[u];k;k=nxt[k]) {
            EDG& e=es[k];
            if (!vis[e.v]&&e.cap>e.flow) {
                vis[e.v]=1;
                d[e.v]=d[u]+1;
                Q.push(e.v);
            }
        }
    }
    return vis[T];
}
int dndfs(int u,int a)
{
    if (u==T||a==0) return a;
    int flow=0,f;
    for (int& k=cur[u];k;k=nxt[k]) {
        EDG& e=es[k];
        if (d[u]+1==d[e.v]&&
            (f=dndfs(e.v,min(a,e.cap-e.flow)))>0)
        {
            e.flow+=f;
            es[k^1].flow-=f;
            flow+=f;
            a-=f;
            if (a==0) break;
        }
    }
    return flow;
}
int dinic()
{
    int flow=0;
    while (dnbfs())
    {
        for (int u=0;u<MAXN;++u)
            cur[u]=fst[u];
        flow+=dndfs(S,INF);
    }
    return flow;
}

int main()
{
#ifdef LOCAL
    freopen("IN.txt","r",stdin);
#endif

    int N,P,C,M;
    int u,v,z;
    while (~scanf("%d%d%d%d",&N,&P,&C,&M))
    {
        coe=1; MEM0(fst);
        for (int i=1;i<=M;++i) {
            while (getchar()!='(');
            scanf("%d,%d)%d",&u,&v,&z);
            mkedg(++u,++v,z);
        }
        for (int i=1;i<=P;++i) {
            while (getchar()!='(');
            scanf("%d)%d",&u,&z);
            mkedg(0,++u,z);
        }
        for (int i=1;i<=C;++i) {
            while (getchar()!='(');
            scanf("%d)%d",&u,&z);
            mkedg(++u,N+1,z);
        }
        S=0; T=++N;
        printf("%d\n",dinic());
    }

    return 0;
}
