CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -MMD -Werror=vla
EXEC = watopoly
OBJECTS = main.o viewboard.o dice.o game.o player.o controller.o subject.o observer.o board.o square.o ownable.o academic.o collectosap.o coopfee.o goosenesting.o gotims.o gym.o needleshall.o residence.o slc.o timsline.o tuition.o invalidtrade.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean


