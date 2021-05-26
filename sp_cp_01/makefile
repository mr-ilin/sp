exe="sp_cp_01"

all:
	g++ Mlispgen.cpp -o ${exe}
debug:
	g++ Mlispgen.cpp -o ${exe} -DDEBUG -g -fsanitize=address

clean:
	rm -f sp_cp_01