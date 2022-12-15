#!/bin/sh
bindir=$(pwd)
cd /home/e20210010747/Bureau/TP_texture/TP4_transformations/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/e20210010747/Bureau/TP_texture/build/TP4_transformations 
	else
		"/home/e20210010747/Bureau/TP_texture/build/TP4_transformations"  
	fi
else
	"/home/e20210010747/Bureau/TP_texture/build/TP4_transformations"  
fi
