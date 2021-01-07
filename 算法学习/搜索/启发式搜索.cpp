/*
启发式搜索[通过对未来的估价函数来筛除不必要的选项]
例如：有N个物品，每个物品有重量wi和价值vi，有1个背包，承重为W，
要求选取若干个物品[每个物品最多1次]放入背包，使得背包内总价值最大
*/

#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,W,res;

//obg[0:n]为物品列表
struct Obj
{
    int w,v,f;
    bool operator< (const Obj& o){
        return (*this).f>o.f;
    }
}obj[N];

//估价函数
int f(int t,int p){
    int tot=0;
    for(int i=t+1;i<n;++i){
        if(p>=obj[i].w){
            p-=obj[i].w;
            tot+=obj[i].v;
        }
        //else return int(tot+p*obj[i].f); 
        else return tot+obj[i].v;
    }
    return tot;
}

void dfs(int t,int p,int v){
    res=max(res,v);
    if(t>=n)return;
    if(f(t,p)+v>res)dfs(t+1,p,v);
    if(obj[t].w<=p)dfs(t+1,p-obj[t].w,v+obj[t].v);
}