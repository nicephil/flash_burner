# default target
default: application-target

# standard common Makefile fragment
include $(OCTEON_ROOT)/common.mk

# include needed component
dir := $(OCTEON_ROOT)/executive
include $(dir)/cvmx.mk


# application specification
TARGET = testmain$(PREFIX)

OBJS = $(OBJ_DIR)/testmain.o $(OBJ_DIR)/burn.o

CFLAGS_LOCAL = -g -O2 -W -Wall -Wno-unused-parameter

include $(OCTEON_ROOT)/application.mk

# run4
run4: $(TARGET)
	oct-sim $(TARGET) -quiet -noperf -numcores=4

# install
install: $(TARGET)
	scp $(TARGET) hzchlg06:~
	ssh hzchlg06 "scp $(TARGET) fews:/tftpboot"


# clean target
clean:
	rm -rvf $(TARGET)
	rm -rvf $(CVMX_CONFIG)
	rm -rvf $(OBJ_DIR)
