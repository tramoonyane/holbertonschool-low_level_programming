/**
 * reverse_array - Reverses the content of an array of integers.
 * @a: Pointer to the array of integers.
 * @n: Number of elements in the array.
 *
 * Description: This function takes an array of integers and its length
 * as arguments and reverses the order of the elements in the array.
 */
void reverse_array(int *a, int n)
{
  int start = 0;
  int end = n - 1;
  int temp;

  while (start < end)
    {
      /* Swap elements at the start and end positions */
      temp = a[start];
      a[start] = a[end];
      a[end] = temp;

      start++;
      end--;
    }
}
