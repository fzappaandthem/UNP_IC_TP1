TARGET=Ej5
LIBS=-pthread
OBJECTS=$(wildcard *.c)

default: $(TARGET)
all:default

$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)