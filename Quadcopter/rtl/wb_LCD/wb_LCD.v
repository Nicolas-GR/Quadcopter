//---------------------------------------------------------------------------
// Wishbone lcd Component
//
//     0x00	
//     
//    
//
//---------------------------------------------------------------------------

module wb_LCD (
	input              clk,
	input              reset, //
	// Wishbone interface	
	input              wb_stb_i,
	input              wb_cyc_i,
	output             wb_ack_o,
	input              wb_we_i,
	input       [31:0] wb_adr_i, 
	input        [3:0] wb_sel_i,
	input       [31:0] wb_dat_i,
	output reg  [31:0] wb_dat_o,	
	// LCD
	output reg   [7:0] in_lcd_1,
	output  RW_1,  
	output  [7:0] Data_out_1,
	output  RS_1,
	output  E_1  
	//
	// IO Wires


);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

//Internal Registers
//wire [3:0] out_lcd_wire;
wire RW_wire;
wire [7:0] Data_out_wire;
wire RS_wire;
wire E_wire;
wire [7:0]in_lcd_wire;


// Wishbone logical Interface
reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;
wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

LCD_MODULE lcd0(
	.clk(clk),
	.RW(RW_wire),  
	.Data_out(Data_out_wire),
	.RS(RS_wire),
	.E(E_wire),
	.in_lcd(in_lcd_wire)	
    );	

assign RW_1 = RW_wire;
assign Data_out_1 = Data_out_wire;
assign RS_1 = RS_wire;
assign E_1 = E_wire;
assign in_lcd_wire[7:0] = in_lcd_1[7:0];

//assign in_lcd_wire[7:0] = wb_dat_i[7:0];
//assign in_lcd_wire[7:0] = 8'h31;

always @(posedge clk)
begin
	if (reset) ack <= 0;
	
	else begin
		ack <= 0;
		if (wb_rd & ~ack) begin           // read cycle
			ack <= 1;
			if (wb_adr_i[3:2] == 2'b01) wb_dat_o <= {31'h00, RS_wire};
				end
	
		if (wb_wr & ~ack) begin           // write cycle
			if (wb_adr_i[3:2] == 2'b00) in_lcd_1[7:0] <= wb_dat_i[7:0];
				end
		end
end

endmodule
