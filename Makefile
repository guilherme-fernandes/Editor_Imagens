all:
	gcc Projeto_Final.c main.c -o Projeto_Final -g -W

run:
	./Projeto_Final

clean:
	rm ./Projeto_Final