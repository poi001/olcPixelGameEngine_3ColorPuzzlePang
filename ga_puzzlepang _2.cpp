#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <stack>

using namespace std;

//매크로 문법
//	매크로 상수 
#define CONTINUOUS_BLOCK_COUNT 3

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
	//CIntStack는 앞으로 stack<int>로 정의된다.
	typedef stack<int> CIntStack;

	//스택자료구조 변수 선언 
	CIntStack mIntStack;



	olc::Pixel mColor[6] =
	{
		olc::BLACK, //아무것도 없음
		//퍼즐피스 색상들
		olc::WHITE,			//1
		olc::RED,			//2
		olc::GREEN,			//3
		olc::BLUE,			//4
		olc::YELLOW			//5
	};

	//5by5 board
	//화면에 표시되는 게임보드 데이터 
	//각 '셀'에 어떤 종류의 '퍼즐피스'가 들어있는지에 대한 정보가 기록되어 있다
	unsigned int mBoardAttrib[5][5] =
	{
		5, 5, 1, 1, 3,
		5, 2, 2, 2, 3,
		5, 4, 2, 3, 2,
		4, 4, 2, 3, 2,
		4, 1, 1, 3, 3
	};


	//방문 검사 기록용 데이터 
	unsigned int tCheckVisit[5][5] =
	{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};


	//select block indicator UI
	int mCurX = 0;
	int mCurY = 0;


public:
	Example()
	{
		// Name your application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels


		if (GetKey(olc::Key::LEFT).bReleased)
		{
			mCurX = mCurX - 1;
		}

		if (GetKey(olc::Key::RIGHT).bReleased)
		{
			mCurX = mCurX + 1;
		}


		if (GetKey(olc::Key::UP).bReleased)
		{
			mCurY = mCurY - 1;
		}

		if (GetKey(olc::Key::DOWN).bReleased)
		{
			mCurY = mCurY + 1;
		}

		if (GetKey(olc::Key::SPACE).bReleased)
		{
			std::cout << "hit" << std::endl;


			int tColorIndex = mBoardAttrib[mCurY][mCurX];

			cout << "tColorIndex\t" << tColorIndex << endl;


			int tCount = 0;

			tCount = DoCheckBlockAttrib(mCurX, mCurY, tColorIndex);
			//연속된 색상의 블럭이 3개 이상이면 
			//if (tCount >= 3 )
			if (tCount >= CONTINUOUS_BLOCK_COUNT)
			{
				cout << "연속된 색상의 블럭이 3개 이상입니다. " << tCount << endl;


				//체크된 위치의 색상블럭들을 제거한다 
				for (int tRow = 0; tRow < 5; ++tRow)
				{
					for (int tCol = 0; tCol < 5; ++tCol)
					{
						if (1 == tCheckVisit[tRow][tCol])
						{
							mBoardAttrib[tRow][tCol] = 0;
						}
					}
				}

				cout << "새로운 색상블럭 생성" << endl;

				//비워진 곳에 새로운 색상 블럭을 랜덤한 색상으로 생성한다 
				for (int tRow = 0; tRow < 5; ++tRow)
				{
					for (int tCol = 0; tCol < 5; ++tCol)
					{
						if (0 == mBoardAttrib[tRow][tCol])
						{
							int tRandAttrib = rand() % 5 + 1;
							mBoardAttrib[tRow][tCol] = tRandAttrib;
						}
					}
				}

			}

		}





		//clear
		Clear(olc::VERY_DARK_BLUE);


		//render



		//display game board
		for (int tRow = 0; tRow < 5; ++tRow)
		{
			for (int tCol = 0; tCol < 5; ++tCol)
			{
				int tIndex = mBoardAttrib[tRow][tCol];

				DrawCircle(
					tCol * 20 + 100,
					tRow * 20 + 100,
					9,
					mColor[tIndex]);
			}
		}

		//display UI
		DrawCircle(
			mCurX * 20 + 100,
			mCurY * 20 + 100,
			5,
			olc::WHITE
		);




		return true;
	}

	//선언
	int DoCheckBlockAttrib(int tCol, int tRow, int tColorIndex);
};

int main()
{
	Example demo;
	if (demo.Construct(256, 240, 2, 2))
		demo.Start();
	return 0;
}

//정의 
int Example::DoCheckBlockAttrib(int tCol, int tRow, int tColorIndex)
{
	int tCount = 0;

	//clear tCheckVisit
	for (int tRow = 0; tRow < 5; ++tRow)
	{
		for (int tCol = 0; tCol < 5; ++tCol)
		{
			tCheckVisit[tRow][tCol] = 0;
		}
	}

	//clear stack
	while (!mIntStack.empty())
	{
		mIntStack.pop();
	}

	//flood fill
	mIntStack.push(tCol);
	mIntStack.push(tRow);

	//스택에 원소(셀의 위치값)가 하나라도 있다면
	while (!mIntStack.empty())
	{
		//스택에 원소를 하나 끄집어내서 
		tRow = mIntStack.top();
		mIntStack.pop();
		tCol = mIntStack.top();
		mIntStack.pop();

		//경계처리
		if (tRow < 0 || tRow > 4)
		{
			continue;
		}
		//경계처리
		if (tCol < 0 || tCol > 4)
		{
			continue;
		}
		//색상블럭의 값이 현재 찾으려는 색상이 아니라면 
		if (tColorIndex != mBoardAttrib[tRow][tCol])
		{
			continue;
		}



		if (1 == tCheckVisit[tRow][tCol])
		{
			continue;
		}

		cout << "remember block: " << tRow << ", " << tCol << endl;

		//체크한다( 기록해둔다 )
		tCheckVisit[tRow][tCol] = 1;

		//( 찾으려는 색상의 )연속적으로 연결된 블럭이 몇개인지 카운트한다 
		tCount++;





		//사방의 위치 정보를 스택자료구조에 담는다
		mIntStack.push(tCol - 1);
		mIntStack.push(tRow);

		mIntStack.push(tCol + 1);
		mIntStack.push(tRow);

		mIntStack.push(tCol);
		mIntStack.push(tRow - 1);

		mIntStack.push(tCol);
		mIntStack.push(tRow + 1);
	}

	return tCount;
}