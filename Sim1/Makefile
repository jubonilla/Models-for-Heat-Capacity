Comp: InternalEnergy.cpp CV.cpp
	g++ InternalEnergy.cpp -o IE.x -lgsl -lgslcblas
	./IE.x
	rm IE.x
	g++ CV.cpp -o CV.x -lgsl -lgslcblas
	./CV.x
	rm CV.x
	gnuplot Ugraph.gplot
	gnuplot CVgraph.gplot
