

for(s=0;s<v;s++)
	for(t=0;t<v;t++);
		for(i=0,C[s][t]=0;i<v;i++)
	C[s][t]+=a[s][i]*b[i][t]
	
/*
	bool 阵
	+ = ||
	* = c&
*/


for(s=0;s<v;s++)
	for(t=0;t<v;t++);
		for(i=0,C[s][t]=0;i<v;i++)
	if(a[s][i]&b[i][t]) C[s][t] = 1;
