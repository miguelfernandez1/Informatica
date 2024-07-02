folders = obj bin
CXX = g++
CXXFLAGS = -I./include -g -O2 -std=c++17

all: make_folders bin/main

make_folders:
	mkdir -p ${folders}

bin/main: obj/main.o obj/BL.o obj/Evolutivos.o obj/funciones.o obj/Geneticos.o obj/KNN.o obj/Memeticos.o obj/MVO.o obj/Relief.o obj/timer.o
	$(CXX) -o bin/p3 obj/main.o obj/BL.o obj/Evolutivos.o obj/funciones.o obj/Geneticos.o obj/KNN.o obj/Memeticos.o obj/MVO.o obj/Relief.o obj/timer.o

obj/main.o: src/main.cpp include/BL.h include/Evolutivos.h include/funciones.h include/Geneticos.h include/KNN.h include/Memeticos.h include/MVO.h include/Relief.h include/timer.h
	$(CXX) $(CXXFLAGS) -o obj/main.o -c src/main.cpp

obj/BL.o: src/BL.cpp include/BL.h
	$(CXX) $(CXXFLAGS) -o obj/BL.o -c src/BL.cpp

obj/Evolutivos.o: src/Evolutivos.cpp include/Evolutivos.h
	$(CXX) $(CXXFLAGS) -o obj/Evolutivos.o -c src/Evolutivos.cpp

obj/funciones.o: src/funciones.cpp include/funciones.h
	$(CXX) $(CXXFLAGS) -o obj/funciones.o -c src/funciones.cpp

obj/Geneticos.o: src/Geneticos.cpp include/Geneticos.h
	$(CXX) $(CXXFLAGS) -o obj/Geneticos.o -c src/Geneticos.cpp

obj/KNN.o: src/KNN.cpp include/KNN.h
	$(CXX) $(CXXFLAGS) -o obj/KNN.o -c src/KNN.cpp

obj/Memeticos.o: src/Memeticos.cpp include/Memeticos.h
	$(CXX) $(CXXFLAGS) -o obj/Memeticos.o -c src/Memeticos.cpp

obj/MVO.o: src/MVO.cpp include/MVO.h
	$(CXX) $(CXXFLAGS) -o obj/MVO.o -c src/MVO.cpp

obj/Relief.o: src/Relief.cpp include/Relief.h
	$(CXX) $(CXXFLAGS) -o obj/Relief.o -c src/Relief.cpp

obj/timer.o: src/timer.cpp include/timer.h
	$(CXX) $(CXXFLAGS) -o obj/timer.o -c src/timer.cpp

clean:
	rm -r -f obj/ bin/