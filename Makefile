engine: engine.cpp Point.cpp Color.cpp Frame.cpp Pixel.cpp Line.cpp Plane2D.cpp
	g++ -o engine Point.cpp Color.cpp Frame.cpp engine.cpp Pixel.cpp Line.cpp Plane2D.cpp -lpthread -I.

