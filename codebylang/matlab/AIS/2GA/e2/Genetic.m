clc
clear

%initial parameters
maxgen = 30;  %Max generation
sizepop =100;
pcross=0.6;
pmutation=0.01;
lenchrom=[1 1];
bound=[-5 5;-5 5];  

%individuals
individuals = struct('fitness',zeros(1,sizepop),'chrom',[]);



% rand  produce population

for i=1:sizepop
	
	%Code Every time a chromosome
	%Code rand X=[x1,x2];
	individuals.chrom(i,:)=Code(lenchrom,bound);
	
	x=individuals.chrom(i,:);
	
	individuals.fitness(i)=fun(x);
	
end

[bestfitness bestindex]=min(individuals.fitness);%best fitness
bestchrom=individuals.chrom(bestindex,:);

avgfitness=sum(individuals.fitness)/sizepop;
%Record the best fitness and average fitness  in each generation

trace=[];

%Evolution start;

for i=1:maxgen
	
	individuals=Select(individuals,sizepop);
	avgfitness=sum(individuals.fitness)/sizepop;
	
	%cross
	individuals.chrom=Cross(pcross,lenchrom,individuals.chrom,sizepop,bound);
	%mutation
	individuals.chrom=Mutation(pmutation,lenchrom,individuals.chrom,sizepop,[i maxgen],bound);
	
	
	%fitness calculation
	for j=1:sizepop
		x = individuals.chrom(j,:);
		individuals.fitness(j)=fun(x);
	end
	
	%Select->Cross->mutation one generation
	%The younger generation is strong
	
	[newbestfitness,newbestindex]=min(individuals.fitness);
    [worestfitness,worestindex]=max(individuals.fitness);
	
	%There is a small probability event is not normal
    
    if bestfitness>newbestfitness
        bestfitness=newbestfitness;
        bestchrom=individuals.chrom(newbestindex,:);
    end
    
	individuals.chrom(worestindex,:)=bestchrom;
    individuals.fitness(worestindex)=bestfitness;

    avgfitness=sum(individuals.fitness)/sizepop;

    trace=[trace;avgfitness bestfitness]; 

end


[r c]=size(trace);

figure

plot([1:r]',trace(:,1),'r-',[1:r]',trace(:,2),'b--');

title(['f(x)Curve',' ','maxgen=' num2str(maxgen)],'fontsize',12);

xlabel('evolutional generation','fontsize',12);ylabel('f(x)','fontsize',12);

legend('average','best');

disp('f(x)              Variables');

ylim([-0.5 8])

%xlim([1,size(trace,1)])

grid on %Drawing add gridlines

disp([bestfitness x]);












