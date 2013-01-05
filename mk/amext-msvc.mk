
Printf = printf $(subst %,%%,$(1)) $(2)

SHELL = cmd.exe

EXEEXT = .exe
LIBEXT = .lib
OBJEXT = .obj

CC = cl -nologo
CFLAGS = -O2
WFLAGS =
WFLAGS = -W2 -WX
CPP = $(CC) -E

AR = lib
ARFLAGS = -nologo -out:$(call vcFixPath,$@)

LDFLAGS = 

MKDIR_P = mkdir

MkDir = $(if $(wildcard $(1)),,md $(call vcFixPath,$(1)))

LIBS = -lws2_32 -ladvapi32

vcFixPath = $(subst /,\,$(1))
vcFixLibs = $(patsubst %.a,%.lib,$(patsubst -l%,%.lib,$(1)))
vcFixAll = $(call vcFixPath,$(call vcFixLibs,$(1)))

AM_LANG_C_COMPILE = $(COMPILE) -c -Fo$(call vcFixPath,$@) $<

LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -Fe$(call vcFixPath,$@)

ar_lib = lib -nologo -out:$(call vcFixAll,$@) $^
AM_LANG_C_LINK = $(LINK) $(call vcFixAll,$^ $(AM_LIBS) $(LIBS)) $(AM_LT_RPATH)


