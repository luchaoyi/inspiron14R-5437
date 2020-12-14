//最优化问题求解的一种思路，重点在于怎样划分子问题
//动态规划，切割子问题，怎么是更小问题
//钢筋切割问题
def cut-rod(p,n):
	if n==0:
		return 0;
	q=-INF;
	for i=1 to n:
		q=max(q,p[i]+cut-rod(p,n-i));
	return q;

//切钢筋一次一次切，每次切钢筋小一段,完成了一个阶段，解决问题是递进的，问题缩小一部分
//最短路径，没走一步是一个过程
//备忘录

def mem-cut-rod(p,n):
	for i to n:
		r[i]=-INF //init
	return mem-cut-rod-aux(p,n,r)

def mem-cut-rod-aux(p,n,r):
	if r[n]>=0
		return r[n]
	if n==0:
		q=0
	else
		q=-INF
		for i=1 to n:
			q=max(q,p[i]+mem-cut-rod-aux(p,n-i,r))
	r[n]=q
	return q

def bottom-up-cut-rod(p,n):
	r[0]=0
	for j=1 to n:
		q=-INF
		for i=1 to j;
			q=max(q,p[i]+r[j-i])
			s[j]=i //j长时切第一次切多长
	r[j]=p
	return r and s

def print-result(p,n):
	r,s=bottom-up-cut-rod(p,n)
	while n>0:
		print s[n]
		n=n-s[n]

//矩阵链乘法
/* 
 *m[i,j]={
	0 i==j
	min{m[i,k]+m[k+1,j]+pi-1pkpj} i<j
 }
 */
def matrix-chain-order(p):
	n=p.lenghth-1
	for i= 1 to n
		m[i,i]=0
	for l= 2 to n //l is chain lenght
		//Ai Aj l=j-i+1
		j=i+l-1
		for k=i to j-1:
			q=m[i,k]+m[k+1,j]+p[i-1]*p[k]*p[j]
			if q<m[i,j]
				m[i,j]=q
				s[i,j]=k
	return m and s
def print-result(s,i,j):
	if i==j:
		print Ai
	else:
		print "("
		print-result(s,i,s[i,j])
		print-result(S,s[i,j]+1,j)
		print ")"
//动态规划，自顶向下时递归重复子问题备忘机制或自底向上产生顺序效率比较高
//分数背包可以贪心,0-1动态规划 


		
				
				
			
			
			
			

















			
	
		
		

	
	

