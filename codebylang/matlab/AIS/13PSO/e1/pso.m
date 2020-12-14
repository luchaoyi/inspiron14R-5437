clc
clear

c1=1.49445;
c2=1.49445;

exn=1;%The number of experiments
fitnessgbestk=1;% The lower limit of the control solution

maxgen=300; % number of loop
sizepop=20; % population number

popmax=2;  
popmin=-2;

Vmax=0.5;
Vmin=-0.5;


for k=1:exn
        %rand produce population

        for i=1:sizepop
            pop(i,:)=2*rands(1,2);%X=[x1,x2]
            v(i,:)=0.5*rands(1,2);

            %fitness
            fitness(i)=fun(pop(i,:));
        end
        %initialization
            [bestfitness bestindex] = max(fitness);

            gbest=pop(bestindex,:);%global best only one Xbest=[x1,x2];
            ibest=pop;			   %individuals best have sizepop

            fitnessibest=fitness; %individuals best
            fitnessgbest=bestfitness;%global best


        %loop found the optimal solution start

        for i=1:maxgen
            for j=1:sizepop

                %set w=1
                v(j,:)=v(j,:)+c1*rand*(ibest(j,:)-pop(j,:))+c2*rand*(gbest-pop(j,:));

                %if Out of bounds  then Correction
                v(j,find(v(j,:)>Vmax)) = Vmax;
                v(j,find(v(j,:)<Vmin))= Vmin;


                pop(j,:)=pop(j,:)+v(j,:);
                pop(j,find(pop(j,:)>popmax))=popmax;
                pop(j,find(pop(j,:)<popmin))=popmin;

               fitness(j)=fun(pop(j,:)); 
            end


            for j=1:sizepop

                %individuals
                if fitness(j)>fitnessibest(j)
                    ibest(j,:)=pop(j,:); %record individuals best Coordinate 
                    fitnessibest(j)=fitness(j);
                end

                %global

                if  fitness(j)>fitnessgbest
                    gbest=pop(j,:);%record global best solution
                    fitnessgbest=fitness(j);
                end
            end

            %record Change process
            result(i)=fitnessgbest;
        end
        


		%多次随机实验下记录最优结果的一次实验
        if fitnessgbest>fitnessgbestk
            fitnessgbestk=fitnessgbest;
            gbestk=gbest;
            resultk=result;
        end    
end

disp('Max f(x)         X');
disp([fitnessgbestk  gbestk]);
plot(resultk);
xlabel('gen');ylabel('f(x)');
	

