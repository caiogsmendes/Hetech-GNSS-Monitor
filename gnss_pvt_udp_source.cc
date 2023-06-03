

#include <iostream>
#include <sstream>
#include <string>
#include "monitor_pvt.pb.h"
#include "gnss_pvt_udp_source.h"

Gnss_Pvt_Udp_Source::Gnss_Pvt_Udp_Source(unsigned short port)
    : socket{io_service}, endpoint{boost::asio::ip::udp::v4(), port}
{
    socket.open(endpoint.protocol(), error);
    socket.bind(endpoint, error);
}

bool Gnss_Pvt_Udp_Source::read_n_parse_gnss_pvt(gnss_sdr::MonitorPvt& monitor) 
{
    char buff[2000];

    // This call will block until one or more bytes of data has been received.
    int bytes = socket.receive(boost::asio::buffer(buff));

    std::string data(&buff[0], bytes);

    return monitor.ParseFromString(data);
}

void Gnss_Pvt_Udp_Source::print_monitor(gnss_sdr::MonitorPvt& monitor,
            double *pos_x,
            double *pos_y,
            double *pos_z,
            double *vel_x,
            double *vel_y,
            double *vel_z,
            double *lat,
            double *longt,
            double *alt) const
{
    *pos_x = monitor.pos_x();  // Position X component in ECEF, expressed in m
    *pos_y = monitor.pos_y();  // Position Y component in ECEF, expressed in m
    *pos_z = monitor.pos_z();  // Position Z component in ECEF, expressed in m
    *vel_x = monitor.vel_x();  // Velocity X component in ECEF, in m/s
    *vel_y = monitor.vel_y();  // Velocity Y component in ECEF, in m/s
    *vel_z = monitor.vel_z(); // Velocity Z component in ECEF, in m/s

    double cov_xx = monitor.cov_xx(); // Position variance in the Y component, in m2
    double cov_yy = monitor.cov_yy(); // Position variance in the Y component, in m2
    double cov_zz = monitor.cov_zz(); // Position variance in the Z component, in m2
    double cov_xy = monitor.cov_xy(); // Position XY covariance, in m2
    double cov_yz = monitor.cov_yz(); // Position YZ covariance, in m2
    double cov_zx = monitor.cov_zx(); // Position ZX covariance, in m2

    *lat = monitor.latitude();  // Latitude, in deg. Positive: North
    *longt = monitor.longitude(); // Longitude, in deg. Positive: East
    *alt = monitor.height();    // Height, in m


    std::cout<<"pos_x: "<< *pos_x <<std::endl;
    std::cout<<"pos_y: " << *pos_y <<std::endl;
    std::cout<<"pos_z: " << *pos_z <<std::endl;
    std::cout<<"vel_x: " << *vel_x <<std::endl;
    std::cout<<"vel_y: " << *vel_y <<std::endl;
    std::cout<<"vel_z: " << *vel_z <<std::endl;
    std::cout<<"cov_xx" << cov_xx <<std::endl;
    std::cout<<"cov_yy" << cov_yy <<std::endl;
    std::cout<<"cov_zz" << cov_zz <<std::endl;
    std::cout<<"cov_xy" << cov_xy <<std::endl;
    std::cout<<"cov_yz" << cov_yz <<std::endl;
    std::cout<<"cov_zx" << cov_zx <<std::endl;
    std::cout<<"lat: " << *lat <<std::endl;
    std::cout<<"long: " << *longt <<std::endl;
    std::cout<<"alt: " << *alt <<std::endl;

}
