EXAMPLE_BIN=spritesrts

OBJF=./Sources/world.o \
./Sources/app.o \
./Sources/persona.o \
./Sources/program.o \
./Sources/precomp.o

LIBS=clanCore clanDisplay clanSound clanApp clanGL clanSWRender

PACKAGES = $(patsubst %,%-3.0,$(LIBS))
# CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -mthreads
CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -pthread

#EXAMPLE_BIN contains list of example binaries to build

all: $(EXAMPLE_BIN)

$(EXAMPLE_BIN): $(OBJF)
	$(CXX) $(CXXFLAGS) $(OBJF) -o $(EXAMPLE_BIN) `pkg-config --libs $(PACKAGES)` $(EXTRA_LIBS)

clean:
	rm -f $(OBJF) $(EXAMPLE_BIN)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
