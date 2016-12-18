

#include"word.h"


int main(void)
{
	//問題数を入力
	int		n;
	//文字列の入力
	char	str[32];

	WORD_DATA	data;
	int			EFlag;

	//データベース管理インターフェイスへのポインタ
	DATABASE*	DataBase;
	DATA_IO		DataIO;
	QUIZ		Quiz;

	system("title English Word Expert");

	//データベース管理クラスをインスタンス化
	if( (DataBase = DataBase->GetInstance()) == NULL)
	{
		cout << "Error\n";
		return 0;
	}

	cout << "読み込むファイル名を指定してください。\n";
	cin.getline(str, 32);

	//読み込むファイルを指定
	if(DataIO.Init(str))
	{
		getch();
		return 0;
	}

	//ファイルからデータを読み込み
	while( (EFlag = DataIO.ReadFromFile(&data)) == 0)
	{
		//単語をデータベースに登録
		if(DataBase->Entry(&data) == -1)
		{
			cout << "Error\n";
			getch();
			return 0;
		}
	}

	if(EFlag == -1)
	{
		cout << "読み込みエラー\n";
		return 0;
	}

	system("cls");
	DataBase->display_number();
	cout << "\n\n\tPress any key.\n\n";
	getch();
	system("cls");

	//データを念入りにランダムソート
	DataBase->Sort(RANDOM);
	DataBase->Sort(RANDOM);
	DataBase->Sort(RANDOM);
	DataBase->Sort(RANDOM);

	//無限ループ
	while(1)
	{
		system("cls");

		cout << "\n\n何問やるか指定してください。\n終了する場合は0を入力してください。\n";

		cin.getline(str, 32);
		n	= atoi(str);

		if(n == 0)
			break;

		system("cls");

		for(int i = 0; i < n; i++)
		{
			//問題表示
			if(EFlag = Quiz.Display(DataBase))
			{
				if(EFlag == -1)
				{
					cout << "\n\n\tエラーが発生しました。プログラムを中断します。\n";
					getch();
					break;
				}

				else
				{
					//データベースの終端に達したらリストをソートしてやり直し
					DataBase->Sort(RANDOM, EFlag);

					//問題数を元に戻すためにループ変数をデクリメント
					i--;
					system("cls");
				}
			}
		}
		//結果を表示し、ポインタを初期化。得点も初期化
		Quiz.Result();
		getch();
		DataBase->ResetPointer();
		Quiz.Reset();
	}
	return 0;
}
