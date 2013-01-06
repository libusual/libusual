

SHELL = cmd.exe

EXEEXT = .exe
LIBEXT = .lib
OBJEXT = .obj

CC = cl -nologo
CFLAGS = -O2
WFLAGS = -W2 -WX
CPP = $(CC) -E

LDFLAGS =
LIBS = -lws2_32 -ladvapi32

AR = lib
ARFLAGS = -nologo -out:$(call vcFixPath,$@)

LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -Fe$(call vcFixPath,$@)

Printf = printf $(subst %,%%,$(1)) $(2)
MKDIR_P = md

MkDir = if not exist $(1) $(MKDIR_P) $(call vcFixPath,$(1))

vcFixPath = $(subst /,\,$(1))
vcFixLibs = $(patsubst %.a,%.lib,$(patsubst -l%,%.lib,$(1)))
vcFixAll = $(call vcFixPath,$(call vcFixLibs,$(1)))

define AM_LANG_C_COMPILE
	$(E) "CC" $<
	$(Q) $(COMPILE) -c -Fo$(call vcFixPath,$@) $<
endef

define AM_LANG_C_LINK
	$(E) "CCLD" $@
	$(Q) $(LINK) $(call vcFixAll,$^ $(AM_LIBS) $(LIBS)) $(AM_LT_RPATH)
endef

define ar_lib
	$(Q) $(call MkDir,$(dir $@))
	$(E) "LIB" $@
	$(Q) $(AM) $(ARFLAGS) $^
endef

