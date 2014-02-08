all:
	rm -f demo cdemo
	gcc cdemo.c -o cdemo
	g++ demo.cpp -o demo
