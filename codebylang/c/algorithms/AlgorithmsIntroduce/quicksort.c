def quicksort(A,p,r):
	if p<r:
		q=parttion(A,p,r);
		quicksort(A,p,q-1);
		quicksort(A,q+1,r);

/*		
def parttion(A,p,r):
	//选主元
	temp=A[r]
	i=p;
	j=r-1;
	while(i<j):
		while(A[i]<temp)
			i++;
		while(A[j]>temp)
			j++;
		exchange(A[i],A[j]);
	exchange(A[r],A[i]);
	return i;
*/
/* p  <=x  i    >x  j 待处理  r-1  r*/
def parttion(A,p,r):
	x=A[r]
	i=p-1
	for j=p to r-1:
		if A[j]<=x
			i=i+1
			exchange(A[i],A[j])

	exchange(A[i+1],A[r])
	return i+1

def random-parttion(A,p,r):
	i=random(p,r);
	exchange(A[i],A[r]);
	return parttion(A,p,r);


//找出第i个	
//划分，只找另一半
def random-select(A,p,r,i):
	if p==r:
		return A[p]
	q=random-parttion(A,p,r)
	k=q-p+1
	if(i==k):
		return A[q]
	else if i<k
		return random-select(A,p,q-1,i);
	else
		return random-select(A,q+1,r,i-k)

