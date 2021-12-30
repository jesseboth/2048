#include <stdio.h>

extern char *int2str(int i, char *str);
extern void output_string(char *str);

char *time_to_string(int t, char *str) {
	int h, m, s;

    char temp[3];
	
	h = (t/3600); 
	m = (t -(3600*h))/60;
	s = (t -(3600*h)-(m*60));

    int i = 0;
    if(h > 0){
        int2str(h, temp);
        str[i] = h > 10 ? temp[0] : '0';
        str[i+1] = h < 10 ? temp[0] : temp[1];
        str[i+2] = ':';
        i+=3;
    }

    int2str(m, temp);
    str[i] = m > 10 ? temp[0] : '0';
    str[i+1] = m < 10 ? temp[0] : temp[1];
    str[i+2] = ':';
    i+=3;

    int2str(s, temp);
    str[i] = s > 10 ? temp[0] : '0';
    str[i+1] = s < 10 ? temp[0] : temp[1];
    i+=2;
	
    str[i] = 0;
	return 0;
}

