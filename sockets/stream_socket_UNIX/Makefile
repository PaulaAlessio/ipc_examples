# project name 
TARGET_SV := us_xfr_sv
TARGET_CL := us_xfr_cl


#---------------------------------------------------------------------
# executables 
#---------------------------------------------------------------------
CC	:= gcc 
MD	:= mkdir 
LINKER  := gcc -o
RM      := rm -f

# compiling flags
CFLAGS   := -Wall -O3 -march=native -std=c11  -Iinclude/  
LFLAGS   := -Wall   


# change these to set the proper directories where each files should be
SRCDIR   := src
INCDIR   := include
OBJDIR   := obj
BINDIR   := bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJ_SV := obj/error_functions.o  obj/get_num.o  obj/us_xfr_sv.o
OBJ_CL := obj/error_functions.o  obj/get_num.o  obj/us_xfr_cl.o


#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------

all: mkdirs $(BINDIR)/$(TARGET_SV)  $(BINDIR)/$(TARGET_CL) 

mkdirs: 
	$(MD) -p $(OBJDIR)
	$(MD) -p $(BINDIR)

$(BINDIR)/$(TARGET_SV): $(OBJECTS)
	@ echo "Linking..."
	$(LINKER) $@  $(LFLAGS) $(OBJ_SV)
	@echo "Linking complete!"

$(BINDIR)/$(TARGET_CL): $(OBJECTS)
	@ echo "Linking..."
	$(LINKER) $@  $(LFLAGS) $(OBJ_CL)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compiling ..."
	$(CC) $(CFLAGS)  -c $< -o $@
	@echo "Compiled "$<" successfully!"


.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	$(RM) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
 
