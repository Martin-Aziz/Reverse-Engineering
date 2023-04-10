
void program(int (*rand)(), int (*print)(char *, ...), int (*scanf)(char *, ...), int (*memset)(void *, int, int), void*(*malloc)(int size))
{
	long buffer[11];
	long random0 = rand();
	long random1 = rand();
	long index = 0;
	long value = 0;
	long* check = malloc(sizeof(long));
	*check = random0; // Writes the value of random0 to the heap which can be used later to make sure that it can not be tempered with by overwriting the value and making it necessary to not only write but also read from the stack.
	while (1)
	{
		memset(buffer, 0, 0x58);
		// The strings are declared this way so that they end up on the stack and in the x86 code (which is the only part that ends up in payload.bin and is inserted into the final program).
		char input[] = "Input: ";
		print(input);
		char input_format[] = "%ld %ld";
		// Similar to Assignment 30 an index and value is read and the value is assigned to the buffer 
		int res = scanf(input_format, &index, &value);
		if (res != 2)
			break;
		buffer[index] = value;
		char result[] = "Result: %ld\n";
		print(result, buffer[index]);
	}

	if (*check == random1)
	{
		char flag[] = "FLAG{hands of my stack}\n";
		print(flag);
	}
}