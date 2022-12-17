#!/bin/sh
bindir=$(pwd)
cd /home/max/Documents/GitHub/Texture/TP_texture/TP4_transformations/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/max/Documents/GitHub/Texture/TP_texture/build/TP4_transformations 
	else
		"/home/max/Documents/GitHub/Texture/TP_texture/build/TP4_transformations"  
	fi
else
	"/home/max/Documents/GitHub/Texture/TP_texture/build/TP4_transformations"  
fi
