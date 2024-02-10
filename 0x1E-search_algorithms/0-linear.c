#include "search_algos.h"

/**
 * linear_search - Sequentialy search for the value in the array
 * @array: array data structure to search
 * @size: size of the array
 * @value: targe value to find or search
 * Return: index value if succees, -1 for otherwise
 */

int linear_search(int *array, size_t size, int value)
{
	size_t i;

	if (array == NULL)
	{
		return (-1);
	}

	for (i = 0; i < size; i++)
	{

		printf("Value checked array[%ld] = [%d]\n", i, array[i]);

		/*check target value*/
		if (value == array[i])
		{
			return (i);
		}
	}

	return (-1);
}