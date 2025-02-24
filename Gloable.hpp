#ifndef GLOABLE_HPP
#define GLOABLE_HPP

#define SHMTRANSPORT 0
#define UDPTRANSPORT 1
#define TCPTRANSPORT 2

extern int is_main_reboot;
extern int is_slave_reboot;

extern int main_transport_type;
extern int slave_transport_type;

extern int timeinterval;
#endif