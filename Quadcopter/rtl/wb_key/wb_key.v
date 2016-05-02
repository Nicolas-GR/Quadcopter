//---------------------------------------------------------------------------
// Wishbone Key Component
//
//     0x00	
//     
//    
//
//---------------------------------------------------------------------------

module wb_key (
	input              clk,
	input              reset, //
	// Wishbone interface
	input              wb_stb_i,
	input              wb_cyc_i,
	output             wb_ack_o,
	input              wb_we_i,
	input       [31:0] wb_adr_i, //
	input        [3:0] wb_sel_i,
	input       [31:0] wb_dat_i,
	output reg  [31:0] wb_dat_o,
	//
	// IO Wires
	output	[3:0] dato_led,
	input  [2:0] JA_in, //
	output  [3:0] JA_out
);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

//Internal Registers
wire [2:0] JA_in_wire;
wire [3:0] JA_out_wire;
wire [3:0] outcode_wire;
wire key_av_wire;

// Wishbone logical Interface
reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;

key_top key0 (
	.clk(clk),
	.JAin(JA_in_wire),
	.JAout(JA_out_wire),
	.outcode(outcode_wire),
	.key_available(key_av_wire)
);

assign JA_in_wire = JA_in;
assign JA_out = JA_out_wire;
assign dato_led = outcode_wire;

always @(posedge clk)
begin
	if (reset) begin
		ack      <= 0;
	end else begin
		ack    <= 0;
		if (wb_rd & ~ack) begin           // read cycle
			ack <= 1;
			case (wb_adr_i[3:2])
			2'b00:begin  
		            wb_dat_o[31:4] <= 28'd0;
		            wb_dat_o[3:0] <= outcode_wire;
			end
			2'b01:begin
		            wb_dat_o[31:1] <= 31'd0;
		            wb_dat_o[0] <= key_av_wire;
			end
			default: wb_dat_o <= 32'd0;
			endcase

	end
end
end

endmodule
