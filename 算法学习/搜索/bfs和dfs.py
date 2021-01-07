from typing import List
n=int(1e5+10)

#邻接表
adj=[[] for i in range(n)]

'''
搜索意味着遍历所有的结果，形式上主要分为bfs和dfs
其中dfs利用递归[注意递归深度]的形式，bfs利用队列的形式

并且适当的修改搜索的步骤
'''

vis=[0 for i in range(n)]
def dfs(root:int)->None:
    for i in range(len(adj[root])):
        if not vis[adj[root][i]]:
            vis[adj[root][i]]=1
            dfs(adj[root][i])

def bfs(root:int)->None:
    q=[root]
    while q:
        cur=q.pop(0)
        if vis[cur]:continue
        vis[cur]=1
        for i in range(len(adj[cur])):
            q.append(adj[cur][i])
    
    
