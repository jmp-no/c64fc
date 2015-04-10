#ifndef PSID_HEADER_H
#define PSID_HEADER_H 1

/* Based on psid.c from VICE-Core */

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int

typedef struct psid_s {
	BYTE psid_header[4];		// 0..3
	WORD version;			// 4..5
	WORD data_offset;		// 6..7
	WORD load_addr;			// 8..9
	WORD init_addr;			// a..b
	WORD play_addr;			// c..d
	WORD songs;			// e..f
	WORD start_song;		// 10..11
	BYTE speed[4];
//	DWORD speed;			// 12..15
	BYTE name[32];			// 16..35
	BYTE author[32];		// 36..55
	BYTE copyright[32];		// 56..75
	WORD flags;			// 76..77
	BYTE start_page;		// 78
	BYTE page_length;		// 79
	WORD reserved;			// 7a..7b
//	WORD data_size;			// 7c..7d
	BYTE data[65536];		// 7e->
} psid_t;

#endif

