#include <Zaap.h>
#include "system/MemoryManager.h"
#include "system/za_ptr.h"

using namespace zaap;
using namespace graphics;
using namespace API;
using namespace scene;
using namespace gui;
using namespace std;
using namespace system;

//#define TEST_COUNT              2000000
#define TEST_COUNT              200
#define MIX_COUNT               (TEST_COUNT * 10)
#define RAND_SEED               0xf4ed0e7
#define INIT_POSSIBILITIES      9

/* //////////////////////////////////////////////////////////////////////////////// */
// // MemoryManager //
/* //////////////////////////////////////////////////////////////////////////////// */

//	index	|	size		|	probability		|
//	1		|	4			|	0.04			|
//	2		|	8			|	0.09			|
//	3		|	16			|	0.23			|
//	4		|	32			|	0.35			|
//	5		|	64			|	0.10			|
//	6		|	128			|	0.09			|
//	7		|	256			|	0.04			|
//	8		|	512			|	0.03			|
//	9		|	1024		|	0.02			|
uint sizes_[INIT_POSSIBILITIES] = 
	{4		, 8		, 16	, 32	, 64	, 128	, 256	, 512	, 1024	};
float probabilities_[INIT_POSSIBILITIES] = 
	{0.04f	, 0.09f	, 0.23f	, 0.35f	, 0.20f	, 0.05f	, 0.02f	, 0.01f	, 0.01f	};

uint free_order_[TEST_COUNT];
uint init_sizes_[TEST_COUNT];

void* mem_blocks_[TEST_COUNT];

void initArrays()
{
	
	//sizes;
	srand(RAND_SEED);
	float chance;
	float tChance;
	for (uint i = 0; i < TEST_COUNT; i++)
	{
		chance = (float)((float)rand() / RAND_MAX);
		tChance = 0;
		for (uint j = 0; j < INIT_POSSIBILITIES; j++)
		{
			if (chance < tChance + probabilities_[j])
			{
				init_sizes_[i] = sizes_[j];
				break;
			}
			tChance += probabilities_[j];
		}
	}

	//free order
	srand(RAND_SEED);
	for (uint i = 0; i < TEST_COUNT; i++)
	{
		free_order_[i] = i;
	}

	uint i1;
	uint i2;
	uint i1Content;
	for (uint i = 0; i < MIX_COUNT; i++)
	{
		i1 = rand() % TEST_COUNT;
		i2 = rand() % TEST_COUNT;

		//swapping
		i1Content = free_order_[i1];
		free_order_[i1] = free_order_[i2];
		free_order_[i2] = i1Content;
	}
	
	/*cout << "init_sizes_: {";
	for (uint i = 0; i < TEST_COUNT; i++)
		cout << init_sizes_[i] << ", ";
	cout << "}" << endl;

	cout << "free_oderer_: {";
	for (uint i = 0; i < TEST_COUNT; i++)
		cout << free_order_[i] << ", ";
	cout << "}" << endl;*/
	
	cout << "==========================================================" << endl;
	cout << "init finished" << endl;
	cout << "==========================================================" << endl;
}

void runTest()
{
	initArrays();
	
	long totalTimer;
	long allocTimer;
	long freeTimer;
	cout << "Le Test has started" << endl;
	totalTimer = GetTickCount();
	allocTimer = GetTickCount();

	for (uint i = 0; i < TEST_COUNT; i++)
	{
		mem_blocks_[i] = newMalloc(init_sizes_[i]);
	}

	allocTimer = (GetTickCount() - allocTimer);
	freeTimer = GetTickCount();

	for (uint i = 0; i < TEST_COUNT; i++) {
		newFree(mem_blocks_[free_order_[i]]);
	}
	totalTimer = GetTickCount() - totalTimer;
	freeTimer = GetTickCount() - freeTimer;
	cout << "STEEEEP: Le Test has stopped" << endl;
	cout << "The test took:          " << totalTimer << endl;
	cout << "The allocation took:    " << allocTimer << endl;
	cout << "The freeing took:       " << freeTimer << endl;
	cout << "CLOCKS_PER_SEC:         " << CLOCKS_PER_SEC << endl;
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZASmartPointer //
/* //////////////////////////////////////////////////////////////////////////////// */
void ptrTestFunc1(ZASmartPointer<int> i)
{
	ZA_INFO("  => ptrTestFunc1");
	ZA_INFO(*i);
	ZA_INFO("  <= ptrTestFunc1");
	i = (int*)newMalloc(sizeof(int));
}

void ptrTestFunc2(ZASmartPointer<int>& i)
{
	ZA_INFO("  => ptrTestFunc2");
	ZA_INFO(*i);
	ZA_INFO("  <= ptrTestFunc2");
}
void ptrTestFunc3(ZASmartPointer<int> i)
{
	ZASmartPointer<int> tp = i;
	ZA_INFO("  => ptrTestFunc3");
	ZA_INFO(*tp);
	ZA_INFO("  <= ptrTestFunc3");
}
void ptrTestFunc4(ZASmartPointer<int> i)
{
	ZASmartPointer<int> tp = i;
	ZA_INFO("  => ptrTestFunc4");
	ZA_INFO(*i);
	ZA_INFO("  <= ptrTestFunc4");
}
void ptrTestFunc5(ZASmartPointer<int> i)
{
	ZASmartPointer<int> tp = i;
	ZA_INFO("  => ptrTestFunc5");
	ptrTestFunc1(i);
	ptrTestFunc2(i);
	ptrTestFunc3(i);
	ZA_INFO("  <= ptrTestFunc5");
}

void testSmartPtr()
{
	ZA_INFO("============START=================");
	
	ZASmartPointer<int> i((int*)newMalloc(sizeof(int)));
	*i = 10;
	ptrTestFunc1(i);
	//ptrTestFunc2(i);
	//ptrTestFunc3(i);
	//ptrTestFunc4(i);
	//ptrTestFunc5(i);

	ZA_INFO("===========END====================");

}

/* //////////////////////////////////////////////////////////////////////////////// */
// // main //
/* //////////////////////////////////////////////////////////////////////////////// */
int main()
{
	runTest();

	//log::LogOpenFile("log.txt");
	//testSmartPtr();
	//log::LogCloseFile();

	cin.get();
	return 0;
}