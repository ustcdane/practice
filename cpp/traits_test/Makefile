# Makefile 
CXX		:= g++
LD		:= g++
AR		:= ar crus
RM		:= rm -rf

SRCROOT	:= .
SRCDIRS	:= $(SRCROOT)
INCS	:= $(addprefix -I, $(SRCDIRS))
VPATH   := $(SRCDIRS)
SRCS	:= $(foreach DIR, $(VPATH), $(notdir $(wildcard $(DIR)/*.cpp))) \
		   $(wildcard *.cpp)

CPPFLAGS:= $(INCS) -w

#CXXFLAGS:= -std=c++11 -g -O0
#CXXFLAGS:= -std=c++11 -g -O0 -fPIC -shared
CXXFLAGS:= -std=c++11 -g -O0
LDFLAGS	:= $(CXXFLAGS)
LIBS	:=
BIN		:= traits_test.exe
OBJS	:= $(SRCS:.cpp=.o)

all : $(BIN)

clean :
	$(RM) $(BIN) $(OBJS)

# bin 
$(BIN) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

