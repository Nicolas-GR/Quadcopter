module key_top
	(
	 input clk,
	 input [2:0] JAin,
	 output [3:0] JAout,
	 output [3:0] outcode,
	 output key_available
	);
 
wire clk_2;

divisor_clk divisor_clk
	(
	.clk(clk),
	.clk_out2(clk_2)
	);

decoder_key decoder_key
	(
	.clk(clk_2),
	.columnas(JAin),
	.outcode(outcode),
	.filas(JAout),
	.key_av(key_available)
	);
endmodule
