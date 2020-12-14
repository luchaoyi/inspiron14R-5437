
//i=lgN,2^i=N, 
int lg(int N)
{
	for (i=0;N>0;i++,N/=2);
	return i;
}
