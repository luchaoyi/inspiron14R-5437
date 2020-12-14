function ret = Select(individuals,sizepop)
%
%


individuals.fitness =1 ./(individuals.fitness);

sumfitness = sum(individuals.fitness);

sumf=individuals.fitness ./sumfitness; %ratio

index=[]; %preallocating

    %Roulette
    %number of Roulette
    for i=1:sizepop
            pick=rand; %default 0-1
            
            while 0==pick
                pick=rand;
            end
            
            
            for j=1:sizepop
                
                pick=pick-sumf(j);
                
                if pick<0
                    
                    index=[index j]; %select chrom fall into section j
                    break;
                end
            end
    end
    
    %Do not select individual death
    %Survival of the fittest
    individuals.chrom=individuals.chrom(index,:); %select chrom
    individuals.fitness=individuals.fitness(index);
    
    ret=individuals;
end

