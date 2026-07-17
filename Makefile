CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -DPROGRAMA

SRCS = main.cpp huffman.cpp lzw.cpp lz77.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
