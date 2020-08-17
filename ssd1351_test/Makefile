all: spi

spi: main.o Adafruit_SSD1351.o
	g++ main.o Adafruit_SSD1351.o -lbcm2835 -lformat -o spi

main.o: main.cpp Adafruit_SSD1351.cpp
	g++ -c main.cpp Adafruit_SSD1351.cpp


clean:
	rm -rf *.o spi
