bin/main: bin/maybe.o src/main.cpp bin/parser.o bin/tokenizer.o bin/test/tokenizer
	g++ bin/parser.o bin/tokenizer.o bin/maybe.o src/main.cpp -o bin/main --std=c++11

bin/test/tokenizer: bin/maybe.o bin/tokenizer.o test/tokenizer.cpp bin/test/parser
	g++ bin/maybe.o bin/tokenizer.o test/tokenizer.cpp -o bin/test/tokenizer --std=c++11

bin/test/parser: bin/maybe.o bin/parser.o test/parser.cpp
	g++ bin/maybe.o bin/parser.o test/parser.cpp -o bin/test/parser --std=c++11

bin/maybe.o: src/maybe.cpp
	g++ -c src/maybe.cpp -o bin/maybe.o --std=c++11

bin/tokenizer.o: src/tokenizer.cpp
	g++ -c src/tokenizer.cpp -o bin/tokenizer.o --std=c++11

bin/parser.o: src/parser.cpp
	g++ -c src/parser.cpp -o bin/parser.o --std=c++11