#include "gnss_pvt_udp_source.h"
#include <boost/lexical_cast.hpp>
#include <iostream>



// Add UART comms


int main(int argc, char *argv[])
{
    //declaração dos ponteiros
    double ppos_x;
    double ppos_y;
    double ppos_z;
    double pvel_x;
    double pvel_y;
    double pvel_z;
    double plat;
    double pllong;
    double palt;

    try
        {
            // Check command line arguments.
            if (argc != 2)
                {
                    // Print help.
                    std::cerr << "Usage: nav_msg_listener <port>\n";
                    return 1;
                }

            unsigned short port = boost::lexical_cast<unsigned short>(argv[1]);
            Gnss_Pvt_Udp_Source udp_listener(port);

            while (true)
                {
                    gnss_sdr::MonitorPvt monitor;
                    if (udp_listener.read_n_parse_gnss_pvt(monitor))
                        {
                            udp_listener.print_monitor(monitor, &ppos_x,&ppos_y,&ppos_z,&pvel_x,&pvel_y,&pvel_z,&plat,&pllong,&palt);
                        }
                    else
                        {
                            std::cout << "Error: the message cannot be parsed." << std::endl;
                        }
                }
        }
    catch (std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

    return 0;
}