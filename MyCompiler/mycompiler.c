#include "mycompiler.h"
// pl/0 compiler with code generation
//for debug
int mycnt = 0;

void switchType(long long sym)
{
	switch (sym):
		{
		case nul:
			printf("nul");
			break;
		case ident:
			printf("ident");
			break;
		case number:
			printf("number");
			break;
		case plus:
			printf("plus");
			break;
		case minus:
			printf("minus");
			break;
		case times:
			printf("times");
			break;
		case slash:
			printf("slash");
			break;
		case oddsym:
			printf("oddsym");
			break;
		case eql:
			printf("eql");
			break;
		case neq:
			printf("neq");
			break;
		case lss:
			printf("lss");
			break;
		case leq:
			printf("leq");
			break;
		case gtr:
			printf("gtr");
			break;
		case geq:
			printf("geq");
			break;
		case lparen:
			printf("lparen");
			break;
		case rparen:
			printf("rparen");
			break;
		case comma:
			printf("comma");
			break;
		case semicolon:
			printf("semicolon");
			break;
		case period:
			printf("period");
			break;
		case becomes:
			printf("becomes");
			break;
		case beginsym:
			printf("beginsym");
			break;
		case endsym:
			printf("endsym");
			break;
		case ifsym:
			printf("ifsym");
			break;
		case thensym:
			printf("thensym");
			break;
		case whilesym:
			printf("whilesym");
			break;
		case dosym:
			printf("dosym");
			break;
		case callsym:
			printf("callsym");
			break;
		case constsym:
			printf("constsym");
			break;
		case varsym:
			printf("varsym");
			break;
		case procsym:
			printf("procsym");
			break;
		case typesym:
			printf("typesym");
			break;
		case arraysym:
			printf("arraysym");
			break;
		case ofsym:
			printf("ofsym");
			break;
		case intersym:
			printf("intersym");
			break;
		case realsym:
			printf("realsym");
			break;
		case Boolsym:
			printf("Boolsym");
			break;
		case funcsym:
			printf("funcsym");
			break;
		case elsesym:
			printf("elsesym");
			break;
		case writesym:
			printf("writesym");
			break;
		case readsym:
			printf("readsym");
			break;
		case exitsym:
			printf("exitsym");
			break;
		case or:
			printf("or");
			break;
		case and:
			printf("and");
			break;
		case not:
			printf("not");
			break;
		case div:
			printf("div");
			break;
		case mod:
			printf("mod");
			break;
		case truesym:
			printf("truesym");
			break;
		case falsesym:
			printf("falsesym");
			break;
		case lmparen:
			printf("lmparen");
			break;
		case rmparen:
			printf("rmparen");
			break;
		case typeerror:
			printf("typeerror");
			break;
		case voiderror:
			printf("voiderror");
			break;
		case dotdot:
			printf("dotdot");
			break;
		default:
			break;
		}
	return;
}

void Tableprint(int i)
{
	printf("\nNow printing table[%d]:\n", i);
	printf("\t.name =\t\t%s\n", table[i].name);
	printf("\t.kind =\t\t");
	switch (table[i].kind):
		{
		case constant:
			puts("constant");
			break;
		case variable:
			puts("variable");
			break;
		case proc:
			puts("procedure");
			break;
		case type:
			puts("type");
			break;
		case func:
			puts("function");
			break;
		}
	printf("\t.val =\t\t%.6lf\n", table[i].val);
	printf("\t.level =\t%ld\n", table[i].level);
	printf("\t.addr =\t\t%ld\n", table[i].addr);
	printf("\t.funcaddr =\t%ld\n", table[i].funcaddr);
	int j = 0;
	printf("\t.paral[] =\n");
	while (table[i].paral[j] != NULL)
	{
		printf("\t\t%d =\t", j);
		switchType(table[i].paral[j]);
		puts("");
		j++;
	}
	printf("\t.type1 =\t");
	switchType(table[i].type1);
	puts("");
	printf("\t.size =\t\t%ld\n", table[i].size);
	printf("\t.drt =\t\t%ld\n", table[i].drt);
	printf("\t.low[] =\n\t\t");
	j = 0;
	while (table[i].low[j] != NULL)
	{
		printf("%ld\t", table[i].low[j]);
		j++;
	}
	puts("");
	printf("\t.high[] =\n\t\t");
	j = 0;
	while (table[i].high[j] != NULL)
	{
		printf("%ld\t", table[i].high[j]);
		j++;
	}
	puts("");
	printf("\t.type2 =\t\t");
	switchType(table[i].type2);
	puts("");
	printf("\t.n =\t\t%d\n", table[i].n);
	return;
}
//debug code end

void error(long n) // show error code
{
	long i;
	printf(" ****");
	for (i = 1; i <= cc - 1; i++)
		printf(" ");
	printf("^%2d\n", n);
	err++;
}

void init() // first init
{
	long i;
	for (i = 0; i < 256; i++)
		ssym[i] = nul;
	for (i = 0; i < norw; i++)
		wsym[i] = nul;
	strcpy(word[0], "Boolean   ");
	strcpy(word[1], "and       ");
	strcpy(word[2], "array     ");
	strcpy(word[3], "begin     ");
	strcpy(word[4], "call      ");
	strcpy(word[5], "const     ");
	strcpy(word[6], "div       ");
	strcpy(word[7], "do        ");
	strcpy(word[8], "else      ");
	strcpy(word[9], "end       ");
	strcpy(word[10], "exit      ");
	strcpy(word[11], "false     ");
	strcpy(word[12], "function  ");
	strcpy(word[13], "if        ");
	strcpy(word[14], "integer   ");
	strcpy(word[15], "mod       ");
	strcpy(word[16], "not       ");
	strcpy(word[17], "odd       ");
	strcpy(word[18], "of        ");
	strcpy(word[19], "or        ");
	strcpy(word[20], "procedure ");
	strcpy(word[21], "read      ");
	strcpy(word[22], "real      ");
	strcpy(word[23], "then      ");
	strcpy(word[24], "true      ");
	strcpy(word[25], "type      ");
	strcpy(word[26], "var       ");
	strcpy(word[27], "while     ");
	strcpy(word[28], "write     ");
	strcpy(mnemonic[lit], "lit");
	strcpy(mnemonic[opr], "opr");
	strcpy(mnemonic[lod], "lod");
	strcpy(mnemonic[sto], "sto");
	strcpy(mnemonic[cal], "cal");
	strcpy(mnemonic[Int], "int");
	strcpy(mnemonic[jmp], "jmp");
	strcpy(mnemonic[jpc], "jpc");
	strcpy(mnemonic[say], "say"); //数组的存指令
	strcpy(mnemonic[lay], "lay"); //数组的取指令
	strcpy(mnemonic[jpq], "jpq");
	wsym[0] = Boolsym;
	wsym[1] = and;
	wsym[2] = arraysym;
	wsym[3] = beginsym;
	wsym[4] = callsym;
	wsym[5] = constsym;
	wsym[6] = div;
	wsym[7] = dosym;
	wsym[8] = elsesym;
	wsym[9] = endsym;
	wsym[10] = exitsym;
	wsym[11] = falsesym;
	wsym[12] = funcsym;
	wsym[13] = ifsym;
	wsym[14] = intersym;
	wsym[15] = mod;
	wsym[16] = not;
	wsym[17] = oddsym;
	wsym[18] = ofsym;
	wsym[19] = or ;
	wsym[20] = procsym;
	wsym[21] = readsym;
	wsym[22] = realsym;
	wsym[23] = thensym;
	wsym[24] = truesym;
	wsym[25] = typesym;
	wsym[26] = varsym;
	wsym[27] = whilesym;
	wsym[28] = writesym;
	ssym['+'] = plus;
	ssym['-'] = minus;
	ssym['*'] = times;
	ssym['/'] = slash;
	ssym['('] = lparen;
	ssym[')'] = rparen;
	ssym[','] = comma;
	ssym['.'] = period;
	ssym[';'] = semicolon;
	ssym['['] = lmparen;
	ssym[']'] = rmparen;

	declbegsys = constsym | typesym | varsym | procsym | funcsym;
	statbegsys = beginsym | callsym | ifsym | whilesym | exitsym | writesym | readsym;
	facbegsys = ident | intersym | realsym | lparen | not | truesym | falsesym;
}

void getch() //read in one char
{
	if (cc == ll)
	{
		if (feof(infile))
		{
			printf("************************************\n");
			printf("      program incomplete\n");
			printf("************************************\n");
			exit(1);
		}
		ll = 0;
		cc = 0;
		printf("%5d ", cx);
		while ((!feof(infile)) && ((ch = getc(infile)) != '\n'))
		{
			printf("%c", ch);
			ll = ll + 1;
			line[ll] = ch;
		}
		printf("\n");
		ll = ll + 1;
		line[ll] = ' ';
	}
	cc = cc + 1;
	ch = line[cc];
}

void getsym() //get one word and init its word type(sym)
{
	long i, j, k;
	int flag = 0;
	double t = 1.0;			//标记小数点后的位数
	double numt = 0, z = 0; //小数部分的值
	while (ch == ' ' || ch == '\t')
		getch();
	if (isalpha(ch)) // identified or reserved  开始进行词法分析
	{
		k = 0;
		do
		{
			if (k < al)
			{
				a[k] = ch;
				k = k + 1;
			}
			getch();
		} while (isalpha(ch) || isdigit(ch));
		if (k >= kk)
			kk = k;
		else
		{
			do
			{
				kk = kk - 1;
				a[kk] = ' ';
			} while (k < kk);
		}
		strcpy(id, a);
		i = 0;
		j = norw - 1; //把符号串（如var）放入id中
		do
		{ // 二分查找 保留字
			k = (i + j) / 2;
			if (strcmp(id, word[k]) <= 0)
				j = k - 1;
			if (strcmp(id, word[k]) >= 0)
				i = k + 1;
		} while (i <= j); //此循环用于在保留字符表中找到对应的保留字
		if (i - 1 > j)
			sym = wsym[k]; //  sym返回词法单元的类型 如果i-1 > j是保留字
		else
			sym = ident; //否则是定义的标识符
	}
	else if (isdigit(ch))
	{ // number
		k = 0;
		num = 0;
		do
		{
			num = num * 10 + (ch - '0');
			k = k + 1;
			getch();
		} while (isdigit(ch));
		if (ch == '.')
		{ //遇到小数点说明是实型数据
			getch();
			if (isdigit(ch))
			{
				while (isdigit(ch))
				{
					t /= 10;
					num = num + (ch - '0') * t;
					k++;
					getch();
				}
				sym = realsym;
			}
			else if (ch == '.')
			{ //又遇到一个点说明是数组的定义
				sym = intersym;
				cc = cc - 2;
			}
			else
				error(57);
		}
		else
			sym = intersym;
		if (k > nmax)
			error(31);
	}
	else if (ch == ':')
	{
		getch();
		if (ch == '=')
		{
			sym = becomes;
			getch();
		}
		else
			sym = nul;
	}
	else if (ch == '/') // 开头为"/"的注释情况
	{
		getch();	   //取词
		if (ch == '*') // "/*"开头
		{
			while (1)
			{
				getch();
				if (ch != '*') // 不为"*"的时候循环取词
					continue;
				else // 为"*"的时候判断"/"符号
				{
					getch();
					if (ch == '/') // /**/注释完整则break
						break;
					else
						continue;
				}
			}
			getch();
			getsym();
		}
		else if (ch == '/') // "//"开头
		{
			cc = ll; //将本行长度赋给当前值，相当于注释掉当前行
			getch();
			getsym();
		}
		else
		{
			sym = ssym[(unsigned char)'/'];
		}
	}
	else if (ch == '*') // "*"开头
	{
		getch();	   //取词
		if (ch == '/') //与上方类似
		{
			getch();
			if (ch == '*')
			{
				sym = ssym[(unsigned char)'*'];
				while (1)
				{
					getch();
					if (ch != '*')
						continue;
					else
					{
						getch();
						if (ch == '/')
							break;
						else
							continue;
					}
				}
				getch();
			}
			else if (ch == '/')
			{
				cc = ll;
				sym = ssym[(unsigned char)'*'];
				getch();
			}
			else
				printf("'*/'not match\n");
		}
		else
			sym = ssym[(unsigned char)'*'];
	}
	else if (ch == '<')
	{
		getch();
		if (ch == '=')
		{
			sym = leq;
			getch();
		}
		else if (ch == '>')
		{
			sym = neq;
			getch();
		}
		else
			sym = lss;
	}
	else if (ch == '>')
	{
		getch();
		if (ch == '=')
		{
			sym = geq;
			getch();
		}
		else
			sym = gtr;
	}
	else if (ch == '=')
	{
		getch();
		if (ch == '=')
			getch();
		sym = eql;
	}
	else if (ch == '.')
	{
		getch();
		if (ch == '.')
		{
			sym = dotdot;
			getch();
		}
		else
			sym = period;
	}
	else
	{
		sym = ssym[(unsigned char)ch];
		getch();
	}
}

void gen(enum fct x, long y, double z) // generate inner code
{
	if (cx > cxmax)
	{
		printf("program too long\n");
		exit(1);
	}
	code[cx].f = x;
	code[cx].l = y;
	code[cx].a = z;
	cx = cx + 1;
}

void test(long long s1, long long s2, long n) // test now error and show it
{
	if (!(sym & s1))
	{
		error(n);
		s1 = s1 | s2;
		while (!(sym & s1))
		{
			getsym();
		}
	}
}

void enter(enum object k) // enter object into table
{
	tx = tx + 1;
	strcpy(table[tx].name, id);
	table[tx].kind = k;
	switch (k):
		{
		case constant:
			if (num > amax)
			{
				error(31);
				num = 0;
			}
			table[tx].val = num;
			table[tx].type1 = sym; //记录Const的类型，int or real
			break;
		case variable:
			table[tx].level = lev;
			table[tx].addr = dx;
			dx = dx + 1;
			break;
		case proc:
			table[tx].level = lev;
			dx = dx + 1;
			break;
		case type:
			table[tx].level = lev;
			table[tx].type1 = sym;
			break;
		case func:
			table[tx].level = lev;
			table[tx].funcaddr = dx;
			dx = dx + 1;
			break;
		}
}

long position(char *id) // find identifier id in table
{
	long i;
	strcpy(table[0].name, id);
	i = tx;
	while (strcmp(table[i].name, id) != 0)
		i = i - 1;
	return i;
}

void constdeclaration() // const type prasing
{
	if (sym == ident)
	{
		getsym(); // 获取单词const之后单词的类型
		if (sym == eql || sym == becomes)
		{
			if (sym == becomes)
				error(1);
			getsym();
			if (sym == intersym || sym == realsym)
			{
				enter(constant);
				getsym();
			}
			else
				error(2);
		}
		else
			error(3);
	}
	else
		error(4);
}

void vardeclaration() // var type prasing
{
	long i;
	int identnum = 0;		 //同类型的变量个数
	char sameid[10][al + 1]; //存放同类型的变量的名字
	long size;
	int j;
	int k = 0;
	int t;
	if (sym == ident)
	{
		identnum++;
		strcpy(sameid[k], id);
		getsym();
		while (sym == comma)
		{
			getsym();
			if (sym == ident)
			{
				for (j = 0; j < identnum; j++)
				{
					if (strcmp(sameid[j], id) == 0)
					{
						error(48); //检查变量是否重复声明
						break;
					}
				}
				identnum++;
				k++;
				strcpy(sameid[k], id);
				getsym();
			}
		}
		if (sym == nul) //说明遇到：后面应该是指示变量的类型
		{
			getsym();
			if (sym == intersym || sym == realsym || sym == Boolsym)
			{
				for (j = 0, k = 0; j < identnum; j++) //之前的变量全部是相同的类型
				{
					strcpy(id, sameid[k]);
					enter(variable);
					table[tx].type1 = sym;
					k++;
				}
			}
			else if (sym == ident)
			{
				i = position(id); //在符号表中找到 标识符 的位置 返给下表付给i
				if (i == 0)
					error(11);
				sym = table[i].type1;
				if (sym == intersym || sym == realsym || sym == Boolsym)
				{
					for (j = 0, k = 0; j < identnum; j++) //之前的变量全部是相同的类型
					{
						strcpy(id, sameid[k]);
						enter(variable);
						k++;
						table[tx].type1 = sym;
					}
				}
				else if (sym == arraysym)
				{
					for (j = 0; j < identnum; j++) //之前的变量全部是相同的类型
					{
						strcpy(id, sameid[j]);
						enter(variable);
						table[tx].type1 = arraysym;
						table[tx].drt = table[i].drt;
						table[tx].size = table[i].size;
						size = table[tx].size;
						for (t = 1; t <= table[tx].drt; t++)
						{
							table[tx].low[t] = table[i].low[t];
							table[tx].high[t] = table[i].high[t];
						}
						sym = table[i].type2;
						table[tx].type2 = sym;
						dx = dx + 2 * table[i].drt + 1; //存放上下界的空间
						dx += size;
					}
				}
			}
			else
				error(36);
			getsym();
		}
		else
			error(55);
	}
	else
		error(4);
}

void typeexpression()
{
	long long sym1;
	long bottom, upper, size;
	long tx1;
	int drtnum = 1;
	int j;
	if (sym == intersym || sym == realsym || sym == Boolsym)
	{
		enter(type);
		getsym();
	}
	else if (sym == arraysym)
	{
		sym1 = sym;
		getsym();
		if (sym == lmparen) // [
		{
			getsym();
			if (sym == intersym)
			{
				bottom = num;
				getch();
				getsym();
				if (sym == dotdot) // ..
				{
					getsym();
					sym = sym1;
					upper = num;
					size = upper - bottom + 1;
					enter(type);
					table[tx].low[drtnum] = bottom;
					table[tx].high[drtnum] = upper;
					table[tx].drt++;
					getsym();
					if (sym != rmparen)
						error(101);
					getsym();
					if (sym != ofsym)
						error(102);
					else
					{
						getsym();
						if (sym == intersym || sym == realsym || sym == Boolsym)
						{
							table[tx].type2 = sym; // type2 中存储了数组中变量的类型
							table[tx].drt = 1;
							table[tx].size = size;
						}
						else
						{
							while (sym == arraysym)
							{ //多维数组开辟
								table[tx].drt++;
								drtnum++;
								getsym();
								if (sym == lmparen) // [
								{
									getsym(); // a
									table[tx].low[drtnum] = num;
									getch();
									getsym(); // ..
									getsym(); // b
									table[tx].high[drtnum] = num;
									getsym(); // ]
									getsym(); // of
									getsym(); // array member type;
									size = size * (table[tx].high[drtnum] - table[tx].low[drtnum] + 1);
								}
								else
									error(34);
								table[tx].size = size;
							}
							if (sym == intersym || sym == realsym || sym == Boolsym)
								table[tx].type2 = sym;
						}
						getsym();
					}
				}
				else
					error(34);
			}
			else
				error(34);
		}
		else
			error(34);
	}
	else
		error(33);
}

void typedeclaration()
{
	char typename[al + 1];
	if (sym == ident)
	{
		strcpy(typename, id);
		getsym();
		if (sym == eql || sym == becomes)
		{
			if (sym == becomes)
				error(1);
			getsym();
			strcpy(id, typename); // type类型的标识符名称传入
			typeexpression();
		}
		else
			error(3);
	}
	else
		error(4);
}

void listcode(long cx0) // list code generated for this block
{
	long i;
	for (i = cx0; i <= cx - 1; i++)
		printf("%10d%5s%3d%10.5lf\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
}

void arraydo(enum fct x, int i)
{
	long d, t;
	switch (x):
		{
		case sto:
			gen(lit, 0, table[i].drt);
			gen(sto, lev - table[i].level, table[i].addr + 1);
			for (t = 1, d = 1; t <= table[i].drt; t++)
			{ //产生指令存入array上下界和维数
				d++;
				gen(lit, 0, table[i].low[t]);
				gen(sto, lev - table[i].level, table[i].addr + d);
				d++;
				gen(lit, 0, table[i].high[t]);
				gen(sto, lev - table[i].level, table[i].addr + d);
			}
			gen(say, lev - table[i].level, table[i].addr); // 存入数组
			break;
		case lod:
			gen(lit, 0, table[i].drt);
			gen(sto, lev - table[i].level, table[i].addr + 1);
			for (t = 1, d = 1; t <= table[i].drt; t++)
			{ //产生指令存入array上下界和维数
				d++;
				gen(lit, 0, table[i].low[t]);
				gen(sto, lev - table[i].level, table[i].addr + d);
				d++;
				gen(lit, 0, table[i].high[t]);
				gen(sto, lev - table[i].level, table[i].addr + d);
			}
			gen(lay, lev - table[i].level, table[i].addr); // 取出数组
			break;
		}
}

void factor(long long fsys)
{
	long i, j, k;
	long drtnum, away;
	test(facbegsys, fsys, 24); // 测试传入指令是否含有表达式（factor）起始符
	while (sym & facbegsys)
	{
		if (sym == ident)
		{
			i = position(id);
			if (i == 0)
				error(11);
			else
			{
				switch (table[i].kind):
					{
					case constant: //对于const 生成中间代码
					{
						gen(lit, 0, table[i].val);
						lastsym = table[i].type1;
						getsym();
						break;
					}
					case variable: //对于 var 生成中间代码
					{
						// 当 var 类型是 int real 或 Boolean时
						long long type = table[i].type1;
						if (type == intersym || type == realsym || type == Boolsym)
						{
							gen(lod, lev - table[i].level, table[i].addr); // lod lev,addr 中间代码，相当于将 var 的值装入栈顶
							lastsym = type;
							getsym();
						}
						else
						{ // var 类型是 array时
							if (type == arraysym)
							{ //数组类型
								away = 0;
								getsym();
								for (j = 0; j < table[i].drt; j++)
								{
									if (sym == lmparen)
									{
										getsym();
										condition(fsys | rmparen);
										if (lastsym != intersym)
										{
											lastsym = typeerror;
											error(49);
										}
										if (sym == rmparen)
											getsym();
										else
											error(40);
									}
									else
										error(46);
								}
								if (lastsym != typeerror)
									lastsym = table[i].type2;
								arraydo(lod, i);
							}
						}
						break;
					}
					case proc:
						error(21);
						break;

					case func:
						getsym();
						k = 0;
						if (sym == lparen) // 有参数
						{
							getsym();
							condition(fsys | comma | rparen);
							if (lastsym != table[i].paral[k])
							{
								error(49);
								lastsym = typeerror;
							}
							while (sym == comma)
							{
								k++;
								getsym();
								condition(fsys | comma | rparen);
								if (lastsym != table[i].paral[k])
								{
									error(49);
									lastsym = typeerror;
								}
							}
							if (sym == rparen) // )
							{
								gen(cal, lev - table[i].level, table[i].addr);
								getsym();
							}
							for (k = 0; k < table[i].n; k++)
							{
								gen(opr, 0, 7); //把实参弹出
							}
							gen(lod, lev - table[i].level, table[i].funcaddr);
							if (lastsym != typeerror)
								lastsym = table[i].type1;
						}
						else if (sym == becomes)
						{ // 返回语句
							// 返回值放到栈顶
							gen(lod, lev - table[i].level, table[i].funcaddr);
							lastsym = table[i].type1;
						}
						else
						{ // 无参函数
							gen(cal, lev - table[i].level, table[i].addr);
							gen(lod, lev - table[i].level, table[i].funcaddr);
							lastsym = table[i].type1;
						}
						break;
					}
			}
		}
		else if (sym == intersym || sym == realsym) // 对于 int or real类型的 单词 进行装入
		{
			if (num > amax)
			{
				error(31);
				num = 0;
			}
			gen(lit, 0, num);
			lastsym = sym;
			getsym();
		}
		else if (sym == not)
		{
			getsym();
			factor(fsys);
			gen(opr, 0, 22);
		}
		else if (sym == truesym)
		{
			gen(lit, 0, 1);
			lastsym = Boolsym;
			getsym();
		}
		else if (sym == falsesym)
		{
			gen(lit, 0, 0);
			lastsym = Boolsym;
			getsym();
		}
		else if (sym == lparen)
		{
			getsym();
			condition(rparen | fsys);
			if (sym == rparen)
				getsym();
			else
				error(22);
		}
		test(fsys, lparen, 23);
	}
}

void term(long long fsys)
{
	long long mulop;
	long long lasttype;
	long cx1, cx2;

	factor(fsys | times | slash | div | mod | and); //表达式判断
	lasttype = lastsym;
	while (sym == times || sym == slash || sym == div || sym == mod || sym == and)
	{
		mulop = sym;
		getsym();
		if (mulop == and)
		{
			cx1 = cx;
			gen(jpc, 0, 0); // 对于布尔值and操作，记录当前程序栈顶并生成逻辑判断回路跳转
		}
		factor(fsys | times | slash | div | mod | and); //表达式判断
		if (mulop == times)
		{ // 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 *
			//gen(opr, 0, 4);
			if (lastsym == intersym && lasttype == intersym)
				lastsym = intersym;
			else if (lastsym == intersym && lasttype == realsym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == intersym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == realsym)
				lastsym = realsym;
			else
			{
				lastsym = typeerror;
				error(50); // 非数字相乘 错误
			}
			gen(opr, 0, 4); //中间代码
		}
		else if (mulop == slash)
		{ // 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 /
			//gen(opr, 0, 5);
			if (lastsym == intersym && lasttype == intersym)
				lastsym = intersym;
			else if (lastsym == intersym && lasttype == realsym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == intersym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == realsym)
				lastsym = realsym;
			else
			{
				lastsym = typeerror;
				error(50); // 非数字相除 错误
			}
			gen(opr, 0, 5); //中间代码
		}
		else if (mulop == div)
		{ // 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 div
			//gen(opr, 0, 18);
			if (lastsym == intersym && lasttype == intersym)
				lastsym = intersym;
			else if (lastsym == intersym && lasttype == realsym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == intersym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == realsym)
				lastsym = realsym;
			else
			{
				lastsym = typeerror;
				error(50); // 非数字相 整除 错误
			}
			gen(opr, 0, 18); //中间代码
		}
		else if (mulop == mod)
		{ // 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 mod
			//gen(opr, 0, 19);
			if (lastsym == intersym && lasttype == intersym)
				lastsym = intersym;
			else
			{
				lastsym = typeerror;
				error(50); // 非整数 mod 错误
			}
			gen(opr, 0, 19); //中间代码
		}
		else if (mulop == and)
		{
			if (lastsym == Boolsym && lastsym == Boolsym)
				lastsym = Boolsym;
			else
			{
				lastsym = typeerror;
				error(50); // 只有Boolean类型可and
			}
			//and 短路计算，如果有假则直接跳转到factor执行
			gen(opr, 0, 20);
			cx2 = cx;
			gen(jmp, 0, 0);
			code[cx1].a = cx;
			gen(lit, 0, 0);
			code[cx2].a = cx;
			//记录当前cx位置
		}
	}
}

void expression(long long fsys) // + - or
{
	long long addop;
	long long lasttype;
	long cx1, cx2;
	if (sym == plus || sym == minus)
	{
		addop = sym;
		getsym();
		term(fsys | plus | minus | or);
		if (addop == minus)
			gen(opr, 0, 1);
	}
	else
		term(fsys | plus | minus | or);
	while (sym == plus || sym == minus || sym == or)
	{
		addop = sym;
		getsym();
		lasttype = lastsym;
		if (addop == or)
		{
			cx1 = cx;
			gen(jpq, 0, 0); //or 指令相关跳转
		}
		term(fsys | plus | minus | or);
		if (addop == plus)
		{ // 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 +
			//gen(opr, 0, 2);
			if (lastsym == intersym && lasttype == intersym)
				lastsym = intersym;
			else if (lastsym == intersym && lasttype == realsym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == intersym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == realsym)
				lastsym = realsym;
			else
			{
				lastsym = typeerror;
				error(50); // 非数字相加 错误
			}
			gen(opr, 0, 2); //中间代码
		}
		else if (addop == minus)
		{ // 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 -
			//gen(opr, 0, 3);
			if (lastsym == intersym && lasttype == intersym)
				lastsym = intersym;
			else if (lastsym == intersym && lasttype == realsym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == intersym)
				lastsym = realsym;
			else if (lastsym == realsym && lasttype == realsym)
				lastsym = realsym;
			else
			{
				lastsym = typeerror;
				error(50); // 非数字相减 错误
			}
			gen(opr, 0, 3); //中间代码
		}
		else
		{ // or
			if (lastsym == lasttype && lastsym == Boolsym)
				lastsym = Boolsym;
			else
			{
				lastsym = typeerror;
				error(50);
			}
			gen(opr, 0, 21);
			cx2 = cx;
			gen(jmp, 0, 0);
			code[cx1].a = cx;
			gen(lit, 0, 1);
			code[cx2].a = cx;
			//or记录当前cx
		}
	}
}

void condition(long long fsys) // odd = != < > <= >= , ) ]
{
	long long relop;
	long long lasttype;
	if (sym == oddsym) // odd
	{
		getsym();
		expression(fsys);
		if (lastsym = intersym)
			lastsym = Boolsym;
		else
		{
			lastsym = typeerror;
			error(50);
		}
		gen(opr, 0, 6);
	}
	else
		expression(fsys | eql | neq | lss | gtr | leq | geq | comma | rparen | rmparen);
	if (sym & (eql | neq | lss | gtr | leq | geq))
	{
		relop = sym;
		getsym();
		lasttype = lastsym;
		expression(fsys);
		if (lasttype == intersym && lastsym == intersym)
			lastsym = Boolsym;
		else if (lasttype == intersym && lastsym == realsym)
			lastsym = Boolsym;
		else if (lasttype == realsym && lastsym == realsym)
			lastsym = Boolsym;
		else if (lasttype == realsym && lastsym == intersym)
			lastsym = Boolsym;
		else if (lasttype == Boolsym && lastsym == Boolsym)
			lastsym = Boolsym;
		else
		{
			lastsym = typeerror;
			error(50);
		}
		switch (relop)
		{
		case eql:
			gen(opr, 0, 8);
			break;
		case neq:
			gen(opr, 0, 9);
			break;
		case lss:
			gen(opr, 0, 10);
			break;
		case geq:
			gen(opr, 0, 11);
			break;
		case gtr:
			gen(opr, 0, 12);
			break;
		case leq:
			gen(opr, 0, 13);
			break;
		}
	}
}

void statement(long long fsys) // 程序控制流程
{
	long i, cx1, cx2;
	long long lasttype;
	long num1[now];
	int drtnum = 0;
	long away = 0;
	long ii;
	if (sym == ident)
	{
		i = position(id);
		if (table[i].type1 == arraysym)
		{
			getsym();
			for (ii = 0; ii < table[i].drt; ii++)
			{
				if (sym == lmparen)
				{
					getsym();
					condition(fsys | rmparen);
					if (lastsym != intersym)
						error(46);
					lasttype = lastsym;
					if (sym == rmparen)
						getsym();
				}
				else
					error(46);
			}
			lasttype = table[i].type2; // 数组元素的类型
		}
		else
		{
			lasttype = table[i].type1;
			getsym();
		} //非数组元素类型存在.type1
		if (sym == becomes)
			getsym();
		else
			error(13);
		condition(fsys);
		if (lasttype == intersym && lastsym == intersym)
			lastsym = voiderror;
		else if (lasttype == intersym && lastsym == realsym)
			lastsym = voiderror;
		else if (lasttype == realsym && lastsym == realsym)
			lastsym = voiderror;
		else if (lasttype == realsym && lastsym == intersym)
			lastsym = voiderror;
		else if (lasttype == Boolsym && lasttype == lastsym)
			lastsym = voiderror;
		else
		{
			lastsym = typeerror;
			error(50);
		}
		if (i != 0)
		{
			//gen(sto, lev - table[i].level, table[i].addr);
			switch (table[i].kind):
				{
				case variable:
					if (table[i].type1 == intersym || table[i].type1 == realsym)
						gen(sto, lev - table[i].level, table[i].addr);
					else if (table[i].type1 = arraysym)
						arraydo(sto, i);
					break;
				case func:
					gen(sto, lev - table[i].level, table[i].funcaddr);
					break;
				case type:
				{
					error(56);
					break;
				}
				default:
					break;
				}
		}
	}
	else if (sym == callsym)
	{
		int k = 0;
		getsym();
		if (sym != ident)
			error(14);
		else
		{
			i = position(id);
			if (i == 0)
				error(11);
			else if (table[i].kind == proc)
			{
				getsym();
				if (sym == lparen) //有参数
				{
					do
					{
						getsym();
						condition(fsys | comma | rparen);
						k++;
					} while (sym == comma);
					if (sym == rparen)
						getsym();
					else
						error(40);
					if (k != table[i].n)
					{
						printf("Parameter counts not match\n");
						error(41);
					}
					gen(cal, lev - table[i].level, table[i].addr);
					for (k = 0; k < table[i].n; k++)
						gen(opr, 0, 7); //实参弹入栈
					if (sym == funcsym)
						gen(lod, lev - table[i].level, table[i].addr);
					// 返回值入栈
				}
				else //无参数
					gen(cal, lev - table[i].level, table[i].addr);
			}
			else
				error(15);
		}
	}
	else if (sym == ifsym)
	{
		getsym();
		condition(fsys | thensym | dosym);
		if (lastsym != Boolsym)
		{
			lastsym = typeerror;
			error(52);
		}
		if (sym == thensym)
			getsym();
		else
			error(16);
		cx1 = cx; //cx1指向当前代码位置
		gen(jpc, 0, 0);
		statement(fsys | semicolon | endsym | elsesym);
		if (sym == semicolon)
			getsym();
		if (sym == elsesym)
		{
			getsym();
			cx2 = cx;
			gen(jmp, 0, 0);
			code[cx1].a = cx;
			statement(fsys | semicolon | endsym);
			code[cx2].a = cx;
		}
		else
		{
			code[cx1].a = cx;
			statement(fsys | semicolon | endsym);
		}
	}
	else if (sym == elsesym)
	{
		getsym();
		statement(fsys | semicolon | endsym);
	}
	else if (sym == beginsym)
	{
		getsym();
		statement(fsys | semicolon | endsym);
		while (sym == semicolon || (sym & statbegsys))
		{
			if (sym == semicolon)
				getsym();
			else
				error(10);
			statement(fsys | semicolon | endsym);
		}
		if (sym == endsym)
			getsym();
		else
			error(17);
	}
	else if (sym == whilesym)
	{
		whilenum++;
		cx1 = cx;
		getsym();
		condition(fsys | dosym);
		if (lastsym != Boolsym)
		{
			lastsym = typeerror;
			error(52);
		}
		cx2 = cx;
		gen(jpc, 0, 0);
		if (sym == dosym)
			getsym();
		else
			error(18);
		statement(fsys);
		gen(jmp, 0, cx1);
		code[cx2].a = cx;
		if (exitcx != 0)
		{
			code[exitcx].a = cx;
			exitcx = 0;
		}
		whilenum--;
	}
	else if (sym == exitsym)
	{
		if (whilenum == 0)
			error(47);
		else
		{
			exitcx = cx;
			gen(jmp, 0, 0);
		}
		getsym();
	}
	else if (sym == writesym)
	{
		getsym();
		if (sym == lparen)
		{
			do
			{
				getsym();
				condition(fsys | rparen | comma);
				if (lastsym != intersym && lastsym != realsym && lastsym != constsym)
				{
					lastsym = typeerror;
					error(53);
				}

				if (lastsym == intersym)
					gen(opr, 0, 16); // write(int)
				else if (lastsym == realsym)
					gen(opr, 0, 24); // write(real)
			} while (sym == comma);
			if (sym != rparen)
				error(35);
			else
				getsym();
			gen(opr, 0, 17); // write(/n)
		}
		else
			error(35);
	}
	else if (sym == readsym)
	{
		getsym();
		if (sym != lparen)
			error(35);
		else
		{
			//while内获取括号内变量，有逗号则继续获取
			while (1)
			{
				getsym();
				if (sym == ident)
					i = position(id);
				else
					i = 0;
				if (i == 0)
					error(36);
				else
				{
					if (table[i].kind == proc || table[i].kind == func || table[i].kind == constant || table[i].type1 == Boolsym)
					{
						error(12);
						i = 0;
					}
					else if (table[i].type1 == realsym || table[i].type1 == intersym)
					{
						gen(opr, 0, 14);
						gen(sto, lev - table[i].level, table[i].addr);
					}
					else if (table[i].type1 == arraysym && (table[i].type2 & (intersym | realsym)))
					{
						getsym();
						for (ii = 0; ii < table[i].drt; ii++) //drt数组维度
						{
							if (sym == lmparen)
							{
								getsym();
								condition(fsys | rmparen);
								if (lastsym != intersym)
								{
									lastsym = typeerror;
									error(46);
								}
								if (sym == rmparen)
								{
									if (ii != table[i].drt - 1)
										getsym();
								}
							}
							else
								error(46);
						}
						gen(opr, 0, 14);
						arraydo(sto, i);
					} //read数组函数位置
					else
						error(39);
				}
				getsym();
				if (sym == comma)
				{
					continue;
				}
				else
				{
					break;
				}
			}
			gen(opr, 0, 15); //获取回车
			if (sym == rparen)
			{
				getsym();
			}
		}
	}
	test(fsys, 0, 19);
}

void block(long long fsys) // 程序 -> 分程序
{
	long i, j, k;
	long tx0; // initial table index
	long cx0; // initial code index
	long tx1; // save current table index before processing nested procedures
	long dx1; // save data allocation index
	long tx2;

	dx = 3;
	tx0 = tx;
	table[tx].addr = cx;
	gen(jmp, 0, 0);
	table[tx].n = prodn;
	for (j = 0; j < prodn; j++)
	{
		tx++;
		strcpy(table[tx].name, pnow[j].id);
		table[tx].kind = variable;
		table[tx].level = lev;
		table[tx].addr = dx;
		table[tx].type1 = pnow[j].sym;
		dx++;
	}
	tx2 = tx;
	if (lev > levmax)
		error(32);
	do
	{
		if (sym == constsym)
		{
			getsym();
			do
			{
				constdeclaration(); // 定义 const 量
				while (sym == comma)
				{
					getsym();
					constdeclaration();
				}
				if (sym == semicolon)
					getsym();
				else
					error(5);
			} while (sym == ident);
		}
		if (sym == typesym)
		{
			getsym();
			do
			{
				typedeclaration();
				if (sym == semicolon)
					getsym();
				else
					error(33);
			} while (sym == ident);
		}
		if (sym == varsym)
		{
			getsym();
			do
			{
				vardeclaration();
				if (sym == semicolon)
					getsym();
				else
					error(5);
			} while (sym == ident);
		}
		while (sym == procsym || sym == funcsym) // function and procedure
		{
			prodn = 0;
			if (sym == procsym)
			{
				getsym();
				if (sym == ident) // procedure name
				{
					enter(proc);
					getsym();
				}
				else
					error(4);
				if (sym == semicolon)
					getsym();
				else if (sym == lparen) // ( 有参数
				{
					getsym();
					while (sym == ident)
					{
						strcpy(pnow[prodn].id, id); // 参数名
						prodn++;
						if (ch == ':')
						{
							getch();
							getsym();
						}
						else
							error(38);
						if (sym == intersym || sym == realsym || sym == Boolsym)
						{
							pnow[prodn - 1].sym = sym;
							getsym();
						}
						else
							error(39);
						if (sym == semicolon || sym == rparen)
							getsym();
						else
							error(5);
					}
					if (sym == semicolon)
						getsym();
				}
				else
					error(5);
			}
			else if (sym == funcsym)
			{
				k = 0;
				getsym();
				if (sym == ident)
				{
					enter(func);
					getsym();
					i = position(id);
				}
				else
					error(4);
				if (sym == lparen)
				{ // 有参数
					getsym();
					while (sym == ident)
					{
						strcpy(pnow[prodn].id, id);
						prodn++;
						if (ch == ':')
						{
							getch();
							getsym();
						}
						else
							error(38);
						if (sym == intersym || sym == realsym)
						{
							table[i].paral[k] = sym;
							k++;
							pnow[prodn - 1].sym = sym;
							getsym();
						}
						else
							error(39);
						if (sym == semicolon || sym == rparen)
							getsym();
						else
							error(5);
					}
				}
				if (sym == nul)
				{
					getsym();
					if (sym == intersym || sym == realsym || sym == Boolsym)
					{
						table[i].type1 = sym;
						getsym();
					}
					else
						error(45);
				}
				else
					error(44);
				if (sym == semicolon)
					getsym();
				else
					error(5);
			}
			lev = lev + 1;
			tx1 = tx;
			dx1 = dx;
			block(fsys | semicolon); //嵌套子程序
			lev = lev - 1;
			tx = tx1;
			dx = dx1;
			if (sym == semicolon)
			{
				getsym();
				test(statbegsys | ident | procsym | funcsym, fsys, 6);
			}
			else
				error(5);
		}
		test(statbegsys | ident, declbegsys, 7);
	} while (sym & declbegsys);

	code[table[tx0].addr].a = cx; //将跳转地址改为正确的CX以保证调用返回的正确性
	table[tx0].addr = cx;		  // start addr of code
	cx0 = cx;
	for (j = 0; j < table[tx0].n; j++)
		gen(sto, lev - table[tx2].level, table[tx2].addr - j);
	gen(Int, 0, dx + table[tx0].n);
	if (sym == beginsym)
		statement(fsys | semicolon | endsym);
	else
	{
		error(54);
		getsym();
	}
	gen(opr, 0, 0); // return
	test(fsys, 0, 8);
	listcode(cx0);
}

int main()
{
	init();
	printf("please input source program file name: ");
	scanf("%s", infilename);
	printf("\n");
	if ((infile = fopen(infilename, "r")) == NULL)
	{
		printf("File %s can't be opened.\n", infilename);
		exit(1);
	}

	err = 0;
	cc = 0;
	cx = 0;
	ll = 0;
	ch = ' ';
	kk = al;
	getsym();
	lev = 0;
	tx = 0;
	block(declbegsys | statbegsys | period);

	if (sym != period)
	{
		error(9);
	}
	if (err == 0)
	{
		if ((outfile = fopen("out.txt", "wb")) == NULL)
		{
			printf("File <out.txt> can't be opened.\n");
			exit(1);
		}
		fwrite(&code, sizeof(instruction), cxmax, outfile);
		fclose(outfile);
		if ((outfile = fopen("code.txt", "w")) == NULL)
		{
			printf("File <out.txt> can't be opened.\n");
			exit(1);
		}
		for (int i = 0; i <= cx; i++)
		{
			fprintf(outfile, "%10d%5s%3d%10.5f\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
		}
		fclose(outfile);
	}
	else
	{
		printf("errors in PL/0 program\n");
	}
	fclose(infile);
	system("pause");
	return 0;
}