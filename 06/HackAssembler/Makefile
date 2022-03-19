CFLAGS = -MMD -Wall -Werror -std=c++14
CC = g++

SRCDIR = src
OBJDIR = bin
TARGET = Assembler

src = $(wildcard $(SRCDIR)/*.cpp)
obj = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(src))
dep = $(obj:.o=.d)

all:
	mkdir -p bin \
	
	make $(TARGET)

$(TARGET): $(obj)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

-include $(dep) 

.PHONY: clean prints
clean:
	rm -r -f bin \
	
	rm -f $(obj) $(TARGET) $(dep)

prints:
	echo '$(OBJDIR)'
	echo '$(src) $(obj)'

