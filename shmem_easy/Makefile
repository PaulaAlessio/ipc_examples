#--------------------------------------------------------------------
# Variable definitions
#--------------------------------------------------------------------
CC 	:= gcc
CCFLAGS := -Wall -Wextra -O2
MD 	:= mkdir
BINDIR 	:= bin


all:
	$(MD) -p $(BINDIR)
	$(CC) $(CCFLAGS) client.c -I. -o $(BINDIR)/client 
	$(CC) $(CCFLAGS) device.c -I. -o $(BINDIR)/device 
	$(CC) $(CCFLAGS) run_device.c -lm -I. -o $(BINDIR)/run_device
clean:
	rm $(BINDIR)/*
