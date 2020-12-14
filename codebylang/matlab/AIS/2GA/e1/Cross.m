function ret = Cross(pcross,lenchrom,chrom,sizepop,bound )

% pcross    input ;Cross Probability
%lenchrom   input ;length of chrom
%sizepop    input ;population size

    for i=1:sizepop
        pick=rand(1,2);
   
    
        while prod(pick)==0;%continued product 
            pick=rand(1,2);
        end

        index=ceil(pick .* sizepop);%selected cross chrom index

        %Combined with the selected chromosome like humans certain probability

        pick=rand;

        while pick==0
            pick=rand;
        end

        if pick>pcross %Do not Cross probability
            continue;
        end
        
        %Cross
        
        flag=0; %Validity
        
        while flag==0;
            pick=rand ;%rand pick Cross position
            
            while pick==0
                pick=rand;
            end
            
            pos=ceil(pick .*sum(lenchrom));
            
            pick=rand;
            
            v1=chrom(index(1),pos); %akj
            v2=chrom(index(2),pos); %alj
            
            %cross
            %akj=akj*b+alj*(1-b)
            %alj=akj*(1-b)+alj*b
          
            chrom(index(1),pos)=v1*pick+v2*(1-pick);
            chrom(index(2),pos)=v1*(1-pick)+v2*pick;
            
            %test chrom is out of bounds
            
            flag1=test(lenchrom,bound,chrom(index(1),:)); 
            flag2=test(lenchrom,bound,chrom(index(2),:)); 
            
            if   flag1*flag2==0
                 flag=0;
            else
                flag=1;   
            end
            
            
        end
        
        
    end
    
    ret=chrom;

end

