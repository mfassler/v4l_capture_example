######
######   What are we building?
######

TARGET = capture


# Objects that must be built in order to link

OBJECTS = main.o
OBJECTS += V4L2_webcam.o


######
######   Binaries and flags
######

CPPFLAGS = -std=c++11
CPPFLAGS += -g
#CPPFLAGS += -O3

LD = g++

#LDFLAGS = -pthread
#LDLIBS += $(shell pkg-config --libs opencv)
LDLIBS += $(shell pkg-config --libs libv4l2)


# Default target:
.PHONY: all
all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)


.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)


