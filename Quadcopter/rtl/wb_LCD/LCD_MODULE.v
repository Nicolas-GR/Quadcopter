
module LCD_MODULE(
	input clk,
	output RW,  
	output reg [7:0] Data_out=8'h00,
	output reg RS = 0,
	output reg E  = 1,
	
	output reg [7:0]in_lcd

 	
    );	
	
	reg [6:0]  estado_in = 0;
	assign RW = 0; // solo escribe 	

wire clk_out_E;
wire clk_out_tado;
//500000
contador_E contador_E (
    .clk(clk), 
    .clk_out_E(clk_out_E)
    );
//1000000
contador_estado contador_estado (
    .clk(clk), 
    .clk_out_tado(clk_out_tado)	
    );	

	always @(posedge clk_out_E) begin  //CONTROL E, IMPRESION
		if (estado_in < 10) begin 	 // NUMERO DE CARACTERES ESCRITOS
			E = ~E;
		end
		else begin
			E = 0;
		end
	end 

	always @(posedge clk_out_tado) begin   
		if (estado_in < 10) begin 	 
			estado_in = estado_in + 1;	 //ACTUALIZA 
		end
		else if (estado_in == 10) begin
			estado_in = 0;
		end
	end

always @(negedge clk_out_tado) begin	 //**IMPRIME Y VE ESTADO.
//case (out_lcd)
	//1: begin
		case (estado_in)
			1: begin RS=0; Data_out = 8'h0C; end   //ESTADO 1 
			2: begin RS=0; Data_out = 8'h38; end   //ESTADO 2 
			3: begin RS=0; Data_out = 8'h01; end 	//Borrar Pantalla
			4: begin RS=1; Data_out = 8'h57; end	//V
			5: begin RS=1; Data_out = 8'h65; end	//e
			6: begin RS=1; Data_out = 8'h6C; end	//l
			7: begin RS=1; Data_out = 8'h2E; end	//.
			8: begin RS=1; Data_out = 8'h3A; end	//:
			9: begin RS=1; Data_out = in_lcd; end	//Espacio	
/*
			10: begin RS=1; Data_out =in_lcd ; end	//número
			11: begin RS=1; Data_out = 8'h57; end	//número
			12: begin RS=1; Data_out = 8'h57; end	//		
			13: begin RS=1; Data_out = 8'h2E; end	//.
			14: begin RS=1; Data_out = 8'h57; end
			15: begin RS=1; Data_out = 8'h57; end
			16: begin RS=1; Data_out = 8'h6D; end	//m
			17: begin RS=1; Data_out = 8'h2F; end	///
			18: begin RS=1; Data_out = 8'h73; end	//s
			19: begin RS=1; Data_out = 8'h20; end	//Espacio
			20: begin RS=0; Data_out = 8'hC0; end	//NUEVA DIRECCION
*/
		/*	21: begin RS=1; Data_out = 8'h52; end	//R
			22: begin RS=1; Data_out = 8'h65; end	//e
			23: begin RS=1; Data_out = 8'h76; end	//v
			24: begin RS=1; Data_out = 8'h2E; end	//o
			25: begin RS=1; Data_out = 8'h3A; end	//:
			26: begin RS=1; Data_out = 8'h20; end	//Espacio
			27: begin RS=1; Data_out = ; end
			28: begin RS=1; Data_out = ; end	//1*
			29: begin RS=1; Data_out = ; end	//8
			30: begin RS=1; Data_out = 8'h20; end	//ones
			31: begin RS=1; Data_out = 8'h52; end	//R
			32: begin RS=1; Data_out = 8'h65; end	//e
			33: begin RS=1; Data_out = 8'h76; end	//v
			34: begin RS=1; Data_out = 8'h2F; end	///
			35: begin RS=1; Data_out = 8'h6D; end	//m
			36: begin RS=1; Data_out = 8'h69; end	//i
			37: begin RS=1; Data_out = 8'h6E; end	//n
			38: begin RS=1; Data_out = 8'h20; end	//Espacio
			39: begin RS=0; Data_out = 8'hC0; end	//NUEVA DIRECCION*/
/*
			
	2: begin
		case (estado_in)
			1: begin RS=0; Data_out = 8'h0C; end   //ESTADO 1 
			2: begin RS=0; Data_out = 8'h38; end   //ESTADO 2 
			3: begin RS=0; Data_out = 8'h01; end 	//Borrar Pantalla
			4: begin RS=1; Data_out = 8'h57; end	//V
			5: begin RS=1; Data_out = 8'h65; end	//e
			6: begin RS=1; Data_out = 8'h6C; end	//l
			7: begin RS=1; Data_out = 8'h2E; end	//.
			8: begin RS=1; Data_out = 8'h3A; end	//:
			9: begin RS=1; Data_out = 8'h20; end	//Espacio	
			10: begin RS=1; Data_out = ; end	//número
			11: begin RS=1; Data_out = ; end	//número
			12: begin RS=1; Data_out = ; end	//		
			13: begin RS=1; Data_out = 8'h2E; end	//.
			14: begin RS=1; Data_out = ; end
			15: begin RS=1; Data_out = ; end
			16: begin RS=1; Data_out = 8'h6D; end	//m
			17: begin RS=1; Data_out = 8'h2F; end	///
			18: begin RS=1; Data_out = 8'h73; end	//s
			19: begin RS=1; Data_out = 8'h20; end	//Espacio
			20: begin RS=0; Data_out = 8'hC0; end	//NUEVA DIRECCION
			21: begin RS=1; Data_out = 8'h52; end	//R
			22: begin RS=1; Data_out = 8'h65; end	//e
			23: begin RS=1; Data_out = 8'h76; end	//v
			24: begin RS=1; Data_out = 8'h2E; end	//o
			25: begin RS=1; Data_out = 8'h3A; end	//:
			26: begin RS=1; Data_out = 8'h20; end	//Espacio
			27: begin RS=1; Data_out = ; end
			28: begin RS=1; Data_out = ; end	//1*
			29: begin RS=1; Data_out = ; end	//8
			30: begin RS=1; Data_out = 8'h20; end	//ones
			31: begin RS=1; Data_out = 8'h52; end	//R
			32: begin RS=1; Data_out = 8'h65; end	//e
			33: begin RS=1; Data_out = 8'h76; end	//v
			34: begin RS=1; Data_out = 8'h2F; end	///
			35: begin RS=1; Data_out = 8'h6D; end	//m
			36: begin RS=1; Data_out = 8'h69; end	//i
			37: begin RS=1; Data_out = 8'h6E; end	//n
			38: begin RS=1; Data_out = 8'h20; end	//Espacio
			39: begin RS=0; Data_out = 8'hC0; end	//NUEVA DIRECCION
			

	3: begin
		case (estado_in)
			1: begin RS=0; Data_out = 8'h0C; end   //ESTADO 1 
			2: begin RS=0; Data_out = 8'h38; end   //ESTADO 2 
			3: begin RS=0; Data_out = 8'h01; end 	//Borrar Pantalla
			4: begin RS=1; Data_out = 8'h57; end	//V
			5: begin RS=1; Data_out = 8'h65; end	//e
			6: begin RS=1; Data_out = 8'h6C; end	//l
			7: begin RS=1; Data_out = 8'h2E; end	//.
			8: begin RS=1; Data_out = 8'h3A; end	//:
			9: begin RS=1; Data_out = 8'h20; end	//Espacio	
			10: begin RS=1; Data_out = ; end	//número
			11: begin RS=1; Data_out = ; end	//número
			12: begin RS=1; Data_out = ;end	//		
			13: begin RS=1; Data_out = 8'h2E; end	//.
			14: begin RS=1; Data_out = ; end
			15: begin RS=1; Data_out = ; end
			16: begin RS=1; Data_out = 8'h6D; end	//m
			17: begin RS=1; Data_out = 8'h2F; end	///
			18: begin RS=1; Data_out = 8'h73; end	//s
			19: begin RS=1; Data_out = 8'h20; end	//Espacio
			20: begin RS=0; Data_out = 8'hC0; end	//NUEVA DIRECCION
			21: begin RS=1; Data_out = 8'h52; end	//R
			22: begin RS=1; Data_out = 8'h65; end	//e
			23: begin RS=1; Data_out = 8'h76; end	//v
			24: begin RS=1; Data_out = 8'h2E; end	//o
			25: begin RS=1; Data_out = 8'h3A; end	//:
			26: begin RS=1; Data_out = 8'h20; end	//Espacio
			27: begin RS=1; Data_out = ; end
			28: begin RS=1; Data_out = ; end	//1*
			29: begin RS=1; Data_out = ; end	//8
			30: begin RS=1; Data_out = 8'h20; end	//ones
			31: begin RS=1; Data_out = 8'h52; end	//R
			32: begin RS=1; Data_out = 8'h65; end	//e
			33: begin RS=1; Data_out = 8'h76; end	//v
			34: begin RS=1; Data_out = 8'h2F; end	///
			35: begin RS=1; Data_out = 8'h6D; end	//m
			36: begin RS=1; Data_out = 8'h69; end	//i
			37: begin RS=1; Data_out = 8'h6E; end	//n
			38: begin RS=1; Data_out = 8'h20; end	//Espacio
			39: begin RS=0; Data_out = 8'hC0; end	//NUEVA DIRECCION
			
	endcase	*/
	
endcase	

end

endmodule
