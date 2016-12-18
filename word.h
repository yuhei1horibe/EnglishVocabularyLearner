

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


//�P��̎�ނ̗�
enum KIND{UNKNOWN, NOUN, VERB, ADJ, ADV, ALL};

//�\�[�g���[�h�̗�
enum MODE{NORMAL, RANDOM};



//�P��f�[�^�������\����
class WORD_DATA{
public:
	//�P��f�[�^
	char*	word;			//�p�P��
	//���
	KIND	kind;			//�P��̎��
	
	char*	mean;			//���{��̈Ӗ�
	char*	example;		//�ᕶ
	char*	Japanese;		//�ᕶ�̓��{���

	WORD_DATA*	next;			//���X�g�|�C���^

	//�R���X�g���N�^����уf�X�g���N�^
	WORD_DATA();
	~WORD_DATA();

	//�o�^���ꂽ�f�[�^������
	void ClearData();
};


class DATA_IO{
private:
	//�f�[�^�m�ۂ̂��߂̕ϐ�
	char		Buffer[512];	//���͕�������ꎞ�I�ɕێ�����o�b�t�@

	//���o�̓X�g���[��
	ifstream	ifs;			//�t�@�C�����̓X�g���[��
	ofstream	ofs;			//�t�@�C���o�̓X�g���[��

	//���삷��t�@�C����
	char		FileName[128];	//�t�@�C���l�[��

public:
	//�R���X�g���N�^
	DATA_IO();

	//�f�X�g���N�^
	~DATA_IO();

	//�t�@�C�����́A����уL�[�{�[�h���͂ɂ��f�[�^���͗p���\�b�h
	//�t�@�C���X�g���[���̏������֐�
	int			Init(char FileName[]);

	//�t�@�C������̓ǂݍ���
	int			ReadFromFile(WORD_DATA* DATA);

	//�L�[�{�[�h����̒��ړ���
//	int			InputFromKeys();

	//�t�@�C���̏����o���p���\�b�h
//	void		Write();
};


//�P��f�[�^�̃f�[�^�x�[�X�Ǘ�
class DATABASE{
private:
	//���X�g
	WORD_DATA	Noun;			//�������X�g
	WORD_DATA	Verb;			//�������X�g
	WORD_DATA	Adjective;		//�`�e�����X�g
	WORD_DATA	Adverb;			//�������X�g

	//���X�g�����̃|�C���^
	WORD_DATA*	TNoun;			//�������X�g�̖���
	WORD_DATA*	TVerb;			//�������X�g�̖���
	WORD_DATA*	TAdjective;		//�`�e�����X�g�̖���
	WORD_DATA*	TAdverb;		//�������X�g�̖���

	//�P��o�^���Ǘ�
	int		NTotal;			//���o�^�P�ꐔ
	int		NNoun;			//�����o�^��
	int		NVerb;			//�����o�^��
	int		NAdjective;		//�`�e���o�^��
	int		NAdverb;		//�����o�^��

	//�t���O
	bool	isSorted;		//����ς݂��ۂ�
	bool	isRandom;		//�����_���\�[�g�ς݂�


	//���[�N�|�C���^
	WORD_DATA*	ptNoun;			//���ݑI�𒆂̖���
	WORD_DATA*	ptVerb;			//���ݑI�𒆂̓���
	WORD_DATA*	ptAdjective;	//���ݑI�𒆂̌`�e��
	WORD_DATA*	ptAdverb;		//���ݑI�𒆂̕���

	//�f�[�^���R�s�[����֐�
	int	Copy(WORD_DATA*	a, const WORD_DATA* b);


	//�\�[�g�Ɋւ��郁�\�b�h
	//���X�g�̃}�[�W
	WORD_DATA* merge_list(WORD_DATA* a, WORD_DATA* b, int (*cmp)(WORD_DATA* a, WORD_DATA* b));

	//�����_���\�[�g�p�}�[�W�֐�
	WORD_DATA* merge_list_rnd(WORD_DATA* a, WORD_DATA* b);

	//�}�[�W�\�[�g�֐�
	WORD_DATA* merge_sort_list(WORD_DATA* x, int (*cmp)(WORD_DATA* a, WORD_DATA* b));

	//�����_���\�[�g�֐�
	WORD_DATA* merge_rndsort(WORD_DATA* x);

	//�R���X�g���N�^
	DATABASE();

public:
	//�f�X�g���N�^
	~DATABASE();

	//�V���O���g���p���������\�b�h
	static DATABASE* GetInstance();


	//�f�[�^�擾�֐��i���[�N�|�C���^���w�������P��f�[�^���擾�j
	int		GetData(KIND kind, WORD_DATA* data);


	//�|�C���^��擪�ɖ߂�
	void	ResetPointer();

	//���X�g���ƂɃ|�C���^��擪�ɖ߂�
	void	ResetListPointer(KIND kind);

	//�f�[�^�o�^����\��
	void	display_number();

	//�f�[�^���������A�������ʂ̃f�[�^���擾
	//void	Serch(char word, WORD_DATA* data);


	//���X�g�Ǘ����\�b�h
	//�����_���\�[�g����і��O���\�[�g�\�ȃ\�[�g�֐�
	void	Sort(MODE mode, int kind = 5);

	//���X�g�ɒP���o�^����֐�
	int		Entry(const WORD_DATA* data);

	//���X�g�J��
	void	ClearList();
};

//��萶������ь��ʕ\���N���X
class QUIZ{
private:
	int		Number;			//�o�肳�ꂽ���̐�
	int		point;			//���_

public:
	//�R���X�g���N�^
	QUIZ();

	//��萶���A�\�����\�b�h
	int		Display(DATABASE* DataBase);

	//���_���萔�Ȃǂ����Z�b�g
	void	Reset();

	//���ʕ\�����\�b�h
	void	Result();
};



//�������r�֐�
int compare(WORD_DATA* a, WORD_DATA* b);
int	rnd(WORD_DATA* a, WORD_DATA* b);
