/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_IO_H
#define __LIBFT_IO_H
/*! @file libft_io.h
**	This header defines all the functions for OS-level input/output, read/write.
**	@addtogroup libft_io
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Arbitrary buffer size for libft_io functions
/*!
**	This is the arbitrary buffer size to be used by the reading functions.
**	Raising this amount will lower the amount of function calls made to
**	the 'read' function from unistd.h, resulting in possible speed improvments,
**	depending on the amount of files to read, and their filesizes.
**	It is also recommended to have this number be a power of 2, as it can be
**	occasionally faster to manage arrays of such sizes on certain machines.
*/
#define BUFF_SIZE 2048

//! File descriptor integer type for libft_io functions
/*!
** Define a type for file descriptors (which is usually the default machine 'int')
*/
typedef int		t_fd;

/*!
**	@def STDIN
**	@def STDOUT
**	@def STDERR
**	Define the 3 standard (std) streams of data - these numbers are special
**	file descriptors used to read from and write to the terminal commandline.
*/
#define STDIN	(t_fd)0	//!< Special file descriptor (0), refers to terminal input stream
#define STDOUT	(t_fd)1	//!< Special file descriptor (1), refers to terminal output stream
#define STDERR	(t_fd)2	//!< Special file descriptor (2), refers to terminal error stream

/*!
**	Define some useful string literals for commandline output colors.
**	May be used with any of the 'ft_output' and 'ft_write' functions.
*/
#ifndef __COLORS__
#define __COLORS__
#define C_RED		"\x1b[31m"	//!< The string sequence to color the terminal text output red
#define C_GREEN		"\x1b[32m"	//!< The string sequence to color the terminal text output green
#define C_YELLOW	"\x1b[33m"	//!< The string sequence to color the terminal text output yellow
#define C_BLUE		"\x1b[34m"	//!< The string sequence to color the terminal text output blue
#define C_MAGENTA	"\x1b[35m"	//!< The string sequence to color the terminal text output magenta
#define C_CYAN		"\x1b[36m"	//!< The string sequence to color the terminal text output cyan
#define C_RESET		"\x1b[0m"	//!< The string sequence to reset the terminal text output to its default color
#endif

/*!
**	@def PRINTF_S64
**	@def PRINTF_U64
**	@def PRINTF_F32
**	@def PRINTF_SIZE
**	Cross-platform '%' Format specifiers for printf calls
*/
#ifdef __APPLE__
	#define PRINTF_S64		"%lld"
	#define PRINTF_U64		"%llu"
#else
	#ifdef __MINGW32__
		#define PRINTF_S64		"%ld"
		#define PRINTF_U64		"%I64llu"
	#else
		#define PRINTF_S64		"%ld"
		#define PRINTF_U64		"%lu"
	#endif
#endif
#define PRINTF_SIZE		"%zu"
#define PRINTF_F32		"%f"

#ifdef _INT_64_
#define PRINTF_W12_INT	"%12ld"
#else
#define PRINTF_W12_INT	"%12d"
#endif

#ifdef _UINT_64_
#define PRINTF_W12_UINT	"%12lu"
#else
#define PRINTF_W12_UINT	"%12u"
#endif



/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define IO_Read_File		ft_readfile
#define IO_Read_NextLine	ft_getnextline
#define IO_Read_Lines		ft_readlines

#define IO_Write_Char		ft_write_char
#define IO_Write_String		ft_write_str
#define IO_Write_Line		ft_write_line
#define IO_Write_Lines		ft_write_strls
#define IO_Write_Memory		ft_write_memory

#define IO_Output_Char		ft_output_char
#define IO_Output_String	ft_output_str
#define IO_Output_Line		ft_output_line
#define IO_Output_Lines		ft_output_strls
#define IO_Output_Memory	ft_output_memory



/*
** ************************************************************************** *|
**                              Reading Functions                             *|
** ************************************************************************** *|
*/

//! Reads the contents of 'fd' and fill a data buffer with those bytes
/*!
**	Reads the full contents of the file descriptor 'fd', and puts it into 'a_file'.
**
**	@param	fd		The file descriptor to read data from
**	@param	a_file	The address of the buffer to fill: is allocated and filled with the data
**	@param	max		The maximum amount of bytes to read from 'fd'
**	@return OK(0) if the stream was read successfully, ERROR(1) if there was an error.
*/
t_bool	ft_readfile(t_fd const fd, char* *a_file, t_size max);

//! Reads the contents of 'fd' and makes an array of strings, one for each line
/*!
**	Reads the contents of the file descriptor 'fd', and puts that into
**	an array of strings, one char pointer for each line (each '\\n' newline char).
**	Each '\\n' character in the string are replaced by '\\0' string terminators.
**
**	@param	fd			The file descriptor to read data from
**	@param	a_strarr	The address of the string array to fill: the top-level
**						top-level pointer array is allocated and filled appropriately.
**	@return OK(0) if the stream was read successfully, ERROR(1) if there was an error.
*/
t_bool	ft_readlines(t_fd const fd, char** *a_strarr);

//! Reads the contents of the file descriptor 'fd' line-per-line.
/*!
**	This function will read 'fd' line-per-line as you call it repeatedly.
**	This means that it will allocate and fill a buffer until reading '\\n',
**	at which point this buffer is returned via the 'line' char pointer arg.
**	As such, this function will typically be called within a while loop.
**
**	@param	fd		The file descriptor to read data from
**	@param	a_line	The address of the string to allocate and fill with the current line.
**	@return
**		- -1 if there's an error
**		- 1 if a line of characters was successfully read
**		- 0 if the end of the file was reached
*/
int		ft_getnextline(t_fd const fd, char* *a_line);
#define GNL_LINE	1	//!< Return value for ft_getnextline: indicates succesful line read, more to follow
#define GNL_END		0	//!< Return value for ft_getnextline: indicates successful line read, end of file reached
#define GNL_ERROR	-1	//!< Return value for ft_getnextline: indicates a read error occurred



/*
** ************************************************************************** *|
**                              Writing Functions                             *|
** ************************************************************************** *|
*/

//! Writes the given character 'c' to the given file descriptor 'fd'
int	ft_write_char(t_fd fd, char c);
//! Writes the given string 'str' to the given file descriptor 'fd'
int	ft_write_str(t_fd fd, char const* str);
//! Writes the given string 'str' to the given file descriptor 'fd', and a newline '\n' char at the end
int	ft_write_line(t_fd fd, char const* str);
//! Writes the given string array 'strls' to the given file descriptor 'fd'
int	ft_write_strls(t_fd fd, char const** strls);
//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the given file descriptor 'fd'
int	ft_write_memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);



/*
** ************************************************************************** *|
**                             Commandline Output                             *|
** ************************************************************************** *|
*/

//! Writes the given char 'c' to the standard output.
int	ft_output_char(char c);
//! Writes the given string 'str' to the standard output.
int	ft_output_str(char const* str);
//! Writes the given string 'str' to the standard output, with a newline '\n' character at the end.
int	ft_output_line(char const* str);
//! Writes the given string array 'strls' to the standard output.
int	ft_output_strls(char const** strls);
//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the standard output
int	ft_output_memory(t_u8 const* ptr, t_size n, t_u8 cols);



/*! @} */
HEADER_END
#endif
