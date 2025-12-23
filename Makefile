CXX = g++

CXXFLAGS = -std=c++11 -Wall -g -Iinclude -lm

SRCDIR = src
OBJDIR = obj
BINDIR = bin

EXECUTABLE = $(BINDIR)/tp2.out

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)

	@mkdir -p $(BINDIR)

	$(CXX) $(CXXFLAGS) -o $@ $^


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)