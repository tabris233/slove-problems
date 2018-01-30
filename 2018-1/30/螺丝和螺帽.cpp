/************
Discrption: 两个数组 A 表示一串螺丝 B 表示一串螺帽 螺丝和螺帽能够配对，
但是A中螺丝之间不能比较大小，B中螺帽之间也不能比较大小，
螺丝和螺帽可以比较大小，返回所有螺丝和螺帽的对应关系，要求复杂度小于O(n^2)

Answer: 类似快速排序,一个和另一个比较就可以了.
author: tabris
date: 2018-01-30 13:21:29
************/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+7;

/********************************/

typedef pair<int,int > pii;

int n;

pii a[N];
pii b[N];

void solve(int l,int r){
    if(r<=l) return ;

//    puts(" ------------- ");
//    printf("[%d-%d]\n",l,r);
//    for(int i=1;i<=n;i++){
//        if(i == l) printf("[");
//        printf("%d ",a[i].first);
//        if(i == r) printf("]");
//    }puts("");
//    for(int i=1;i<=n;i++){
//        if(i == l) printf("[");
//        printf("%d ",b[i].first);
//        if(i == r) printf("]");
//    }puts("");

    int ll=l,rr=r;
    while(ll<=rr){
        while( ll<rr && b[ll].first<a[l].first )ll++;
        while( ll<rr && b[rr].first>a[l].first )rr--;
        swap(b[ll],b[rr]);
        ll++,rr--;
    }

    int p;
    for(int i=l;i<=r;i++){
        if(b[i].first == a[l].first) p=i;
    }
    ll=l,rr=r;
    while(ll<=rr){
        while( ll<rr && a[ll].first<b[p].first )ll++;
        while( ll<rr && a[rr].first>b[p].first )rr--;
        swap(a[ll],a[rr]);
        ll++,rr--;
    }
//    printf("%d\n",p);
//    puts(" ++++++++++++++ ");
    solve(l, p-1 ),solve( p+1 , r);
}

int main (){
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++)scanf("%d",&a[i].first),a[i].second = i;
        for(int i=1;i<=n;i++)scanf("%d",&b[i].first),b[i].second = i;

        solve(1,n);

        for(int i=1;i<=n;i++){
            printf("%d - %d\n",a[i].second,b[i].second);
        }
    }
    return 0;
}
/******
53142
34512

******/

