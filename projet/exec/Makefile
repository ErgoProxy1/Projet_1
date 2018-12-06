EXEC= main.out
LIBS = -L../lib -lex
INC = -I../include
CC1 = avr-gcc
CC2=  avr-gcc
FLAGS = -Wl,-Map,$(TRG).map -mmcu=$(MCU) -o 
PRJSRC = $(wildcard *.cpp)
CFILES= $(filter %.c, $(PRJSRC))
CPPFILES= $(filter %.cpp, $(PRJSRC))
OBJDEPS= $(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)
TRG1=$(EXEC)
.PHONY : all install clean
all: $(TRG1)
-include ../Makefile_common





