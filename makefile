.phony: clean

EXECS=ejemploProceso crearProceso directCalling manualCalling leerFichero

all: $(EXECS)

ejemploProceso: ejemploProceso.o
	g++ -o $@ $<

ejemploProceso.o: ejemploProceso.cpp

crearProceso: crearProceso.o
	g++ -o $@ $<

crearProceso.o: crearProceso.cpp
	g++ -Wwrite-strings -c $<

manualCalling: manualCalling.o mifuncion.o
	g++ -o $@ $^

directCalling: directCalling.o mifuncion.o
	g++ -o $@ $^

manualCalling.o: manualCalling.cpp

directCalling.o: directCalling.cpp

mifuncion.o: mifuncion.cpp

leerFichero: leerFichero.o
	g++ -o $@ $<

leerFichero.o: leerFichero.cpp 

clean:
	rm -f *.o *.cpp~ makefile~
	rm -f $(EXECS)
