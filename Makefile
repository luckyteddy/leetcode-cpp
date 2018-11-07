cc = g++
prom = leetcode
#deps = calc.h
obj = leetcode.o
CXXFLAGS += -std=c++11

$(prom): $(obj)
	    $(cc) -o $(prom) $(obj)

%.o: %.c $(deps)
	    $(cc) -c $< -o $@

clean:
	    rm -rf $(obj) $(prom)
