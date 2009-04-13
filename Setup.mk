
#USUAL_DIR = .
#USUAL_MODULES = fileutil logging lookup3 bitswap misc
#USUAL_OBJDIR

USUAL_HDRS = $(addprefix $(USUAL_DIR)/usual/, $(addsuffix .h, $(USUAL_MODULES)))
USUAL_CPPFLAGS = -I$(USUAL_DIR)

# target: local objs
USUAL_OBJDIR ?= .
USUAL_SRCS = $(wildcard $(addprefix $(USUAL_DIR)/usual/, $(addsuffix .c, $(USUAL_MODULES))))
USUAL_OBJS = $(addprefix $(USUAL_OBJDIR)/, $(notdir $(USUAL_SRCS:.c=.o)))
# needs following rule:
#$(USUAL_OBJDIR)/%.o: $(USUAL_DIR)/usual/%.c $(USUAL_HDRS)
#	$(CC) -c -o $@ $< $(DEFS) $(CPPFLAGS) $(CFLAGS)

# target: libusual.a
USUAL_LIBS = -lusual
USUAL_LDFLAGS = -L$(USUAL_DIR)

