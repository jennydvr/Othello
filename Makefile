CXX = g++-mp-4.6
CXXFLAGS = -std=gnu++0x -Os

build-exec = $(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean

all: othello
clean: ; rm -f ./*.o ./*.gch othello

%.o: %.cpp ; $(CXX) $(CXXFLAGS) -c $<

othello: main.o alphabetapr.o negascout.o minimax.o; $(build-exec)
	
main.o: main.cpp algorithms.h othello_cut.h
alphabetapr.o: alphabetapr.cpp algorithms.h
negascout.o: negascout.cpp algorithms.h
minimax.o: minimax.cpp algorithms.h
