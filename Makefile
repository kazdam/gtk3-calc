calc: calc.cpp
	g++ -o calc calc.cpp `pkg-config -libs --cflags gtk+-3.0` -Wint-to-pointer-cast
