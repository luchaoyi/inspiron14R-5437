module newspaper_fsm(
input wire[1:0] coinin, //01:5分 10:10分 
input outpaper,
input rst,
input clk,
output reg newspaper 
);


reg[2:0] current_state;


always @(posedge clk)
begin
	if(rst)
	begin
		current_state<=3'd0;
		newspaper<=0;
	end
	else
	begin
		case (current_state)
			3'd0:
			begin 
				newspaper<=0;
				if (coinin==2'b01)
					current_state<=3'd1;
				else if (coinin==2'b10)
					current_state<=3'd2;
				else
					;
			end 

			3'd1:
			begin 
				if (coinin==2'b01)
					current_state<=3'd4;
				else if (coinin==2'b10)
					current_state<=3'd3;
				else
					;
			end 

			3'd2:
			begin
				if (coinin==2'b01 || coinin==2'b10)
					current_state<=3'd3;
				else
					;
			end

			3'd3:
			begin
				if(outpaper)
				begin
					newspaper<=1;
					current_state<=3'd0;
				end
				else
				;
			end
			3'd4:
			begin
				if (coinin==2'b01 || coinin==2'b10)
					current_state<=3'd3;
				else
					;

			end 
			default:
			;
		endcase
	end 
end  
endmodule
