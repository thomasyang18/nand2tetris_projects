CFLAGS = -std=c++17 -MMD -MP -Wall -Werror -fsanitize=address,undefined
 
SRCDIR = src
OBJDIR = bin
TARGET = $(OBJDIR)/jack_compiler

src = $(shell find $(SRCDIR) -name '*.cpp')
obj = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(src))
dep = $(obj:.o=.d)
dirs = $(sort $(dir $(obj)))

all:
	make jack_compiler

jack_compiler:
	mkdir -p $(OBJDIR) \
	
	mkdir -p $(dirs) \

	make $(TARGET)

$(TARGET): $(obj)
	g++ $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

-include $(dep) 

.PHONY: clean prints jack_compiler

clean:
	rm -r -f $(OBJDIR) \
	
	rm -f $(obj) $(TARGET) $(dep)

prints:
	echo '$(src)'