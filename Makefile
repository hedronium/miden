bin/main: src/tokenizer.cpp src/main.cpp
	g++ src/tokenizer.cpp src/main.cpp -o bin/main --std=c++11