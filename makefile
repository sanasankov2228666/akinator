FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE 


INCLUDES = -I./headers

FILES = akinator.cpp interface.cpp read_tree.cpp dot_generator.cpp stack1.cpp

OUTPUT = program.exe

all: akin

akin: $(FILES)
	@echo "=== Compiling Akinator ==="
	g++ $(FLAGS) $(FILES) $(INCLUDES) -o $(OUTPUT)
	@echo "=== Compilation complete ==="

run-akin: akin
	@echo "=== Running Akinator ==="
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)

help:
	@echo "Available commands:"
	@echo "  make all       - compile Akinator (default)"
	@echo "  make akin      - compile Akinator"
	@echo "  make run-akin  - compile and run Akinator"
	@echo "  make clean     - remove compiled program"
	@echo "  make help      - show this help"