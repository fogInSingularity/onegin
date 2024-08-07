CC = g++
EXE = onegin
BUILD_DIR = build
SOURCES = $(wildcard *.cpp)
OBJECTS = $(foreach src,$(SOURCES),./$(BUILD_DIR)/$(src:.cpp=.o))
DEPS = $(wildcard $(BUILD_DIR)/*.d)
OPT_LEVEL = -O0
DEFINES = NOTHING
FLAGS = -MMD -MP -ggdb3 -std=c++17 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
		-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual \
		-Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy \
		-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
		-Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor \
		-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
		-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
		-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn \
		-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override \
		-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code \
		-Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix \
		-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast \
		-Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation \
		-fstack-protector -fstrict-overflow -flto-odr-type-merging \
		-fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 \
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,$\
		float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,$\
		object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,$\
		undefined,unreachable,vla-bound,vptr

all: $(EXE)

$(EXE): $(OBJECTS)
	@$(CC) $(OBJECTS) $(FLAGS) -o $(EXE)

$(BUILD_DIR)/%.o: %.cpp
	@$(CC) $^ -c $(OPT_LEVEL) $(FLAGS) -D $(DEFINES) -o $@

clean:
	@rm $(BUILD_DIR)/*

doxygen:
	@doxygen Doxyfile

release:
	@g++ $(wildcard *.cpp) -o onegin -O3

# -include $(DEPS)

