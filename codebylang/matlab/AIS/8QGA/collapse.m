function binary = collapse(chrom)
% > a or > b can test the bit state
% select a test if rand >a^2  --> 1 else 0

[M,N] = size(chrom)

M=2/M;

for i=1:M
	for j=1:N
		pick = rand;
		if (chrom(2*i-1,j)^2)
			binary(i,j) = 1;
		else
			binary(i,j) = 0;
		end
	end
end



