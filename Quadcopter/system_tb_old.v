//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 20;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
wire       led;
wire	   led1;
wire       led2;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;
wire         uart_rxd1;
wire         uart_txd1;

//----------------------------------------------------------------------------
// SPI 
//----------------------------------------------------------------------------
wire         spi_mosi;
wire         spi_miso;
wire         spi_clk;



//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------
system #(
	.clk_freq(           clk_freq         ),
	.uart_baud_rate(     uart_baud_rate   )
) dut  (
	.clk(          clk    ),
	// Debug
	.rst(          rst    ),
	.led(          led    ),
	.led1(          led1    ),
	// Uart0
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  ),
	//uart1
	.uart_rxd1(  uart_rxd1  ),
	.uart_txd1(  uart_txd1  ),
	// SPI
	spi_miso(spi_miso),
	spi_mosi(spi_mosi),
	spi_clk(clk_clk)
);

/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;

/* Simulation setup */
initial begin



	$dumpfile("system_tb.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, dut);
	//$dumpvars(-1,clk,rst,uart_txd);
	// reset
	#0  rst <= 0;
	#80 rst <= 1;

	#(tck*10000) $finish;
end



endmodule
