function chrom = InitPop(M,N)
%Pop size M/2 (a,b)
% [	a1 ...
%	b1 ...
%	a2 ...
%	b2 ...
%	...
%	]

for i=1:M
	for j=1:N
		chrom(i,j) = 1/sqrt(2);
	end
end

