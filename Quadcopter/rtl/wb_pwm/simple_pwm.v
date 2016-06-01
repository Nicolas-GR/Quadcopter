module simplePWM(reset, clk, time_work, period, PWM_out);
	
	input reset;
	input clk; 				
	input [31:0] time_work;	// time [us] of PWM_out = 1
	input [31:0] period;	// Period [us]
	
	output reg PWM_out = 1'b0;			//PWM signal out
	
	reg [31:0] counter = 32'b0;	//Counter: 0 ~ Period
	reg [31:0] timeWork_reg = 32'b0;
	reg [31:0] period_reg = 32'b0;
	reg enable = 1'b0; 	//Habilita el PWM
	reg avail = 1'b1;
	
	always @(posedge clk) begin
		if(avail)begin
			period_reg	<= period;
			if(time_work <= period)begin
				timeWork_reg <= time_work;
			end else begin
				timeWork_reg <= period;
			end
		end
	end

	always @(posedge clk) begin
		if((period_reg != 32'b0) && (timeWork_reg != 32'b0) && (!reset))begin
			enable <= 1'b1;
		end else begin
			enable <= 1'b0;
		end
	end
	
	always @(posedge clk)begin //Controla el contador
		if(period_reg != 32'b0)begin
			if(counter < period_reg - 32'b1)begin
				counter <= counter+1'b1;	//Aumenta uno con cada subida de flanco del clk
				avail <= 1'b0;
			end else begin
				counter <= 32'b0;
				avail <= 1'b1;		//Solo se habilita el cambio de work_time cuando el contador es cero
			end
		end
	end
	
	always @(posedge clk)begin //Controla la salida del PWM
		if(enable)begin
			if(counter == period_reg - 32'b1)begin
				PWM_out <= 1'b1;
			end else if(counter == (timeWork_reg - 32'b1)) begin
				PWM_out <= 1'b0;
			end			
		end else begin
			PWM_out <= 1'b0;
		end
	end
			
endmodule
	

