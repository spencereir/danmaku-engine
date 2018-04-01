CC=g++
CXXFLAGS=-Wall -Wextra -std=c++14 -g -Wno-switch
EXTRA=-lsfml-graphics -lsfml-window -lsfml-system
OBJS=$(patsubst %.cc,%.o,$(wildcard *.cc)) $(patsubst %.cc,%.o,$(wildcard */*.cc))
EXEC=a
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(EXTRA)

%.o: %.cc
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	-rm -f $(OBJS) $(EXEC)
