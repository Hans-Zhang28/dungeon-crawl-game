CXX = g++ -g
CXXFLAGS = -Wall -MMD
EXEC = cc3k
OBJECTS = main.o dragon.o view.o controller.o cell.o textdisplay.o treasure.o potion.o drow.o vampire.o troll.o goblin.o shade.o player.o enemy.o human.o dwarf.o halfling.o elf.o orc.o merchant.o game.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
