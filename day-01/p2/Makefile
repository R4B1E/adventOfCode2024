CC = cc
CFLAGS = -Wall -Werror -Wextra -O2 -g
LDFLAGS =

APPNAME := program

SRCS := $(wildcard *.c)
OBJDIR := .objs
DEPDIR := .deps

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(SRCS:%.c=$(DEPDIR)/%.d)

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
$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# include generated dependency files if present
-include $(DEPS)

clean:
	@rm -rf $(APPNAME) $(OBJDIR) $(DEPDIR)

run: all
	@clear
	@./$(APPNAME)