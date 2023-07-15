# 3ColorPuzzlePang
 olcPixelGameEngine에서 구현한 퍼즐게임입니다.

## Preview
![ezgif com-video-to-gif](https://github.com/poi001/olcPixelGameEngine_3ColorPuzzlePang/assets/107660181/42b53f70-0027-4450-bbde-ce3235de601b)

## YoutubeLink ( 사진을 누르면 유튜브로 넘어갑니다 )
https://youtube.com/shorts/mn4AN7mKGrI?feature=share

## 게임 알고리즘
이 게임 기반은 FloodFill알고리즘을 사용했다

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

