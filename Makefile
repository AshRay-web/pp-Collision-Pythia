tutorial%: tutorial%.cc
	g++ -I /home/aasharya/pythia8312/include $@.cc -o $@ -lpythia8 -L/home/aasharya/pythia8312/lib
	
tutorial4: tutorial4.cc
	g++ -I /home/aasharya/pythia8312/include `root-config --cflags` tutorial4.cc -o tutorial4 -lpythia8 -L/home/aasharya/pythia8312/lib `root-config --glibs`

tutorial5: tutorial5.cc
	g++ -I /home/aasharya/pythia8312/include `root-config --cflags` tutorial5.cc -o tutorial5 -lpythia8 -L/home/aasharya/pythia8312/lib `root-config --glibs`
	
tutorial6: tutorial6.cc
	g++ -I /home/aasharya/pythia8312/include `root-config --cflags` tutorial6.cc -o tutorial6 -lpythia8 -L/home/aasharya/pythia8312/lib `root-config --glibs`
	
tutorial7: tutorial7.cc
	g++ -I /home/aasharya/pythia8312/include `root-config --cflags` tutorial7.cc -o tutorial7 -lpythia8 -L/home/aasharya/pythia8312/lib `root-config --glibs`
