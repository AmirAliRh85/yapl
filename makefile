TARGET = yapl
FILE = ./examples/hello_world.yapl

SRCS = ${wildcard ./src/*.cpp}


run : compile
	./${TARGET}.exe ${FILE}

compile :
	g++ ${TARGET}.cpp -o ${TARGET}.exe ${SRCS}