#Adicionar uma descrição



# --------------------  LICENSA GLP ---------------------------------#


#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  



#Compilador
CC = g++

#Linker
LD = g++

#Flags para compilação
CFLAGS = -Wall

#Flags para o linker
LFLAGS = -Wall 

#Bibliotecas usadas
LIB = -larmadillo -lstdc++ 

#Objetos
OBJ = linearSolver.o

#Arquivo principal
MAIN = simul-dbg

#Arquivos .h
DEPS = plu.h

ALL = $(MAIN)

# Regra Implicita
%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(ALL)

simul-dbg : $(OBJ)
	$(LD) $(LFLAGS) -o $@ $(OBJ) $(LIB)
