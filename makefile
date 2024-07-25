# Nome do executável
TARGET = base-defense

# Arquivos fonte
SRCS = main.cpp Gerenciamento_Tela.cpp heroi.cpp

# Compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -I/path/to/SFML/include

# Bibliotecas
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Diretório das bibliotecas
LDFLAGS = -L/path/to/SFML/lib

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS) $(CXXFLAGS) $(LDFLAGS) $(LIBS)

# Limpar arquivos gerados
clean:
	rm -f $(TARGET) *.o

.PHONY: all clean