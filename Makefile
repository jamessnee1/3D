

main: main.c
	@echo Making main...
	@gcc main.c -o main -lglut -lGLU -lGL -lm

clean:
	rm -f *.o main


