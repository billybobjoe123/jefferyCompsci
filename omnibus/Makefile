CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

omnibus: main.o Atlas.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp Atlas.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Atlas.o: Atlas.cpp Atlas.h Trip.h
	${CXX} $(CXXFLAGS) -c -o $@ $<



clean:
	rm -f omnibus main.o Atlas.o