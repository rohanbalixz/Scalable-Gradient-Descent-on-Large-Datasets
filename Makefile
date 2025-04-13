CXX = g++
CXXFLAGS = -O3 -std=c++11

all: linreg_gd linreg_gd_omp

linreg_gd: src/linreg_gd.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

linreg_gd_omp: src/linreg_gd_omp.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $<

clean:
	rm -f linreg_gd linreg_gd_omp

