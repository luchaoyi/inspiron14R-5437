function chrom = Qgate(chrom,fitness,best,binary)
% compare with best decide spin 
% if xi == besti  still else spin


[sizepop,lenchrom] = size(chrom);
sizepop = sizepop/2;

for i=1:sizepop
	for j=1:lenchrom
		
		A=chrom(2*i-1,j) % alpha
		B=chrom(2*i,j) %beta

		x=binary(i,j)
		b=best.binary(j);

		

		 if ((x==0)&(b==0))||((x==1)&(b==1))
            delta=0;                  % delta为旋转角的大小
            s=0;                        % s为旋转角的符号，即旋转方向
        elseif (x==0)&(b==1)&(fitness(i)<best.fitness)
            delta=0.01*pi;
            if A*B>0
                s=1;
            elseif A*B<0
                s=-1;
            elseif A==0
                s=0;
            elseif B==0
                s=sign(randn);
            end
        elseif (x==0)&(b==1)&(fitness(i)>=best.fitness)
            delta=0.01*pi;
            if A*B>0
                s=-1;
            elseif A*B<0
                s=1;
            elseif A==0
                s=sign(randn);
            elseif B==0
                s=0;
            end
        elseif (x==1)&(b==0)&(fitness(i)<best.fitness)
            delta=0.01*pi;
            if A*B>0
                s=-1;
            elseif A*B<0
                s=1;
            elseif A==0
                s=sign(randn);
            elseif B==0
                s=0;
            end
        elseif (x==1)&(b==0)&(fitness(i)>=best.fitness)
            delta=0.01*pi;
            if A*B>0
                s=1;
            elseif A*B<0
                s=-1;
            elseif A==0
                s=0;
            elseif B==0
                s=sign(randn);
            end
        end

		e=s*delta;

		U=[cos(e),-sin(e);sin(e),cos(e)];

		y= U*[A B]';
		
		chrom(2*i-1,j) = y(1);
		chrom(2*i,j) = y(2);
 
	end
end





