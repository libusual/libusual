
AM_FEATURES = msvc

abs_top_srcdir = $(dir $(filter %build.mk, $(MAKEFILE_LIST)))

include $(abs_top_srcdir)/mk/antimake.mk

