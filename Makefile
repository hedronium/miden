# bin/test: test/tokenizer.cpp bin/main
# 	g++ test/tokenizer.cpp -o bin/test --std=c++11

# bin/main: src/tokenizer.cpp src/main.cpp src/maybe.cpp
# 	g++ src/maybe.cpp src/tokenizer.cpp src/main.cpp -o bin/main --std=c++11


bin/main: src/main.cpp bin/parser.o bin/tokenizer.o bin/maybe.o bin/test/tokenizer
	g++ bin/parser.o bin/tokenizer.o bin/maybe.o src/main.cpp -o bin/main --std=c++11

bin/test/tokenizer: test/tokenizer.cpp bin/tokenizer.o bin/maybe.o
	g++ test/tokenizer.cpp bin/tokenizer.o bin/maybe.o -o bin/test/tokenizer --std=c++11

bin/maybe.o: src/maybe.cpp
	g++ -c src/maybe.cpp -o bin/maybe.o --std=c++11

bin/tokenizer.o: src/parser.cpp
	g++ -c src/tokenizer.cpp -o bin/tokenizer.o --std=c++11

bin/parser.o: src/parser.cpp
	g++ -c src/parser.cpp -o bin/parser.o --std=c++11