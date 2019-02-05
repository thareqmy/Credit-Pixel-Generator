engine: engine.cpp Point.cpp Color.cpp Frame.cpp Pixel.cpp
	g++ -o engine Point.cpp Color.cpp Frame.cpp engine.cpp Pixel.cpp -lpthread -I.

