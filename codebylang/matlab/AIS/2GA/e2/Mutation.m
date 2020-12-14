function ret=Mutation(pmutation,lenchrom,chrom,sizepop,pop,bound)
%mutation

%pmutation input ;mutation probability

	for i=1:sizepop
		pick=rand; %rand select chromsome mutation
		
		while pick==0
			pick=rand;
		end
		index=ceil(pick .* sizepop);
		
		%mutation depending on mutation probability 
		
		pick=rand;
		
		if pick>pmutation
			continue;
		end
		
		flag=0; %mutation  effective flag
		
		while flag==0
			
			%pmutation position
			
			pick = rand;
			
			while pick==0
				pick=rand;
			end
			
			pos=ceil(pick .* sum(lenchrom));
			
			v=chrom(i,pos); %aij
			
			v1=v-bound(pos,2);
			
			v2=bound(pos,1)-v;
			
			%mutation start
			
			pick=rand;
			
			
			if pick>0.5

				delta=v2*(1-pick^((1-pop(1)/pop(2))^2));

				chrom(i,pos)=v+delta;

			else

				delta=v1*(1-pick^((1-pop(1)/pop(2))^2));

				chrom(i,pos)=v-delta;

			end   

			flag=test(lenchrom,bound,chrom(i,:));     %����Ⱦɫ��Ŀ�����
		end			
	end
	
	ret =chrom;
end