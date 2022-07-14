#pragma once
#include "cumt_vec.h"
#include <iostream>
#include <ostream>
#include <stdarg.h>
#include <string>
#include <fstream>

namespace cumt
{
	template <typename T>
	inline void msg(std::ostream& s, const T& arg) { s << arg << std::endl; }
	template <typename T, typename... Ts>
	inline void msg(std::ostream& s, const T& first, const Ts& ...args)
	{
		s << first;
		msg(s, args...);
	}

	template <typename... Ts> inline void log(const Ts& ...args)
	{
		msg(std::cout, "| cumt | (i) |> ", args...);
		#ifdef CUMT_LOG_FILE
		std::ofstream o;
		o.open("cumt_log.txt");
		msg(o, "(i) |> ", args...);
		o.close();
		#endif
	}
	template <typename... Ts> inline void wrn(const Ts& ...args)
	{
		msg(std::cout, "| cumt | /!\\ |> ",args...);
		#ifdef CUMT_LOG_FILE
		std::ofstream o;
		o.open("cumt_log.txt");
		msg(o, "/i\\ |> ", args...);
		o.close();
		#endif
	}
	template <typename... Ts> inline void err(const Ts& ...args)
	{
		msg(std::cout, "| cumt | !!! |> ", args...);
		#ifdef CUMT_LOG_FILE
		std::ofstream o;
		o.open("cumt_log.txt");
		msg(o, "!!! |> ", args...);
		o.close();
		#endif
	}
}
