# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

# Include flags
IFLAGS = -I/usr/local/include/opencv4

# Linker flags
LFLAGS = -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

# Source files
SRCS = main.cpp camera.cpp

# Output executable
TARGET = camera

# Default rule
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(IFLAGS) $(LFLAGS)

# Clean rule
clean:
	rm -f $(TARGET) *.o

# Phony targets
.PHONY: all clean