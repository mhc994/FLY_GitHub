#include "mhc.h"
#include "GlobalVariables.h"

/**************************ʵ�ֺ���********************************************
����ԭ�ͣ�int16o_string(int16 data, char *string)
�������ܣ���int16������ת�����ַ���������ӵ�*stringָ����ַ�����ĩβ
���������int16 data	��Ҫת��������
		  char *string 	ָ����ת��������ַ�����ָ��
�����������
ע    �⣺��֤���ת��������ַ��������㹻����������������ӵ��ַ�����ĩβ��
		  ʹ��ǰ���ȰѴ�Ž�����ַ�������Ч�������
��    �ߣ�Ф����
��    ����1.0
��    �ڣ�2013-11-18
*******************************************************************************/
void int16_to_string(int16 data, char *string)
{ 
 char char_temp[11];
 int16 data_temp;
 Uint8 posi=0;
 Uint8 zeroflag=0;
 if(data<0)
 {
  data_temp=data*(-1);
  char_temp[0]='-';
  posi=1;
 }
 else
 {
  data_temp=data;
 }
 char_temp[posi]=data_temp/10000+'0';
 if(char_temp[posi]!='0')
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000)/1000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000)/100+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100)/10+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10)+'0';	
 posi++; 
 char_temp[posi]=SEPARATE;
 posi++;
// char_temp[posi]=SEPARATE;
// posi++;
 char_temp[posi]=0;
 strcat(string,char_temp);
}
/**************************ʵ�ֺ���********************************************
����ԭ�ͣ�uint32o_string(uint32 data, char *string)
�������ܣ���uint32������ת�����ַ���������ӵ�*stringָ����ַ�����ĩβ
���������uint32 data	��Ҫת��������
		  char *string 	ָ����ת��������ַ�����ָ��
�����������
ע    �⣺��֤���ת��������ַ��������㹻����������������ӵ��ַ�����ĩβ��
		  ʹ��ǰ���ȰѴ�Ž�����ַ�������Ч�������
��    �ߣ�Ф����
��    ����1.0
��    �ڣ�2013-11-18
*******************************************************************************/
void uint32_to_string(Uint32 data, char *string)
{ 
 char char_temp[14];
 Uint8 posi=0;
 Uint8 zeroflag=0;
 char_temp[posi]=data/1000000000+'0';
 if(char_temp[posi]!='0')
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%1000000000)/100000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%100000000)/10000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%10000000)/1000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%1000000)/100000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%100000)/10000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%10000)/1000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%1000)/100+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%100)/10+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%10)+'0';	
 posi++; 
 char_temp[posi]=SEPARATE;
 posi++; 
 char_temp[posi]=SEPARATE;
 posi++;
 char_temp[posi]=0;
 strcat(string,char_temp);
}
/**************************ʵ�ֺ���********************************************
����ԭ�ͣ�double_to_string(int16 data, char *string)
�������ܣ���double������ת�����ַ���������ӵ�*stringָ����ַ�����ĩβ
���������double data	��Ҫת��������
		  char *string 	ָ����ת��������ַ�����ָ��
�����������
ע    �⣺��֤���ת��������ַ��������㹻����������������ӵ��ַ�����ĩβ��
		  ʹ��ǰ���ȰѴ�Ž�����ַ�������Ч���������ת�������-99999.99��99999.99֮��
		  ����0.01��������Χ�����ݲ�����ȷת��
��    �ߣ�Ф����
��    ����1.0
��    �ڣ�2013-11-18
*******************************************************************************/
void double_to_string(double data,char *string)
{
 char char_temp[21];
 int32 data_temp;
 Uint8 posi=0;
 Uint8 zeroflag=0;
if(data>0)
	{
	data_temp=(int32)(data*100);
	}
else  
	{
	char_temp[0]='-';
	posi=1;
	data_temp=(int32)(data*(-100));
	}
 char_temp[posi]=(data_temp%10000000000)/1000000000+'0';
 if(char_temp[posi]!='0')
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000000000)/100000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100000000)/10000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000000)/1000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000000)/100000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100000)/10000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000)/1000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
  char_temp[posi]=(data_temp%1000)/100+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 char_temp[posi]='.';
 posi++;
 char_temp[posi]=(data_temp%100)/10+'0'; 
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 char_temp[posi]=(data_temp%10)+'0';	
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 if(zeroflag)
	 {
	 posi++; 
	 char_temp[posi]=SEPARATE;
	 posi++;
//	 char_temp[posi]=SEPARATE;
//	 posi++;
	 char_temp[posi]=0;
	 }
 else
	 {
	 char_temp[0]='0';
	 char_temp[1]=SEPARATE;
	 posi++;
//	 char_temp[2]=SEPARATE;
//	 posi++;
//	 char_temp[3]=0;
	 char_temp[2]=0;
	 }
 strcat(string,char_temp);
}


/**************************ʵ�ֺ���********************************************
����ԭ�ͣ�double_to_string3(int16 data, char *string)
�������ܣ���double������ת�����ַ���������ӵ�*stringָ����ַ�����ĩβ
���������double data	��Ҫת��������
		  char *string 	ָ����ת��������ַ�����ָ��
�����������
ע    �⣺��֤���ת��������ַ��������㹻����������������ӵ��ַ�����ĩβ��
		  ʹ��ǰ���ȰѴ�Ž�����ַ�������Ч���������ת�������-9999.999��9999.999֮��
		  ����0.001��������Χ�����ݲ�����ȷת��
��    �ߣ���Ƴ�
��    ����1.0
��    �ڣ�2013-11-18
*******************************************************************************/
void double_to_string3(double data,char *string)
{
 char char_temp[23];
 int32 data_temp;
 Uint8 posi=0;
 Uint8 zeroflag=0;
if(data>0)
	{
	data_temp=(int32)(data*1000);
	}
else
	{
	char_temp[0]='-';
	posi=1;
	data_temp=(int32)(data*(-1000));
	}
 char_temp[posi]=(data_temp%100000000000)/10000000000+'0';
 if(char_temp[posi]!='0')
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000000000)/1000000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000000000)/100000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100000000)/10000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000000)/1000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000000)/100000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100000)/10000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
  char_temp[posi]=(data_temp%10000)/1000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 char_temp[posi]='.';
 posi++;
 char_temp[posi]=(data_temp%1000)/100+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 char_temp[posi]=(data_temp%100)/10+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 char_temp[posi]=(data_temp%10)+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 if(zeroflag)
	 {
	 posi++;
	 char_temp[posi]=SEPARATE;
	 posi++;
//	 char_temp[posi]=SEPARATE;
//	 posi++;
	 char_temp[posi]=0;
	 }
 else
	 {
	 char_temp[0]='0';
	 char_temp[1]=SEPARATE;
	 posi++;
//	 char_temp[2]=SEPARATE;
//	 posi++;
//	 char_temp[3]=0;
	 char_temp[2]=0;
	 } 
 strcat(string,char_temp);
}



//
///**************************ʵ�ֺ���********************************************
//����ԭ�ͣ�void string_to_command(char *string,COMMAND_TypeDef *command)
//�������ܣ��������ַ����س�double����������
//���������COMMAND_TypeDef command	ָ��ת����Ľ����ָ��
//		  char *string 	ָ����Դ�ַ�����ָ��
//�����������
//��    �ߣ�Ф����
//��    ����1.0
//��    �ڣ�2013-11-19
//*******************************************************************************/
//void string_to_command(char *string,COMMAND_TypeDef *command)
//{
// double data=0,temp=0,mul=0.1;
// char cmd[4];
// char *p=string;
// Uint8 data_num_count=0;
// Uint8 signe=0;
// Uint8 string_stata=0;
// if(*p=='$')
//	{
//	  p++;
//	  while((*p>='a'&&*p<='z')||(*p>='A'&&*p<='Z'))
//		  {
//
//		  cmd[data_num_count]=*p;
//		  if(data_num_count<2)
//		  	 data_num_count++;
//			 p++;
//		  }
//		data_num_count++;
//		cmd[data_num_count]=0;
//		data_num_count=0;
//	  	if(*p==RECEIVE_SEPARATE)
//		   	 {
//			  p++;
//			  while((*p=='-')||(*p>='0'&&*p<='9')||(*p==RECEIVE_SEPARATE))
//				{
//				  signe=0;
//				  mul=0.1;
//				  data=0;
//				  temp=0;
//				  if(*p=='-')
//				  	{
//					if(string_stata==0)
//			          {
//					  signe=1;
//					  p++;
//					  }
//					else
//						return ;
//					}
//		          while(*p>='0'&&*p<='9')
//					 {
//					 temp=(double)(*p-'0');
//					 data=data*10;
//					 data=data+temp;
//					 p++;
//					 string_stata=1;
//					 }
//				 if(*p=='.')
//					{
//					if(string_stata==1)
//					  {
//					  p++;
//					  while(*p>='0'&&*p<='9')
//						 {
//						 temp=(double)(*p-'0');
//						 data=data+temp*mul;
//						 mul*=0.1;
//						 p++;
//						 }
//					  string_stata=2;
//					  }
//					else return;
//					}
//				 if(*p==RECEIVE_SEPARATE)
//					{
//					if(signe==1)
//					   data=0-data;
//
//					if(0==strcmp(cmd,"Pit"))
//						{
//						if(string_stata)
//							{
//							command->Pitch[data_num_count]=data;
//							(command->Send)|=0x20;
//							}
//						if(6>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					if(0==strcmp(cmd,"Rol"))
//						{
//						if(string_stata)
//							{
//							command->Roll[data_num_count]=data;
//						    (command->Send)|=0x40;
//							}
//						if(6>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					 if(0==strcmp(cmd,"Yaw"))
//						{
//						if(string_stata)
//							{
//							command->Yaw[data_num_count]=data;
//							(command->Send)|=0x80;
//							}
//
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					 if(0==strcmp(cmd,"Alt"))
//						{
//						if(string_stata)
//							{
//							command->Alt[data_num_count]=data;
//							(command->Send)|=0x100;
//							}
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					if(0==strcmp(cmd,"Nor"))
//						{
//						if(string_stata)
//							{
//							command->Sn[data_num_count]=data;
//							(command->Send)|=0x200;
//							}
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					if(0==strcmp(cmd,"Eas"))
//						{
//						if(string_stata)
//							{
//							command->Se[data_num_count]=data;
//							(command->Send)|=0x400;
//							}
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					 if(0==strcmp(cmd,"Ser"))
//						{
//						if(string_stata)
//							{
//							command->Ser[data_num_count]=data;
//							(command->Send)|=0x800;
//							}
//						if(2>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					  if(0==strcmp(cmd,"Sen"))
//						{
//						if(string_stata)
//							{
//							command->Send=(Uint32)data;
//							}
//				        return;
//						}
//
//					p++;
//					string_stata=0;
//					}
//				 if(*p=='*')return;
//				 }
//			 }
//
//	}
//
//}

/**************************ʵ�ֺ���********************************************
����ԭ�ͣ�string_to_one_double(char *string,double *data)
�������ܣ��ض���ʽ���ַ���ת����double������
���������double *data	ָ��ת����Ľ����ָ��
		  char *string 	ָ����Դ�ַ�����ָ��
�����������
��    �ߣ�Ф����
��    ����1.0
��    �ڣ�2013-11-26
*******************************************************************************/		
void string_to_one_double(char *string,double *data)
{
 double tempf=0;
 Uint8 bits=0;
 Uint8 signe=0;
 double mul=0.1;

 if(string[bits]=='-')
 {
  signe=1;
  bits++; 
 }
 while(string[bits]<='9'&&string[bits]>='0')
	 {
	 tempf=tempf*10+(string[bits]-'0');
	 bits++;
	 }
 if(string[bits]=='.')
 {
 bits++;
 while(string[bits]<='9'&&string[bits]>='0')
	 {
	 tempf+=mul*(string[bits]-'0');
	 mul*=0.1;
	 bits++;
	 }
 if(signe)
   *data=-tempf;	
 else
   *data=tempf;
 }
}

/**************************ʵ�ֺ���********************************************
����ԭ�ͣ�string_to_one_double(char *string,double *data)
�������ܣ��ض���ʽ���ַ���ת����int32������
���������int32 *data	ָ��ת����Ľ����ָ��
		  char *string 	ָ����Դ�ַ�����ָ��
�����������
��    �ߣ�Ф����
��    ����1.0
��    �ڣ�2013-11-26
*******************************************************************************/
void string_to_one_int32(char *string,int32 *data)
{
 double temp_32=0;
 Uint8 bits=0;
 Uint8 signe=0;
 if(string[bits]=='-')
 {
  signe=1;
  bits++; 
 }
 while(string[bits]<='9'&&string[bits]>='0')
	 {
	 temp_32=temp_32*10+(string[bits]-'0');
	 bits++;
	 }
 if(signe)
 	*data=-temp_32;
 else
  	*data=temp_32;

}
