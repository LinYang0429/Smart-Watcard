TYPE:=MC
OPT:=-O2

CXX = u++					# compiler
CXXFLAGS = -g -Wall ${OPT} -multi -MMD -std=c++11 -DIMPLTYPE_${TYPE} # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS2 = main.o config.o vendingmachine.o bank.o watcard.o bottlingplant.o nameserver.o \
watcardoffice.o student.o parent.o groupoff.o truck.o printer.o# list of object files for question 1 prefixed with "q2"
EXEC2 = soda

OBJECTS = ${OBJECTS2}				# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC2}				# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@

ImplType :
	echo "IMPLTYPE=${TYPE}" > ImplType
	sleep 1

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplType
