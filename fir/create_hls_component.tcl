open_component -reset fir -flow_target vivado

add_files ./fir/fir.cpp
add_files ./fir/fir.h
add_files -tb ./fir/fir_test.cpp

# top level function
set_top fir 

set_part {xc7z020clg400-1}
create_clock -period 10 -name sys_clk
