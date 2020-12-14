
void A(){
	//循环控制依赖
	for int i=1;i<n;i++
		a[i]=b[i]+c[i];
			if(a[i-1])
				c[i]=a[i]+2;

	//a[i],a[i-1]->使用临时变量
	prev=a[0];
	for ...{
		next=b[i]+c[i];
		if(prev){
			c[i]=next+2;
		}

		a[i]=next;
		prev=next;
	}
	//c[i]->
	prev=a[0];
	for ...{
		tempc=c[i];
		next=b[i]+tempc;
		if(prev){
			tempc=next+2;
		}
		c[i]=tempc;
		a[i]=next;
		prev=next;

	}
	//->remove if
	prev=a[0];
	for ...{
		tempc=c[i];
		next=b[i]+tempc;
		c[i]=prev?next+2:tempc;

		a[i]=next;
		prev=next;
	}
	//临时变量减少了内存访问
	//此时或可考虑循环展开
}

void B(){

	//1
	for i=0:n{
		a[i+1]=b[i]+c;
		d[i]=a[i]+2 ;  
	}
	//a[i]依赖 临时变量思路
	preva=a[0] 
	for i=0:n{
		nexta=b[i]+c;
		d[i]=preva+2 ;
		a[i+1]=nexta;
		preva=nexta;
	}

	//2
	for i=0:n{
		a[i]=b[i]+1;
		c[i]=a[i]+2;
		d[i]=c[i+1]+1;
	}

	//c[i],a[i]
	//d[i]=c[i+1]+1操作的是原始c中的值与c新值无关，此时可以复制c数组
	//增加了内存拷贝，有开销
	cb=deepcopy(c);
	for i=0:n{
		ta=b[i]+1;
		a[i]=ta;
		c[i]=ta+2;
		d[i]=cb[i+1]+1;
	}

	//循环拆分,d[i]拆出
	for i=1:n{
		d[i]=c[i+1]+1;
	}

	for i=0:n{
		ta=b[i]+1;
		a[i]=ta;
		c[i]=ta+2;
	}

	//进一步优化可以将d[i]=c[i+1]+1->d[i]=c[i]+1;
}
