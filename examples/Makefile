

all: fl_assert_example testing

fl_assert_example: fl_assert_example.cpp ../*
	clang++ $< -o $@ -std=c++2a -L ../lib -lflawed -fPIC -g

testing: testing.cpp ../*
	clang++ $< -o $@ -std=c++2a -L ../lib -lflawed -lflawed_testing -fPIC -g
