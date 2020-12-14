strlen(a)
{	for(i=0;a[i]!=0;i++)
	return i;
}

strcpy(a,b)
{
	for(i=0;(a[i]=b[i])!=0;i++)
}

strcmp(a,b)
{
	for(i=0;a[i]==b[i];i++)
		if(a[i]==0) return 0;
	return a[i]-b[i];
}


