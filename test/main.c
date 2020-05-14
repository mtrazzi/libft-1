
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

#include "test.h"



static char const * program_name = NULL;

/*
** ************************************************************************** *|
**                           Global Testing Variables                         *|
** ************************************************************************** *|
*/

char const* test1 = "Omae wa mou shindeiru.\0";		size_t const test1_len = 23;
char const* test2 = "Nani???\0";					size_t const test2_len = 8;
char const* test3 = "Un ange mange de la fange.\0";	size_t const test3_len = 27;



/*
** ************************************************************************** *|
**                              Segfault Handling                             *|
** ************************************************************************** *|
*/

char*	nullstr	= "(NULL)";
char*	segstr	= "(segfault)";

void	segfault_handler(int sig, siginfo_t *info, void *ptr)
{
    if (sig == SIGSEGV)
    {
        longjmp(restore, SIGSEGV);
    }
}

void	init_segfault_handler(void)
{
	memset(&sig, 0, sizeof(sigaction));
	sigemptyset(&sig.sa_mask);
	sig.sa_flags     = SA_NODEFER;
	sig.sa_sigaction = segfault_handler;
	sigaction(SIGSEGV, &sig, NULL);
}



/*
** ************************************************************************** *|
**                           Main Program Definitions                         *|
** ************************************************************************** *|
*/

static void	handle_arg_verbose()	{ g_test.flags.verbose = TRUE; }
static void	handle_arg_arguments()	{ g_test.flags.show_args = TRUE; }
static void handle_arg_performance(){ g_test.flags.show_speed = TRUE; }
static void	handle_arg_overflow()	{ g_test.flags.test_overflow = TRUE; }

/*
**	This function initializes the global variable 'g_test', which is used everywhere.
*/
static void	init(void)
{
	// default every option to FALSE
	g_test.flags = (s_test_flags){ FALSE, FALSE, FALSE };

	g_test.suites[0x0] = (s_test_suite){ FALSE, "memory",		test_memory };
	g_test.suites[0x1] = (s_test_suite){ FALSE, "char",			test_char };
	g_test.suites[0x2] = (s_test_suite){ FALSE, "string",		test_string };
	g_test.suites[0x3] = (s_test_suite){ FALSE, "stringarray",	test_stringarray };
	g_test.suites[0x4] = (s_test_suite){ FALSE, "convert",		test_convert };
	g_test.suites[0x5] = (s_test_suite){ FALSE, "color",		test_color };
	g_test.suites[0x6] = (s_test_suite){ FALSE, "list",			test_list };
	g_test.suites[0x7] = (s_test_suite){ FALSE, "math",			test_math };
	g_test.suites[0x8] = (s_test_suite){ FALSE, "stat",			test_stat };
	g_test.suites[0x9] = (s_test_suite){ FALSE, "random",		test_random };
	g_test.suites[0xA] = (s_test_suite){ FALSE, "vlq",			test_vlq };
	g_test.suites[0xB] = (s_test_suite){ FALSE, "io",			test_io };

	g_test.args[0] = (s_test_arg){ NULL,					'h', "help",		"If provided, display only the program usage help and exit." };
	g_test.args[1] = (s_test_arg){ handle_arg_verbose,		'v', "verbose",		"If provided, output each test result (as either 'OK!' or 'ERROR: return was _')." };
	g_test.args[2] = (s_test_arg){ handle_arg_arguments,	'a', "arguments",	"If provided, output the arguments used for each test performed." };
	g_test.args[3] = (s_test_arg){ handle_arg_performance,	'p', "performance",	"If provided, output the execution speed for each test performed." };
	g_test.args[4] = (s_test_arg){ handle_arg_overflow,		'o', "overflow",	"If provided, perform the overflowing number tests for 'libft_convert' functions." };
}



/*
** ************************************************************************** *|
**                             Main Program Logic                             *|
** ************************************************************************** *|
*/

static int	check_no_test_suites(void)
{
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (g_test.suites[i].run)
			return (FALSE);
	}
	return (TRUE);
}



#define MATCHED_HELP	((int)-1)

static int	handle_args_test_suites(char const * arg)
{
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (str_equals(arg, g_test.suites[i].name))
		{
			g_test.suites[i].run = TRUE;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	handle_args_option_char(char arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (arg == g_test.args[i].arg)
		{
			if (g_test.args[i].handle_arg)
				g_test.args[i].handle_arg();
			else return (MATCHED_HELP);
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	handle_args_option_string(char const * arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (str_equals(arg, g_test.args[i].name))
		{
			if (g_test.args[i].handle_arg)
				g_test.args[i].handle_arg();
			else return (MATCHED_HELP);
			return (TRUE);
		}
	}
	return (FALSE);
}



int		main(int argc, char **argv)
{
	if (argc < 1 || argv == NULL)
	{
		print_error("Invalid platform, no 'argv' program argument list recieved.");
		return (ERROR);
	}
	program_name = argv[0];

	init();
	init_segfault_handler();

	// Handle main program arguments
	int	match;
	int tmp;
	for (int i = 1; i < argc; ++i)
	{
		match = FALSE;
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '\0')
			{
				print_error("Unexpected end of argument after '-'.");
				continue;
			}
			else if (argv[i][1] == '-')
			{
				match = handle_args_option_string(argv[i] + 2);
			}
			else for (int j = 1; j < strlen(argv[i]); ++j)
			{
				tmp = handle_args_option_char(argv[i][j]);
				if (match)
					match = (tmp == MATCHED_HELP ? tmp : match);
				else match = tmp;
			}
		}
		else if (isalpha(argv[i][0]))
		{
			match = handle_args_test_suites(argv[i]);
		}

		if (match == FALSE)
		{
			print_error("Argument not recognized (%s)\n", argv[i]);
			print_usage(program_name);
			return (ERROR);
		}
		else if (match == MATCHED_HELP)
		{
			print_usage(program_name);
			return (OK);
		}
	}

	// Run the appropriate test suites
	print_title();
	print_endian_warning();
	if (check_no_test_suites())
	{
		for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
		{
			g_test.suites[i].run = TRUE;
		}
	}
	g_test.totals.tests = 0;
	g_test.totals.failed = 0;
	s_test_totals suite;
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (g_test.suites[i].run)
		{
			suite = g_test.totals;
			g_test.suites[i].test();
			suite.tests = g_test.totals.tests - suite.tests;
			suite.failed = g_test.totals.failed - suite.failed;
			print_totals(suite, g_test.suites[i].name);
		}
	}
	print_totals(g_test.totals, NULL);
	return (OK);
}
