uno: Effect.o Colors.o card.o CardStack.o PlayerCards.o player.o PlayedCards.o turn.o game.o main.o
	g++ -o uno main.o game.o turn.o card.o CardStack.o Colors.o Effect.o player.o PlayerCards.o PlayedCards.o

Effect.o: Effect.cpp
	g++ -c Effect.cpp

Colors.o: Colors.cpp
	g++ -c Colors.cpp

card.o: card.cpp card.hpp 
	g++ -c card.cpp 

CardStack.o: CardStack.cpp CardStack.hpp
	g++ -c CardStack.cpp 

PlayerCards.o: PlayerCards.cpp PlayerCards.hpp
	g++ -c PlayerCards.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

PlayedCards.o: PlayedCards.cpp PlayedCards.hpp
	g++ -c PlayedCards.cpp

turn.o: turn.cpp turn.hpp
	g++ -c turn.cpp

game.o: game.cpp game.hpp
	g++ -c game.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o uno




