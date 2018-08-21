'''
    베르트랑 공준

    소수

    (n,2n]의 소수의 개수를 구하자. (n<=123456)
    에라토스테네스의 체를 이용하면 된다. O(nlogn)
    
    필수는 아니지만
    미리 sum[n](:n까지의 소수갯수)를 계산해서
    누적합으로 계산하면 쿼리를 빨리 처리할수있다.

    C++ 로도 똑같이 할 수는 있었지만,
    배열을 만들때 집컴에서는 123456*2의 길이로 할 수가 없어서
    대신 파이썬으로 해결했다.
'''

max = 123456*2
seen = [0 for i in range(max+1)]
sum = [0 for i in range(max+1)]

from math import sqrt

# eratos
for i in range(2,int(sqrt(max))+2):
    if seen[i]:
        continue
    for j in range(2*i,max+1,i):
        seen[j] = 1

#pre-calculation
for i in range(2, max+1):
    sum[i] = sum[i-1] + 1-seen[i]
 
while 1:
    n = int(input())
    if n == 0:
        break
    print(sum[2*n]-sum[n])