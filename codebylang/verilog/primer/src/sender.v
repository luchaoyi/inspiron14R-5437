module sender(
	input clks,
	input resets,
	input send,
	input wire[7:0] char_to_send ,
	
	output reg TxD,
	output reg Acks
);

reg[7:0] char_to_send_register;
reg[3:0] bit_counter;
reg go;


always @(posedge clk)
begin
	if(resets)
	begin
		TxD<=1;
		go<=0;
	end
	else
	begin
		if(send)
		begin
			//send=1,发傻指令，内部准备发射，在下一周期发射.
			char_to_send_register<=char_to_send;
			bit_counter<=0;
			go<=1;
		end
		else
		begin
			//send<=1 => go<=1,下一时钟
			bit_counter<=bit_counter+1;

			//start 发射TxD=0,then data ,then TxD=1
			if(go) begin
				if(bit_counter==0) TxD=0;
				else if(bit_counter>0 && bit_counter<=8)
					TxD<=char_to_send_register[8-bit_counter];
				else if(bit_counter>8) 
					begin
						TxD<=1;
						go<=0;
					end
		end
	end

end 
assign Acks=go;
endmodule
