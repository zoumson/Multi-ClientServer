
/*
* License plate detection
* See COPYRIGHT file at the top of the source tree.
*
* This product includes software developed by the
* STARGUE Project (http://www.stargue.org/).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the STARGUE License Statement and
* the GNU General Public License along with this program. If not,
* see <http://www.lsstcorp.org/LegalNotices/>.
*/

/**
 * @file Manager.h
 *
 * @brief Provide logs
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */


#ifndef MY_MANAGER_H
#define MY_MANAGER_H


/**
 * Implementation of a log manager
 * This log manager store each log in a specifc file
 * define by the user
 * the log file name may change and the following logs output 
 * is directed in the file name given right before
 *
 */
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <fstream>
#include <boost/core/null_deleter.hpp>
#include <boost/log/trivial.hpp>
namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
 
namespace za{
enum sign_severity_level 
{
  trace,
  debug,
  info,
  warning,
  error,
  fatal,
  report
};


BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(
    my_logger, src::severity_logger_mt<sign_severity_level>
);


class Manager 
{

public:
  using Backend = sinks::text_ostream_backend;
  using TextSink = sinks::synchronous_sink<Backend>; 
  
private:
boost::shared_ptr<Backend> backend_;
boost::shared_ptr<std::ostream> current_stream_;

 public:
  Manager() 
  {
    backend_ = boost::make_shared<Backend>();
    backend_->auto_flush(true);
 
    boost::shared_ptr<TextSink> sink(new TextSink(backend_));
    sink->set_formatter(
        expr::format("[%1%]<%2%>: %3%") %
        //expr::format("[%1%]<%2%>(%3%): %4%") %
            expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") %
            //logging::trivial::severity %
            expr::attr < sign_severity_level > ("Severity") %
            //expr::attr < attrs::current_thread_id::value_type > ("ThreadID") %
            expr::smessage
    );
    sink->set_filter(expr::attr<sign_severity_level>("Severity") >= warning);
    logging::core::get()->add_sink(sink);
 
    logging::add_common_attributes();
    logging::core::get()->add_global_attribute(
        "ThreadID", attrs::current_thread_id()
    );
  }
 
  void set_log_file(const char* filename) 
  {
    backend_->remove_stream(current_stream_);
    current_stream_.reset(new std::ofstream(filename));
    backend_->add_stream(current_stream_);
    //stdout
     backend_->add_stream(
        boost::shared_ptr< std::ostream >(&std::clog, boost::null_deleter()));
  }
 
};
 
}
#endif