module selector_filas_key
	(
	 input [1:0] sel,
	 output reg [3:0] valfilas
	);
	
	always @(*)
	case (sel)
		2'b00: valfilas = 4'b0001;
		2'b01: valfilas = 4'b0010;
		2'b10: valfilas = 4'b0100;
		2'b11: valfilas = 4'b1000;
	endcase
endmodule
