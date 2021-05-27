#ifndef MY_MANAGER_H
#define MY_MANAGER_H


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
 
 private:
  boost::shared_ptr<Backend> backend_;
  boost::shared_ptr<std::ostream> current_stream_;
};
 

#endif