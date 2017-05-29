LINK_TARGET = val.exe
VPATH = ./src/

all : val.exe

val.exe: SB.o AS.o AU.o AL.o nominal.o
	g++ -std=c++1y  ./src/main.cpp ./src/nominal.o ./src/AS.o ./src/AU.o ./src/AL.o ./src/SB.o `root-config --cflags --glibs` -lTreePlayer -o val.exe -O2 -march=native

nominal.o: nominal.C
	g++ -std=c++1y -c ./src/nominal.C -o ./src/nominal.o `root-config --cflags --glibs`

SB.o: SB.cc
	g++ -std=c++1y -c ./src/SB.cc -o ./src/SB.o `root-config --cflags --glibs` -O2 -march=native

AS.o: AtlasStyle.C
	g++ -std=c++1y -c ./src/AtlasStyle.C -o ./src/AS.o `root-config --cflags --glibs`

AU.o: AtlasUtils.C
	g++ -std=c++1y -c ./src/AtlasUtils.C -o ./src/AU.o `root-config --cflags --glibs`

AL.o: AtlasLabels.C
	g++ -std=c++1y -c ./src/AtlasLabels.C -o ./src/AL.o `root-config --cflags --glibs`

clean:
	rm ./src/main.o ./src/DataMC.o ./src/SB.o ./src/AS.o ./src/AU.o ./src/AL.o ./src/nominal.o val.exe
