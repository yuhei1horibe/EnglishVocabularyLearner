

#include"word.h"
#include<time.h>

#define DEBUG	1

#define SHURUI	4


//���[�h�N���X�R���X�g���N�^
WORD_DATA::WORD_DATA()
{
	//�|�C���^�����ׂ�NULL�ɏ�����
	word		= NULL;
	kind		= UNKNOWN;
	mean		= NULL;
	example		= NULL;
	Japanese	= NULL;
	next		= NULL;
}

//���[�h�N���X�f�X�g���N�^
WORD_DATA::~WORD_DATA()
{
	//�f�[�^������
	ClearData();
}

//�f�[�^�̏���
void	WORD_DATA::ClearData()
{
	//�f�[�^�����ׂĊJ��
	SAFE_DELETE_ARRAY(word);
	SAFE_DELETE_ARRAY(mean);
	SAFE_DELETE_ARRAY(example);
	SAFE_DELETE_ARRAY(Japanese);

	kind	= UNKNOWN;
}


//�f�[�^�x�[�X�N���X�R���X�g���N�^
DATABASE::DATABASE()
{
	//���X�g�̖����̃|�C���^��������
	TNoun		= &Noun;
	TVerb		= &Verb;
	TAdjective	= &Adjective;
	TAdverb		= &Adverb;

	//�_�~�[�̎��i�擪�ւ̃|�C���^�j��NULL�ɏ�����
	Noun.next		= NULL;
	Verb.next		= NULL;
	Adjective.next	= NULL;
	Adverb.next		= NULL;

	//�P��o�^�����O�ɏ�����
	NTotal			= 0;
	NNoun			= 0;
	NVerb			= 0;
	NAdjective		= 0;
	NAdverb			= 0;

	//�t���O��������
	isSorted		= FALSE;
	isRandom		= FALSE;

	//���[�N�|�C���^�����X�g�̐擪�ɃZ�b�g
	ptNoun			= &Noun;
	ptVerb			= &Verb;
	ptAdjective		= &Adjective;
	ptAdverb		= &Adverb;

	srand((unsigned)time(NULL));
}

//�f�[�^�x�[�X�Ǘ��N���X�f�X�g���N�^
DATABASE::~DATABASE()
{
	ClearList();
}

//�|�C���^��擪�ɖ߂�
void	DATABASE::ResetPointer()
{
	//���[�N�|�C���^�����X�g�̐擪�ɃZ�b�g
	//���[�N�|�C���^�����X�g�̐擪�ɃZ�b�g
	ptNoun			= &Noun;
	ptVerb			= &Verb;
	ptAdjective		= &Adjective;
	ptAdverb		= &Adverb;
}

//���X�g�̃|�C���^��擪�ɖ߂�
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



//��̃��X�g���N���A����֐�
void Clear(WORD_DATA* List)
{
	WORD_DATA*	wp1;		//���[�N�|�C���^�P
	WORD_DATA*	wp2;		//���[�N�|�C���^�Q

	if(List == NULL)
		return ;

	//���[�N�|�C���^��擪�ɏ�����
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

//���X�g�����ׂăN���A
void DATABASE::ClearList()
{
	//���ׂẴ��X�g���N���A
	Clear(Noun.next);
	Clear(Verb.next);
	Clear(Adjective.next);
	Clear(Adverb.next);
	//�����̃|�C���^��������
	TNoun		= &Noun;
	TVerb		= &Verb;
	TAdjective	= &Adjective;
	TAdverb		= &Adverb;

	//�_�~�[�̎��i�擪�ւ̃|�C���^�j��NULL�ɏ�����
	Noun.next		= NULL;
	Verb.next		= NULL;
	Adjective.next	= NULL;
	Adverb.next		= NULL;

	//�P��o�^�����O�ɏ�����
	NTotal			= 0;
	NNoun			= 0;
	NVerb			= 0;
	NAdjective		= 0;
	NAdverb			= 0;

	//�t���O��������
	isSorted		= FALSE;
	isRandom		= FALSE;

	ResetPointer();
}

//�f�[�^���R�s�[����֐�
int	DATABASE::Copy(WORD_DATA* a, const WORD_DATA* b)
{
	int	Length;

	if(b == NULL)
		return -1;

	//�P��
	Length	= strlen(b->word);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->word	= new char[Length + 1];

	if(!a->word)
	{
		cout << "�������m�ۂɎ��s���܂���\n";
		return -1;
	}
	strcpy(a->word, b->word);

	//���
	a->kind	= b->kind;

	//�Ӗ�
	Length	= strlen(b->mean);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->mean	= new char[Length + 1];

	if(!a->mean)
	{
		cout << "�������m�ۂɎ��s���܂���\n";
		return -1;
	}
	strcpy(a->mean, b->mean);

	//�ᕶ
	Length	= strlen(b->example);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->example	= new char[Length + 1];

	if(!a->example)
	{
		cout << "�������m�ۂɎ��s���܂���\n";
		return -1;
	}
	strcpy(a->example, b->example);

	//�ᕶ�̓��{���
	Length	= strlen(b->Japanese);
	if(Length == 0)
	{
		cout << "Error\n";
		return -1;
	}
	a->Japanese	= new char[Length + 1];

	if(!a->Japanese)
	{
		cout << "�������m�ۂɎ��s���܂���\n";
		return -1;
	}
	strcpy(a->Japanese, b->Japanese);

	return 0;
}

//�C���X�^���X�쐬�֐�
DATABASE* DATABASE::GetInstance()
{
	//�C���X�^���X���쐬
	static DATABASE		Instance;

	return &Instance;
}

//���X�g�̃\�[�g�֐��B�����_���\�[�g�ƒʏ�̃\�[�g���g�������\
void DATABASE::Sort(MODE mode, int kind)
{
	if(mode == NORMAL)
	{
		Noun.next		= merge_sort_list(Noun.next, compare);
		Verb.next		= merge_sort_list(Verb.next, compare);
		Adjective.next	= merge_sort_list(Adjective.next, compare);
		Adverb.next		= merge_sort_list(Adverb.next, compare);

		//���[�N�|�C���^�����X�g�̐擪�ɃZ�b�g
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

			//���[�N�|�C���^�����X�g�̐擪�ɃZ�b�g
			ResetPointer();
			break;
		}

		isSorted	= FALSE;
		isRandom	= TRUE;
	}


	//�����̃|�C���^���X�V
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

//���X�g�ɒP���o�^����֐�
int DATABASE::Entry(const WORD_DATA* data)
{
	WORD_DATA*	data1;

	if(data == NULL)
	{
		cout << "�o�^����P�ꂪ����܂���\n";
		return -1;
	}

	//�P��f�[�^�o�^�p���������m��
	data1	= new WORD_DATA;

	//�������m�ۂɎ��s
	if(data1 == NULL)
	{
		cout << "�������m�ۂɎ��s���܂���\n";
		return -1;
	}

	if(Copy(data1, data))
		return -1;

	//���X�g�ɒǉ�
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
		cout << "\n\n�P��̎�ނ̎w�肪����܂���\n";
		return -1;
	}

	//�P��o�^�����X�V
	NTotal++;

	//�\�[�g����Ă��邩�ǂ����̃t���O�����Z�b�g
	isSorted	= FALSE;
	isRandom	= FALSE;

	return 0;
}

//�f�[�^���擾���郁�\�b�h
int	DATABASE::GetData(KIND kind, WORD_DATA* data)
{
	//���[�N�|�C���^���w�������f�[�^���R�s�[���A���[�N�|�C���^���X�V
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
		cout << "��ނ̎w�肪����܂���\n";
		return -1;
	}

	return 0;
}

//�P��o�^����\������֐�
void	DATABASE::display_number()
{
	cout << "���P�ꐔ�F" << NTotal << "\n�����o�^���F\t" << NNoun << "\n�����o�^���F\t" << NVerb << "\n�`�e���o�^���F\t" << NAdjective << "\n�����o�^���F\t" << NAdverb << endl;
}

//���X�g�̐���
WORD_DATA*	DATABASE::merge_sort_list(WORD_DATA* x, int (*cmp)(WORD_DATA* a, WORD_DATA* b))
{
	//���[�N�|�C���^
	WORD_DATA*	a;
	WORD_DATA*	b;
	WORD_DATA*	p;

	int		cnt	= 0;

	//���X�g�ɗv�f���Ȃ����A�ЂƂ����Ȃ��ꍇ�̓��^�[��
	if(x == NULL || x->next == NULL)
		return x;

	//���X�g���X�L��������|�C���^
	a	= x;
	b	= x->next;

	if(b != NULL)
		b	= b->next;

	//���X�g�̗v�f�����J�E���g
	while(b != NULL)
	{
		//a�̓|�C���^���ЂƂ��ǂ�
		a	= a->next;
		b	= b->next;

		//b�̓|�C���^�����ǂ�
		if(b != NULL)
			b	= b->next;
	}

	//���X�g�𒆉��ŕ��f
	p		= a->next;
	a->next	= NULL;

	return merge_list(merge_sort_list(x, cmp), merge_sort_list(p, cmp), cmp);
}

//���X�g�̃}�[�W�֐��i�ʏ�̃\�[�g�j
WORD_DATA*	DATABASE::merge_list(WORD_DATA* a, WORD_DATA* b, int (*cmp)(WORD_DATA* a, WORD_DATA* b))
{
	//�_�~�[
	WORD_DATA	head;
	WORD_DATA*	p;

	//�|�C���^p���_�~�[�̗v�f�������悤�ɂ���
	p	= &head;

	//���X�g�̈������ɂȂ�܂�
	while((a != NULL) && (b != NULL))
	{
		//���X�g�̐擪�v�f�̔�r
		if((*cmp)(a, b))
		{
			//a�̂ق�����������΁Aa�̗v�f�����o���A�����ɕt��
			p->next	= a;
			p		= a;
			a		= a->next;
		}

		else
		{
			//b�̂ق�����������΁Ab�̗v�f�����o���A�����ɕt��
			p->next	= b;
			p		= b;
			b		= b->next;
		}
	}

	//�c���Ă��郊�X�g�𖖔��ɕt��
	if(a == NULL)
		p->next	= b;

	else
		p->next	= a;

	return head.next;
}

//�������r�֐�
int	compare(WORD_DATA* a, WORD_DATA* b)
{
	int		i	= 0;

	//���������񂾂����烊�^�[��
	if(!strcmp(a->word, b->word))
		return 1;

	while(a->word[i] == b->word[i])
		i++;

	if(a->word[i] < a->word[i])
		return 1;

	return 0;
}

//�����_����0��1�𔭐�����֐�
int	rnd(WORD_DATA* a, WORD_DATA* b)
{
	return rand() % 2;
}





//�t�@�C�����o�̓N���X
DATA_IO::DATA_IO()
{
}

//�f�X�g���N�^
DATA_IO::~DATA_IO()
{
	if(ifs)
		ifs.close();
}


//�������֐�
int	DATA_IO::Init(char FileName[])
{
	//�t�@�C�����I�[�v��
	ifs.open(FileName);

	if(!ifs)
	{
		cout << "�t�@�C�����I�[�v���ł��܂���ł����B\n";
		return -1;
	}

	return 0;
}


//�t�@�C������̓ǂݍ��݊֐�
int	DATA_IO::ReadFromFile(WORD_DATA* DATA)
{
	int		Length;		//������̒�����ێ�

	if(!DATA)
		return -1;

	if(!ifs.getline(Buffer, sizeof Buffer))
		return 1;


	//�����̒������擾
	Length	= strlen(Buffer);

	//���͂��ꂽ���������̃��������m�ۂ��A�L�^
	DATA->word	= new char[Length + 1];

	if(DATA->word == NULL)
	{
		cout << "�������m�ۂɎ��s���܂����B\n";
		return -1;
	}

	//�f�[�^�����[�h
	strcpy(DATA->word, Buffer);

	//�P��̎�ނ𔻕�
	if(!ifs.getline(Buffer, sizeof Buffer))
		return -1;

	//�f�[�^�̎�ނ�o�^
	if(!strcmp(Buffer, "��"))
		DATA->kind	= NOUN;

	else if(!strcmp(Buffer, "��"))
		DATA->kind	= VERB;

	else if(!strcmp(Buffer, "�`"))
		DATA->kind	= ADJ;

	else if(!strcmp(Buffer, "��"))
		DATA->kind	= ADV;

	//�w�肪�Ȃ���Εs���̃t���O�𗧂Ă�
	else
		DATA->kind	= UNKNOWN;

	//�f�[�^���擾
	if(!ifs.getline(Buffer, sizeof Buffer))
		return -1;

	//�����̒������擾
	Length	= strlen(Buffer);

	//���͂��ꂽ���������̃��������m�ۂ��A�L�^
	DATA->mean	= new char[Length + 1];

	if(DATA->mean == NULL)
	{
		cout << "�������m�ۂɎ��s���܂����B\n";
		return -1;
	}

	//�f�[�^�����[�h
	strcpy(DATA->mean, Buffer);

	//�f�[�^���擾
	if(!ifs.getline(Buffer, sizeof Buffer))
		return -1;

	//�����̒������擾
	Length	= strlen(Buffer);

	if(Length != 0)
	{
		//���͂��ꂽ���������̃��������m�ۂ��A�L�^
		DATA->example	= new char[Length + 1];

		if(DATA->example == NULL)
		{
			cout << "�������m�ۂɎ��s���܂����B\n";
			return -1;
		}

		//�f�[�^�����[�h
		strcpy(DATA->example, Buffer);

		if(!ifs.getline(Buffer, sizeof Buffer))
			return -1;

		//�����̒������擾
		Length	= strlen(Buffer);

		//���͂��ꂽ���������̃��������m�ۂ��A�L�^
		DATA->Japanese	= new char[Length + 1];

		if(DATA->Japanese == NULL)
		{
			cout << "�������m�ۂɎ��s���܂����B\n";
			return -1;
		}

		//�f�[�^�����[�h
		strcpy(DATA->Japanese, Buffer);

		return 0;
	}

	return 0;
}


//���o��N���X�R���X�g���N�^
QUIZ::QUIZ()
{
	Number	= 0;
	point	= 0;
}


//���o��֐�
int QUIZ::Display(DATABASE* DataBase)
{
	int			answer;		//�I�������̉񓚔ԍ�
	char		MODE;		//�o��`��
	KIND		Kind;		//�o�肷��P��̕i��
	char		temp[256];	//�������ꎞ�I�ɋL��
	char		input[64];	//���[�U�[����̓����̓���
	int			Num;		//���[�U�[����̐��l����
	int			result;		//��r���ʂ̈ꎞ�L��
	int			n;			//�ꎞ�ϐ�
	WORD_DATA	data;		//�P��f�[�^���ꎞ�I�ɋL��
	int			EFlag;		//�G���[�̎�ނ𔻕�
	int			i;			//���[�v����ϐ�
	int			k;			//���[�v����ϐ�
	int			l;			//���[�v����ϐ�


	//�o�肷����̌`���𗐐��Ō���
	MODE	= rand() % 4 + 1;

	//�ǂ̕i������o�肷�邩������(��������O�̌���)
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


	//��ʂ�������
	system("cls");

	cout << "��" << Number + 1 << "��\n\n";

	//�o�肷��P����f�[�^�x�[�X����擾�i�������A���X�g���I�[�ɒB���邩�G���[���N�����烊�^�[���j
	if(EFlag = DataBase->GetData(Kind, &data))
		return EFlag;


	//�����p�^�[�����Ƃɏo��
	switch(MODE)
	{
	case 1:
		cout << "\n\t���̒P��̈Ӗ���I��������I�сA�L���œ�����B\n\n" << '\t' << data.word << endl;
		cout << endl;

		//�����̔ԍ��������_���Ō���
		answer	= (rand() % 4) + 1;

		//�������ꎞ�I�ɋL��
		strcpy(temp, data.mean);

		//�I�����S���̃��[�v
		for(i = 1; i < 5; i++)
		{
			//����ԍ��̑I�����\���i������\���j
			if(i == answer)
				cout << '\t' << i << "�F" << temp << endl;

			//�_�~�[�̕\��
			else
			{
				//�ꎞ�I�ɓǂݍ��񂾒P��f�[�^�̍폜
				data.ClearData();

				//�_�~�[�̓ǂݍ���
				if(EFlag = DataBase->GetData(Kind, &data))
					return EFlag;

				//�_�~�[��\��
				cout << '\t' << i << "�F" << data.mean << '\n';
			}
		}
		break;

	case 2:
		cout << "\n\t���̈Ӗ������p�P���I��������I�сA�L���œ�����B\n\n" << '\t' << data.mean << endl;
		cout << endl;

		//�����̔ԍ��������_���Ō���
		answer	= (rand() % 4) + 1;

		//�������ꎞ�I�ɋL��
		strcpy(temp, data.word);

		//�I�����S���̃��[�v
		for(i = 1; i < 5; i++)
		{
			//����ԍ��̑I�����\���i������\���j
			if(i == answer)
				cout << '\t' << i << "�F" << temp << endl;

			//�_�~�[�̕\��
			else
			{
				//�ꎞ�I�ɓǂݍ��񂾒P��f�[�^�̍폜
				data.ClearData();

				//�_�~�[�̓ǂݍ���
				if(EFlag = DataBase->GetData(Kind, &data))
					return EFlag;

				//�_�~�[��\��
				cout << '\t' << i << "�F" << data.word << '\n';
			}
		}
		break;

	case 3:
		cout << "\n\t���̈Ӗ������p�P��������B\n\n" << '\t' << data.mean << '\n';
		cout << '\n';

		strcpy(temp, data.word);
		break;

	case 4:
		cout << "\n\t���̗ᕶ��()�𖄂߂�B\n\n\t";
		
		k	= 0;
		while( (data.example[k] != '(') && (data.example[k] != '\0') )
		{
			putchar(data.example[k]);
			k++;
		}

		if(data.example[k] == '\0')
		{
			cout << "�ᕶ��()�̎w�肪����܂���B\n";
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
			cout << "�ᕶ��()�̎w�肪����܂���B\n";
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


	//���[�U�[����̓��͑҂�
	cout << "\n\n";
	cout << "Put your answer.\n\n";

	//���[�U�[����̓����̓���
	cin.getline(input, 64);

	//�I�������̎��̐��𔻒�
	if(MODE < 3)
	{
		//�����𐔒l�ɕϊ�
		Num		= atoi(input);

		//�������ԈႦ���̔���
		result	= (Num == answer);
	}

	//�p�P�ꏑ���������̎��̐��𔻒�
	else
	{
		//�������ԈႦ���̔���
		result	= (strcmp(input, temp) == 0);
	}


	//���������ꍇ
	if(result)
	{
		cout << "\n\t\t\t�����ł��B\n\n\t\t\t" << "Press any key.\n";
		point++;
	}

	//�Ԉ���Ă����ꍇ
	else
		cout << "\n\t\t\t�c�O�B�����́u" << temp << "�v�ł��B\n\n\t\t\t" << "Press any key.\n";

	getch();

	//�o�萔���X�V
	Number++;

	return 0;
}

//���ʕ\�����\�b�h
void QUIZ::Result()
{
	system("cls");

	cout << "�����l�ł����B\n\n\n";
	cout << "����̌��ʂ́A\n��萔�F" << Number << '\n';
	cout << "���𐔁F" << point << '\n';
	cout << "�������F" << ((float)point / Number) * 100 << "%�ł����B" << '\n';
}

void QUIZ::Reset()
{
	Number	= 0;
	point	= 0;
}
