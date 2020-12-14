//T哨兵保存tree的一些信息,以及nil

/*
T.nil=NIL
T.root=树根
*/
def left-rotate(T,x)
	//设置y指向x右孩子
	y=x.right;
	x.right=y.left 
	y.right=x

	if y.left!=T.nil:
		y.left.p=x
	y.p=x.p


	//调整x,y,以及孩子，以及x的p
	if x.p==T.nil:
		T.root=y
	//x是p的左孩子
	else if x==x.p.left:
		x.p.left=y
	else // x==x.p.right:
		x.p.right=y
		y.left=x;
		x.p=y

def RB-insert(T,z):
	y=T.nil
	x=T.root
	while x!=T.nil
		y=x
	//left
		if z.key < x.key :
			x=x.left 
		else
			x=x.right
			
		






