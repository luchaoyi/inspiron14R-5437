#!/bin/bash
read   -p  "The number of input parameter is $#,continue? 
" answer
#echo $answer
#obj_file is $1
obj_file=$1
in_file=""
shift 1

while [ $# != 0 ]
do 


	    in_file=$in_file" "$1
		shift 1
done

echo "input file:"$in_file
iverilog -o $obj_file $in_file 
vvp -n $obj_file -lxt2

echo "-*-*-*-*-*-*-"
#cp $obj_file.vcd $obj_file.lxt
#gtkwave $obj_file.lxt
gtkwave $obj_file.vcd


#iverilog -o test tb.v test.v
#vvp -n test -lxt2
#cp test.vcd test.lxt
#gtkwave test.lxt
