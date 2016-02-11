CXX = clang++

# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11
# SDL2 and libcurl are dependencies
LDFLAGS = -lsdl2 -lcurl
EXE = ps3host

all: $(EXE)

$(EXE): main.o ps3controller.o callbacks.o
	$(CXX) $(LDFLAGS) main.o ps3controller.o callbacks.o -o $@


main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

ps3controller.o: ps3controller.cpp
	$(CXX) $(CXXFLAGS) $< -o $@


callbacks.o: callbacks.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)