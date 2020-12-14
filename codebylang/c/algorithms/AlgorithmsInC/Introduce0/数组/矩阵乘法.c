
a[I][K]*b[K][J]=c[I][J]
{
	for(i=0;i<I;i++)//a行
		for(j=0;j<J;j++)//b列
			for(k=0;k<K;k++)//a列 b行
				c[i][j]+=a[i][k]*b[k][j]; //行列同时动的所以在内层循环
}

