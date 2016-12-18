

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>
#include<windows.h>
using namespace std;

#define SAFE_DELETE_ARRAY(p) {if(p){delete[] p; p = NULL;}}


class WORD_DATA;
class DATABASE;
class DATA_IO;


//単語の種類の列挙
enum KIND{UNKNOWN, NOUN, VERB, ADJ, ADV, ALL};

//ソートモードの列挙
enum MODE{NORMAL, RANDOM};



//単語データを扱う構造体
class WORD_DATA{
public:
	//単語データ
	char*	word;			//英単語
	//種類
	KIND	kind;			//単語の種類
	
	char*	mean;			//日本語の意味
	char*	example;		//例文
	char*	Japanese;		//例文の日本語訳

	WORD_DATA*	next;			//リストポインタ

	//コンストラクタおよびデストラクタ
	WORD_DATA();
	~WORD_DATA();

	//登録されたデータを消去
	void ClearData();
};


class DATA_IO{
private:
	//データ確保のための変数
	char		Buffer[512];	//入力文字列を一時的に保持するバッファ

	//入出力ストリーム
	ifstream	ifs;			//ファイル入力ストリーム
	ofstream	ofs;			//ファイル出力ストリーム

	//操作するファイル名
	char		FileName[128];	//ファイルネーム

public:
	//コンストラクタ
	DATA_IO();

	//デストラクタ
	~DATA_IO();

	//ファイル入力、およびキーボード入力によるデータ入力用メソッド
	//ファイルストリームの初期化関数
	int			Init(char FileName[]);

	//ファイルからの読み込み
	int			ReadFromFile(WORD_DATA* DATA);

	//キーボードからの直接入力
//	int			InputFromKeys();

	//ファイルの書き出し用メソッド
//	void		Write();
};


//単語データのデータベース管理
class DATABASE{
private:
	//リスト
	WORD_DATA	Noun;			//名詞リスト
	WORD_DATA	Verb;			//動詞リスト
	WORD_DATA	Adjective;		//形容詞リスト
	WORD_DATA	Adverb;			//副詞リスト

	//リスト末尾のポインタ
	WORD_DATA*	TNoun;			//名詞リストの末尾
	WORD_DATA*	TVerb;			//動詞リストの末尾
	WORD_DATA*	TAdjective;		//形容詞リストの末尾
	WORD_DATA*	TAdverb;		//副詞リストの末尾

	//単語登録数管理
	int		NTotal;			//総登録単語数
	int		NNoun;			//名詞登録数
	int		NVerb;			//動詞登録数
	int		NAdjective;		//形容詞登録数
	int		NAdverb;		//副詞登録数

	//フラグ
	bool	isSorted;		//整列済みか否か
	bool	isRandom;		//ランダムソート済みか


	//ワークポインタ
	WORD_DATA*	ptNoun;			//現在選択中の名詞
	WORD_DATA*	ptVerb;			//現在選択中の動詞
	WORD_DATA*	ptAdjective;	//現在選択中の形容詞
	WORD_DATA*	ptAdverb;		//現在選択中の副詞

	//データをコピーする関数
	int	Copy(WORD_DATA*	a, const WORD_DATA* b);


	//ソートに関するメソッド
	//リストのマージ
	WORD_DATA* merge_list(WORD_DATA* a, WORD_DATA* b, int (*cmp)(WORD_DATA* a, WORD_DATA* b));

	//ランダムソート用マージ関数
	WORD_DATA* merge_list_rnd(WORD_DATA* a, WORD_DATA* b);

	//マージソート関数
	WORD_DATA* merge_sort_list(WORD_DATA* x, int (*cmp)(WORD_DATA* a, WORD_DATA* b));

	//ランダムソート関数
	WORD_DATA* merge_rndsort(WORD_DATA* x);

	//コンストラクタ
	DATABASE();

public:
	//デストラクタ
	~DATABASE();

	//シングルトン用初期化メソッド
	static DATABASE* GetInstance();


	//データ取得関数（ワークポインタが指し示す単語データを取得）
	int		GetData(KIND kind, WORD_DATA* data);


	//ポインタを先頭に戻す
	void	ResetPointer();

	//リストごとにポインタを先頭に戻す
	void	ResetListPointer(KIND kind);

	//データ登録数を表示
	void	display_number();

	//データを検索し、検索結果のデータを取得
	//void	Serch(char word, WORD_DATA* data);


	//リスト管理メソッド
	//ランダムソートおよび名前順ソート可能なソート関数
	void	Sort(MODE mode, int kind = 5);

	//リストに単語を登録する関数
	int		Entry(const WORD_DATA* data);

	//リスト開放
	void	ClearList();
};

//問題生成および結果表示クラス
class QUIZ{
private:
	int		Number;			//出題された問題の数
	int		point;			//得点

public:
	//コンストラクタ
	QUIZ();

	//問題生成、表示メソッド
	int		Display(DATABASE* DataBase);

	//得点や問題数などをリセット
	void	Reset();

	//結果表示メソッド
	void	Result();
};



//文字列比較関数
int compare(WORD_DATA* a, WORD_DATA* b);
int	rnd(WORD_DATA* a, WORD_DATA* b);
