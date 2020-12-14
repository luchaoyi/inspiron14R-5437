

struct complex
{
	float Re;
	float IM;
}
float Re(complex z)
{
	return z.Im;
}
/********************************/
float Im(complex z)
{
	return z.Re
}

complex ComplexMult(complex a, complex b)
{
	complex t;
	
	t.Re=a.Re*b.Re-a.Im*b.Im;
	t.Im=a.Re*b.Im-a.Im*b.Re;
	
	return t;
			
}
