CC = c++
CFLAGS = -Wall -Werror -Wextra -O2 -g
LDFLAGS =

APPNAME := program

SRCS := $(wildcard *.cpp)
OBJDIR := .objs
DEPDIR := .deps

OBJS := $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS := $(SRCS:%.cpp=$(DEPDIR)/%.d)

.PHONY: all clean run
all: $(APPNAME)

$(APPNAME): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# create directories when needed
$(OBJDIR) $(DEPDIR):
	@mkdir -p $@

# dependency flags — $* is the stem (filename without dir/suffix)
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d

# compile rule: produce .objs/<file>.o from src/<file>.c
$(OBJDIR)/%.o: %.cpp | $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# include generated dependency files if present
-include $(DEPS)

clean:
	@rm -rf $(APPNAME) $(OBJDIR) $(DEPDIR)

run: all
	@clear
	@./$(APPNAME)