#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/thread/thread.hpp>

#include "Logger.h"

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace trivial = boost::log::trivial;

Logger::Logger()
{
    logging::add_file_log
    (
        keywords::file_name = "modulo.log",
        keywords::format =
        (
            expr::stream <<
            "[" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
            "] [" << trivial::severity <<
            "] " << expr::message
        )
    );

    logging::add_common_attributes();

    logging::core::get()->set_filter(trivial::severity >= trivial::info);
}

Logger& Logger::getLogger()
{
	static Logger logger;
	return logger;
}

void Logger::info(const std::string &message) const
{
    BOOST_LOG_TRIVIAL(info) << message;
}

void Logger::warning(const std::string &message) const
{
    BOOST_LOG_TRIVIAL(warning) << message;
}

void Logger::error(const std::string &message) const
{
    BOOST_LOG_TRIVIAL(error) << message;
}

void Logger::fatal(const std::string& message) const
{
    BOOST_LOG_TRIVIAL(fatal) << message;
}
