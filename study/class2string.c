#include<stdio.h>
#include<malloc.h>
typedef unsigned char  u8;

void printHexBuffer(void *buf, unsigned long len)
{
    unsigned long i;
    unsigned char *bytes = (unsigned char *)buf;
    unsigned char buffer[1024] ={0};
    unsigned char *tmp;
    tmp = buffer;
    if (NULL == buf || 0 == len)
    {
        return;
    }
    printf ("len = %d\n",len);

    for (i=0; i<len; i++)
    {
        sprintf(tmp,"%02x ",bytes[i]);
        tmp += 3;
        if((i+1)%8 == 0)
        {
                sprintf(tmp,"\n");
                tmp += 1;
        }
    }
    printf("%s\n", buffer);
}

int radius_msg_attr_add_class(u8* pucRadiusAttrClass)
{
        u8 count = *pucRadiusAttrClass;
        pucRadiusAttrClass += 1;
        if(count == 0)
        {
                return;
        }
        u8 i = 0;
        u8 len;
        for(i = 0; i < count; i++)
        {
                len = *pucRadiusAttrClass;
                pucRadiusAttrClass += 1;
		printHexBuffer(pucRadiusAttrClass, len);
                pucRadiusAttrClass += len;
        }
}


struct radius_attr_data {
	u8 *data;
	int len;
};

struct radius_class_data {
	struct radius_attr_data *attr;
	int count;
};

void radius_attr_class2octets(struct radius_class_data radius_class, u8 *octets)
{
        int i = 0;
	*octets = radius_class.count;
	octets += 1;
        for(i = 0; i < (int)radius_class.count; i ++)
        {
		*octets = radius_class.attr[0].len;
		octets += 1;
                memcpy(octets, radius_class.attr[i].data, radius_class.attr[i].len);
                octets += radius_class.attr[i].len;
        }
}

int main()
{
	u8 app[10]="shabi";
	struct radius_class_data bb;
        bb.count = 2;
	bb.attr = calloc(1,bb.count*sizeof(struct radius_attr_data));
	bb.attr[0].data = app;
	bb.attr[0].len = 5;
        bb.attr[1].data = app;
        bb.attr[1].len = 5;
       		


	u8 out[100]={0};
	radius_attr_class2octets(bb, out);
	
	printHexBuffer(out, sizeof(out));
radius_msg_attr_add_class(out);

	return 0;
}
