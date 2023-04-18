CC=g++
CFLAGS=--std=c++11 -Wall -g -DDebug


INCLUDE_PATH = ./include

SRCDIR   = src
OBJDIR   = obj

TARGET = echecs

SRC := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJ := $(SRC:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS)
	cp $(TARGET) $(SRCDIR)/$(TARGET)
	@echo "Linking complete!"


$(OBJ): $(OBJDIR)/%.o:  $(SRCDIR)/%.cc $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

.PHONY: clean cov


projet: 
	./echecs

docs:
	@doxygen

clean:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(OBJDIR)/*.gcda
	rm -rf $(OBJDIR)/*.gcno
	rm -rf $(TARGET)
	rm -rf $(SRCDIR)/$(TARGET)
