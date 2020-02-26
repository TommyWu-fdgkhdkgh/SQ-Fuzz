a.out: 
	g++ -Idl -DDOC_PATH=\"/home/tommy/\" -DBIN_PATH=\"/usr/local/bin\"   ./SQ-Fuzz.cpp  -ldl

clean:
	rm -f a.out
