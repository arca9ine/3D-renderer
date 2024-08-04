
build: main.o hlinalg.o randomutils.o triangles.o
	gcc main.o hlinalg.o randomutils.o triangles.o -o output -lSDL2 -lm -g

run: output
	./output

test: tests.o hlinalg.o randomutils.o triangles.o
	gcc tests.o hlinalg.o randomutils.o triangles.o -o output -lSDL2 -g

tests.o: tests.c
	gcc -c tests.c -g

main.o: main.c
	gcc -c main.c -g

hlinalg.o: ./utils/hlinalg.c ./utils/hlinalg.h
	gcc -c ./utils/hlinalg.c -g

randomutils.o: ./utils/randomutils.c ./utils/randomutils.h
	gcc -c ./utils/randomutils.c -g

triangles.o: ./utils/triangles.c ./utils/triangles.h
	gcc -c ./utils/triangles.c -g

clean:
	rm *.o output