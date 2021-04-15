#
# Makefile for compiling programs for the DETI robot
#
# Simplest way to use: 
# - compile my_file.c
# $ make SOURCES=my_file.c
# 
# - compile and load to the robot:
# $ make SOURCES=my_file.c dload
#
# - compile, load to the robot and run pterm:
# $ make SOURCES=my_file.c run
#
# PF, Nov 2012
# Revised:
# Date:        By:        	Description:
# March 2014   pf@ua.pt   	Changed to have more than one source file
# March 2014   fabiorico@ua.pt  Support for labE library
# March 2017   fmsilva@ua.pt  	Change the target name from "load" 
#				(option of the make command) to "dload"
# March 2019   fmsilva@ua.pt  	Change the global variable PICDIR to /usr/local/pic32mx 
#
# The default for the makefile is to compile all C files defined 
# in SOURCES and to create TARGET.hex, where TARGET is the name
# of the first file in SOURCES
#
# Other targets are:
#
# dload    : load the latest version to PIC (and previously compile, 
#	     if necessary)
# run      : run pterm after loading the hex file.
# clean    : remove all unnecessary files
# cleanall : drastic cleaning; remove every output of compilation
#            including documentation
# help     : this help message...
#
# In the following line, define the name of your program source files
# by writing in the line starting with SOURCES= 
# (this is all you need to change...)
SOURCES=p3c.c 

# Next line defines the USB port used by ldpic32. Change this if the
# USB port is not /dev/ttyUSB0
USBPORT=/dev/ttyUSB0

# Your program can have more than one source file. Use space to 
# separate the name of the source files. 
# The first file name will be used for the name of the hex file. 
#
# The name of the target can also be defined in the command line
# (overrides the definition in the file) when calling make.
#
# The following line shows how to compile a file called new_target.c
# $ make SOURCES=new_target.c
#
# ('$' stands for the command line prompt; it is not to be typed...)
#
# When you have more than one source file, include the file name list
# in "":
# $ make SOURCES="file1.c file2.c"
#
# or escape the space character with '\':
# $ make SOURCES=file1.c\ file2.c
#
# Same as before, but now load the resulting file into the PIC:
# $ make SOURCES=new_target.c dload

#
# You can have a look at the rest of the file, to understand how
# a makefile works.
#
# Nevertheless, keep in mind:
# Don't change below this line, unless you know what you are doing!
#

#
# Global variables
# 
PICDIR=/opt/pic32mx
CFLAGS=-Wall -O2 -mprocessor=32MX795F512H -I$(CPATH)
# CFLAGS=-Wall -O2 -mprocessor=32MX795F512H 
CPATH=$(PICDIR)/include
CC=$(PICDIR)/bin/pic32-gcc
LIB=labE.o
# TARGET is the first file in SOURCES
TARGET=$(basename $(firstword $(SOURCES)))

# The OBJECTS are same as .c files, but changing .c for .o
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))


#
# Compile source files 
# This is not required, and it is performed by an automatic rule
# given the definitions above
#
# %.o : %.c
#	$(CC) $(CFLAGS) -c -o $@ $<


#
# Create $(TARGET).hex
#
$(TARGET).hex : $(OBJECTS) $(LIB)
	$(PICDIR)/bin/pic32-ld -nostdlib $(OBJECTS) $(LIB) \
		-o $(TARGET).elf -L$(PICDIR)/lib -L$(PICDIR)/lib/gcc/pic32mx/3.4.4 \
		-ldetpic32 -lgcc -Map $(TARGET).map
	$(PICDIR)/bin/pic32-bin2hex $(TARGET).elf



.PHONY: dload run clean cleanall help

#
# Load hex file to PIC
#
dload : $(TARGET).hex
	ldpic32 -p $(USBPORT) -w $(TARGET).hex

#
# Run pterm at the end...
#
run : dload
	pterm -p $(USBPORT)

#
# Housekeeping section...
#
clean : 
	echo "Cleaning all discardable files..."
	rm -rf *.elf *.map *~
	rm -f *.o

cleanall : clean
	echo "Cleaning all non-source files..."
	rm -rf *.hex *.o
	rm -rf Doc/

help:
	@cat Makefile | head -68 | less	

