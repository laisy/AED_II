CC = gcc -g
LIBS = -lm

NOME = teste

DIRETORIO_FONTE = ./fonte/
DIRETORIO_OBJECT = ./object/
DIRETORIO_EXECUTAVEL = ./executavel/

FONTES := $(shell ls fonte/*.c | cut -d '/' -f2)
OBJETOS = $(FONTES:.c=.o)

OBJETOS_PASTA = $(OBJETOS:%.o=$(DIRETORIO_OBJECT)%.o)
EXECUTAVEL_PASTA = $(DIRETORIO_EXECUTAVEL)$(NOME)


all : rodar

rodar : $(EXECUTAVEL_PASTA)
	$(EXECUTAVEL_PASTA)

debugar : $(EXECUTAVEL_PASTA)
	gdb $(EXECUTAVEL_PASTA)
	#run < fonte/teste1.in

$(EXECUTAVEL_PASTA) : $(OBJETOS_PASTA)
	$(CC) $(OBJETOS_PASTA) -o $(EXECUTAVEL_PASTA) $(LIBS)

$(OBJETOS_PASTA) : $(DIRETORIO_OBJECT)%.o : $(DIRETORIO_FONTE)%.c
	$(CC) -c $< -o $@

clean :
	rm $(EXECUTAVEL_PASTA) $(OBJETOS_PASTA)
