banqueiro: banqueiro.c sistema.c sistema.h processos.c processos.h
	gcc -o banqueiro banqueiro.c sistema.c processos.c -pthread 