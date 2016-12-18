

#include"word.h"
#include<time.h>

#define DEBUG	1

#define SHURUI	4


//ワードクラスコンストラクタ
WORD_DATA::WORD_DATA()
{
	//ポインタをすべてNULLに初期化
	word		= NULL;
	kind		= UNKNOWN;
	mean		= NULL;
	example		= NULL;
	Japanese	= NULL;
	next		= NULL;
}

//ワードクラスデストラクタ
WORD_DATA::~WORD_DATA()
{
	//データを消去
	ClearData();
}

//データの消去
void	WORD_DATA::ClearData()
{
	//データをすべて開放
	SAFE_DELETE_ARRAY(word);
	SAFE_DELETE_ARRAY(mean);
	SAFE_DELETE_ARRAY(example);
	SAFE_DELETE_ARRAY(Japanese);

	kind	= UNKNOWN;
}


//データベースクラスコンストラクタ
DATABASE::DATABASE()
{
	//リストの末尾のポインタを初期化
	TNoun		= &Noun;
	TVerb		= &Verb;
	TAdjective	= &Adjective;
	TAdverb		= &Adverb;

	//ダミーの次（先頭へのポインタ）をNULLに初期化
	Noun.next		= NULL;
	Verb.next		= NULL;
	Adjective.next	= NULL;
	Adverb.next		= NULL;

	//単語登録数を０に初期化
	NTotal			= 0;
	NNoun			= 0;
	NVerb			= 0;
	NAdjective		= 0;
	NAdverb			= 0;

	//フラグを初期化
	isSorted		= FALSE;
	isRandom		= FALSE;

	//ワークポインタをリストの先頭にセット
	ptNoun			= &Noun;
	ptVerb			= &Verb;
	ptAdjective		= &Adjective;
	ptAdverb		= &Adverb;

	srand((unsigned)time(NULL));
}

//データベース管理クラスデストラクタ
DATABASE::~DATABASE()
{
	ClearList();
}

//ポインタを先頭に戻す
void	DATABASE::ResetPointer()
{
	//ワークポインタをリストの先頭にセット
	//ワークポインタをリストの先頭にセット
	ptNoun			= &Noun;
	ptVerb			= &Verb;
	ptAdjective		= &Adjective;
	ptAdverb		= &Adverb;
}

//リストのポインタを先頭に戻す
void	DATABASE::ResetListPointer(KIND kind)
{
	switch(kind)
	{
	case NOUN:
		ptNoun		= &Noun;
		break;
		
	case VERB:
		ptVerb		= &Verb;
		break;

	case ADJ:
		ptAdjective	= &Adjective;
		break;

	case ADV:
		ptAdverb	= &Adverb;
		break;
	}
}



//一個のリストをクリアする関数
void Clear(WORD_DATA* List)
{
	WORD_DATA*	wp1;		//ワークポインタ１
	WORD_DATA*	wp2;		//ワークポインタ２

	if(List == NULL)
		return ;

	//ワークポインタを先頭に初期化
	wp1	= List;
	wp2	= List->next;

	while(wp2 != NULL)
	{
		delete wp1;
		wp1	= wp2;
		wp2	= wp2->next;
	}
	delete wp1;
}

//リストをすべてクリア
void DATABASE::ClearList()
{
	//すべてのリストをクリア
	Clear(Noun.next);
	Clear(Verb.next);
	Clear(Adjective.next);
	Clear(Adverb.next);
	//末尾のポインタを初期化
	TNoun		= &Noun;
	TVerb		= &Verb;
	TAdjective	= &Adjective;
	TAdverb		= &Adverb;

	//ダミーの次（先頭へのポインタ）をNULLに初期化
	Noun.next		= NULL;
	Verb.next		= NULL;
	Adjective.next	= NULL;
	Adverb.next		= NULL;

	//単語登録数を０に初期化
	NTotal			= 0;
	NNoun			= 0;
	NVerb			= 0;
	NAdjective		= 0;
	NAdverb			= 0;

	//フラグを初期化
	isSorted		= FALSE;
	isRandom		= FALSE;

	ResetPointer();
}

//データをコピーする関数
int	DATABASE::Copy(WORD_DATA* a, const WORD_DATA* b)
{
	int	Length;

	if(b == NULL)
		return -1;

	//単語
	Length	= strlen(b->word);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->word	= new char[Length + 1];

	if(!a->word)
	{
		cout << "メモリ確保に失敗しました\n";
		return -1;
	}
	strcpy(a->word, b->word);

	//種類
	a->kind	= b->kind;

	//意味
	Length	= strlen(b->mean);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->mean	= new char[Length + 1];

	if(!a->mean)
	{
		cout << "メモリ確保に失敗しました\n";
		return -1;
	}
	strcpy(a->mean, b->mean);

	//例文
	Length	= strlen(b->example);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->example	= new char[Length + 1];

	if(!a->example)
	{
		cout << "メモリ確保に失敗しました\n";
		return -1;
	}
	strcpy(a->example, b->example);

	//例文の日本語訳
	Length	= strlen(b->Japanese);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->Japanese	= new char[Length + 1];

	if(!a->Japanese)
	{
		cout << "メモリ確保に失敗しました\n";
		return -1;
	}
	strcpy(a->Japanese, b->Japanese);

	return 0;
}

//インスタンス作成関数
DATABASE* DATABASE::GetInstance()
{
	//インスタンスを作成
	static DATABASE		Instance;

	return &Instance;
}

//リストのソート関数。ランダムソートと通常のソートを使い分け可能
void DATABASE::Sort(MODE mode, int kind)
{
	if(mode == NORMAL)
	{
		Noun.next		= merge_sort_list(Noun.next, compare);
		Verb.next		= merge_sort_list(Verb.next, compare);
		Adjective.next	= merge_sort_list(Adjective.next, compare);
		Adverb.next		= merge_sort_list(Adverb.next, compare);

		//ワークポインタをリストの先頭にセット
		ResetPointer();
		isSorted	= TRUE;
		isRandom	= FALSE;
	}

	else
	{
		switch(kind)
		{
		case NOUN:
			Noun.next		= merge_sort_list(Noun.next, rnd);
			ResetListPointer(NOUN);
			break;

		case VERB:
			Verb.next		= merge_sort_list(Verb.next, rnd);
			ResetListPointer(VERB);
			break;
		
		case ADJ:
			Adjective.next	= merge_sort_list(Adjective.next, rnd);
			ResetListPointer(ADJ);
			break;

		case ADV:
			Adverb.next		= merge_sort_list(Adverb.next, rnd);
			ResetListPointer(ADV);
			break;

		case ALL:
			Noun.next		= merge_sort_list(Noun.next, rnd);
			Verb.next		= merge_sort_list(Verb.next, rnd);
			Adjective.next	= merge_sort_list(Adjective.next, rnd);
			Adverb.next		= merge_sort_list(Adverb.next, rnd);

			//ワークポインタをリストの先頭にセット
			ResetPointer();
			break;
		}

		isSorted	= FALSE;
		isRandom	= TRUE;
	}


	//末尾のポインタを更新
	TNoun		= &Noun;
	TVerb		= &Verb;
	TAdjective	= &Adjective;
	TAdverb		= &Adverb;

	while(TNoun->next != NULL)
		TNoun		= TNoun->next;

	while(TVerb->next != NULL)
		TVerb		= TVerb->next;

	while(TAdjective->next != NULL)
		TAdjective	= TAdjective->next;

	while(TAdverb->next != NULL)
		TAdverb		= TAdverb->next;
}

//リストに単語を登録する関数
int DATABASE::Entry(const WORD_DATA* data)
{
	WORD_DATA*	data1;

	if(data == NULL)
	{
		cout << "登録する単語がありません\n";
		return -1;
	}

	//単語データ登録用メモリを確保
	data1	= new WORD_DATA;

	//メモリ確保に失敗
	if(data1 == NULL)
	{
		cout << "メモリ確保に失敗しました\n";
		return -1;
	}

	if(Copy(data1, data))
		return -1;

	//リストに追加
	switch(data1->kind)
	{
	case NOUN:
		TNoun->next	= data1;
		TNoun		= data1;
		TNoun->next	= NULL;
		NNoun++;
		break;

	case VERB:
		TVerb->next	= data1;
		TVerb		= data1;
		TVerb->next	= NULL;
		NVerb++;
		break;

	case ADJ:
		TAdjective->next	= data1;
		TAdjective			= data1;
		TAdjective->next	= NULL;
		NAdjective++;
		break;

	case ADV:
		TAdverb->next	= data1;
		TAdverb			= data1;
		TAdverb->next	= NULL;
		NAdverb++;
		break;

	default:
		cout << data1->word;
		cout << "\n\n単語の種類の指定がありません\n";
		return -1;
	}

	//単語登録数を更新
	NTotal++;

	//ソートされているかどうかのフラグをリセット
	isSorted	= FALSE;
	isRandom	= FALSE;

	return 0;
}

//データを取得するメソッド
int	DATABASE::GetData(KIND kind, WORD_DATA* data)
{
	//ワークポインタが指し示すデータをコピーし、ワークポインタを更新
	switch(kind)
	{
	case NOUN:
		if(!ptNoun->next)
			return NOUN;
		ptNoun	= ptNoun->next;

		Copy(data, ptNoun);
		break;

	case VERB:
		if(!ptVerb->next)
			return VERB;
		ptVerb	= ptVerb->next;

		Copy(data, ptVerb);
		break;

	case ADJ:
		if(!ptAdjective->next)
			return ADJ;
		ptAdjective	= ptAdjective->next;

		Copy(data, ptAdjective);
		break;

	case ADV:
		if(!ptAdverb->next)
			return ADV;
		ptAdverb	= ptAdverb->next;

		Copy(data, ptAdverb);
		break;

	default:
		cout << "種類の指定がありません\n";
		return -1;
	}

	return 0;
}

//単語登録数を表示する関数
void	DATABASE::display_number()
{
	cout << "総単語数：" << NTotal << "\n名詞登録数：\t" << NNoun << "\n動詞登録数：\t" << NVerb << "\n形容詞登録数：\t" << NAdjective << "\n副詞登録数：\t" << NAdverb << endl;
}

//リストの整列
WORD_DATA*	DATABASE::merge_sort_list(WORD_DATA* x, int (*cmp)(WORD_DATA* a, WORD_DATA* b))
{
	//ワークポインタ
	WORD_DATA*	a;
	WORD_DATA*	b;
	WORD_DATA*	p;

	int		cnt	= 0;

	//リストに要素がないか、ひとつしかない場合はリターン
	if(x == NULL || x->next == NULL)
		return x;

	//リストをスキャンするポインタ
	a	= x;
	b	= x->next;

	if(b != NULL)
		b	= b->next;

	//リストの要素数をカウント
	while(b != NULL)
	{
		//aはポインタをひとつたどり
		a	= a->next;
		b	= b->next;

		//bはポインタを二個たどる
		if(b != NULL)
			b	= b->next;
	}

	//リストを中央で分断
	p		= a->next;
	a->next	= NULL;

	return merge_list(merge_sort_list(x, cmp), merge_sort_list(p, cmp), cmp);
}

//リストのマージ関数（通常のソート）
WORD_DATA*	DATABASE::merge_list(WORD_DATA* a, WORD_DATA* b, int (*cmp)(WORD_DATA* a, WORD_DATA* b))
{
	//ダミー
	WORD_DATA	head;
	WORD_DATA*	p;

	//ポインタpがダミーの要素を示すようにする
	p	= &head;

	//リストの一方が空になるまで
	while((a != NULL) && (b != NULL))
	{
		//リストの先頭要素の比較
		if((*cmp)(a, b))
		{
			//aのほうが小さければ、aの要素を取り出し、末尾に付加
			p->next	= a;
			p		= a;
			a		= a->next;
		}

		else
		{
			//bのほうが小さければ、bの要素を取り出し、末尾に付加
			p->next	= b;
			p		= b;
			b		= b->next;
		}
	}

	//残っているリストを末尾に付加
	if(a == NULL)
		p->next	= b;

	else
		p->next	= a;

	return head.next;
}

//文字列比較関数
int	compare(WORD_DATA* a, WORD_DATA* b)
{
	int		i	= 0;

	//同じ文字列だったらリターン
	if(!strcmp(a->word, b->word))
		return 1;

	while(a->word[i] == b->word[i])
		i++;

	if(a->word[i] < a->word[i])
		return 1;

	return 0;
}

//ランダムで0と1を発生する関数
int	rnd(WORD_DATA* a, WORD_DATA* b)
{
	return rand() % 2;
}





//ファイル入出力クラス
DATA_IO::DATA_IO()
{
}

//デストラクタ
DATA_IO::~DATA_IO()
{
	if(ifs)
		ifs.close();
}


//初期化関数
int	DATA_IO::Init(char FileName[])
{
	//ファイルをオープン
	ifs.open(FileName);

	if(!ifs)
	{
		cout << "ファイルをオープンできませんでした。\n";
		return -1;
	}

	return 0;
}


//ファイルからの読み込み関数
int	DATA_IO::ReadFromFile(WORD_DATA* DATA)
{
	int		Length;		//文字列の長さを保持

	if(!DATA)
		return -1;

	if(!ifs.getline(Buffer, sizeof Buffer))
		return 1;


	//文字の長さを取得
	Length	= strlen(Buffer);

	//入力された文字数分のメモリを確保し、記録
	DATA->word	= new char[Length + 1];

	if(DATA->word == NULL)
	{
		cout << "メモリ確保に失敗しました。\n";
		return -1;
	}

	//データをロード
	strcpy(DATA->word, Buffer);

	//単語の種類を判別
	if(!ifs.getline(Buffer, sizeof Buffer))
		return -1;

	//データの種類を登録
	if(!strcmp(Buffer, "名"))
		DATA->kind	= NOUN;

	else if(!strcmp(Buffer, "動"))
		DATA->kind	= VERB;

	else if(!strcmp(Buffer, "形"))
		DATA->kind	= ADJ;

	else if(!strcmp(Buffer, "副"))
		DATA->kind	= ADV;

	//指定がなければ不明のフラグを立てる
	else
		DATA->kind	= UNKNOWN;

	//データを取得
	if(!ifs.getline(Buffer, sizeof Buffer))
		return -1;

	//文字の長さを取得
	Length	= strlen(Buffer);

	//入力された文字数分のメモリを確保し、記録
	DATA->mean	= new char[Length + 1];

	if(DATA->mean == NULL)
	{
		cout << "メモリ確保に失敗しました。\n";
		return -1;
	}

	//データをロード
	strcpy(DATA->mean, Buffer);

	//データを取得
	if(!ifs.getline(Buffer, sizeof Buffer))
		return -1;

	//文字の長さを取得
	Length	= strlen(Buffer);

	if(Length != 0)
	{
		//入力された文字数分のメモリを確保し、記録
		DATA->example	= new char[Length + 1];

		if(DATA->example == NULL)
		{
			cout << "メモリ確保に失敗しました。\n";
			return -1;
		}

		//データをロード
		strcpy(DATA->example, Buffer);

		if(!ifs.getline(Buffer, sizeof Buffer))
			return -1;

		//文字の長さを取得
		Length	= strlen(Buffer);

		//入力された文字数分のメモリを確保し、記録
		DATA->Japanese	= new char[Length + 1];

		if(DATA->Japanese == NULL)
		{
			cout << "メモリ確保に失敗しました。\n";
			return -1;
		}

		//データをロード
		strcpy(DATA->Japanese, Buffer);

		return 0;
	}

	return 0;
}


//問題出題クラスコンストラクタ
QUIZ::QUIZ()
{
	Number	= 0;
	point	= 0;
}


//問題出題関数
int QUIZ::Display(DATABASE* DataBase)
{
	int			answer;		//選択肢問題の回答番号
	char		MODE;		//出題形式
	KIND		Kind;		//出題する単語の品詞
	char		temp[256];	//正解を一時的に記憶
	char		input[64];	//ユーザーからの答えの入力
	int			Num;		//ユーザーからの数値入力
	int			result;		//比較結果の一時記憶
	int			n;			//一時変数
	WORD_DATA	data;		//単語データを一時的に記憶
	int			EFlag;		//エラーの種類を判別
	int			i;			//ループ制御変数
	int			k;			//ループ制御変数
	int			l;			//ループ制御変数


	//出題する問題の形式を乱数で決定
	MODE	= rand() % 4 + 1;

	//どの品詞から出題するかを決定(ただし非０の結果)
	n	= (rand() % SHURUI);
		
	switch(n)
	{
	case 0:
		Kind	= NOUN;
		break;

	case 1:
		Kind	= VERB;
		break;

	case 2:
		Kind	= ADJ;
		break;

	case 3:
		Kind	= ADV;
		break;
	}


	//画面を初期化
	system("cls");

	cout << "第" << Number + 1 << "問\n\n";

	//出題する単語をデータベースから取得（ただし、リストが終端に達するかエラーが起きたらリターン）
	if(EFlag = DataBase->GetData(Kind, &data))
		return EFlag;


	//問題をパターンごとに出題
	switch(MODE)
	{
	case 1:
		cout << "\n\t次の単語の意味を選択肢から選び、記号で答えよ。\n\n" << '\t' << data.word << endl;
		cout << endl;

		//正解の番号をランダムで決定
		answer	= (rand() % 4) + 1;

		//正解を一時的に記憶
		strcpy(temp, data.mean);

		//選択肢４つ分のループ
		for(i = 1; i < 5; i++)
		{
			//正解番号の選択肢表示（正解を表示）
			if(i == answer)
				cout << '\t' << i << "：" << temp << endl;

			//ダミーの表示
			else
			{
				//一時的に読み込んだ単語データの削除
				data.ClearData();

				//ダミーの読み込み
				if(EFlag = DataBase->GetData(Kind, &data))
					return EFlag;

				//ダミーを表示
				cout << '\t' << i << "：" << data.mean << '\n';
			}
		}
		break;

	case 2:
		cout << "\n\t次の意味を持つ英単語を選択肢から選び、記号で答えよ。\n\n" << '\t' << data.mean << endl;
		cout << endl;

		//正解の番号をランダムで決定
		answer	= (rand() % 4) + 1;

		//正解を一時的に記憶
		strcpy(temp, data.word);

		//選択肢４つ分のループ
		for(i = 1; i < 5; i++)
		{
			//正解番号の選択肢表示（正解を表示）
			if(i == answer)
				cout << '\t' << i << "：" << temp << endl;

			//ダミーの表示
			else
			{
				//一時的に読み込んだ単語データの削除
				data.ClearData();

				//ダミーの読み込み
				if(EFlag = DataBase->GetData(Kind, &data))
					return EFlag;

				//ダミーを表示
				cout << '\t' << i << "：" << data.word << '\n';
			}
		}
		break;

	case 3:
		cout << "\n\t次の意味を持つ英単語を書け。\n\n" << '\t' << data.mean << '\n';
		cout << '\n';

		strcpy(temp, data.word);
		break;

	case 4:
		cout << "\n\t次の例文の()を埋めよ。\n\n\t";
		
		k	= 0;
		while( (data.example[k] != '(') && (data.example[k] != '\0') )
		{
			putchar(data.example[k]);
			k++;
		}

		if(data.example[k] == '\0')
		{
			cout << "例文に()の指定がありません。\n";
			return -1;
		}

		putchar('(');

		k++;
		l	= 0;
		while( (data.example[k] != ')') && (data.example[k] != '\0') )
		{
			temp[l]	= data.example[k];
			putchar(' ');
			k++;
			l++;
		}

		temp[l]	= '\0';

		if(data.example[k] == '\0')
		{
			cout << "例文に()の指定がありません。\n";
			return -1;
		}

		putchar(')');

		k++;

		while(data.example[k] != '\0')
		{
			putchar(data.example[k]);
			k++;
		}

		cout << endl;

		cout << '\t' << data.Japanese;
		cout << "\n\n";
		break;
	}


	//ユーザーからの入力待ち
	cout << "\n\n";
	cout << "Put your answer.\n\n";

	//ユーザーからの答えの入力
	cin.getline(input, 64);

	//選択肢問題の時の正解判定
	if(MODE < 3)
	{
		//答えを数値に変換
		Num		= atoi(input);

		//正解か間違えかの判定
		result	= (Num == answer);
	}

	//英単語書き抜き問題の時の正解判定
	else
	{
		//正解か間違えかの判定
		result	= (strcmp(input, temp) == 0);
	}


	//正解した場合
	if(result)
	{
		cout << "\n\t\t\t正解です。\n\n\t\t\t" << "Press any key.\n";
		point++;
	}

	//間違っていた場合
	else
		cout << "\n\t\t\t残念。正解は「" << temp << "」です。\n\n\t\t\t" << "Press any key.\n";

	getch();

	//出題数を更新
	Number++;

	return 0;
}

//結果表示メソッド
void QUIZ::Result()
{
	system("cls");

	cout << "お疲れ様でした。\n\n\n";
	cout << "今回の結果は、\n問題数：" << Number << '\n';
	cout << "正解数：" << point << '\n';
	cout << "正答率：" << ((float)point / Number) * 100 << "%でした。" << '\n';
}

void QUIZ::Reset()
{
	Number	= 0;
	point	= 0;
}
