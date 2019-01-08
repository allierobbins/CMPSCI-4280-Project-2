all: scanner.o parser.o testTree.o main.o
	g++ -o frontEnd -g scanner.o parser.o testTree.o main.o 

scanner.o: scanner.cpp
	g++ -c -g scanner.cpp

parser.o: parser.cpp
	g++ -c -g parser.cpp

testTree.o: testTree.cpp
	g++ -c -g testTree.cpp

main.o: main.cpp
	g++ -c -g main.cpp

clean: remove

remove:
	rm *.o frontEnd

clear:
	clear

success:
	$(info SUCCESS)

readme:
	cat README.txt
