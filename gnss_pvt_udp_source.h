#ifndef GNSS_PVT_UDP_SOURCE_H
#define GNSS_PVT_UDP_SOURCE_H

#include <boost/asio.hpp>
#include "monitor_pvt.pb.h"

class Gnss_Pvt_Udp_Source
{
    public:
        explicit Gnss_Pvt_Udp_Source(unsigned short port);
        void print_monitor(gnss_sdr::MonitorPvt& monitor) const;
        bool read_n_parse_gnss_pvt(gnss_sdr::MonitorPvt& monitor);

    private:
        boost::asio::io_service io_service;
        boost::asio::ip::udp::socket socket;
        boost::system::error_code error;
        boost::asio::ip::udp::endpoint endpoint;
};

#endif
