#include<bits/stdc++.h>
using namespace std;

//快排
void quickSort(vector<int>& vec, int left, int right)
{
    if(left >= right) return;
    int temp = vec[left];
    int head = left, tail = right;
    while(head < tail)
    {
        while(head < tail && vec[tail] >= temp) --tail;
        swap(vec[head],vec[tail]);
        while(head < tail && vec[head] <= temp) ++head;
        swap(vec[head],vec[tail]);
    }
    vec[head] = temp;
    quickSort(vec, left, head - 1);
    quickSort(vec, head + 1, right);
}

//归并
void merge(vector<int> &vec, int left, int mid, int right)
{
    int i1 = left, i2 = mid + 1, cur = 0;
    vector<int> temp(right - left + 1, 0);
    while(i1 <= mid && i2 <= right)
    {
        if(vec[i1] < vec[i2])temp[cur++] = vec[i1++];
        else temp[cur++] = vec[i2++];
    }
    while(i1 <= mid)temp[cur++] = vec[i1++];
    while(i2 <= right)temp[cur++] = vec[i2++];
    for(int i = left; i <= right; ++i)vec[i] = temp[i - left];
}

void mergeSort(vector<int> &vec, int left, int right)
{
    if(right <= left)return;
    int mid = (right + left) >> 1;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}   

//堆排
struct heap
{
    heap(){h.push_back(0);}
    
    void push(int val)
    {
        h.push_back(val);
        int cur = h.size() - 1;
        while(cur && h[cur] < h[cur >> 1])
        {
            swap(h[cur], h[cur >> 1]);
            cur >>= 1;
        }
    }
    void pop()
    {
       h[1] = h[h.size() - 1];
       h.pop_back();
       int cur = 1, next = -1;
       while(true)
       {
            next = cur << 1;
            if(next >= h.size())break;
            if(next + 1 >= h.size())
            {
                if(h[cur] > h[next])
                {
                    swap(h[cur], h[next]);
                }             
                break;
            }
            if(h[next] > h[next + 1])++next;
            if(h[cur] > h[next])
            {
                swap(h[cur], h[next]);
                cur = next;
                continue;
            }
            else
            {
                break;
            }
       } 
    }
    int get()
    {
        return h[1];
    }
    void print()
    {
        for(int i = 1; i < h.size(); ++i)
        {
            cout<<h[i]<<" ";
        }
        cout<<endl;
    }
    vector<int> h;
};

void heapSort(vector<int> &vec, int left, int right)
{
    heap h;
    for(int i = left; i <= right; ++i)
    {
        h.push(vec[i]);
    }
    for(int i = left; i <= right; ++i)
    {
        vec[i] = h.get();
        h.pop();
    }
}

//kmp
int kmp(const string &s,const string &p) // s in p
{
    vector<int> dp(s.size(), -1);
    int pre = -1, cur = 0, n = s.size();
    while(cur < n - 1)
    {
        if(pre == -1 || s[cur] == s[pre])
        {
            ++cur;
            ++pre;
            if(s[cur] == s[pre])
            {
                dp[cur] = dp[pre];
            }
            else
            {
                dp[cur] = pre; //如果第cur个点不匹配，则转到pre上去
            }
        }
        else
        {
            pre = dp[pre];
        }
    }
    //for(int i = 0; i < n; ++i)cout<<dp[i]<<" ";
    //cout<<endl;
    pre = 0, cur = 0;
    while(pre < s.size() && cur < p.size())
    {
        if(pre == -1 || p[cur] == s[pre])
        {
            ++cur;
            ++pre;
        }
        else
        {
            pre = dp[pre];
        }
        if(pre == n)return cur - n;
    }
    return -1;
}

//马拉车
int manachers(string s)
{
    string str("#*");
    for(int i = 0; i < s.size(); ++i)
    {
        str += s[i];
        str += '*';
    }
    int n = str.size();
    str += "{}";
    vector<int> dp(n, 0);
    int right = 0, mid = 0, res = 0;
    //string res; int cnt = 0;
    for(int i = 1; i < n; ++i)
    {
        dp[i] = right > i ? min(right - i, dp[2 * mid - i]) : 1;
        while(str[i + dp[i]] == str[i - dp[i]]) ++dp[i];
        --dp[i];
        if(i + dp[i] > right) right = i + dp[i], mid = i;
        res = max(res, dp[i] - 1);
        // res.clear()
        // if(dp[i] - 1 > cnt)
        // for(int idx = i - dp[i] + 1; idx < i + dp[i]; idx += 2)res += str[idx];
    }
}

//二分匹配
struct augmemt_path
{
    vector<vector<int>> g;
    vector<int> pa;
    vector<int> pb;
    vector<int> vis;
    vector<int> vism;
    int n, m;
    int dfn;
    int res;

    augmemt_path(int _n, int _m):n(_n),m(_m)
    {
        pa = vector<int> (n, -1);
        pb = vector<int> (m, -1);
        vis = vector<int> (n, 0);
        g.resize(n);
        res = dfn = 0;
    }

    void add(int u, int v)
    {
        g[u].push_back(v);
    }

    bool dfs(int u)
    {
        vis[u] = dfn;
        for(int v : g[u])
        {
            if(pb[v] == -1)
            {
                pa[u] = v;
                pb[v] = u; 
                return true;
            }
        }
        for(int v : g[u])
        {
            //防止v找到u
            if(vis[pb[v]] != dfn && dfs(pb[v]))
            {
                pa[u] = v;
                pb[v] = u;
            }
        }
    }

    int solve()
    {
        while(true)
        {
            dfn++;
            int cnt = 0;
            for(int i = 0; i < n; ++i)
            {
                if(pa[i] == -1 && dfs(i))
                {
                    ++cnt;
                }
            }
            if(cnt == 0)break;
            res += cnt;
        }
        return res;
    }

    //soluton2
    bool dfs(int u)
    {
        for(int v : g[u])
        {
            if(!vism[v])
            {
                vism[v] = 1;
                if(pb[v] == -1 || dfs(pb[v]))
                {
                    pb[v] = u;
                    return true;
                }
            }
        }
    }
    int solve()
    {
        vism.resize(m);
        for(int i = 0; i < n; ++ i)
        {
            for(int j = 0; j < n; ++j)
            {
                vism[j] = 0;
            }
            if(dfs(i)) ++res;
        }
    }
};

