
# toplevel dir of libusual - always required
#req: USUAL_DIR = .
USUAL_CPPFLAGS = -I$(USUAL_DIR)

#
# target: local objs
#

# req: USUAL_LOCAL_SRCS or USUAL_MODULES
# opt: USUAL_OBJDIR

# needs following rule:
#$(USUAL_OBJDIR)/%.o: $(USUAL_DIR)/usual/%.c $(USUAL_HDRS)
#	$(CC) -c -o $@ $< $(DEFS) $(CPPFLAGS) $(CFLAGS)

USUAL_OBJDIR ?= .
USUAL_HDRS = $(addprefix $(USUAL_DIR)/usual/, $(addsuffix .h, $(USUAL_MODULES)))
USUAL_SRCS = $(wildcard $(addprefix $(USUAL_DIR)/usual/, $(addsuffix .c, $(USUAL_MODULES))))
USUAL_OBJS = $(addprefix $(USUAL_OBJDIR)/, $(notdir $(USUAL_SRCS:.c=.o)))

# find_modules is slow, so do immediate assignment
#USUAL_MODULES ?= $(shell $(USUAL_DIR)/find_modules.sh $(USUAL_DIR) $(USUAL_LOCAL_SRCS))
ifeq ($(origin USUAL_MODULES),undefined)
USUAL_MODULES := $(shell $(USUAL_DIR)/find_modules.sh $(USUAL_DIR) $(wildcard $(USUAL_LOCAL_SRCS)))
endif

#
# target: libusual.a
#

USUAL_LIBS = -lusual
USUAL_LDFLAGS = -L$(USUAL_DIR)

