



int **malloc2d(int r,int c)
{
	int i;
	int **t=(int**)malloc(r*sizeof(int*));//r个行指针
	for(i = 0;i<r;i++)
	{
		t[i]=(int*)malloc(c*sizeof(int))
	}
	return t;
}
