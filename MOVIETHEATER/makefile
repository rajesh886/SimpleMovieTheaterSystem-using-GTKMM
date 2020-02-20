CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

ex: movie_main.o movie.o
	$(CXX) $(CXXFLAGS) -o movie movie_main.o movie.o $(GTKFLAGS)
movie_main.o: movie_main.cpp movie.h
	$(CXX) $(CXXFLAGS) -c movie_main.cpp $(GTKFLAGS)
movie.o: movie.h movie.cpp
	$(CXX) $(CXXFLAGS) -c movie.cpp $(GTKFLAGS)
