module decoder_key
	(
	 input clk,
	 input [2:0] columnas,
	 output reg [3:0] outcode = 4'd0,
	 output [3:0] filas,
	 output reg key_av = 1'b0
	);

reg [1:0] cont = 2'b0;

always @(posedge clk)
	begin
		if (cont == 2'b11) begin cont <= 0; end
		else begin cont <= cont + 2'b01; end
	end

selector_filas_key sel1
	(
	.sel(cont),
	.valfilas(filas)
	);

always @(negedge clk) begin
		case (cont)
		2'b00:	begin
				case (columnas)
				3'b001: begin
					outcode <= 4'd1;
					key_av <= 1'b1;
					end
				3'b010: begin
					outcode <= 4'd2;
					key_av <= 1'b1;
					end
				3'b100: begin
					outcode <= 4'd3;
					key_av <= 1'b1;
					end
				default: begin
					outcode <= 4'd11;
					key_av <= 1'b0;
					end
				endcase
			end
		2'b01:	begin
				case (columnas)
				3'b001: begin
					outcode <= 4'd4;
					key_av <= 1'b1;
					end
				3'b010: begin
					outcode <= 4'd5;
					key_av <= 1'b1;
					end
				3'b100: begin
					outcode <= 4'd6;
					key_av <= 1'b1;
					end
				default: begin
					outcode <= 4'd11;
					key_av <= 1'b0;
					end
				endcase
			end
		2'b10:	begin
				case (columnas)
				3'b001: begin
					outcode <= 4'd7;
					key_av <= 1'b1;
					end
				3'b010: begin
					outcode <= 4'd8;
					key_av <= 1'b1;
					end
				3'b100: begin
					outcode <= 4'd9;
					key_av <= 1'b1;
					end
				default: begin
					outcode <= 4'd11;
					key_av <= 1'b0;
					end
				endcase
			end
		2'b11:	begin
				case (columnas)
				3'b001: begin
					outcode <= 4'd14; //Asterisco
					key_av <= 1'b1;
					end
				3'b010: begin
					outcode <= 4'd0;
					key_av <= 1'b1;
					end
				3'b100: begin
					outcode <= 4'd15; //Numeral
					key_av <= 1'b1;
					end
				default: begin
					outcode <= 4'd11;
					key_av <= 1'b0;
					end
				endcase
			end
		endcase
		end 

endmodule
