
module contador_estado(clk,clk_out_tado);

 input clk;         //Clock de entrada del FPGA de entrada 
 output reg clk_out_tado;  //Señal de salida 

  reg[257:0] contador_tado; 

 always @(posedge clk)
  begin
	if(contador_tado >= 1_000_000) 
	begin
	contador_tado = 0;
	end	
   if(contador_tado == 999_999) // FRECUENCIA 50 Hz
   begin
      contador_tado= 0;
      clk_out_tado= ~clk_out_tado; 
   end
	else begin
		  contador_tado= contador_tado + 1;
	end
  end

endmodule
