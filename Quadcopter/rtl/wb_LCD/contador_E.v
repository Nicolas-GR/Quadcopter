
module contador_E(clk,clk_out_E);

 input clk;         //Clock de entrada del FPGA de entrada 
 output reg clk_out_E = 1;  //Señal de salida 

  reg[257:0] contador_E = 0; 

 always @(posedge clk)
  begin
   if(contador_E >= 500_000)
	begin
		contador_E=0;
	end
	else if(contador_E == 499_999) // FRECUENCIA 100 Hz
   begin
      contador_E = 0;
      clk_out_E= ~clk_out_E; 
   end
	else 
	begin
		contador_E= contador_E + 1; 
	end	
  end


endmodule
