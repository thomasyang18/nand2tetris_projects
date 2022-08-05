CFLAGS = -MMD -MP -Wall -Werror -fsanitize=address,undefined
 
SRCDIR = src
OBJDIR = bin
TARGET = $(OBJDIR)/vm_compiler

src = $(wildcard $(SRCDIR)/*.cpp)
obj = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(src))
dep = $(obj:.o=.d)

all:
	make vm_compiler

vm_compiler:
	mkdir -p $(OBJDIR) \
	
	make $(TARGET)

$(TARGET): $(obj)
	g++ $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

-include $(dep) 

.PHONY: clean prints vm_compiler

clean:
	rm -r -f $(OBJDIR) \
	
	rm -f $(obj) $(TARGET) $(dep)

prints:
	echo '$(OBJDIR)'
	echo '$(src) $(obj)'
