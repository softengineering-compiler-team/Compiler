// pl/0 compiler with code generation
#include "mycompiler.h"

int mycnt = 0;

void error(long n)
{
	long i;

	printf(" ****");
	for (i = 1; i <= cc - 1; i++)
	{
		printf(" ");
	}
	printf("^%2d\n", n);
	err++;
}

void getch()
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
/*
void getsym()
{
	long i, j, k;

	while (ch == ' ' || ch == '\t')
	{
		getch();
	}
	if (isalpha(ch))
	{ // identified or reserved
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
		{
			kk = k;
		}
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
		j = norw - 1;
		do
		{
			k = (i + j) / 2;
			if (strcmp(id, word[k]) <= 0)
			{
				j = k - 1;
			}
			if (strcmp(id, word[k]) >= 0)
			{
				i = k + 1;
			}
		} while (i <= j);
		if (i - 1 > j)
		{
			sym = wsym[k];
		}
		else
		{
			sym = ident;
		}
	}
	else if (isdigit(ch))
	{ // number
		k = 0;
		num = 0;
		sym = number;
		do
		{
			num = num * 10 + (ch - '0');
			k = k + 1;
			getch();
		} while (isdigit(ch));
		if (k > nmax)
		{
			error(31);
		}
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
		{
			sym = nul;
		}
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
		{
			sym = lss;
		}
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
		{
			sym = gtr;
		}
	}
	else
	{
		sym = ssym[(unsigned char)ch];
		getch();
	}
}
*/
void getsym()
{
	long i, j, k;
	int flag = 0;
	double t = 1.0;			//标记小数点后的位数
	double numt = 0, z = 0; //小数部分的值
	while (ch == ' ' || ch == '\t')
	{
		getch();
	}
	if (isalpha(ch))
	{ // identified or reserved  开始进行词法分析
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
		{
			kk = k;
		}
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
		{
			k = (i + j) / 2;
			if (strcmp(id, word[k]) <= 0)
			{
				j = k - 1;
			}
			if (strcmp(id, word[k]) >= 0)
			{
				i = k + 1;
			}
		} while (i <= j); //此循环用于在保留字符表中找到对应的保留字
		if (i - 1 > j)
		{
			sym = wsym[k]; //  sym返回词法单元的类型 如果i-1》j是保留字
		}
		else
		{
			sym = ident; //否则是定义的标识符
		}
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
			{
				error(57); // new error id 57
			}
		}
		else
		{
			sym = intersym;
		}
		if (k > nmax)
		{
			error(31);
		}
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
		{
			sym = nul;
		}
	}
	else if (ch == '/')
	{ //新增 /* .. */
		getch();
		if (ch == '*')
		{
			flag++;
			getch();
			while (flag > 0)
			{
				while (ch != '*')
				{
					getch();
				}
				getch();
				if (ch == '/')
					flag--;
			}
			getch();
			getsym();
		}
		else
		{
			sym = ssym[(unsigned char)'/'];
		}
	}
	else if (ch == '*')
	{ // /* .. */ .. */
		getch();
		if (ch == '/')
		{
			getch();
			if (ch == '*')
			{
				flag = 0;
				sym = ssym[(unsigned char)'*'];
				flag++;
				getch();
				while (flag > 0)
				{
					while (ch != '*')
					{
						getch();
					}
					getch();
					if (ch == '/')
						flag--;
				}
				getch();
			}
			else
			{
				printf("a superflous note symbol \n");
				sym = nul;
			}
		}
		else
		{
			sym = ssym[(unsigned char)'*'];
		}
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
		{
			sym = lss;
		}
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
		{
			sym = gtr;
		}
	}
	else if (ch == '=')
	{
		getch();
		if (ch == '=')
		{
			getch();
		}
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
		{
			sym = period;
		}
	}
	else
	{
		sym = ssym[(unsigned char)ch];
		getch();
	}
}


//



void gen(enum fct x, long y, double z)
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

void test(long long s1, long long s2, long n)
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

void enter(enum object k)
{ // enter object into table
	tx = tx + 1;
	strcpy(table[tx].name, id);
	table[tx].kind = k;
	switch (k)
	{
	case constant:
		if (num > amax)
		{
			error(31);
			num = 0;
		}
		table[tx].val = num;
		table[tx].type1 = sym;	//记录Const的类型，int or real
		break;
	case variable:
		table[tx].level = lev;
		table[tx].addr = dx;
		dx = dx + 1;
		break;
	case proc:
		table[tx].level = lev;
		break;
	}
}

long position(char *id)
{ // find identifier id in table
	long i;

	strcpy(table[0].name, id);
	i = tx;
	while (strcmp(table[i].name, id) != 0)
	{
		i = i - 1;
	}
	return i;
}

void constdeclaration()
{
	if (sym == ident)
	{
		getsym();
		if (sym == eql || sym == becomes)
		{
			if (sym == becomes)
			{
				error(1);
			}
			getsym();
			if (sym == intersym || sym == realsym)
			{
				enter(constant);
				getsym();
			}
			else
			{
				error(2);
			}
		}
		else
		{
			error(3);
		}
	}
	else
	{
		error(4);
	}
}
/*
void vardeclaration()
{
	if (sym == ident)
	{
		enter(variable);
		getsym();
	}
	else
	{
		error(4);
	}
}
*/
void vardeclaration()
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
						error(48);
						break;
					}
				}
				identnum++;
				k++;
				strcpy(sameid[k], id);
				getsym();
			}
		}
		if (sym == nul)
		{ //说明遇到：后面应该是指示变量的类型
			getsym();
			if (sym == intersym || sym == realsym || sym == Boolsym)
			{
				for (j = 0, k = 0; j < identnum; j++)
				{ //之前的变量全部是相同的类型
					strcpy(id, sameid[k]);
					/*if((i=position(id))!=0){   //检查变量是否重复声明
					  error(48);

					}*/
					enter(variable);
					//tx1++;
					table[tx].type1 = sym;

					k++;
				}
			}
			else if (sym == ident)
			{
				i = position(id); //在符号表中找到Id的位置 返给下表付给i
				if (i == 0)
				{
					error(11);
				}
				sym = table[i].type1;
				if (sym == intersym || sym == realsym || sym == Boolsym)
				{
					for (j = 0, k = 0; j < identnum; j++)
					{ //之前的变量全部是相同的类型
						strcpy(id, sameid[k]);
						enter(variable);
						//tx1++;
						k++;
						table[tx].type1 = sym;
					}
				}
				else if (sym == arraysym)
				{
					for (j = 0; j < identnum; j++)
					{ //之前的变量全部是相同的类型
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
			{
				error(36);
			}
			getsym();
		}
		else
		{
			error(55);
		}
	}
	else
	{
		error(4);
	}
}


void listcode(long cx0)
{ // list code generated for this block
	long i;

	for (i = cx0; i <= cx - 1; i++)
	{
		printf("%10d%5s%3d%10.5lf\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
	}
}

//void expression(long long);
void factor(long long fsys)
{
	long i, j, k;
	/// 数组用
	//long drtnum, away;

	test(facbegsys, fsys, 24); // 测试传入信号是否有factor判断条件
	while (sym & facbegsys)
	{
		if (sym == ident)
		{
			i = position(id);
			if (i == 0)
			{
				error(11);
			}
			else
			{
				switch (table[i].kind)
				{
				case constant: //对于const 生成中间代码
					gen(lit, 0, table[i].val);
					lastsym = table[i].type1;
					getsym();
					break;
				case variable: //对于 var 生成中间代码
				{
					long long type = table[i].type1;
					// 当 var 类型是 int real 或 Boolean时
					if(type == intersym || type == realsym || type == Boolsym){
						gen(lod, lev-table[i].level, table[i].addr); // lod lev,addr 中间代码，相当于将 var 的值装入栈顶
						lastsym = type;
						getsym;
					}else{ // var 类型是 array时
						printf("Array!");
						error(100);
					}
					break;
				}
					//gen(lod, lev - table[i].level, table[i].addr);
					//break;
				case proc:
					error(21);
					break;
				}
			}
			// getsym操作 在 break前做掉
			//getsym();
		}
		else if (sym == intersym || sym == realsym) // 对于 int or real类型的 单词 进行装入
		{
			if (num > amax)
			{
				error(31);
				num = 0;
			}
			gen(lit, 0, num);
			getsym();
		}
		else if (sym == lparen)
		{
			getsym();
			expression(rparen | fsys);
			if (sym == rparen)
			{
				getsym();
			}
			else
			{
				error(22);
			}
		}
		test(fsys, lparen, 23);
	}
}

void term(long long fsys)
{
	long long mulop;
	long long lasttype;
	long cx1,cx2;

	factor(fsys | times | slash | div | mod | and); //表达式判断
	lasttype = lastsym;
	while (sym == times || sym == slash || sym == div || sym == mod || sym == and)
	{
		mulop = sym;
		getsym();
		if(mulop == and){
			cx1 = cx;
			gen(jpc, 0, 0); // 对于布尔值and操作，记录当前程序栈顶并生成逻辑判断回路跳转
		}
		factor(fsys | times | slash | div | mod | and); //表达式判断
		if (mulop == times)
		{// 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 *
			//gen(opr, 0, 4);
			if(lastsym == intersym && lasttype == intersym){
				lastsym = intersym;
			}else if(lastsym == intersym && lasttype == realsym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == intersym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == realsym){
				lastsym = realsym;
			}else{
				lastsym = typeerror;
				error(50); // 非数字相乘 错误
			}
			gen(opr, 0, 4);//中间代码
		}
		else if(mulop == slash)
		{// 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 /
			//gen(opr, 0, 5);
			if(lastsym == intersym && lasttype == intersym){
				lastsym = intersym;
			}else if(lastsym == intersym && lasttype == realsym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == intersym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == realsym){
				lastsym = realsym;
			}else{
				lastsym = typeerror;
				error(50); // 非数字相除 错误
			}
			gen(opr, 0, 5);//中间代码
		}
		else if(mulop == div)
		{// 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 div
			//gen(opr, 0, 18);
			if(lastsym == intersym && lasttype == intersym){
				lastsym = intersym;
			}else if(lastsym == intersym && lasttype == realsym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == intersym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == realsym){
				lastsym = realsym;
			}else{
				lastsym = typeerror;
				error(50); // 非数字相 整除 错误
			}
			gen(opr, 0, 18);//中间代码
		}
		else if(mulop == mod)
		{// 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 mod
			//gen(opr, 0, 19);
			if(lastsym == intersym && lasttype == intersym){
				lastsym = intersym;
			}else{
				lastsym = typeerror;
				error(50); // 非整数 mod 错误
			}
			gen(opr, 0, 19);//中间代码
		}
		else if(mulop == and)
		{
			if(lastsym == Boolsym && lastsym == Boolsym){
				lastsym = Boolsym;
			}else{
				lastsym = typeerror;
				error(50); // 只有Boolean类型可and
			}
			//and 短路计算，如果有假则直接跳转到factor执行
			gen(opr, 0, 20);
			cx2 = cx;
			gen(jmp, 0, 0);
			code[cx1].a = cx;
			gen(lit,0 , 0);
			code[cx2].a = cx;
		}
	}
}

void expression(long long fsys) // simple expression
{
	long long addop;
	long long lasttype;
	long cx1,cx2;

	if (sym == plus || sym == minus)
	{
		addop = sym;
		getsym();
		term(fsys | plus | minus | or);
		if (addop == minus)
		{
			gen(opr, 0, 1);
		}
	}
	else
	{
		term(fsys | plus | minus | or);
	}
	while (sym == plus || sym == minus || sym == or)
	{
		addop = sym;
		getsym();
		lasttype = lastsym;
		if(addop == or){
			cx1 = cx;
			gen(jpq, 0, 0);//or 指令相关跳转
		}
		term(fsys | plus | minus | or);
		if (addop == plus)
		{// 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 +
			//gen(opr, 0, 2);
			if(lastsym == intersym && lasttype == intersym){
				lastsym = intersym;
			}else if(lastsym == intersym && lasttype == realsym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == intersym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == realsym){
				lastsym = realsym;
			}else{
				lastsym = typeerror;
				error(50); // 非数字相加 错误
			}
			gen(opr, 0, 2);//中间代码
		}
		else if(addop == minus)
		{// 计算栈 -> b(lastsym) | a (lasttype) ,符号栈 -
			//gen(opr, 0, 3);
			if(lastsym == intersym && lasttype == intersym){
				lastsym = intersym;
			}else if(lastsym == intersym && lasttype == realsym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == intersym){
				lastsym = realsym;
			}else if(lastsym == realsym && lasttype == realsym){
				lastsym = realsym;
			}else{
				lastsym = typeerror;
				error(5007); // 非数字相减 错误
			}
			gen(opr, 0, 3);//中间代码
		}
		else{// or
			if(lastsym == lasttype && lastsym == Boolsym){
				lastsym = Boolsym;
			}else{
				lastsym = typeerror;
				error(5008);
			}
			gen(opr, 0, 21);
			cx2 = cx;
			gen(jmp, 0, 0);
			code[cx1].a = cx;
			gen(lit, 0, 1);
			code[cx2].a = cx;
		}
	}
}

void condition(long long fsys)
{
	long long relop;
	long long lasttype;

	if (sym == oddsym)
	{
		getsym();
		expression(fsys);
		if(lastsym = intersym){
			lastsym = Boolsym;
		}else{
			lastsym = typeerror;
			error(5009);
		}
		gen(opr, 0, 6);
	}
	else{
		expression(fsys | eql | neq | lss | gtr | leq | geq | comma | rparen | rmparen);
	}
	if (sym & (eql | neq | lss | gtr | leq | geq)){
		relop = sym;
		getsym();
		lasttype = lastsym;
		expression(fsys);
		if(lasttype == intersym && lastsym == intersym){
			lastsym = Boolsym;
		}else if(lasttype == intersym && lastsym == realsym){
			lastsym = Boolsym;
		}else if(lasttype == realsym && lastsym == realsym){
			lastsym = Boolsym;
		}else if(lasttype == realsym && lastsym == intersym){
			lastsym = Boolsym;
		}else if(lasttype == Boolsym && lastsym == Boolsym){
			lastsym = Boolsym;
		}else{
			lastsym = typeerror;
			error(5010);
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
		/*
		if (i == 0)
		{
			error(11);
		}
		else if (table[i].kind != variable)
		{ // assignment to non-variable
			error(12);
			i = 0;
		}
		getsym();
		*/
		if(table[i].type1 == arraysym){
			//是数组
		}else{
			lasttype = table[i].type2;
			getsym();
		}//不是数组，类型存在type2

		if (sym == becomes)
		{
			getsym();
		}
		else
		{
			error(13);
		}
		condition(fsys);
		// if(lasttype == intersym && lastsym == intersym){
		// 	lastsym = voiderror;
		// }else if(lasttype == intersym && lastsym == realsym){
		// 	lastsym = voiderror;
		// }else if(lasttype == realsym && lastsym == realsym){
		// 	lastsym = voiderror;
		// }else if(lasttype == realsym && lastsym == intersym){
		// 	lastsym = voiderror;
		// }else if(lasttype == Boolsym && lasttype == lastsym){
		// 	lastsym = voiderror;
		// }else{
		// 	printf("lastsym=%lld\nlasttype=%lld\n",lastsym,lasttype);
		// 	lastsym = typeerror;
		// 	error(5011);
		// 	}
		if (i != 0)
		{
			//gen(sto, lev - table[i].level, table[i].addr);
			switch (table[i].kind)
			{
			case variable:
				if(table[i].type1 == intersym || table[i].type1 == realsym){
					gen(sto, lev-table[i].level, table[i].addr);
				}else if(table[i].type1 = arraysym){
					//arraydo(sto,i);
				}
				break;
			case func:
				gen(sto, lev-table[i].level, table[i].funcaddr);
				break;
			case type:
				error(56);
			default:
				break;
			}
		}
	}
	else if (sym == callsym)
	{
		getsym();
		if (sym != ident)
		{
			error(14);
		}
		else
		{
			i = position(id);
			if (i == 0)
			{
				error(11);
			}
			else if (table[i].kind == proc)
			{
				gen(cal, lev - table[i].level, table[i].addr);
			}
			else
			{
				error(15);
			}
			getsym();
		}
	}
	else if (sym == ifsym)
	{
		getsym();
		condition(fsys | thensym | dosym);
		if (sym == thensym)
		{
			getsym();
		}
		else
		{
			error(16);
		}
		cx1 = cx;
		gen(jpc, 0, 0);
		statement(fsys);
		code[cx1].a = cx;
	}
	else if (sym == beginsym)
	{
		getsym();
		statement(fsys | semicolon | endsym);
		while (sym == semicolon || (sym & statbegsys))
		{
			if (sym == semicolon)
			{
				getsym();
			}
			else
			{
				error(10);
			}
			statement(fsys | semicolon | endsym);
		}
		if (sym == endsym)
		{
			getsym();
		}
		else
		{
			error(17);
		}
	}
	else if (sym == whilesym)
	{
		cx1 = cx;
		getsym();
		condition(fsys | dosym);
		cx2 = cx;
		gen(jpc, 0, 0);
		if (sym == dosym)
		{
			getsym();
		}
		else
		{
			error(18);
		}
		statement(fsys);
		gen(jmp, 0, cx1);
		code[cx2].a = cx;
	}
	test(fsys, 0, 19);
}

void block(long long fsys) // 程序 -> 分程序
{	
	long i,j,k;
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
	for(j=0;j<prodn;j++){
		tx++;
		strcpy(table[tx].name,pnow[j].id);
		table[tx].kind = variable;
		table[tx].level = lev;
		table[tx].addr = dx;
		table[tx].type1 = pnow[j].sym;
		dx++;
	}
	tx2 = tx;
	if (lev > levmax)
	{
		error(32);
	}
	do
	{ // Const a=1,b=2;
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
				{
					getsym();
				}
				else
				{
					error(5);
				}
			} while (sym == ident);
		}
		if(sym == typesym){
			
		}
		if (sym == varsym)
		{
			getsym();
			do
			{
				vardeclaration();
				while (sym == comma)
				{
					getsym();
					vardeclaration();
				}
				if (sym == semicolon)
				{
					getsym();
				}
				else
				{
					error(5);
				}
			} while (sym == ident);
		}
		while (sym == procsym || sym == funcsym) // function and procedure
		{
			getsym();
			if (sym == ident)
			{
				enter(proc);
				getsym();
			}
			else
			{
				error(4);
			}
			if (sym == semicolon)
			{
				getsym();
			}
			else
			{
				error(5);
			}
			lev = lev + 1;
			tx1 = tx;
			dx1 = dx;
			block(fsys | semicolon);
			lev = lev - 1;
			tx = tx1;
			dx = dx1;
			if (sym == semicolon)
			{
				getsym();
				test(statbegsys | ident | procsym, fsys, 6);
			}
			else
			{
				error(5);
			}
		}
		test(statbegsys | ident, declbegsys, 7);
	} while (sym & declbegsys);
	code[table[tx0].addr].a = cx;
	table[tx0].addr = cx; // start addr of code
	cx0 = cx;
	for(j=0;j<table[tx0].n;j++){
		gen(sto, lev-table[tx2].level, table[tx2].addr-j);
	}
	gen(Int, 0, dx+table[tx0].n);
	if(sym == beginsym){
		statement(fsys | semicolon | endsym);
	}else{
		error(54);
		getsym();
	}
	gen(opr, 0, 0); // return
	test(fsys, 0, 8);
	listcode(cx0);
}

long base(long b, long l)
{
	long b1;

	b1 = b;
	while (l > 0)
	{ // find base l levels down
		b1 = s[b1];
		l = l - 1;
	}
	return b1;
}

void interpret()
{
	long p, b, t;  // program-, base-, topstack-registers
	instruction i; // instruction register

	printf("start PL/0\n");
	t = 0;
	b = 1;
	p = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
	do
	{
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
			case 5:
				t = t - 1;
				s[t] = s[t] / s[t + 1];
				break;
			case 6:
				s[t] = (long)s[t] % 2;
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
			}
			break;
		case lod:
			t = t + 1;
			s[t] = s[base(b, i.l) + (long) i.a];
			break;
		case sto:
			s[base(b, i.l) + (long) i.a] = s[t];
			printf("%10d\n", s[t]);
			t = t - 1;
			break;
		case cal: // generate new block mark
			s[t + 1] = base(b, i.l);
			s[t + 2] = b;
			s[t + 3] = p;
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
			t = t - 1;
		}
	} while (p != 0);
	printf("end PL/0\n");
}

int main()
{
	long i;
	for (i = 0; i < 256; i++)
	{
		ssym[i] = nul;
	}
	for(i=0;i<norw;i++)	wsym[i]=nul;
	strcpy(word[0],  "Boolean   ");
	strcpy(word[1],  "and       ");
	strcpy(word[2],  "array     ");
    strcpy(word[3],  "begin     ");
    strcpy(word[4],  "call      ");
    strcpy(word[5],  "const     ");
	strcpy(word[6],  "div       ");
    strcpy(word[7],  "do        ");
	strcpy(word[8],  "else      ");
    strcpy(word[9],  "end       ");
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
	strcpy(mnemonic[lit],"lit");
    strcpy(mnemonic[opr],"opr");
    strcpy(mnemonic[lod],"lod");
    strcpy(mnemonic[sto],"sto");
    strcpy(mnemonic[cal],"cal");
    strcpy(mnemonic[Int],"int");
    strcpy(mnemonic[jmp],"jmp");
    strcpy(mnemonic[jpc],"jpc");
	strcpy(mnemonic[say],"say");   //数组的存指令
	strcpy(mnemonic[lay],"lay");    //数组的取指令
	strcpy(mnemonic[jpq],"jpq");
	wsym[0]=Boolsym;
	wsym[1]=and;
	wsym[2]=arraysym;
	wsym[3]=beginsym;
    wsym[4]=callsym;
    wsym[5]=constsym;
	wsym[6]=div;
    wsym[7]=dosym;
	wsym[8]=elsesym;
    wsym[9]=endsym;
	wsym[10]=exitsym;
	wsym[11]=falsesym;
	wsym[12]=funcsym;
    wsym[13]=ifsym;
	wsym[14]=intersym;
	wsym[15]=mod;
	wsym[16]=not;
    wsym[17]=oddsym;
	wsym[18]=ofsym;
	wsym[19]=or;
    wsym[20]=procsym;
	wsym[21]=readsym;
	wsym[22]=realsym;
    wsym[23]=thensym;
	wsym[24]=truesym;
	wsym[25]=typesym;
    wsym[26]=varsym;
    wsym[27]=whilesym;
	wsym[28]=writesym;
    ssym['+']=plus;
    ssym['-']=minus;
    ssym['*']=times;
    ssym['/']=slash;
    ssym['(']=lparen;
    ssym[')']=rparen;
    //ssym['=']=eql;
    ssym[',']=comma;
    ssym['.']=period;
    ssym[';']=semicolon;
	ssym['[']=lmparen;
	ssym[']']=rmparen;

	declbegsys = constsym | typesym | varsym | procsym | funcsym;
	statbegsys = beginsym | callsym | ifsym | whilesym | exitsym | writesym | readsym;
	facbegsys = ident | intersym | realsym | lparen | not | truesym | falsesym;

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
		interpret();
	}
	else
	{
		printf("errors in PL/0 program\n");
	}
	fclose(infile);
	system("pause");
}