/*
https://www.nowcoder.com/acm/contest/152/E

涉及算法，dfs序，扫描线，线段树，lca

dfs序后 每加一条边
两点关系的bool矩阵中 就有2/4个矩形部分 没有了

if lca(a,b)==b||lca(a,b)==a :
    4个 
    设fa[x]=lca(a,b) a,b中a的深度大
    那么{<x,y>|x \in [L[a],R[a]] ,y \in ([1,L[x]-1] and [R[x]+1,n])就被灭掉了
else：
    2个
    那么{<x,y>|x \in [L[a],R[a]] ,y \in [L[x]，R[x]] 就被灭掉了
    
别忘了把{<x,x>|x \in [1,n]} 给去掉

*/
#include <bits/stdc++.h>
typedef long long int LL;
using namespace std;

const int N = 1e5+7;

/****************************************************************/
int n,m;

struct edge{
    int to,next;
}G[N<<1];
int head[N],cnt;
void add(int u,int v){
    G[cnt].to=v,G[cnt].next=head[u],head[u]=cnt++;
    G[cnt].to=u,G[cnt].next=head[v],head[v]=cnt++;
}

int L[N],R[N],tot;
int f[N][20],dep[N];

void dfs(int u,int fa = 0){
    L[u] = ++tot; 

    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for(int i=1;i<20;i++){
        f[u][i] = f[f[u][i-1]][i-1];
    }
    
    for(int i=head[u],to;i!=-1;i=G[i].next){
        to = G[i].to;
        if(to == fa) continue;
        dfs(to,u);
    }
    R[u] = tot;
}

int LCA(int u,int v){
    int lca = 0;
    if(dep[u] < dep[v]) swap(u,v);
    for(int i=19;i>=0;i--){
        if(dep[f[u][i]] >= dep[v])
            u = f[u][i];
    }
    if(u == v) lca = u;
    else {
        for(int i=19;i>=0;i--){
            if(dep[f[u][i]] != dep[f[v][i]]){
                u = f[u][i];
                v = f[v][i];
            }
        }
        lca = f[u][0];
    }
    return lca;
}

int get(int u,int v){
    if(dep[u] < dep[v]) swap(u,v);
    for(int i=19;i>=0;i--){
        if(dep[f[u][i]] > dep[v])
            u = f[u][i];
    }
    return u;
}

bool judge(int u,int v){
    int lca = LCA(u,v);
    // printf("lca(%d,%d)=%d\n",u,v,lca);
    return u == lca || v == lca;
}


int sum[N<<2],cntt[N<<2];

void pushup(int rt,int l,int r){
    if(cntt[rt]) sum[rt] = r+1 - l; //lisanhua
    else if(r == l) sum[rt] = 0;
    else sum[rt] = sum[rt<<1]+sum[rt<<1|1];
}

void build(int rt,int l,int r){
    cntt[rt] = sum[rt] = 0;
    if(l >= r) return ;
    int m = (r+l) >> 1;
    build(rt<<1  ,l  ,m);
    build(rt<<1|1,m+1,r);
}

void update(int rt,int l,int r,int L,int R,int v){
    // printf("[%d,%d] (%d,%d)\n",l,r,L,R);
    if(L<=l && r<=R){
        cntt[rt]+=v;
        pushup(rt,l,r);
        return ;
    }
    int m = (r+l)>>1;
    if(L<=m) update(rt<<1  ,l  ,m,L,R,v);
    if(R> m) update(rt<<1|1,m+1,r,L,R,v);
    pushup(rt,l,r);
}


void init(){
    memset(head,-1,sizeof(head));
    cnt = tot = 0;
    build(1,1,n);
    dep[0]=0;
}


int main(){

    while(~scanf("%d%d",&n,&m)){
        init();

        for(int i=2,u,v;i<=n;i++){
            scanf("%d%d",&u,&v);
            add(u,v);
        }
        
        dfs(1);
        vector<pair<pair<int,int>,pair<int,int> > > ve;
        for(int i=1,u,v;i<=m;i++){
            scanf("%d%d",&u,&v);
            // printf("%d %d <<--\n",u,v);
            if(judge(u,v)){
                if(dep[u] < dep[v]) swap(u,v);

                v = get(u,v);
                // printf("%d %d\n",u,v );
                // printf("L[%d]=%d R[%d]=%d | L[%d]=%d R[%d]=%d \n",u,L[u],u,R[u],v,L[v],v,R[v]);
                //(L[u],R[u]) - (1 -> L[v]-1)
                    // printf("-[%d,%d,%d -> %d]\n",L[u],R[u],1,L[v]-1);
                if(1<=L[v]-1){ //puts("++");
                    ve.push_back({{1-1,1},{L[u],R[u]}});
                    ve.push_back({{L[v]-1,2},{L[u],R[u]}});
                }
                //(L[u],R[u]) - (R[v]+1 -> n)
                    // printf("-[%d,%d,%d -> %d]\n",L[u],R[u],R[v]+1,n);
                if(R[v]+1<=n){ //puts("++");
                    ve.push_back({{R[v]+1-1,1},{L[u],R[u]}});
                    ve.push_back({{n,2},{L[u],R[u]}});
                }
                //(1,L[v]-1) - (L[u]->R[u])
                    // printf("-[%d,%d,%d -> %d]\n",1,L[v]-1,L[u],R[u]);
                if(1<=L[v]-1){ //puts("++");
                    ve.push_back({{L[u]-1,1},{1,L[v]-1}});
                    ve.push_back({{R[u],2},{1,L[v]-1}});
                }
                //(R[v]+1,n) - (L[u] ->R[u])
                    // printf("-[%d,%d,%d -> %d]\n",R[v]+1,n,L[u],R[u]);
                if(R[v]+1<=n){ //puts("++");
                    ve.push_back({{L[u]-1,1},{R[v]+1,n}});
                    ve.push_back({{R[u],2},{R[v]+1,n}});
                }
            }
            else{
                //(L[u],R[u]) - (L[v] -> R[v])
                // printf("+[%d,%d,%d -> %d]\n",L[u],R[u],L[v],R[v]);
                ve.push_back({{L[v]-1,1},{L[u],R[u]}});
                ve.push_back({{R[v],2},{L[u],R[u]}});
                //(L[v],R[v]) - (L[u] -> R[u])
                // printf("+[%d,%d,%d -> %d]\n",L[v],R[v],L[u],R[u]);
                ve.push_back({{L[u]-1,1},{L[v],R[v]}});
                ve.push_back({{R[u],2},{L[v],R[v]}});
            }
        }

        for(int i=1;i<=n;i++){
            ve.push_back({{i-1, 1},{i,i}});
            ve.push_back({{i  ,2},{i,i}});
        }
        sort(ve.begin(), ve.end());
        // for(int i=1;i<=n;i++)printf("%d %d\n",L[i],R[i]);
        int p = 0;
        LL ans = 0;
        for(auto a: ve){
            // printf("<%d,%d><%d,%d>\n",a.first.first,a.first.second,a.second.first,a.second.second);
            if(a.first.second == 1){
                ans += 1LL*sum[1]*(a.first.first-p);
                update(1,1,n,a.second.first,a.second.second,1);
            }   
            else { 
                ans += 1LL*sum[1]*(a.first.first-p);
                update(1,1,n,a.second.first,a.second.second,-1);
             
        
            }
            p = a.first.first;
        }
        printf("%lld\n",1LL*n*n-ans);
    }
}
