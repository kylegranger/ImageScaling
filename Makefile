

CXX           = g++
CXXFLAGS += -Wall -Wextra -Wformat -Wno-multichar -std=c++2a

OBJECTS = \
	obj/demo.o \
	obj/filter16.o \
	obj/linear16.o

release: release/demo

release/demo: $(OBJECTS)
	[-d release] || mkdir -p release
	$(CXX) -o release/demo  -static-libstdc++ $(OBJECTS) -v

obj/demo.o: demo.cpp
	[-d obj] || mkdir -p obj
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/demo.o demo.cpp

obj/filter16.o: filter16.cpp filter16.h
	[-d obj] || mkdir -p obj
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/filter16.o filter16.cpp

obj/linear16.o: linear16.cpp linear16.h
	[-d obj] || mkdir -p obj
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/linear16.o linear16.cpp


clean:
	rm -f obj/*
	rm -f release/*
	rm -rf obj
	rm -rf release
