from typing import List
mod=int(1e9+7)

'''
1.枚举   枚举所有可行的情况进行判断 
2.递推/递归 从初始状态向目标状态传递/从目标状态向初始状态传递
'''



'''
3.贪心 每次传递过程状态都保持最优值
'''

'''
4.二分法
'''
#查找不小于val的第一个值的位置
def bsearch(arr: List[int] , val:int) ->int:
    #[left,right)
    left,right=0,len(arr)
    while left<right:
        mid=left+(right-left)//2
        #除去不可能的一边 如果用其他判断方法需注意 judge(mid)==false 
        if(arr[mid]<val):left=mid+1
        else:right=mid
    return left

'''
5.前缀和
通常处理需要频繁直接获取区间和操作的时候 例如arr=[1,2,3,4,5] 需要获取[1,3]的和 
6.差分
通常处理需要频繁区间进行加减操作时  例如 arr=[1,2,3,4,5] 需要对[1,3]中的数加上2 
'''

'''
7.倍增 采取二进制的增加方法 
例如从0->5 二进制看为 000 -> 101 因此可以采取 初始步长为1 然后翻倍为2 翻倍为4的操作 可以将n的时长降低为logn 
例如快速幂
'''
def qexp(m:int,n:int)->int:
    res=1%mod
    while n:
        if n&1:res=res*m%mod
        n>>=1
        m=m*m%mod
    return res

'''
8常见小tips记录


'''

