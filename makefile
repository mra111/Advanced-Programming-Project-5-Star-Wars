CC = g++ -std=c++11
FLAGS = -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
COMPILE_FLAGS = $(FLAGS) -c 

starwars.out: main.o game.o round.o ship.o shot.o enemy1.o enemy2.o hostage.o
	$(CC) main.o game.o round.o ship.o shot.o enemy1.o enemy2.o hostage.o rsdl.cpp $(FLAGS) -o starwars.out

main.o: main.cpp game.h round.h
	$(CC) $(COMPILE_FLAGS) main.cpp

game.o: game.h game.cpp round.h ship.h enemy1.h enemy2.h shot.h hostage.h
	$(CC) $(COMPILE_FLAGS) game.cpp

round.o: round.h round.cpp ship.h enemy1.h enemy2.h shot.h hostage.h
	$(CC) $(COMPILE_FLAGS) round.cpp

shot.o: shot.h shot.cpp ship.h
	$(CC) $(COMPILE_FLAGS) shot.cpp

ship.o: ship.h ship.cpp shot.h
	$(CC) $(COMPILE_FLAGS) ship.cpp

enemy1.o: enemy1.h enemy1.cpp shot.h
	$(CC) $(COMPILE_FLAGS) enemy1.cpp

enemy2.o: enemy2.h enemy2.cpp enemy1.h shot.h
	$(CC) $(COMPILE_FLAGS) enemy2.cpp

hostage.o: hostage.h hostage.cpp
	$(CC) $(COMPILE_FLAGS) hostage.cpp


.PHONY: clean

clean:
	rm *.o