engine: engine.cpp Point.cpp Color.cpp Frame.cpp
	g++ -o engine Point.cpp Color.cpp Frame.cpp engine.cpp -lpthread -I.

