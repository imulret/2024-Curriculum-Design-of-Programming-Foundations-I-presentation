//2025-01-05编写用环境
//encoding=UTF-8 with BOM
//#define _MSC_FULL_VER 194033813
//#define _MSC_BUILD 0
//#define _MSVC_LANG 201402
//x64-release
//(未发现问题)
//
//2024-12-28在此编译器上编译通过
//encoding=UTF-8 with BOM
//gcc (tdm64-1) 4.9.2
//gcc -std=c99 -fexec-charset=gbk -O3
//（部分功能会导致程序死机）
//
//2024-12-28编写用环境
//encoding=UTF-8 with BOM
//#define _MSC_FULL_VER 194033813
//#define _MSC_BUILD 0
//#define _MSVC_LANG 201402
//x64-release
//
//2024-12-28在此编译器上编译通过（尚未检查运行逻辑）
//encoding=UTF-8 with BOM
//gcc (tdm64-1) 4.9.2
//gcc -std=c99 -fexec-charset=gbk -O3

/*
十二、设计一个人事管理程序
  管理的数据包括：姓名、部门、籍贯、出生年月日、学历/学位、职务/职称、工资和奖惩记录。
  要求具有如下功能：
  （1）加入新记录；
  （2）删除一条记录；
  （3）有关查询；
  （4）访问控制。
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stddef.h"
#define LEVER_OF_ACCESS_CONTROL_VERSION_L 1

#define TASKID_DISPLAY_MENU_L		1
#define TASKID_APPEND_NEW_RECORD_L	2
#define TASKID_DELETE_RECORD_L		3
#define TASKID_SEARCH_RECORD_L		4
#define TASKID_ACCESS_CONTROL_L		5
#define TASKID_INPUT_PASSWORD_L		6
#define TASKID_DISPLAY_ACCESS_CONTROL_MENU_L	7
#define TASKID_LOAD_RECORD_FROM_FILE_L			8
#define TASKID_SAVE_RECORD_TO_FILE_L			9
#define TASKID_UPDATE_RECORD_L					10
#define TASKID_SORT_RECORD_L					11

void callprocl();
void dealSthBeforeExitl();
void displayMenul();
void appendNewRecordl();
void deleteRecordl();
void searchRecordl();
void inputPasswordl();


int getInputNumber(int maxNumber);
void listAllRecordl();
inline void printInfoAfterAbnormalExit();
__int64 distribueUniqueID();
__int64 getStringHash(char sz[]);

void callprocAccessControll();
void displayAccessControlMenul();
void loadRecordFromFilel();
void saveRecordToFilel();
void updateRecordl();
void accessControll();
void sortRecordl();

struct recordl
{
	__int64 id;
	float gongZi;
	unsigned int chuShengNian;
	unsigned int chuShengYue;
	unsigned int chuShengRi;
	char xingMing[16];
	char buMen[64];
	char jiGuan[32];
	char xueLi[16];
	char zhiWu[32];
	char jiangChengJiLu[128];
	struct recordl* next;
} *headptr_recordl = NULL;
void listSingleRecordl(struct recordl* crl);

struct
{
	__int64 version_lever;
	__int64 user_privilege;
	__int64 taskid;
	size_t resource_size;
	void* resource;
} tsl = { 0, 0, 6, 0, NULL };
char default_passwordl[] = "123123";
char default_filepathl[] = ".\\srcl\\hb4Q34vGPBz8mEL3g1RK.txt";
char default_resource_filepathl[] = ".\\srcl\\default_resource.txt";

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
#if LEVER_OF_ACCESS_CONTROL_VERSION_L
		tsl.version_lever = 1;
#endif // LEVER_OF_ACCESS_CONTROL_VERSION_L
		callprocl();
		system("pause");
	}
	else if (argc == 2 && !(strcmp(argv[1], "/?") && strcmp(argv[1], "--help") && strcmp(argv[1], "-h")))
	{
		puts("一个缺少_人事信息文件交互(题目没要求实现它)_的人事管理系统。");
		putchar('\n');
		puts("程序正常使用时不需要参数");
		putchar('\n');
		puts("--------------------------------2025-01-05更新");
		puts("增加callprocAccessControll()系列功能");
		puts("增加宏开关LEVER_OF_ACCESS_CONTROL_INTEGRATED_IN_DISPLAY_MENU_L");
		puts("增加tsl.version_lever和tsl.user_privilege");
		putchar('\n');
		putchar('\n');
		puts("--------------------------------2024-12-28更新");
		puts("现在，代码的注释还不是很多。");
		puts("源文件单独编译时，记得把main3改成main。");
		puts("写一开始的代码用的IDE(Microsoft Visual Studio)我只知道它支持C++，不知道它是否支持纯C。");
		puts("所以一开始源文件后缀名是.cpp的。");
		puts("如果你发现了有C++对于C独有的特性，或者是MSVC对于其他编译器独有的特性，请你修改修改。");
		putchar('\n');
		puts("另外，这里的某些变量命名我偷了些懒。");
		puts("比如作为这个程序最重要的结构体--一个存储??的信息--我只用了recordl来命名它");
		puts("而且该结构体里的数据域我是用拼音命名的");
		puts("还有函数里面经常能看到 变量crl，那是current_recordl的缩写(我瞎编的)");
		puts("主要是链表操作要经常用到crl，如果名字太长的话逻辑看起来就不那么清晰了...");
		puts("其中的errorlevel，其灵感源于windows批处理脚本bat的%errorlevel%");
		putchar('\n');
		puts("还有，你可能疑惑，为什么许多好端端的名字后面都出现一个小写字母L？");
		puts("因为这是第十二个题目，而第12个英文字母恰好是l");
		putchar('\n');
		puts("源代码中很多函数看上去不接收参数，其实还需要一些全局变量的支持。");
		puts("比如baseptr_recordl, tsl.taskid; 访问控制会用到的default_passwordl, default_filepathl之类的");
		putchar('\n');
		putchar('\n');
	}
#if !LEVER_OF_ACCESS_CONTROL_VERSION_L
	else if (argc == 2 && !strcmp(argv[1], "-h=h"))
	{
		tsl.version_lever = 1;
		tsl.taskid = 1;
		callprocl();
	}
#endif // LEVER_OF_ACCESS_CONTROL_VERSION_L
	else
	{
		puts("程序正常使用时不需要参数。");
	}
	return 0;
}

void printInfoAfterAbnormalExit()
{
	printf("程序非正常退出!\n");
	printf("[ERROR]:\ttaskid=%lld, resource_size=%lld\n\tresource=%llx\n", tsl.taskid, tsl.resource_size, tsl.resource);
	printf("\theadptr_recordl=%llx\n", headptr_recordl);
}

void callprocl()
{
	while (1)
	{
		//printf("[INFO]:current tsl.taskid=%lld\n", tsl.taskid);
		if (tsl.taskid == 0)
		{
			dealSthBeforeExitl();
			break;
		}
		else if (tsl.taskid == TASKID_DISPLAY_MENU_L)
		{
			displayMenul();
		}
		else if (tsl.taskid == TASKID_APPEND_NEW_RECORD_L)
		{
			appendNewRecordl();
		}
		else if (tsl.taskid == TASKID_DELETE_RECORD_L)
		{
			deleteRecordl();
		}
		else if (tsl.taskid == TASKID_SEARCH_RECORD_L)
		{
			searchRecordl();
		}
		else if (tsl.taskid == TASKID_ACCESS_CONTROL_L)
		{
			if (tsl.version_lever)
			{
				tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
				callprocAccessControll();
			}
			else
			{
				accessControll();
			}
		}
		else if (tsl.taskid == TASKID_INPUT_PASSWORD_L)
		{
			inputPasswordl();
		}
		else
		{
			printInfoAfterAbnormalExit();
			break;
		}
	}
}

void dealSthBeforeExitl()
{
	struct recordl* crl = headptr_recordl;
	struct recordl* temp = NULL;
	if (!crl)
	{
		return;
	}
	while (crl)
	{
		temp = crl;
		crl = crl->next;
		free(temp);
	}
	return;
}

void listSingleRecordl(struct recordl* crl)
{
	printf("存储编号:%lld\n", crl->id);
	printf("姓名:%s\n", crl->xingMing);
	printf("部门:%s\n", crl->buMen);
	printf("籍贯:%s\n", crl->jiGuan);
	printf("出生日期:%d-%d-%d\n", crl->chuShengNian, crl->chuShengYue, crl->chuShengRi);
	printf("学历/学位:%s\n", crl->xueLi);
	printf("职务/职称:%s\n", crl->zhiWu);
	printf("工资:%.2f\n", crl->gongZi);
	printf("奖惩记录:%s\n\n", crl->jiangChengJiLu);
	return;
}

void displayMenul()
{
	puts("------------------------------");
	puts("\t人事管理程序");
#if LEVER_OF_ACCESS_CONTROL_VERSION_L
	printf("1 加入新纪录\n2 删除一条记录\n3 有关查询\n4 更多功能\n0 退出\n请选择:");
#else
	printf("1 加入新纪录\n2 删除一条记录\n3 有关查询\n4 访问控制\n0 退出\n请选择:");
#endif // LEVER_OF_ACCESS_CONTROL_VERSION_L

	
	switch (getInputNumber(4))
	{
	case 1:
		tsl.taskid = TASKID_APPEND_NEW_RECORD_L;
		break;
	case 2:
		tsl.taskid = TASKID_DELETE_RECORD_L;
		break;
	case 3:
		tsl.taskid = TASKID_SEARCH_RECORD_L;
		break;
	case 4:
		tsl.taskid = TASKID_ACCESS_CONTROL_L;
		break;
	case 0:
		tsl.taskid = 0;
		break;
	}
}

int getInputNumber(int maxNumber)
{
	int result = 0;
	while (1)
	{
		while (getchar() != '\n') continue;
		if (scanf("%d", &result) == 1 && result >= 0 && result <= maxNumber)
		{
			break;
		}
		else
		{
			printf("输入有误，请重新输入。\n");
			continue;
		}
	}
	return result;
}

void inputPasswordl()
{
	int errorlevel = 0;
	int filesize = 0;
	char buffer[128] = { 0 };
	__int64 fbuffer = 0;
	FILE* file = NULL;
	__int64 storagedHash = 0;
	while (1)
	{
		file = fopen(default_filepathl, "r");
		if (!file)
		{
			storagedHash = getStringHash(default_passwordl);
			printf("文件不存在，将使用默认密码。\n");
			printf("请输入密码(0退出)(1不输入密码):\n");
			scanf("%128s", buffer);
			if (buffer[0] == '0' && buffer[1] == 0)
			{
				errorlevel = 1;
				break;
			}
			else if (buffer[0] == '1' && buffer[1] == 0)
			{
				errorlevel = 4;
				break;
			}
			else if (storagedHash == getStringHash(buffer))
			{
				errorlevel = 0;
				break;
			}
			else
			{
				errorlevel = 2;
				break;
			}
		}

		printf("请输入密码(0退出)(1不输入密码):\n");
		scanf("%128s", buffer);
		if (buffer[0] == '0' && buffer[1] == 0)
		{
			errorlevel = 1;
			break;
		}
		else if (buffer[0] == '1' && buffer[1] == 0)
		{
			errorlevel = 4;
			break;
		}
		storagedHash = getStringHash(buffer);
		fseek(file, 0, SEEK_END);
		filesize = ftell(file);
		rewind(file);
		if (fscanf(file, "%lld", &fbuffer) != 1)
		{
			errorlevel = 3;
			break;
		}
		if (storagedHash != fbuffer)
		{
			errorlevel = 2;
			break;
		}

		fclose(file);
		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.user_privilege = 1;
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	case 1:
		tsl.taskid = 0;
		break;
	case 2:
		printf("密码错误\n");
		tsl.taskid = TASKID_INPUT_PASSWORD_L;
		break;
	case 3:
		printf("密码读入错误\n");
		tsl.taskid = 0;
		break;
	case 4:
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	default:
		printInfoAfterAbnormalExit();
		tsl.taskid = 0;
		break;
	}

	return;
}

void listAllRecordl()
{
	struct recordl* crl = headptr_recordl;
	while (crl)
	{
		listSingleRecordl(crl);
		crl = crl->next;
	}
	tsl.taskid = TASKID_DISPLAY_MENU_L;
}

void appendNewRecordl()
{
	struct recordl* rl = NULL;
	struct recordl** pcrl = &headptr_recordl;
	int errorlevel = 0;
	while (1)
	{
		rl = (struct recordl*)malloc(sizeof(struct recordl));
		if (!rl)
		{
			errorlevel = 1;
			break;
		}
		memset(rl, 0, sizeof(struct recordl));
		printf("需要输入:姓名、部门、籍贯、出生年月日、学历/学位、职务/职称、工资和奖惩记录。\n");
		if (
			printf("输入姓名:") <= 0 ||
			scanf("%s", rl->xingMing) != 1 ||
			printf("输入部门:") <= 0 ||
			scanf(" %s", rl->buMen) != 1 ||
			printf("输入籍贯:") <= 0 ||
			scanf(" %s", rl->jiGuan) != 1 ||
			printf("输入出生日期(年):") <= 0 ||
			scanf("%u", &rl->chuShengNian) != 1 ||
			printf("输入出生日期(月):") <= 0 ||
			scanf("%u", &rl->chuShengYue) != 1 ||
			printf("输入出生日期(日):") <= 0 ||
			scanf("%u", &rl->chuShengRi) != 1 ||
			printf("输入学历:") <= 0 ||
			scanf(" %s", rl->xueLi) != 1 ||
			printf("输入职务:") <= 0 ||
			scanf(" %s", rl->zhiWu) != 1 ||
			printf("输入工资:") <= 0 ||
			scanf("%f", &rl->gongZi) != 1 ||
			printf("输入奖惩记录:") <= 0 ||
			scanf(" %s", rl->jiangChengJiLu) != 1
			)
		{
			errorlevel = 2;
			break;
		}
		rl->id = distribueUniqueID();

		if (!*pcrl)
		{
			*pcrl = rl;
			break;
		}
		pcrl = (struct recordl**)*pcrl;
		while (((struct recordl*)pcrl)->next)
		{
			pcrl = (struct recordl**)((struct recordl*)pcrl)->next;
		}
		((struct recordl*)pcrl)->next = rl;

		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	case 2:
		free(rl);
		printf("输入失败!\n");
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	case 1:
		printf("calloc内存分配失败!\n");
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	default:
		printInfoAfterAbnormalExit();
		tsl.taskid = 0;
		break;
	}
}

void deleteRecordl()
{
	int errorlevel = 0;
	struct recordl* crl = headptr_recordl;
	struct recordl* prevrl = NULL;
	__int64 storage_id = 0;
	int position = -1;
	while (1)
	{
		if (!crl)
		{
			printf("当前记录内容为空.\n");
			errorlevel = 0;
			break;
		}
		printf("只能根据存储编号删除记录,如果不知道,请查询\n请输入存储编号:");
		if (scanf(" %lld", &storage_id) != 1)
		{
			errorlevel = 1;
			break;
		}
		for (__int64 i = 1; crl; ++i, crl = crl->next)
		{
			if (storage_id == crl->id)
			{
				position = i;
				printf("即将要删除的记录如下:\n");
				listSingleRecordl(crl);
				break;
			}
		}
		if (position == -1)
		{
			printf("没有找到记录.\n");
			errorlevel = 0;
			break;
		}
		while (getchar() != '\n') continue;
		printf("确定删除(y/N)(区分大小写)?");
		if (getchar() != 'y')
		{
			errorlevel = 2;
			break;
		}
		if (position == 1)
		{
			headptr_recordl = headptr_recordl->next;
			free(crl);
		}
		else
		{
			prevrl = headptr_recordl;
			while (prevrl->next != crl)
			{
				prevrl = prevrl->next;
			}
			prevrl->next = crl->next;
			free(crl);
		}
		printf("删除成功.\n");

		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	case 1:
		printf("输入有误，请重新输入!\n");
		tsl.taskid = TASKID_DELETE_RECORD_L;
		break;
	case 2:
		printf("放弃删除.\n");
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	default:
		printInfoAfterAbnormalExit();
		tsl.taskid = 0;
		break;
	}
	return;
}

void searchRecordl()
{
	int errorlevel = 0;
	int mode_number = 0;
	struct recordl* crl = headptr_recordl;
	char* buffer = NULL;
	while (1)
	{
		if (!crl)
		{
			puts("当前记录内容为空.");
			errorlevel = 0;
			break;
		}
		buffer = (char*)calloc(1024 / sizeof(int), sizeof(int));
		if (!buffer)
		{
			errorlevel = 2;
			break;
		}
		puts("针对什么查询:1:姓名,2:部门,3:籍贯,4:出生年,5:出生月,6:出生日,7:学历/学位,8:职务/职称,9:工资,10:奖惩记录,11:(遍历),0:退出");
		mode_number = getInputNumber(11);
		if (mode_number == 0)
		{
			errorlevel = 1;
			break;
		}
		else if (mode_number == 1)
		{
			printf("输入姓名:");
			scanf(" %s", buffer);
			printf("----查询结果:\n");
			while (crl)
			{
				if (!strcmp(buffer, crl->xingMing))
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 2)
		{
			printf("输入部门:");
			scanf(" %s", buffer);
			printf("----查询结果:\n");
			while (crl)
			{
				if (!strcmp(buffer, crl->buMen))
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 3)
		{
			printf("输入籍贯:");
			scanf(" %s", buffer);
			printf("----查询结果:\n");
			while (crl)
			{
				if (!strcmp(buffer, crl->jiGuan))
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 7)
		{
			printf("输入学历/学位:");
			scanf(" %s", buffer);
			printf("----查询结果:\n");
			while (crl)
			{
				if (!strcmp(buffer, crl->xueLi))
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 8)
		{
			printf("输入职务/职称:");
			scanf(" %s", buffer);
			printf("----查询结果:\n");
			while (crl)
			{
				if (!strcmp(buffer, crl->zhiWu))
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 10)
		{
			printf("输入奖惩记录:");
			scanf(" %s", buffer);
			printf("----查询结果:\n");
			while (crl)
			{
				if (!strcmp(buffer, crl->jiangChengJiLu))
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 4)
		{
			printf("输入出生年:");
			if (scanf(" %u", (unsigned int*)buffer) != 1)
			{
				errorlevel = 3;
			}
			printf("----查询结果:\n");
			while (crl)
			{
				if (*(unsigned int*)buffer == crl->chuShengNian)
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 5)
		{
			printf("输入出生月:");
			if (scanf(" %u", (unsigned int*)buffer) != 1)
			{
				errorlevel = 3;
			}
			printf("----查询结果:\n");
			while (crl)
			{
				if (*(unsigned int*)buffer == crl->chuShengYue)
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 6)
		{
			printf("输入出生日:");
			if (scanf(" %u", (unsigned int*)buffer) != 1)
			{
				errorlevel = 3;
			}
			printf("----查询结果:\n");
			while (crl)
			{
				if (*(unsigned int*)buffer == crl->chuShengRi)
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 9)
		{
			printf("输入工资下限:");
			if (scanf(" %f", (float*)buffer) != 1)
			{
				errorlevel = 3;
			}
			printf("输入工资上限:");
			if (scanf(" %f", (float*)buffer + 1) != 1)
			{
				errorlevel = 3;
			}
			printf("----查询结果:\n");
			while (crl)
			{
				if (crl->gongZi >= *(float*)buffer && crl->gongZi <= *((float*)buffer + 1))
				{
					listSingleRecordl(crl);
				}
				crl = crl->next;
			}
			break;
		}
		else if (mode_number == 11)
		{
			printf("----遍历结果:\n");
			listAllRecordl();
			break;
		}


		free(buffer);
		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	case 1:
		free(buffer);
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	case 2:
		printf("calloc内存分配失败!\n");
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	case 3:
		free(buffer);
		printf("输入有误!\n");
		tsl.taskid = TASKID_SEARCH_RECORD_L;
		break;
	default:
		printInfoAfterAbnormalExit();
		tsl.taskid = 0;
		break;
	}

	return;
}

__int64 distribueUniqueID()
{
	struct recordl* crl = headptr_recordl;
	int flag = 1;
	for (__int64 id = 1; id != LLONG_MAX; ++id)
	{
		while (crl)
		{
			if (id == crl->id)
			{
				flag = 0;
				break;
			}
			crl = crl->next;
		}
		if (flag)
		{
			return id;
		}
		flag = 1;
	}
}

__int64 getStringHash(char sz[])
{
	__int64 result = 5381;
	char* t = sz;
	if (!sz)
	{
		return 0;
	}
	while (*t)
	{
		result += result << 5 + *t;
		++t;
	}
	result &= 9223372036854775807;
	return result;
}

void accessControll()
{
	int errorlevel = 0;
	FILE* file = NULL;
	char buffer[128] = { 0 };
	__int64 storagedHash = 0;
	while (1)
	{
		if (tsl.user_privilege == 0)
		{
			puts("当前用户特权级不够.");
			errorlevel = 0;
			break;
		}
		file = fopen(default_filepathl, "w");
		if (!file)
		{
			errorlevel = 1;
			break;
		}
		printf("修改密码(0退出):");
		scanf("%128s", buffer);
		if (buffer[0] == '0' && buffer[1] == 0)
		{
			errorlevel = 2;
			break;
		}
		storagedHash = getStringHash(buffer);
		if (fprintf(file, "%lld", storagedHash) < 0)
		{
			errorlevel = 3;
			break;
		}
		printf("密码修改成功.\n");
		fclose(file);
		break;
	}
	switch (errorlevel)
	{
	case 0:
		if (tsl.version_lever == 0)
		{
			tsl.taskid = TASKID_DISPLAY_MENU_L;
		}
		else
		{
			tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		}
		break;
	case 1:
		printf("密码文件打开失败.\n");
		if (tsl.version_lever == 0)
		{
			tsl.taskid = TASKID_DISPLAY_MENU_L;
		}
		else
		{
			tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		}
		break;
	case 2:
		fclose(file);
		if (tsl.version_lever == 0)
		{
			tsl.taskid = TASKID_DISPLAY_MENU_L;
		}
		else
		{
			tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		}
		break;
	case 3:
		printf("密码写入失败.\n");
		fclose(file);
		if (tsl.version_lever == 0)
		{
			tsl.taskid = TASKID_DISPLAY_MENU_L;
		}
		else
		{
			tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		}
		break;
	default:
		printInfoAfterAbnormalExit();
		tsl.taskid = 0;
		break;
	}
}

void callprocAccessControll()
{
	while (1)
	{
		if (tsl.taskid == TASKID_DISPLAY_ACCESS_CONTROL_MENU_L)
		{
			displayAccessControlMenul();
		}
		else if (tsl.taskid == 0)
		{
			tsl.taskid = TASKID_DISPLAY_MENU_L;
			break;
		}
		else if (tsl.taskid == TASKID_LOAD_RECORD_FROM_FILE_L)
		{
			loadRecordFromFilel();
		}
		else if (tsl.taskid == TASKID_SAVE_RECORD_TO_FILE_L)
		{
			saveRecordToFilel();
		}
		else if (tsl.taskid == TASKID_UPDATE_RECORD_L)
		{
			updateRecordl();
		}
		else if (tsl.taskid == TASKID_ACCESS_CONTROL_L)
		{
			accessControll();
			if (tsl.taskid == TASKID_DISPLAY_MENU_L)
			{
				tsl.taskid == TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
			}
			else if (tsl.taskid == TASKID_DISPLAY_ACCESS_CONTROL_MENU_L)
			{
				;
			}
			else
			{
				break;
			}
		}
		else if (tsl.taskid == TASKID_SORT_RECORD_L)
		{
			sortRecordl();
		}
		else if (tsl.taskid == TASKID_DISPLAY_MENU_L)
		{
			break;
		}
		else
		{
			printInfoAfterAbnormalExit();
			tsl.taskid = 0;
			break;
		}
	}
}

void displayAccessControlMenul()
{
	puts("------------------------------");
	puts("1 从文件中导入记录");
	puts("2 将记录导出至文件");
	puts("3 更改某一记录");
	puts("4 修改密码");
	puts("5 有关排序");
	puts("6 清屏");
	puts("0 返回上级目录");
	putchar('\n');
	printf("请选择:");
	switch (getInputNumber(6))
	{
	case 1:
		tsl.taskid = TASKID_LOAD_RECORD_FROM_FILE_L;
		break;
	case 2:
		tsl.taskid = TASKID_SAVE_RECORD_TO_FILE_L;
		break;
	case 3:
		tsl.taskid = TASKID_UPDATE_RECORD_L;
		break;
	case 4:
		tsl.taskid = TASKID_ACCESS_CONTROL_L;
		break;
	case 5:
		tsl.taskid = TASKID_SORT_RECORD_L;
		break;
	case 6:
		system("cls");
		tsl.taskid == TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 0:
		tsl.taskid = TASKID_DISPLAY_MENU_L;
		break;
	}
}

void loadRecordFromFilel()
{
	char pathbuffer[256] = { 0 };
	FILE* file;
	struct recordl* crl = headptr_recordl;
	struct recordl* prev = NULL;
	int errorlevel = 0;
	while (1)
	{
		if (tsl.user_privilege == 0)
		{
			puts("当前用户特权级不够.");
			errorlevel = 0;
			break;
		}
		printf("输入要存放的路径(当前路径为应用程序所在路径)(0默认路径)\n");
		scanf("%s", pathbuffer);
		if (pathbuffer[0] == '0' && pathbuffer[1] == 0)
		{
			strcpy(pathbuffer, default_resource_filepathl);
		}
		file = fopen(pathbuffer, "r");
		if (!file)
		{
			errorlevel = 1;
			break;
		}
		crl = headptr_recordl;
		while (1)
		{
			if (!crl)
			{
				break;
			}
			while (crl)
			{
				prev = crl;
				crl = crl->next;
				free(prev);
			}
			break;
		}
		prev = NULL;
		crl = (struct recordl*)malloc(sizeof(struct recordl));
		if (!crl)
		{
			errorlevel = 3;
			break;
		}
		headptr_recordl = crl;
		memset(crl, 0, sizeof(struct recordl));
		while (1)
		{
			crl->id = distribueUniqueID();
			errorlevel = fscanf(file, "%*lld:[%f,%u,%u,%u,%*c%16[^\"]%*c,%*c%64[^\"]%*c,%*c%32[^\"]%*c,%*c%16[^\"]%*c,%*c%32[^\"]%*c,%*c%128[^\"]%*c,%lld],\n",
				&crl->gongZi,
				&crl->chuShengNian,
				&crl->chuShengYue,
				&crl->chuShengRi,
				&crl->xingMing,
				&crl->buMen,
				&crl->jiGuan,
				&crl->xueLi,
				&crl->zhiWu,
				&crl->jiangChengJiLu,
				&crl->next);
			if (errorlevel < 0)
			{
				errorlevel = 4;
				break;
			}
			if (crl->next == 0)
			{
				errorlevel = 0;
				break;
			}
			prev = crl;
			crl = (struct recordl*)malloc(sizeof(struct recordl));
			if (!crl)
			{
				errorlevel = 3;
				break;
			}
			memset(crl, 0, sizeof(struct recordl));
			prev->next = crl;
		}
		if (errorlevel == 4 || errorlevel == 3)
		{
			break;
		}
		fclose(file);
		puts("存入成功。");
		errorlevel = 0;
		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 1:
		perror("[ERROR]:文件打开失败");
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 2:
		perror("[ERROR]:in loadRecordFromFilel()");
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 3:
		perror("[ERROR]:分配内存失败");
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 4:
		perror("[ERROR]:从文件中读取内容失败");
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	default:
		break;
	}
	return;
}

void saveRecordToFilel()
{
	char pathbuffer[256] = { 0 };
	FILE* file;
	struct recordl* crl = headptr_recordl;
	int errorlevel = 0;
	while (1)
	{
		if (tsl.user_privilege == 0)
		{
			puts("当前用户特权级不够.");
			errorlevel = 0;
			break;
		}
		printf("输入要保存的路径(当前路径为应用程序所在路径)(0默认路径)\n");
		scanf("%s", pathbuffer);
		if (pathbuffer[0] == '0' && pathbuffer[1] == 0)
		{
			strcpy(pathbuffer, default_resource_filepathl);
		}
		file = fopen(pathbuffer, "w");
		if (!file)
		{
			errorlevel = 1;
			break;
		}

		while (crl)
		{
			errorlevel = fprintf(file, "%lld:[%f,%u,%u,%u,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%lld],\n",
				crl->id,
				crl->gongZi,
				crl->chuShengNian,
				crl->chuShengYue,
				crl->chuShengRi,
				crl->xingMing,
				crl->buMen,
				crl->jiGuan,
				crl->xueLi,
				crl->zhiWu,
				crl->jiangChengJiLu,
				crl->next
			);
			if (errorlevel < 0)
			{
				errorlevel = 2;
				break;
			}
			crl = crl->next;
		}
		if (errorlevel == 2)
		{
			break;
		}

		fclose(file);
		puts("导出成功。");
		errorlevel = 0;
		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 1:
		perror("[ERROR]:打开文件失败");
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 2:
		perror("[ERROR]:从文件中写入内容失败");
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	default:
		break;
	}
	return;
}

void updateRecordl()
{
	int errorlevel = 0;
	struct recordl* crl = headptr_recordl;
	__int64 storage_id = 0;
	int position = -1;
	int mode_number = 0;
	while (1)
	{
		if (!crl)
		{
			printf("当前记录内容为空.\n");
			errorlevel = 0;
			break;
		}
		printf("只能根据存储编号删除记录,如果不知道,请查询\n请输入存储编号:");
		if (scanf(" %lld", &storage_id) != 1)
		{
			errorlevel = 1;
			break;
		}
		for (__int64 i = 1; crl; ++i, crl = crl->next)
		{
			if (storage_id == crl->id)
			{
				position = i;
				printf("即将要更改的记录如下:\n");
				listSingleRecordl(crl);
				break;
			}
		}
		if (position == -1)
		{
			printf("没有找到记录.\n");
			errorlevel = 0;
			break;
		}
		puts("针对什么更改:1:姓名,2:部门,3:籍贯,4:出生年,5:出生月,6:出生日,7:学历/学位,8:职务/职称,9:工资,10:奖惩记录,0:退出");
		mode_number = getInputNumber(10);
		if (mode_number == 0)
		{
			errorlevel = 0;
			break;
		}
		crl = headptr_recordl;
		printf("请输入最新的数据:");
		while (getchar() != '\n') continue;
		while (crl)
		{
			if (crl->id == storage_id)
			{
				if (mode_number == 1)
				{
					char buffer[128];
					memset(buffer, 0, sizeof(buffer));
					scanf("%s", buffer);
					memcpy(crl->xingMing, buffer, sizeof(crl->xingMing));
				}
				else if (mode_number == 2)
				{
					char buffer[128];
					memset(buffer, 0, sizeof(buffer));
					scanf("%s", buffer);
					memcpy(crl->buMen, buffer, sizeof(crl->buMen));
				}
				else if (mode_number == 3)
				{
					char buffer[128];
					memset(buffer, 0, sizeof(buffer));
					scanf("%s", buffer);
					memcpy(crl->jiGuan, buffer, sizeof(crl->jiGuan));
				}
				else if (mode_number == 7)
				{
					char buffer[128];
					memset(buffer, 0, sizeof(buffer));
					scanf("%s", buffer);
					memcpy(crl->xueLi, buffer, sizeof(crl->xueLi));
				}
				else if (mode_number == 8)
				{
					char buffer[128];
					memset(buffer, 0, sizeof(buffer));
					scanf("%s", buffer);
					memcpy(crl->zhiWu, buffer, sizeof(crl->zhiWu));
				}
				else if (mode_number == 10)
				{
					char buffer[128];
					memset(buffer, 0, sizeof(buffer));
					scanf("%s", buffer);
					memcpy(crl->jiangChengJiLu, buffer, sizeof(crl->jiangChengJiLu));
				}
				else if (mode_number == 4)
				{
					unsigned int buffer = 0;
					if (scanf("%d", &buffer) != 1)
					{
						errorlevel = 1;
						break;
					}
					crl->chuShengNian = buffer;
				}
				else if (mode_number == 5)
				{
					unsigned int buffer = 0;
					if (scanf("%d", &buffer) != 1)
					{
						errorlevel = 1;
						break;
					}
					crl->chuShengYue = buffer;
				}
				else if (mode_number == 6)
				{
					unsigned int buffer = 0;
					if (scanf("%d", &buffer) != 1)
					{
						errorlevel = 1;
						break;
					}
					crl->chuShengRi = buffer;
				}
				else if (mode_number == 9)
				{
					float buffer = 0;
					if (scanf("%f", &buffer) != 1)
					{
						errorlevel = 1;
						break;
					}
					crl->gongZi = buffer;
				}
				puts("更改成功。");
				break;
			}
			crl->next;
		}
		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 1:
		while (getchar() != '\n') continue;
		printf("输入有误，请重新输入!\n");
		tsl.taskid = TASKID_UPDATE_RECORD_L;
		break;
	default:
		printInfoAfterAbnormalExit();
		tsl.taskid = 0;
		break;
	}
	return;
}

static int sort_compare_function_1(const void* a, const void* b)
{
	return strcmp((const char*)a + offsetof(struct recordl, xingMing), (const char*)b + offsetof(struct recordl, xingMing));
}
static int sort_compare_function_2(const void* a, const void* b)
{
	return strcmp((const char*)a + offsetof(struct recordl, buMen), (const char*)b + offsetof(struct recordl, buMen));
}
static int sort_compare_function_3(const void* a, const void* b)
{
	return strcmp((const char*)a + offsetof(struct recordl, jiGuan), (const char*)b + offsetof(struct recordl, jiGuan));
}
static int sort_compare_function_4(const void* a, const void* b)
{
	return  *(const unsigned int*)((const char*)a + offsetof(struct recordl, chuShengNian)) - *(const unsigned int*)((const char*)b + offsetof(struct recordl, chuShengNian));
}
static int sort_compare_function_5(const void* a, const void* b)
{
	return  *(const unsigned int*)((const char*)a + offsetof(struct recordl, chuShengYue)) - *(const unsigned int*)((const char*)b + offsetof(struct recordl, chuShengYue));
}
static int sort_compare_function_6(const void* a, const void* b)
{
	return  *(const unsigned int*)((const char*)a + offsetof(struct recordl, chuShengRi)) - *(const unsigned int*)((const char*)b + offsetof(struct recordl, chuShengRi));
}
static int sort_compare_function_7(const void* a, const void* b)
{
	return strcmp((const char*)a + offsetof(struct recordl, xueLi), (const char*)b + offsetof(struct recordl, xueLi));
}
static int sort_compare_function_8(const void* a, const void* b)
{
	return strcmp((const char*)a + offsetof(struct recordl, zhiWu), (const char*)b + offsetof(struct recordl, zhiWu));
}
static int sort_compare_function_9(const void* a, const void* b)
{
	return  *(const float*)((const char*)a + offsetof(struct recordl, gongZi)) - *(const float*)((const char*)b + offsetof(struct recordl, gongZi));
}
static int sort_compare_function_10(const void* a, const void* b)
{
	return strcmp((const char*)a + offsetof(struct recordl, jiangChengJiLu), (const char*)b + offsetof(struct recordl, jiangChengJiLu));
}


int (* const sort_compare_function_array[10])(const void* a, const void* b) = 
{
	sort_compare_function_1,
	sort_compare_function_2,
	sort_compare_function_3,
	sort_compare_function_4,
	sort_compare_function_5,
	sort_compare_function_6,
	sort_compare_function_7,
	sort_compare_function_8,
	sort_compare_function_9,
	sort_compare_function_10
};
void sortRecordl()
{
	int errorlevel = 0;
	int mode_number = 0;
	int node_num = 0;
	struct recordl* crl = headptr_recordl;
	struct recordl* buffer = NULL;
	struct recordl* temp = NULL;
	while (1)
	{
		if (!crl)
		{
			puts("当前记录内容为空.");
			errorlevel = 0;
			break;
		}
		while (crl)
		{
			++node_num;
			crl = crl->next;
		}
		buffer = (struct recordl*)calloc(node_num, sizeof(struct recordl));
		if (!buffer)
		{
			errorlevel = 1;
			break;
		}
		temp = buffer;
		crl = headptr_recordl;
		while (crl)
		{
			memcpy(temp, crl, sizeof(struct recordl));
			++temp;
			crl = crl->next;
		}
		crl = headptr_recordl;
		puts("针对什么排序:1:姓名,2:部门,3:籍贯,4:出生年,5:出生月,6:出生日,7:学历/学位,8:职务/职称,9:工资,10:奖惩记录,0:退出");
		mode_number = getInputNumber(11);
		if (mode_number == 0)
		{
			errorlevel = 2;
			break;
		}
		qsort(buffer, node_num, sizeof(struct recordl), sort_compare_function_array[mode_number-1]);

		puts("----------------排序结果:");
		crl = buffer;
		for (int i = 0; i < node_num; i++)
		{
			listSingleRecordl(&buffer[i]);
		}
		errorlevel = 0;
		free(buffer);
		break;
	}
	switch (errorlevel)
	{
	case 0:
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 1:
		perror("[ERROR]:分配内存失败");
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;
	case 2:
		free(buffer);
		tsl.taskid = TASKID_DISPLAY_ACCESS_CONTROL_MENU_L;
		break;

	default:
		break;
	}
}
