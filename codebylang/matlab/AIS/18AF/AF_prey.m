function [Xnext,Ynext] = AF_prey(Xi,ii,visual,step,try_number,LBUB,lastY)

%Foraging fisher move to better position

Xnext=[];
Yi=lastY(ii);%lastY record Yi  To avoid repeated calculation

	for i=1:try_number

		Xj=Xi+visual*rands(length(Xi),1);%visual
		Yj=AF_foodconsistence(Xj);
		
		%better then move
		if Yj>Yi
			%move
			%(Xj-Xi)/norm(Xj-Xi) A unit vector vector
			Xnext=Xi+rand*step*(Xj-Xi)/norm(Xj-Xi);
			
			for j=1:length(Xnext)
			
				if Xnext(j)>LBUB(j,2);
				
					Xnext(j)=LBUB(j,2);
				end
				
				if Xnext(j)<LBUB(j,1);
				
					Xnext(j)=LBUB(j,1);
				end	
			end
			% found better stop try view;
			break;
		end
	end
	
	%rand move
	if isempty(Xnext)
		Xj=Xi+visual*rands(length(Xi),1);
		
		Xnext=Xj;
		
		for j=1:length(Xnext)
			
				if Xnext(j)>LBUB(j,2);
				
					Xnext(j)=LBUB(j,2);
				end
				
				if Xnext(j)<LBUB(j,1);
				
					Xnext(j)=LBUB(j,1);
				end	
			end
	end
	
	Ynext=AF_foodconsistence(Xnext);

end