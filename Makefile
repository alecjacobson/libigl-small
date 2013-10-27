.PHONY: all
all: lib extras examples

GG=g++
#GG=clang++
#GG=/usr/bin/g++     17s
#GG=/usr/bin/clang++ 14s
#GG=g++-mp-4.3       15.5s
#GG=g++-mp-4.7       19.9s

# Shared flags etc.
include Makefile.conf
$(info Hello, $(IGL_USERNAME)!)

# optimized default settings
all: LFLAGS +=
OPTFLAGS+=-O3 -DNDEBUG $(OPENMP)
#debug: OPTFLAGS= -g -Wall -Werror
debug: OPTFLAGS= -g -Wall
debug: DEBUG=debug
CFLAGS += $(OPTFLAGS)
#CFLAGS += -DIGL_NO_OPENGL -DIGL_NO_ANTTWEAKBAR

EXTRA_DIRS=
ifeq ($(IGL_WITH_TETGEN),1)
	# append tetgen extra dir
	EXTRA_DIRS+=include/igl/tetgen
endif
ifeq ($(IGL_WITH_MATLAB),1)
	EXTRA_DIRS+=include/igl/matlab
endif
ifeq ($(IGL_WITH_BBW),1)
	EXTRA_DIRS+=include/igl/BBW
endif
ifeq ($(IGL_WITH_MOSEK),1)
	EXTRA_DIRS+=include/igl/mosek
endif
ifeq ($(IGL_WITH_PNG),1)
	EXTRA_DIRS+=include/igl/png
endif
ifeq ($(IGL_WITH_XML),1)
	EXTRA_DIRS+=include/igl/xml
endif
ifeq ($(IGL_WITH_EMBREE),1)
	EXTRA_DIRS+=include/igl/embree
endif
ifeq ($(IGL_WITH_BOOST),1)
	EXTRA_DIRS+=include/igl/boost
endif

.PHONY: examples
.PHONY: extras
debug: lib extras
lib: lib/libigl.a
examples: lib extras
	make -C examples
extras:
	for p in  $(EXTRA_DIRS); \
	do \
	echo "cd $$p" ; \
	$(MAKE) -C $$p $(DEBUG); \
	done


#############################################################################
# SOURCE 
#############################################################################
CPP_FILES=$(wildcard include/igl/*.cpp)
OBJ_FILES=$(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

# include igl headers
INC+=-Iinclude/

#############################################################################
# DEPENDENCIES
#############################################################################
INC+=$(OPENGL_INC)

# Eigen dependency
ifndef EIGEN3_INC
	EIGEN3_INC=-I$(DEFAULT_PREFIX)/include/eigen3 -I$(DEFAULT_PREFIX)/include/eigen3/unsupported
endif
INC+=$(EIGEN3_INC)

# AntTweakBar dependency
#ANTTWEAKBAR_INC=-I$(DEFAULT_PREFIX)/include
ANTTWEAKBAR_INC=-Iexternal/AntTweakBar/include
INC+=$(ANTTWEAKBAR_INC)

## OpenGL dependency
#LIB+=-framework OpenGL
#LIB+=-framework GLUT
#LIB+=-framework AppKit

obj: 
	mkdir -p obj

lib/libigl.a: $(OBJ_FILES)
	mkdir -p lib
	rm -f $@
	ar cqs $@ $(OBJ_FILES)

obj/%.o: include/igl/%.cpp include/igl/%.h
	$(GG) $(CFLAGS) $(AFLAGS) -c -o $@ $< $(INC)

clean:
	rm -f obj/*.o
	rm -f lib/libigl.a
	make -C examples clean
	for p in  $(EXTRA_DIRS); \
	do \
	echo "cd $$p" ; \
	$(MAKE) -C $$p clean; \
	done
