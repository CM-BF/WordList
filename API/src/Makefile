CC=g++ -std=c++11 -shared -fPIC
GCC = g++ -std=c++11


test_main:test_main.o libwordlist.so main
	$(GCC) -o $@ $< -I./ -L./ -lwordlist -lgtest -lpthread
main:main.o
	$(GCC) -o $@ $< -I./ -L./ -lwordlist
main.o:cmd.cpp
	$(GCC) -c $^ -o $@
wordlist.o:wordlist.cpp wordlist.h
	$(GCC) -c $< -o $@ 
libwordlist.so:wordlist.o
	$(CC) -o $@ wordlist.cpp 
test_main.o:test_main.cpp
	$(GCC) -c $^ -o $@ 
.PHONY: clean
clean:
	-rm -f *.o
