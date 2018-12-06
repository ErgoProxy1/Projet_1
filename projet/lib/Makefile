LIB= libex.a
CC1 = avr-ar
CC2 = avr-gcc
INC= -I ../include
CXXFLAGS=-I. -MMD $(INC) -g -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall              
FLAGS = -crs
PRJSRC = $(wildcard *.cpp)
CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)
TRG1=$(LIB)
TRG2 = noExNeed
.PHONY : all clean
all : $(TRG1) $(TRG2)
include ../Makefile_common
noExNeed:
	rm -rf *.out
	rm -rf *.hex
	rm -rf *.d




