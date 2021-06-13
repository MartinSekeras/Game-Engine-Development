/** \file log.h */
#pragma once

#include "system.h"
#include <spdlog/spdlog.h>


namespace Engine
{
	/*	\class Log
	*	\brief Class for the creation of a logging system, to be used throughout Engine. 
	*/
	class Log : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) override;		//!< start the logger.
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override;		//!< stop the logger.

		template<class ...Args>
		static void info(Args&&... args);	//!< double reference for a paramater pack

		template<class ...Args>
		static void debug(Args&&... args);

		template<class ...Args>
		static void error(Args&&... args);

		template<class ...Args>
		static void trace(Args&&... args);

		template<class ...Args>
		static void warn(Args&&... args);

		template<class ...Args>
		static void release(Args&&... args);

		template<class ...Args>
		static void file(Args&&... args);

	private:
		static std::shared_ptr<spdlog::logger> s_consolelogger;		//!< console logger.
		static std::shared_ptr<spdlog::logger> s_filelogger;		//!< file logger, will make a .txt file of the log.

	};

	template<class ...Args>
	static void Log::info(Args&&... args)
	{
		if (s_consolelogger) {
			//perfect forwarding to forward to the logger
#ifdef NG_DEBUG
			s_consolelogger->info(std::forward<Args>(args) ...);
#endif
		}
	}

	template<class ...Args>
	static void Log::debug(Args&&... args)
	{
		if (s_consolelogger) {
			//perfect forwarding to forward to the logger
#ifdef NG_DEBUG
			s_consolelogger->debug(std::forward<Args>(args) ...);
#endif
		}
	}

	template<class ...Args>
	static void Log::error(Args&&... args)
	{
		if (s_consolelogger) {
			//perfect forwarding to forward to the logger
#ifdef NG_DEBUG
			s_consolelogger->error(std::forward<Args>(args) ...);
#endif
		}
	}

	template<class ...Args>
	static void Log::trace(Args&&... args)
	{
		if(s_consolelogger) {
			//perfect forwarding to forward to the logger
#ifdef NG_DEBUG
			s_consolelogger->trace(std::forward<Args>(args) ...);
#endif
		}
	}

	template<class ...Args>
	static void Log::warn(Args&&... args)
	{
		if (s_consolelogger) {
			//perfect forwarding to forward to the logger
#ifdef NG_DEBUG
			s_consolelogger->warn(std::forward<Args>(args) ...);
#endif
		}
	}

	//release does the same as trace but works whatever mode that you are in.
	template<class ...Args>
	static void Log::release(Args&&... args)
	{
		if (s_consolelogger) {
			//perfect forwarding to forward to the logger
			s_consolelogger->trace(std::forward<Args>(args) ...);
		}	}

	template<class ...Args>
	static void Log::file(Args&&... args)
	{
		//an if statement to make sure it has been initialised.
		//and perfect forwarding to forward to the logger.
		if(s_filelogger)
		{
		s_filelogger->trace(std::forward<Args>(args) ...);
		}
	}
}