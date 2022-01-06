#ifndef ISAAC_H
#define ISAAC_H

class ISAAC
{
private:
	int count;
	int results[256];
	int memory[256];
	int a;
	int b;
	int c;

	void isaac();

	void init();

public:
	ISAAC(int seed[], int seedSize);

	int getNextValue();
};

#endif