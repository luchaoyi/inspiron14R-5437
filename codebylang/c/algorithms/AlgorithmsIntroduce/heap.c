//堆
def parent(i):
	return floor(i/2);

def left(i):
	return 2i;
def right(i):
	return 2i+1;

//检查A[i],维护最大堆性质
def max-heapify(A,i):
	l=left(i)
	r=right(i)
	//交换左右更大的
	if l<A.size and A[l]>A[i]:
		large=l
	else
		large=i
	
	if r<A.size and A[r]>A[large]:
		large=r

	if large!=i:
		exchange(A,i,large)
		max-heapify(A,large)

def build-max-heap(A):
	//自底向上堆化，建立一个大顶堆
	for i=A.size/2 downto 1:
		max-heapify(A,i)

def heap-sort(A):
	build-max-heap(A)
	//堆顶最大元素置于末尾，缩小堆范围，直到全部有序
	for i=A.size to 2:
		exchange(A[1],A[i])
		A.size-=1;
		max-heapify(A,1)

//堆实现优先队列
def heap-max(A):
	return A[1]

def heap-extract-max(A):
	if A.size<1:
		error "heap underflow"

	max=A[1]
	exchange(A[1],A[A.size]);
	A.size-=1;
	max-heapify(A,1)
	return max 

//if key>A[i],A[i]=key
def heap-increase-key(A,i.key):
	if key<A[i]:
		error "..."
	A[i]=key 
	//调整
	
	while i>1 and A[parent(i)]<A[i]:
		exchange(A,i,parent(i))
		i=parent(i)

def heap-insert(A,key)
	A.size+=1
	A[A.size]=-INF
	heap-increase-key(A,A.size,key)

		
		
