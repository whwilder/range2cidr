#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main (int argc, char **argv){
   int i;
   char *range = malloc(sizeof(char) * 40);
   char *ip1, *ip2;
   int ip1int, ip2int;
   int ip1err, ip2err;
   int mask;
   int cidr;


   struct in_addr addr1,addr2;
   for (i = 1; i < argc; i++){
   FILE *file = fopen(argv[i], "r");
   while (fgets(range, 40, file)) {
      if (range[0] == '\n') {
         printf("empty line\n"); continue;}
      ip1 = strtok(range, "-");
      ip2 = strtok(NULL, "-");
      ip2 = strtok(ip2, "\n");

      ip1err = inet_aton( ip1, &addr1 );
      if (ip1err == 0){ fprintf(stderr, "Invalid address: %s\n", ip1); continue; }
      ip1int = ntohl(addr1.s_addr);
      ip2err = inet_aton( ip2, &addr2 );
      if (ip2err == 0){ fprintf(stderr, "Invalid address: %s\n", ip2); continue; }
      ip2int = ntohl( addr2.s_addr );

      printf("%d\n", ip1int);
      printf("%d\n", ip2int);

      mask = ip1int ^ ip2int;
      int mask1 = ~mask;
      cidr = 0;
      while ( mask > 0 ) {
         mask <<= 1;
         cidr++;
      }
      if (cidr == 0)
         printf("%s/32\n", ip1);
      else
         printf("%s/%d\n", ip1, cidr);
   }
   }
   return 0;
}
