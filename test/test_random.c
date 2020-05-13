
#include "libft_stat.h"
#include "libft_random.h"

#include "test.h"



t_sortedlist_int	print_test_random(int samples)
{
	t_sortedlist_int	result;
	t_list_int			ilst;

	ft_random_renew_seed();

	if (g_test.flags.verbose)
	{
		printf("Statistic repartition test of RNG (sample size: %d)\n", samples);
	}
	ilst = ft_stat_new_ilst(samples);

	for (int i = 0; i < ilst.len; ++i)
	{
		ilst.data[i] = ft_random_int_a_to_b(-500, 501);
	}

/*	static t_int arr[5] = {-339, 214, 394, -162, -50};//{-339, -162, -50, 214, 394};
	for (int i = 0; i < ilst.len; ++i)
		ilst.data[i] = arr[i];

	for (int i = 0; i < ilst.len; ++i)
		printf("%d, ", ilst.data[i]);
	printf("\n");
*/
	if (g_test.flags.verbose)
		printf("Quicksorting... ");
	result = ft_stat_quicksort_i_new(ilst);
	if (g_test.flags.verbose)
		printf("Done !\n");
	for (int i = 0; i < result.len - 1; ++i)
	{
		if (result.data[i] > result.data[i + 1])
			printf(C_RED"Sorting error at index %d\n"C_RESET, i);
	}
	ft_stat_free_ilst(&ilst);
	return (result);
}



int		test_random(void)
{
	print_suite_title("random");

	static const int	samples = 20000;
	t_sortedlist_int	ilst_sorted = print_test_random(samples);

	ft_stat_free_ilst(&ilst_sorted);
	return (OK);
}
