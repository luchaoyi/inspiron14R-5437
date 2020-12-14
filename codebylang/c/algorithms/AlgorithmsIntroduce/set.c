def make-set(x):
	x.p=x
	x.rank=0
def union-set(x,y):
	link(find-set(x),find-set(y))
def find-set(x):
	if x!=x.p
		x.p=find-set(x.p)
	return x.p

def link(x,y):
	if x.rank>y.rank:
		y.p=x
	else 
		x.p=y
		if x.rank==y,rank:
			y.rank=y.rank+1
			

	

