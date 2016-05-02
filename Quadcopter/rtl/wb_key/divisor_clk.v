module divisor_clk
	(
	 input clk,
	 output reg clk_out2 = 1'b1
	);

reg [23:0] cont_2 = 24'b0;

parameter valor_divisor2 =24'd250000;// 24'd250000; //200 Hz fecuencia de muestreo

always @(posedge clk) begin
	if (cont_2 == (valor_divisor2-1)) begin
		clk_out2 <= ~clk_out2;
		cont_2 <= 0;
		end
	else begin cont_2 <= cont_2 + 1'b1; end
	end

endmodule
