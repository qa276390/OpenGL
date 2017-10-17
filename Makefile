.PHONY:clean

Poly: hw1.cpp Poly.h
	g++ -o Poly -std=c++11 hw1.cpp Poly.h

clean:
	rm -f Poly
