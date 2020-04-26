Libxml2_INCLUDE_PATH=libxml2-2.9.10/include
Libxml2_LIBRARY_PATH=libxml2-2.9.10/.libs
CXX = g++
CXXFLAGS = -Idl -DDOC_PATH=\"/home/tommy/\" -DBIN_PATH=\"/usr/local/bin\" -L$(Libxml2_LIBRARY_PATH) -I$(Libxml2_INCLUDE_PATH) 

a.out: ./parser.cpp ./parser.h ./SQ-Fuzz.cpp 
	g++ -O0 -Idl -DDOC_PATH=\"/home/tommy/\" -DBIN_PATH=\"/usr/local/bin\"  -Llibxml2-2.9.10/.libs -Ilibxml2-2.9.10/include ./SQ-Fuzz.cpp ./parser.cpp ./parser.h  -lxml2 -ldl

debug: ./parser.cpp ./parser.h ./SQ-Fuzz.cpp 
	g++ -g -fstack-protector-all -Idl -DDOC_PATH=\"/home/tommy/\" -DBIN_PATH=\"/usr/local/bin\"  -Llibxml2-2.9.10/.libs -Ilibxml2-2.9.10/include ./SQ-Fuzz.cpp ./parser.cpp ./parser.h  -lxml2 -ldl



clean:
	rm -f a.out
