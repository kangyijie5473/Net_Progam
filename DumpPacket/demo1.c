#include <stdio.h>
#include <assert.h>
#include <pcap/pcap.h>
char error_buffer[PCAP_ERRBUF_SIZE];
int get_app_layer_index(const u_char *start, int caplen);
void deal_packet(u_char *user, const struct pcap_pkthdr* h, const u_char *bytes)
{
	assert(!user);
	//printf("get %u bytes %u \n", h->caplen, h->len);
	// for(u_int i = 0; i < h->caplen; i++){
	// 	printf("%x ", bytes[i]);
	// }
	int APP_index = get_app_layer_index(bytes, h->caplen);
	if(APP_index){
		printf("Application length is %d\n", h->caplen - APP_index);
		for(int i = APP_index; i < h->caplen; i++)
			printf("%c", bytes[i]);
		printf("\n");
	}
}
int get_app_layer_index(const u_char *start, int caplen)
{
	const u_char *IP_head = start + 14;
	int TCP_index = (*IP_head & 0x0F) * 4;
	const u_char *TCP_head = IP_head + TCP_index;
	int APP_index = ((*(TCP_head + 12) & 0xF0) >> 4) * 4;
	if(caplen - (14 + TCP_index + APP_index))
		return 14 + TCP_index + APP_index;
	else
		return 0;
	
}
int main()
{
	//pcap_t *cap_handle = pcap_create("any",error_buffer); why not use this function
	bpf_u_int32 mask;
	bpf_u_int32 net;

	pcap_t *cap_handle ;
	pcap_lookupnet("wlp2s0", &net, &mask, error_buffer);
	cap_handle =  pcap_open_live("wlp2s0",BUFSIZ, 1,0,error_buffer);
	if(!cap_handle){
		printf("Error: pcap_open_live---%s\n", error_buffer);
		return -1;
	}

	struct bpf_program filter;
	char filter_app[] = "dst port 5473";
	pcap_compile(cap_handle, &filter, filter_app, 0, net);
	pcap_setfilter(cap_handle, &filter);
	
	pcap_loop(cap_handle, 5, deal_packet, NULL);

	// if(!pcap_activate(cap_handle)){
	// 	pcap_loop(cap_handle, 10, deal_packet, NULL);
	// }else{
	// 	printf("Error: pcap_activate\n");
	// 	return -1;
	// }
	pcap_close(cap_handle);
	return 0;
}