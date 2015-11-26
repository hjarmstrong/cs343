CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD -O2 
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS2 = q3main.o q3printer.o q3voter.o q3tallyVotes.o # list of object files for question 1 prefixed with "q2"
EXEC2 = soda

OBJECTS = ${OBJECTS2}				# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC2}				# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables


-include ImplType

${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC01} ${EXECS} 
