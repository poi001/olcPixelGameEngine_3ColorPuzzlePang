# 3ColorPuzzlePang
 olcPixelGameEngine에서 구현한 퍼즐게임입니다.

## Preview
![ezgif com-video-to-gif](https://github.com/poi001/olcPixelGameEngine_3ColorPuzzlePang/assets/107660181/42b53f70-0027-4450-bbde-ce3235de601b)

## YoutubeLink
https://youtube.com/shorts/mn4AN7mKGrI?feature=share

## 게임 알고리즘
이 게임 기반은 FloodFill알고리즘을 사용했습니다

```
unsigned int mBoardAttrib[5][5] =
	{
		5, 5, 1, 1, 3,
		5, 2, 2, 2, 3,
		5, 4, 2, 3, 2,
		4, 4, 2, 3, 2,
		4, 1, 1, 3, 3
	};
```

화면에 표시되는 게임보드 5by5 배열

```
unsigned int tCheckVisit[5][5] =
	{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};
```

방문 검사 기록용 데이터 5by5 배열

```
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
```

위 코드는 스페이스 바를 누르면 호출되는 리턴형이 int형인 DoCheckBlockAttrib 함수입니다.

첫 번째 매개변수 tCol는 현재 플레이어의 위치의 열(세로)

두 번째 매개변수 tRow는 현재 플레이어의 위치의 행(가로)인 매개변수입니다.

마지막 세 번쨰 매개변수 tColorIndex는 현재 플레이어의 위치의 색깔 정보인 매개변수입니다. (0 = 빈 공간, 1 = 백, 2 = 적, 3 = 녹, 4 = 청, 5 = 황)

위 함수를 아래로 내려가면서 차례로 설명하겠습니다.

```
for (int tRow = 0; tRow < 5; ++tRow)
{
	for (int tCol = 0; tCol < 5; ++tCol)
	{
		tCheckVisit[tRow][tCol] = 0;
	}
}
```

위 코드는 방문 검사 기록용 5x5 배열의 모든 원소를 0으로 초기화하는 코드입니다.

```
while (!mIntStack.empty())
{
	mIntStack.pop();
}
```

자료구조가 stack인 mIntStack를 모두 비우는 코드이다. mIntStack는 밑에서 쓰일 예정입니다.

```
mIntStack.push(tCol);
mIntStack.push(tRow);
```

여기서 부터는 FloodFill알고리즘을 이용하였다. mIntStack에 현재 위치의 열과 행을 차례로 넣습니다.

```
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
```

mIntStack에 원소가 하나도 없을 때까지 반복하는 반복문 while을 선언합니다.

그리고 mIntStack에 맨 위에 있는 원소를 tRow에 그 다음 원소를 tCol에 넣습니다. (Stack이기 때문에 아까 넣었을 때와 반대로 tRow를 먼저 꺼내야 합니다.)

tRow와 tCol이 0보다 작거나 4보다 크면 반복문을 다시 시작합니다. 5x5 배열이기 때문에 행과 열이 0미만 4초과이면 안되기 떄문입니다.

mBoardAttrib[tRow][tCol]에 있는 색과 매개변수tColorIndex의 색이 같지 않으면 반복문을 다시 시작합니다.

tCheckVisit[tRow][tCol]에 있는 원소가 1이면 다시 시작합니다. 이미 방문했다는 뜻이기 떄문입니다.

위에 모든 조건을 만족하지 않는다면 방문 기록용 배열인 tCheckVisit[tRow][tCol]에 1을 삽입하고 tCount를 +1 합니다.(tCount는 같은 색이 몇 개가 붙어 있는지 확인용 변수)

그리고 현재 위치에서 상하좌우의 위치들을 mIntStack에 넣고 while문을 다시 실행합니다.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

지금까지 DoCheckBlockAttrib함수의 정의였고 이제 OnUserUpdate(언리얼로 치면 Tick함수)에서 DoCheckBlockAttrib를 이용하여 인접해 있는 같은 색 공이 3개 이상이면 모두 터뜨리고 다른 색 공을 랜덤하게 채워주는 코드에 대해서 설명하겠습니다.

```
if (GetKey(olc::Key::SPACE).bReleased)
{
	int tColorIndex = mBoardAttrib[mCurY][mCurX];
	int tCount = 0;

	tCount = DoCheckBlockAttrib(mCurX, mCurY, tColorIndex);

	//연속된 색상의 블럭이 3개 이상이면 
	if (tCount >= 3)
	{
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
```

tCount에 DoCheckBlockAttrib함수의 리턴을 받아 넣습니다.

tCount이 3이상이면 방문 기록용 배열을 for문을 이용해 1인 위치를 찾아내 게임보드 배열에서 같은 위치인 곳을 0(빈 공간)으로 설정해놓습니다.

그리고 게임보드 배열을 for문을 이용해 원소가 0인 곳에 rand을 이용하여 랜덤한 색상의 공으로 채워놓습니다.

## 마무리
FloodFill알고리즘을 이용한 퍼즐게임에 대한 설명을 마치겠습니다.
