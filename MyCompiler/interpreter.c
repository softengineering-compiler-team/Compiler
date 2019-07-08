#include "mycompiler.h"

long base(long b, long l)
{ //返回访问链的下标，b表示起始指针位置，l表示回溯次数
	long b1;
	b1 = b;
	while (l > 0)
	{
		b1 = s[b1];
		l = l - 1; //根据访问链往上回溯找到变量
	}
	return b1;
}

int main()
{
	FILE *infile = fopen("out.txt", "rb");
	long p, b, t;  // 指令计数器-,栈基址寄存器,栈顶指针
	instruction i; // instruction register
	int k = 0, kk;
	int a, j;
	int n;
	double getnum = 0;
	double tt = 1.0;
	long ls = 0;
	long away = 0;
	long adr;
	long d;
	char ch;
	printf("start PL/0\n");
	t = 0;
	b = 1;
	p = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
	fread(&code, sizeof(instruction), cxmax, infile); //instruction中 f表示操作符，l是层级，a是放置地址
	fclose(infile);
	do
	{
		if (t > stacksize)
		{
			printf("overflow running_stack\n");
			exit(0);
		}
		i = code[p];
		p = p + 1;
		switch (i.f)
		{
		case lit:
			t = t + 1;
			s[t] = i.a;
			break;
		case opr:
			switch ((long)i.a)
			{		// operator
			case 0: // return
				t = b - 1;
				p = s[t + 3];
				b = s[t + 2];
				break;
			case 1:
				s[t] = -s[t];
				break;
			case 2:
				t = t - 1;
				s[t] = s[t] + s[t + 1];
				break;
			case 3:
				t = t - 1;
				s[t] = s[t] - s[t + 1];
				break;
			case 4:
				t = t - 1;
				s[t] = s[t] * s[t + 1];
				break;
			case 5: //slash
				t = t - 1;
				s[t] = (long)s[t] / (long)s[t + 1];
				break;
			case 6:
				s[t] = (long)s[t] % 2;
				break;
			case 7:
				t--;
				break;
			case 8:
				t = t - 1;
				s[t] = (s[t] == s[t + 1]);
				break;
			case 9:
				t = t - 1;
				s[t] = (s[t] != s[t + 1]);
				break;
			case 10:
				t = t - 1;
				s[t] = (s[t] < s[t + 1]);
				break;
			case 11:
				t = t - 1;
				s[t] = (s[t] >= s[t + 1]);
				break;
			case 12:
				t = t - 1;
				s[t] = (s[t] > s[t + 1]);
				break;
			case 13:
				t = t - 1;
				s[t] = (s[t] <= s[t + 1]);
				break;
			case 14: // read
			{
				j = 0;
				getnum = 0;
				a = 0;
				t++;
				char input[128];
				int flag = 0;
				scanf("%s", input);
				int len = strlen(input);
				for (j = 0; j < len; j++)
				{
					if (input[j] == '.')
					{
						break;
					}
				}
				if (j == len)
				{
					for (j = len - 1; j >= 0; j--)
					{
						int nowdix = len - j - 1;
						long dix = pow(10, nowdix);
						getnum += dix * (input[j] - '0');
					}
				}
				else
				{
					for (a = j - 1; a >= 0; a--)
					{
						int nowdix = j - a - 1;
						double dix = pow(10, nowdix);
						getnum += dix * (input[a] - '0');
					}
					for (a = j + 1; a < len; a++)
					{
						int nowdix = j - a;
						double dix = pow(10, nowdix);
						char check = input[a];
						if (check < '0' || check > '9')
							break;
						getnum += dix * (input[a] - '0');
					}
					if (a != len - 1)
					{
						printf("Read error!\n");
						exit(0);
					}
				}
				printf("read in as：%.6lf\n", getnum);
				s[t] = getnum;
				break;
			}
			case 15:
				ch = getchar(); //读取换行符
				break;
			case 16: //write指令
			{
				double tmp = s[t];
				long tmpp = floor(tmp);
				long tmpm = ceil(tmp);
				if (tmpp != tmpm)
				{
					printf("\t%5.6lf", s[t]);
				}
				else
				{
					printf("\t%5ld", (long)s[t]);
				}
				t--;
				break;
			}
			case 17:
				printf("\n");
				break;
			case 18: //div
				t = t - 1;
				s[t] = s[t] / s[t + 1];
				break;
			case 19:
				t = t - 1;
				s[t] = (long)s[t] % (long)s[t + 1];
				break;
			case 20:
				t = t - 1;
				s[t] = (long)s[t] && (long)s[t + 1];
				break;
			case 21:
				t = t - 1;
				s[t] = (long)s[t] || (long)s[t + 1];
				break;
			case 22:
				s[t] = !(long)s[t];
				break;
			case 23:
				t++;
				break;
			case 24:
				printf("%5.2f  ", s[t]);
				t--;
				break;
			}
			break;
		case lod:
			t = t + 1;
			s[t] = s[base(b, i.l) + (long)i.a];
			break;
		case lay:
			//adr=table[i.a].drt;
			adr = 0;
			for (k = 0, d = 0; k < s[base(b, i.l) + (long)i.a + 1]; k++)
			{
				ls = s[t - (long)(s[base(b, i.l) + (long)i.a + 1] - 1) + k];
				d++;
				if (ls < s[base(b, i.l) + (long)i.a + 1 + d])
				{
					printf("array overflow\n");
					exit(0);
					break;
				}
				d++;
				if (ls > s[base(b, i.l) + (long)i.a + 1 + d])
				{
					printf("array overflow\n");
					exit(0);
					break;
				}
				if (s[base(b, i.l) + (long)i.a + 1] == 1 || k == 0)
				{ //第一维情况
					away = ls - s[base(b, i.l) + (long)i.a + 1 + 1];
				}
				else
				{
					away = away * (s[base(b, i.l) + (long)i.a + 1 + d] - s[base(b, i.l) + (long)i.a + 1 + d - 1] + 1) + ls - s[base(b, i.l) + (long)i.a + 1 + d - 1] + 1;
				}
			}
			adr = adr + away;
			t = t + 1 - s[base(b, i.l) + (long)i.a + 1];
			s[t] = s[base(b, i.l) + (long)i.a + 1 + 2 * (long)s[base(b, i.l) + (long)i.a + 1] + 1 + adr];
			break;
		case sto:
			s[base(b, i.l) + (long)i.a] = s[t];
			t = t - 1;
			break;
		case say:
			// adr=table[i.a.longnum].drt;
			adr = 0;
			away = 0;
			for (k = 0, d = 0; k < s[base(b, i.l) + (long)i.a + 1]; k++)
			{
				ls = s[t - (long)s[base(b, i.l) + (long)i.a + 1] + k];
				//ls=s[base(b,i.l)+table[i.a.longnum].addr+k];
				d++;
				if (ls < s[base(b, i.l) + (long)i.a + 1 + d])
				{
					printf("array overflow\n");
					exit(0);
					break;
				}
				d++;
				if (ls > s[base(b, i.l) + (long)i.a + 1 + d])
				{
					printf("array overflow\n");
					exit(0);
					break;
				}

				if (s[base(b, i.l) + (long)i.a + 1] == 1 || k == 0)
				{
					away = ls - s[base(b, i.l) + (long)i.a + 1 + 1];
				}
				else
				{
					away = away * (s[base(b, i.l) + (long)i.a + 1 + d] - s[base(b, i.l) + (long)i.a + 1 + d - 1] + 1) + ls - s[base(b, i.l) + (long)i.a + 1 + d - 1] + 1;
				}
			}
			adr = adr + away;
			//  t--;
			s[base(b, i.l) + (long)i.a + 1 + 2 * (long)s[base(b, i.l) + (long)i.a + 1] + 1 + adr] = s[t];
			t = t - 1 - s[base(b, i.l) + (long)i.a + 1]; //把要赋的值以及下标出栈
			break;
		case cal:					 // generate new block mark
			s[t + 1] = base(b, i.l); //将父过程基地址入栈  ,访问链
			s[t + 2] = b;			 //本过程基地址   控制链
			s[t + 3] = p;			 //返回地址
			b = t + 1;
			p = i.a;
			break;
		case Int:
			t = t + i.a;
			break;
		case jmp:
			p = i.a;
			break;
		case jpc:
			if (s[t] == 0)
			{
				p = i.a;
			}
			//t=t-1;     //实现表达式短路计算时注释掉此行，若以后函数或啥跳转出现问题在这找
			break;
		case jpq:
			if (s[t] == 1)
			{
				p = i.a;
			}
			break;
		}
	} while (p != 0);
	printf("end PL/0\n");
	system("pause");
}
