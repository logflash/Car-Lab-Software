# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\ianh\Documents\Car Lab\Navigation\Design.cydsn\Design.cyprj
# Date: Sun, 08 Oct 2023 19:14:17 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {dc_motor_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {hall_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {servo_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {XBee_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {hall_clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 24001 48001} [list [get_pins {ClockBlock/dclk_glb_5}]]
create_generated_clock -name {dark_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_0}]]


# Component constraints for C:\Users\ianh\Documents\Car Lab\Navigation\Design.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\ianh\Documents\Car Lab\Navigation\Design.cydsn\Design.cyprj
# Date: Sun, 08 Oct 2023 19:14:11 GMT
