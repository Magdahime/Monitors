CFLAGS:= -pthread -Wall  -Iinclude -Isrc

INCLUDE:= include
SRC := src
BUILD := build
BIN := bin

$(BIN)/Monitor: $(BUILD)/queue.o $(BUILD)/main.o 
	g++ $(CFLAGS) $(BUILD)/queue.o $(BUILD)/main.o -o $(BIN)/Monitor 

$(BUILD)/main.o: $(SRC)/main.cpp $(INCLUDE)/monitor.h $(INCLUDE)/queue.h $(INCLUDE)/my_monitor.h
	g++ $(CFLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/queue.o: $(SRC)/queue.c $(INCLUDE)/queue.h 
	g++ $(CFLAGS) -c $(SRC)/queue.c -o $(BUILD)/queue.o

clean:
	rm -f $(BUILD)/*.o
	rm -f $(BIN)/Monitor



