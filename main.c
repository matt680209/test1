#include <stdio.h> 
#include <string.h> 
#include <malloc.h> 
#include <sys/socket.h> 
#include <linux/netlink.h> 


#define MAX_PAYLOD 1024
int main(int argc,char *argv[])
{
	struct sockaddr_nl src_addr, dest_addr;
	struct nlmsghdr *nlh = NULL;
	struct iovec iov;
	int sock_fd;
	struct msghdr msg;

	memset(&msg,0,sizeof(msg));

	sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
		
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid();
	src_addr.nl_groups = 0;

	bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));
	
	memset(&dest_addr, 0, sizeof(src_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0; // Linux kernel
	dest_addr.nl_groups = 0;

	nlh = (struct nlmsghdr *) malloc(NLMSG_SPACE(MAX_PAYLOD));


	nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOD);
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_flags = 0;

	strcpy(NLMSG_DATA(nlh), "Hi, I am Matt Chen.");

	iov.iov_base = (void *) nlh;
	iov.iov_len = nlh->nlmsg_len;
	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	sendmsg(sock_fd, &msg, 0);

	printf("Wait for message from kernel\n");

	recvmsg(sock_fd, &msg, 0);


	printf("Received message from kernel %s\n", NLMSG_DATA(msg.msg_iov->iov_base));

	close(sock_fd);
	return 0;
}
